/*
 * task_console.c
 *
 *  Created on: Oct 21, 2020
 *      Author: Joe Krachey
 */
#include <main.h>

QueueHandle_t Queue_Console;
TaskHandle_t Task_Console_Handle;

/******************************************************************************
* Task used to print out messages to the console
******************************************************************************/
void Task_Console(void *pvParameters)
{
    ACCELEROMETER_DIR_t dir;

    while(1)
    {
        /* ADD CODE
         * wait until we receive a message in Queue_Console
         */
        xQueueReceive(Queue_Console, &dir, portMAX_DELAY);


        /* ADD CODE
         * based on the message that was received, print out one of the following
         * message to the UART.
         *
         *  "Task_Console: Joystick position - CENTER\n\r"
         *  "Task_Console: Joystick position - LEFT\n\r"
         *  "Task_Console: Joystick position - RIGHT\n\r"
         *  "Task_Console: Joystick position - UP\n\r"
         *  "Task_Console: Joystick position - DOWN\n\r"
         *
         * NOTE, the UART is only accessed in this task, so
         * there is no need to use a semaphore for mutual exclusion of the UART.
         */
        if (dir == ACCELEROMETER_DIR_CENTER) {
            ece353_MKII_RGB_LED(false, false, false);
        }
        else if (dir == ACCELEROMETER_DIR_LEFT) {
            ece353_MKII_RGB_LED(true, false, false);
        }
        else if (dir == ACCELEROMETER_DIR_RIGHT) {
            ece353_MKII_RGB_LED(false, true, false);
        }
        else if (dir == ACCELEROMETER_DIR_UP) {
            ece353_MKII_RGB_LED(true, true, true);
        }
        else if (dir == ACCELEROMETER_DIR_DOWN) {
            ece353_MKII_RGB_LED(false, false, true);
        }
    }
}




