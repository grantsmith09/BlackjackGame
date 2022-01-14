/*
 * task_console.h
 *
 *  Created on: Oct 21, 2020
 *      Author: Joe Krachey
 */

#ifndef TASK_LED_H_
#define TASK_LED_H_

#include <main.h>

extern QueueHandle_t Queue_LED;
extern TaskHandle_t Task_LED_Handle;



/******************************************************************************
* Task used to print out messages to the console
******************************************************************************/
void Task_LED(void *pvParameters);



#endif /* TASK_LED_H_ */
