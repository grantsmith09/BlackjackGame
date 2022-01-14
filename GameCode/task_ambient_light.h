/*
 * task_ambient_light.h
 *
 *  Created on: Dec 9, 2021
 *      Author: Grant Smith + Luke Kolder
 */

#ifndef TASK_AMBIENT_LIGHT_H_
#define TASK_AMBIENT_LIGHT_H_

#include "main.h"

#define I2C_LIGHT_ADDR   0x44

#define I2C_LIGHT_RESULT         0x00
#define I2C_LIGHT_CONFIG         0x01
#define I2C_LIGHT_LOW_LIM        0x02
#define I2C_LIGHT_HIGH_LIM       0x03
#define I2C_LIGHT_MAN_ID         0x7E
#define I2C_LIGHT_DEV_ID         0x7F

/* CONFIGURATION REGISTER SETTINGS */
#define OPT3001_RST            0xC810
#define OPT3001_CONT_MODE      0x0600 // Continuous conversions
#define OPT3001_CONV_TIME      0x0800 // Convert data every 800 ms
#define OPT3001_CONV_RDY       0x0080 // When 1 conversion ready

extern TaskHandle_t Task_Ambient_Light_Timer_Handle;
extern TaskHandle_t Task_Ambient_Light_Bottom_Half_Handle;

/******************************************************************************
 * Examines the data from the Ambient Light Sensor on the MKII
 ******************************************************************************/
float OPT3001_read_light(void);

/******************************************************************************
 * Used to start a Timer 32 Interrupt
 ******************************************************************************/
void Task_Ambient_Light_Timer(void *pvParameters);

/******************************************************************************
 * Bottom Half Task. Sends data to Queue_LCD
 ******************************************************************************/
void Task_Ambient_Light_Bottom_Half(void *pvParameters);

/******************************************************************************
 * Used to start a Timer 32 Interrupt
 ******************************************************************************/
void T32_INT2_IRQHandler(void);

#endif /* TASK_AMBIENT_LIGHT_H_ */
