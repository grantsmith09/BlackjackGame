/*
 *
 *
 *  Created on: Oct 19, 2020
 *      Author: Joe Krachey
 */

#include <main.h>

TaskHandle_t TaskHandle_MKII_RGB;

/******************************************************************************
* Controls the RGB LED on the MKII
******************************************************************************/
void Task_MKII_RGB(void *pvParameters)
{
    uint8_t led_count = 0;

    // Set the RED LED On.
    ece353_staff_MKII_RGB_LED(true, false, false);

    while(1)
    {

        /****************************************************
         * Wait indefinitely for the Sem_RGB_MKII semaphore
         *
         * This semaphore acts as a synchronization between
         * this task and task that is monitoring S1.  When
         * the S1 task gives the semaphore, this task will
         * be moved from the blocked state into the ready
         * state.
         *
         * ADD CODE
         ***************************************************/
        xSemaphoreTake(Sem_MKII_RGB, portMAX_DELAY);

        /****************************************************
         * Take the semaphore that provides access to the
         * UART
         *
         * ADD CODE
         ***************************************************/
        xSemaphoreTake(Sem_UART, portMAX_DELAY);

        /****************************************************
         * The led_count will be used to determine which
         * led to turn on.
         *
         * led_count == 0 --> Red   ON
         * led_count == 1 --> Green ON
         * led_count == 2 --> Blue  ON
         ***************************************************/
        led_count = (led_count + 1) % 3;

        switch(led_count)
        {
            case 0:
                {
                    printf("Task_RGB_MKII:  RED On\n\r");
                    ece353_staff_MKII_RGB_LED(true, false, false);
                    break;
                }
            case 1:
                {
                    printf("Task_RGB_MKII:  GREEN On\n\r");
                    ece353_staff_MKII_RGB_LED(false, true, false);
                    break;
                }
            case 2:
                {
                    printf("Task_RGB_MKII:  BLUE On\n\r");
                    ece353_staff_MKII_RGB_LED(false, false, true);
                    break;
                }
            default:
            {
                break;
            }
        }

        /****************************************************
         * You are done with the UART, so release the
         * semaphore.
         *
         * ADD CODE
         ***************************************************/
        xSemaphoreGive(Sem_UART);

    }

}



