/*
 * task_LCD.h
 *
 *  Created on: Dec 13, 2021
 *      Author: Grant Smith + Luke Kolder
 */

#ifndef TASK_LCD_H_
#define TASK_LCD_H_

#include "main.h"

extern QueueHandle_t Queue_LCD;
extern TaskHandle_t Task_LCD_Handle;
extern TaskHandle_t Task_LCD_Bottom_Half_Handle;

typedef enum {DARK_MODE, LIGHT_MODE} SCREEN_MODE;
typedef enum {PRESSED,PRESSED1,PRESSED2, NOTPRESSED} BUTTON_STATUS;
typedef enum {ACCELEROMETER_DIR_CENTER, ACCELEROMETER_DIR_LEFT, ACCELEROMETER_DIR_RIGHT, ACCELEROMETER_DIR_UP, ACCELEROMETER_DIR_DOWN} ACCELEROMETER_DIR_t;

/******************************************************************************
 * Data structures being added to the queue.
 *****************************************************************************/
typedef struct {
    BUTTON_STATUS s1;
    SCREEN_MODE screen_mode;
    ACCELEROMETER_DIR_t dir;
}LCD_MSG_t;

/******************************************************************************
 * Read in data from the queue and affect the LCD accordingly.
 *****************************************************************************/
void Task_LCD(void *pvParameters);

#endif /* TASK_LCD_H_ */
