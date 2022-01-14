/*
 * main.h
 *
 *  Created on: Dec 8, 2021
 *      Author: Grant Smith + Luke Kolder
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
#include "task_accelerometer.h"
#include "task_ambient_light.h"
#include "task_button.h"
#include "task_LCD.h"

/* Helper Function Files */
#include "hardware_init.h"
#include "deck.h"
#include "screen.h"
#include "blackjackFunctions.h"
#include "lcd.h"
#include "i2c.h"


#endif /* MAIN_H_ */
