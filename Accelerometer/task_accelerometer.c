/*
 * task_accelerometer.c
 *
 *  Created on: Dec 8, 2021
 *      Author: grant
 */

#include <main.h>


TaskHandle_t Task_Accelerometer_Timer_Handle;
TaskHandle_t Task_Accelerometer_Bottom_Half_Handle;

volatile uint32_t ACCELEROMETER_X_DIR = 0;
volatile uint32_t ACCELEROMETER_Y_DIR = 0;


/******************************************************************************
* Used to start an ADC14 Conversion
******************************************************************************/
void Task_Accelerometer_Timer(void *pvParameters)
{

    while(1)
    {
        /*
         * Start the ADC conversion
        */
        ADC14->CTL0 |= ADC14_CTL0_SC | ADC14_CTL0_ENC;

        /*
         * Delay 50mS
        */
        vTaskDelay(pdMS_TO_TICKS(50));

    }
}


/******************************************************************************
* Bottom Half Task.  Examines the ADC data from the accelerometer on the MKII
******************************************************************************/
void Task_Accelerometer_Bottom_Half(void *pvParameters)
{

    ACCELEROMETER_DIR_t dir;
    uint32_t ulEventsToProcess;

    while(1)
    {
        /*
         * Wait until we get a task notification from the ADC14 ISR
        */
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);


        /*
         * Set the dir variable to one of the following values based
         * on the values of ACCELEROMETER_X_DIR and ACCELEROMETER_Y_DIR
        */
        if(ACCELEROMETER_X_DIR < VOLT_1P25)
        {
            dir = ACCELEROMETER_DIR_LEFT;
        }
        else if(ACCELEROMETER_X_DIR > VOLT_2P05)
        {
            dir = ACCELEROMETER_DIR_RIGHT;
        }
        else if(ACCELEROMETER_Y_DIR < VOLT_1P25)
        {
            dir = ACCELEROMETER_DIR_UP;
        }
        else if(ACCELEROMETER_Y_DIR > VOLT_2P05)
        {
             dir = ACCELEROMETER_DIR_DOWN;
        }
        else
        {
             dir = ACCELEROMETER_DIR_CENTER;
        }

        /*
         * Send dir to Queue_LCD if the the current direction
         * of the accelerometer does not match the previous direction of the accelerometer
        */
        xQueueSendToBack(Queue_Console, &dir, portMAX_DELAY);



    }
}


/******************************************************************************
* Top Half of ADC14 Handler.
******************************************************************************/
void ADC14_IRQHandler(void)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    ACCELEROMETER_X_DIR = ADC14->MEM[0]; // Read the value and clear the interrupt
    ACCELEROMETER_Y_DIR = ADC14->MEM[1]; // Read the value and clear the interrupt

    /*
     * Send a task notification to Task_Accelerometer_Bottom_Half
    */
    vTaskNotifyGiveFromISR(Task_Accelerometer_Bottom_Half_Handle, &xHigherPriorityTaskWoken);

    portYIELD_FROM_ISR( xHigherPriorityTaskWoken );

}









