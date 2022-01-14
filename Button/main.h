/*
 * main.h
 *
 *  Created on: Dec 8, 2021
 *      Author: grant
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "msp.h"
#include "msp432p401r.h"
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

/* RTOS header files */
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>

/* Task Includes */
#include <hardware_init.h>
#include <task_led.h>
#include <task_button.h>

extern TaskHandle_t Task_LED_Handle;
extern TaskHandle_t Task_LED_Timer_Handle;
extern TaskHandle_t Task_LED_Bottom_Half_Handle;

#endif /* MAIN_H_ */
