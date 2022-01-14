/*
 * task_led.c
 *
 *  Created on: Oct 21, 2020
 *      Author: Joe Krachey
 */
#include <main.h>

QueueHandle_t Queue_LED;
TaskHandle_t Task_LED_Handle;

/******************************************************************************
* Task used to print out messages to the console
******************************************************************************/
void Task_LED(void *pvParameters)
{
    BUTTON_STATUS s1;

    while(1)
    {
        /* ADD CODE
         * wait until we receive a message in Queue_Console
         */
        xQueueReceive(Queue_LED, &s1, portMAX_DELAY);


        if (s1 == PRESSED) {
            ece353_MKII_RGB_LED(true, false, false);
        }
        else if (s1 == PRESSED1)
        {
            ece353_MKII_RGB_LED(false, false, true);
        }
        else if (s1 == PRESSED2)
        {
            ece353_MKII_RGB_LED(false, true, true);
        }

    }
}




