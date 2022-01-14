/*
 * task_buzzer.c
 *
 *  Created on: Dec 12, 2021
 *      Author: grant
 */

#include <task_buzzer.h>

QueueHandle_t Queue_Buzzer;
TaskHandle_t Task_Buzzer_Handle;

/******************************************************************************
* Task used to print out messages to the console
******************************************************************************/
void Task_Buzzer(void *pvParameters)
{
    BUTTON_STATUS s1;

    while(1)
    {
        /* ADD CODE
         * wait until we receive a message in Queue_Console
         */
        xQueueReceive(Queue_Buzzer, &s1, portMAX_DELAY);

        if (s1 == PRESSED) {
            buzzer_init(6377);
            buzzer_on();
            vTaskDelay(pdMS_TO_TICKS(336));
            buzzer_off();

            buzzer_init(4778);
            buzzer_on();
            vTaskDelay(pdMS_TO_TICKS(336));
            buzzer_off();

            buzzer_init(3792);
            buzzer_on();
            vTaskDelay(pdMS_TO_TICKS(336));
            buzzer_off();

            buzzer_init(3188);
            buzzer_on();
            vTaskDelay(pdMS_TO_TICKS(504));
            buzzer_off();

            buzzer_init(3792);
            buzzer_on();
            vTaskDelay(pdMS_TO_TICKS(168));
            buzzer_off();

            buzzer_init(3188);
            buzzer_on();
            vTaskDelay(pdMS_TO_TICKS(672));
            buzzer_off();
        }
        else if (s1 == PRESSED1) {
            buzzer_init(30000);
            buzzer_on();
            vTaskDelay(pdMS_TO_TICKS(400));
            buzzer_off();

            buzzer_init(50000);
            buzzer_on();
            vTaskDelay(pdMS_TO_TICKS(800));
            buzzer_off();
        }

    }
}


