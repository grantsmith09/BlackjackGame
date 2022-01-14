/*
 * task_accelerometer.h
 *
 *  Created on: Dec 8, 2021
 *      Author: grant
 */

#ifndef TASK_ACCELEROMETER_H_
#define TASK_ACCELEROMETER_H_


#include "main.h"

#define VOLT_1P25  6206    // 1.25 /(3.3/16384)
#define VOLT_2P05 10178      // 2.05 /(3.3/16384)

extern TaskHandle_t Task_Accelerometer_Timer_Handle;
extern TaskHandle_t Task_Accelerometer_Bottom_Half_Handle;

typedef enum {
    ACCELEROMETER_DIR_CENTER,
    ACCELEROMETER_DIR_LEFT,
    ACCELEROMETER_DIR_RIGHT,
    ACCELEROMETER_DIR_UP,
    ACCELEROMETER_DIR_DOWN,
} ACCELEROMETER_DIR_t;



/******************************************************************************
* Used to start an ADC14 Conversion
******************************************************************************/
void Task_Accelerometer_Timer(void *pvParameters);


/******************************************************************************
* Examines the ADC data from the joystick on the MKII
******************************************************************************/
void Task_Accelerometer_Bottom_Half(void *pvParameters);


#endif /* TASK_ACCELEROMETER_H_ */
