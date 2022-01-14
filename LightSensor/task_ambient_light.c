/*
 * task_ambient_light.c
 *
 *  Created on: Dec 9, 2021
 *      Author: grant
 */


#include <main.h>


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
* Used to start an I2C Conversion
******************************************************************************/
void Task_Ambient_Light_Timer(void *pvParameters)
{

    while(1)
    {

        ece353_T32_1_Interrupt_Ms(25);

        /*
         * Delay 50mS
        */
        vTaskDelay(pdMS_TO_TICKS(50));

    }
}
/******************************************************************************
* Bottom Half Task. Sends data to Queue_LCD
******************************************************************************/
void Task_Ambient_Light_Bottom_Half(void *pvParameters)
{

    SCREEN_MODE screen_mode;
    uint32_t ulEventsToProcess;

    while (1) {

           /* Wait until we receive a task notification from T32_INT2_IRQHandler */
           ulTaskNotifyTake(pdTRUE, portMAX_DELAY);


           /*
            * Set the dir variable to one of the following values based
            * on the values of ACCELEROMETER_X_DIR and ACCELEROMETER_Y_DIR
           */
           if(lux < 50)
           {
              screen_mode = DARK_MODE;
           }
           else
           {
              screen_mode = LIGHT_MODE;
           }

           /*
            * Send dir to Queue_LCD if the the current direction
            * of the accelerometer does not match the previous direction of the accelerometer
           */
          xQueueSendToBack(Queue_Console, &screen_mode, portMAX_DELAY);

    }

}


/******************************************************************************
* Top Half of T32 Handler.
******************************************************************************/
void T32_INT1_IRQHandler(void)
{

    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    lux = OPT3001_read_light();

    /*
     * Send a task notification to Task_Ambient_Light_Bottom_Half
    */
    vTaskNotifyGiveFromISR(Task_Ambient_Light_Bottom_Half_Handle, &xHigherPriorityTaskWoken);

    portYIELD_FROM_ISR( xHigherPriorityTaskWoken );

    TIMER32_1->INTCLR = BIT0;

}




