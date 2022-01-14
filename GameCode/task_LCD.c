/*
 * task_LCD.c
 *
 *  Created on: Dec 13, 2021
 *      Author: Grant Smith + Luke Kolder
 */

#include "task_LCD.h"

QueueHandle_t Queue_LCD;
TaskHandle_t Task_LCD_Handle;
uint8_t dontChangeCol;

/******************************************************************************
 * Read in data from the queue and affect the LCD accordingly.
 *****************************************************************************/
void Task_LCD(void *pvParameters)
{
    LCD_MSG_t msg;
    dontChangeCol = 0;

    while (1)
    {
        /*
         * wait until we receive a message in Queue_LCD
         */
        xQueueReceive(Queue_LCD, &msg, portMAX_DELAY);

        if ((msg.s1 == PRESSED) && (handDone == 1))
        {
            dontChangeCol = 1;
            s1Function(1);
        }
        else if ((msg.s1 == PRESSED1) && (handDone == 1))
        {
            dontChangeCol = 0;
            s1Function(2);
        }
        else if ((msg.screen_mode) == DARK_MODE && (dontChangeCol == 1))
        {
            changeColors(1);
        }
        else if ((msg.screen_mode == LIGHT_MODE) && (dontChangeCol == 1))
        {
            changeColors(0);
        }
        else if ((msg.s1 == PRESSED2) && (handDone == 1))
        {
            dontChangeCol = 0;
            s1Function(3);
        }

        else if ((msg.dir == ACCELEROMETER_DIR_DOWN) && (handDone == 0))
        {
            accelerometerFunction(0);

        }
        else if ((msg.dir == ACCELEROMETER_DIR_LEFT) && (handDone == 0))
        {
            accelerometerFunction(1);

        }
        else if ((msg.dir == ACCELEROMETER_DIR_RIGHT) && (handDone == 0))
        {
            accelerometerFunction(2);
        }
        if (game_result != 0)
        {
            if (game_result == 1)
            {
                vTaskDelay(pdMS_TO_TICKS(3000));
                gameResults(1);
                dontChangeCol = 1;
            }
            else if (game_result == 2)
            {
                vTaskDelay(pdMS_TO_TICKS(3000));
                gameResults(0);
                dontChangeCol = 1;
            }
        }
    }
}

