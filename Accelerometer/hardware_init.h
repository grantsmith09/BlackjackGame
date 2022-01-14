/*
 * hardware_init.h
 *
 *  Created on: Dec 8, 2021
 *      Author: grant
 */

#ifndef HARDWARE_INIT_H_
#define HARDWARE_INIT_H_

#include <main.h>

void hardware_init(bool init);
void ece353_MKII_S1_Init(void);
bool ece353_MKII_S1(void);
void ece353_MKII_S2_Init(void);
bool ece353_MKII_S2(void);
void ece353_MKII_RGB_IO_Init(void);
void ece353_MKII_RGB_LED(bool red, bool green, bool blue);
void Accelerometer_init(void);

#endif /* HARDWARE_INIT_H_ */
