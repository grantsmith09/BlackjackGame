/*
 * task_buzzer.h
 *
 *  Created on: Dec 12, 2021
 *      Author: grant
 */

#ifndef TASK_BUZZER_H_
#define TASK_BUZZER_H_

#include <main.h>

extern QueueHandle_t Queue_Buzzer;
extern TaskHandle_t Task_Buzzer_Handle;

void Task_Buzzer(void *pvParameters);



#endif /* TASK_BUZZER_H_ */
