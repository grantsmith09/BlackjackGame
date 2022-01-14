/*
 * hardware_init.h
 *
 *  Created on: Dec 8, 2021
 *      Author: Grant Smith + Luke Kolder
 */

#ifndef HARDWARE_INIT_H_
#define HARDWARE_INIT_H_

#include "main.h"

/*****************************************************
 * Initializes all hardware needed
 *****************************************************/
void hardware_init(bool init);

/*****************************************************
 * Initializes MKII.S1
 *****************************************************/
void ece353_MKII_S1_Init(void);

/*****************************************************
 * Returns if MKII.S1 is currently pressed.
 *
 * Parameters
 *
 * Returns
 *      true    :   Button1 is pressed
 *      false   :   Button1 is NOT pressed
 *****************************************************/
bool ece353_MKII_S1(void);

/*****************************************************
 * Initializes MKII.S2
 *****************************************************/
void ece353_MKII_S2_Init(void);

/*****************************************************
 * Returns if MKII.S2 is currently pressed.
 *
 * Parameters
 *
 * Returns
 *      true    :   Button1 is pressed
 *      false   :   Button1 is NOT pressed
 *****************************************************/
bool ece353_MKII_S2(void);

/*****************************************************
 * Initialize the 3 GPIO pins that control the RGB
 * LED on the MKII.
 *
 * Parameters
 *      None
 * Returns
 *      None
 *****************************************************/
void ece353_MKII_RGB_IO_Init(void);

/*****************************************************
 * Turn RGB on the MKII LED ON/Off.
 *
 * Parameters
 *  red:    if true,  turn RED LED on
 *          if false, turn RED LED off
 *  green:  if true,  turn GREEN LED on
 *          if false, turn GREEN LED off
 *  blue:   if true,  turn BLUE LED on
 *          if false, turn BLUE LED off
 *****************************************************/
void ece353_MKII_RGB_LED(bool red, bool green, bool blue);

/******************************************************************************
 * Initialize the accelerometer
 ******************************************************************************/
void Accelerometer_init(void);

/******************************************************************************
 * Initialize the I2C conversion
 ******************************************************************************/
void ambient_light_init(void);

/*****************************************************
 * Configures Timer32_1 to generate a periodic interrupt
 *
 * Parameters
 *      ticks  - Number of milliseconds per interrupt
 * Returns
 *      None
 *****************************************************/
void ece353_T32_1_Interrupt_Ms(uint16_t ms);

/*****************************************************
 * Configures Timer32_2 to generate a periodic interrupt
 *
 * Parameters
 *      ticks  - Number of milliseconds per interrupt
 * Returns
 *      None
 *****************************************************/
void ece353_T32_2_Interrupt_Ms(uint16_t ms);

/******************************************************************************
 * Initialize the buzzer
 ******************************************************************************/
void buzzer_init(uint16_t ticks_period);

/******************************************************************************
 * Turn buzzer on
 ******************************************************************************/
void buzzer_on(void);

/******************************************************************************
 * Turn buzzer off
 ******************************************************************************/
void buzzer_off(void);

/******************************************************************************
 * Initialize the LCD
 ******************************************************************************/
void LCD_init(void);

#endif /* HARDWARE_INIT_H_ */
