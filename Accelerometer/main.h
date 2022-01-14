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

/* RTOS header files */
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>

/* Task Includes */
#include <task_accelerometer.h>
#include <hardware_init.h>
#include <task_console.h>

extern TaskHandle_t Task_Console_Handle;
extern TaskHandle_t Task_Accelerometer_Timer_Handle;
extern TaskHandle_t Task_Accelerometer_Bottom_Half_Handle;

#endif /* MAIN_H_ */
