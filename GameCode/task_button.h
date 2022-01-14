/*
 * task_button.h
 *
 *  Created on: Dec 12, 2021
 *      Author: Grant Smith + Luke Kolder
 */

#ifndef TASK_BUTTON_H_
#define TASK_BUTTON_H_

#include "main.h"

extern TaskHandle_t Task_Button_Timer_Handle;
extern TaskHandle_t Task_Button_Bottom_Half_Handle;

/******************************************************************************
 * De-bounce switch S1.
 *****************************************************************************/
bool debounce_s1(void);

/******************************************************************************
 * Used to start a Timer 32 Interrupt
 ******************************************************************************/
void Task_Button_Timer(void *pvParameters);

/******************************************************************************
 * Everytime the button s1 is pressed, the LCD should react accordingly
 *****************************************************************************/
void Task_Button_Bottom_Half(void *pvParameters);

/******************************************************************************
 * Top Half of T32 Handler.
 ******************************************************************************/
void T32_INT1_IRQHandler(void);

#endif /* TASK_BUTTON_H_ */
