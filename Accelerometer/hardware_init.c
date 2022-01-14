/*
 * hardware_init.c
 *
 *  Created on: Dec 8, 2021
 *      Author: grant
 */

#include "hardware_init.h"


void hardware_init(bool init)
{
    if (init)
    {
        ece353_MKII_S1_Init();
        ece353_MKII_S2_Init();
        ece353_MKII_RGB_IO_Init();
        Accelerometer_init();

    }
}


/*****************************************************
 * Initializes MKII.S1
 *****************************************************/
void ece353_MKII_S1_Init(void)
{

    // Configure P5.1 as an input
    P5->DIR &= ~BIT1;

}


/*****************************************************
 * Returns if MKII.S1 is currently pressed.
 *
 * Parameters
 *
 * Returns
 *      true    :   Button1 is pressed
 *      false   :   Button1 is NOT pressed
 *****************************************************/
bool ece353_MKII_S1(void)
{
    if((P5->IN & BIT1) == 0){
        return true;
    }
    else{
        return false;
    }
}

/*****************************************************
 * Initializes MKII.S2
 *****************************************************/
void ece353_MKII_S2_Init(void)
{
    // Configure P3.5 as an input
    P3->DIR &= ~BIT5;

}

/*****************************************************
 * Returns if MKII.S2 is currently pressed.
 *
 * Parameters
 *
 * Returns
 *      true    :   Button1 is pressed
 *      false   :   Button1 is NOT pressed
 *****************************************************/
bool ece353_MKII_S2(void)
{
    if((P3->IN & BIT5) == 0){
        return true;
    }
    else{
        return false;
    }
}

/*****************************************************
 * Initialize the 3 GPIO pins that control the RGB
 * LED on the MKII.
 *
 * Parameters
 *      None
 * Returns
 *      None
 *****************************************************/
void ece353_MKII_RGB_IO_Init(void)
{

    // Complete the comments below to identify which pins
    // control which LEDs.
    //
    // Replace a and c with the correct port number
    // Replace b and d with the correct pin numbers.
    // RED      : P2.6
    // GREEN    : Pa.b
    // BLUE     : Pc.d

    // ADD CODE that configures the RED, GREEN, and
    // BLUE LEDs to be outputs
    P2->DIR |= BIT6;

    P2->DIR |= BIT4;

    P5->DIR |= BIT6;

}

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
void ece353_MKII_RGB_LED(bool red, bool green, bool blue)
{

    if (red) {

            // turn red LED on
            P2->OUT |= BIT6;

        } else {

            // turn red LED off
            P2->OUT &= ~BIT6;

        }

        if (green) {

            // turn green LED on
            P2->OUT |= BIT4;

        } else {

            // turn green LED off
            P2->OUT &= ~BIT4;

        }

        if (blue) {

            // turn blue LED on
            P5->OUT |= BIT6;

        } else {

            // turn blue LED off
            P5->OUT &= ~BIT6;

        }

}


/******************************************************************************
* Initialize the accelerometer
******************************************************************************/
void Accelerometer_init(void)
{
    // Configure the X direction as an analog input pin.
    P6->SEL0 |= BIT1;
    P6->SEL1 |= BIT1;
    // Configure the Y direction as an analog input pin.
    P4->SEL0 |= BIT0;
    P4->SEL1 |= BIT0;
    // Configure CTL0 to sample 16-times in pulsed sample mode.
    ADC14->CTL0 = ADC14_CTL0_SHP | ADC14_CTL0_SHT0_2 | ADC14_CTL0_CONSEQ_1;;
    // Configure ADC to return 14-bit values
    ADC14->CTL1 = ADC14_CTL1_RES_3;
    // Associate the X direction analog signal with MEM[0]
    ADC14->MCTL[0] |= ADC14_MCTLN_INCH_14;
    // Associate the Y direction analog signal with MEM[1]
    ADC14->MCTL[1] |= ADC14_MCTLN_INCH_13;
    // NEW -- Make sure to indicate this is the end of a sequence.
    ADC14->MCTL[1] |= ADC14_MCTLN_EOS;
    // Enable interrupts in the ADC AFTER a value is written into MEM[1].
    ADC14->IER0 = ADC14_IER0_IE1;
    // Enable ADC Interrupt in the NVIC
    NVIC_EnableIRQ(ADC14_IRQn);
    NVIC_SetPriority(ADC14_IRQn, 2);
    // Turn ADC ON
    ADC14->CTL0 |= ADC14_CTL0_ON;
}




















