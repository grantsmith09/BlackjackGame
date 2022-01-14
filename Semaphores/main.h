/*
 * main.h
 *
 *  Created on: Oct 19, 2020
 *      Author: Joe Krachey
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "msp.h"
#include "msp432p401r.h"
#include <stdint.h>
#include <stdio.h>

/* RTOS header files */
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <task_mkII_rgb.h>
#include <task_mkII_s1.h>
#include <task_mkII_s2.h>
#include <task_launchpad_rgb.h>
#include "ece353_staff.h"


extern SemaphoreHandle_t Sem_UART;

extern SemaphoreHandle_t Sem_MKII_RGB;
extern SemaphoreHandle_t Sem_LAUNCHPAD_RGB;

extern TaskHandle_t TaskHandle_MKII_S1;
extern TaskHandle_t TaskHandle_MKII_S2;
extern TaskHandle_t TaskHandle_MKII_RGB;
extern TaskHandle_t TaskHandle_LAUNCHPAD_RGB;

#endif /* MAIN_H_ */
