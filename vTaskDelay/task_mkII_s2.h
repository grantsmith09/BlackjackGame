/*
 * task_mkII_s2.h
 *
 *  Created on: Oct 14, 2020
 *      Author: Joe Krachey
 */

#ifndef TASK_MKII_S2_H_
#define TASK_MKII_S2_H_
#include "msp.h"
#include <stdint.h>
#include <stdio.h>

/* RTOS header files */
#include <FreeRTOS.h>
#include <task.h>

extern TaskHandle_t task_mkII_s2_Handle;

void task_mkII_s2(void *pvParameters);

#endif /* TASK_MKII_S2_H_ */
