/*
 * task_button.h
 *
 *  Created on: Dec 12, 2021
 *      Author: grant
 */

#ifndef TASK_BUTTON_H_
#define TASK_BUTTON_H_


#include "main.h"

extern TaskHandle_t Task_Button_Timer_Handle;
extern TaskHandle_t Task_Button_Bottom_Half_Handle;

typedef enum {
    PRESSED,
    PRESSED1,
    PRESSED2,
} BUTTON_STATUS;

bool debounce_s1(void);
void Task_Button_Timer(void *pvParameters);
void Task_Button_Bottom_Half(void *pvParameters);
void T32_INT1_IRQHandler(void);

#endif /* TASK_BUTTON_H_ */
