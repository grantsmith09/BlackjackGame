/*
 * task_led.c
 *
 *  Created on: Oct 19, 2020
 *      Author: Joe Krachey
 */

#include <main.h>

 QueueHandle_t Queue_LED;

/******************************************************************************
* Controls the RGB LED on the MSP432 Launchpad
******************************************************************************/
static void update_rgb_led(LED_COLOR color)
{
    switch(color)
    {
        case LED_RED:
            {
                ece353_staff_RGB_LED(true, false, false);
                break;
            }
        case LED_GREEN:
            {
                ece353_staff_RGB_LED(false, true, false);
                break;
            }
        case LED_BLUE:
            {
                ece353_staff_RGB_LED(false, false, true);
                break;
            }
        default:
        {
            break;
        }
    }

}

/******************************************************************************
* Controls the RGB LED on the MKII
******************************************************************************/
static void update_mkII_rgb_led(LED_COLOR color)
{
    switch(color)
    {
        case LED_RED:
            {
                ece353_staff_MKII_RGB_LED(true, false, false);
                break;
            }
        case LED_GREEN:
            {
                ece353_staff_MKII_RGB_LED(false, true, false);
                break;
            }
        case LED_BLUE:
            {
                ece353_staff_MKII_RGB_LED(false, false, true);
                break;
            }
        default:
        {
            break;
        }
    }

}

/******************************************************************************
* Controls the RGB LED on the MSP432 Launchpad
******************************************************************************/
void Task_LED(void *pvParameters)
{
    BaseType_t status;
    LED_MSG_t msg;

    while(1)
    {
        /* ADD CODE
         * Wait until we receive a message from the Queue_LED
         */
        status = xQueueReceive(Queue_LED, &msg, portMAX_DELAY);

        /* ADD CODE
        * take Sem_UART semaphore
        */
        xSemaphoreTake(Sem_UART, portMAX_DELAY);

        printf("Task_LED updating LED\n\r");

        /* ADD CODE
         * give Sem_UART semaphore
         */
        xSemaphoreGive(Sem_UART);

        /* ADD CODE
         * Turn on the specified LED based on the message
         * received from Queue_LED.
         *
         * The color of the LED is also specified
         * in the message received from Queue_LED.
         *
         * There are two helper functions provided above to
         * make this process easier.
         */

        if (msg.color == 1 && msg.led_location == MKIIEDU){
            update_mkII_rgb_led(LED_RED);
            printf("S1 has been pressed and MKII LED set to RED\n\r");
        }
        else if (msg.color == 1 && msg.led_location == MSP432){
            update_rgb_led(LED_RED);
            printf("S2 has been pressed and MSP432 Launchpad LED set to RED\n\r");
        }
        else if (msg.color == 2 && msg.led_location == MKIIEDU){
            update_mkII_rgb_led(LED_GREEN);
            printf("S1 has been pressed and MKII LED set to GREEN\n\r");
        }
        else if (msg.color == 2 && msg.led_location == MSP432){
            update_rgb_led(LED_GREEN);
            printf("S2 has been pressed and MSP432 Launchpad LED set to GREEN\n\r");
        }
        else if (msg.color == 0 && msg.led_location == MKIIEDU){
            update_mkII_rgb_led(LED_BLUE);
            printf("S1 has been pressed and MKII LED set to BLUE\n\r");
        }
        else if (msg.color == 0 && msg.led_location == MSP432){
            update_rgb_led(LED_BLUE);
            printf("S2 has been pressed and MSP432 Launchpad LED set to BLUE\n\r");
        }
    }

}



