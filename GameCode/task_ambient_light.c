/*
 * task_ambient_light.c
 *
 *  Created on: Dec 9, 2021
 *      Author: Grant Smith + Luke Kolder
 */

#include "task_ambient_light.h"

TaskHandle_t Task_Ambient_Light_Timer_Handle;
TaskHandle_t Task_Ambient_Light_Bottom_Half_Handle;

volatile uint16_t lux = 0;

/******************************************************************************
 * Examines the data from the Ambient Light Sensor on the MKII
 ******************************************************************************/
float OPT3001_read_light(void)
{
    uint16_t res;
    uint16_t light;
    uint16_t E;
    uint16_t R;

    // Read the ambient temperature
    res = i2c_read_16(I2C_LIGHT_ADDR, I2C_LIGHT_RESULT);

    // Convert result register to lux
    E = (res >> 12);
    R = (res << 4);
    R = (R >> 4);

    light = ((0.08) * (pow(2, E)) * R);
    return light;
}

/******************************************************************************
 * Used to start a Timer 32 Interrupt
 ******************************************************************************/
void Task_Ambient_Light_Timer(void *pvParameters)
{

    while (1)
    {

        ece353_T32_2_Interrupt_Ms(2);

        vTaskDelay(pdMS_TO_TICKS(50));

    }
}
/******************************************************************************
 * Bottom Half Task. Sends data to Queue_LCD
 ******************************************************************************/
void Task_Ambient_Light_Bottom_Half(void *pvParameters)
{

    LCD_MSG_t msg;
    LCD_MSG_t prev_msg;

    while (1)
    {

        /* Wait until we receive a task notification from T32_INT2_IRQHandler */
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        /*
         * Set the dir variable to one of the following values based
         * on the values of ACCELEROMETER_X_DIR and ACCELEROMETER_Y_DIR
         */
        if (lux < 50)
        {
            msg.screen_mode = DARK_MODE;
        }
        else
        {
            msg.screen_mode = LIGHT_MODE;
        }

        xQueueSendToBack(Queue_LCD, &msg, portMAX_DELAY);

        prev_msg.screen_mode = msg.screen_mode;
    }

}

/******************************************************************************
 * Top Half of T32 Handler.
 ******************************************************************************/
void T32_INT2_IRQHandler(void)
{

    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    lux = OPT3001_read_light();

    /*
     * Send a task notification to Task_Ambient_Light_Bottom_Half
     */
    vTaskNotifyGiveFromISR(Task_Ambient_Light_Bottom_Half_Handle,
                           &xHigherPriorityTaskWoken);

    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);

    TIMER32_2->INTCLR = BIT0;

}

