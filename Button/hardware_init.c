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
        buzzer_init(2000);

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


/*****************************************************
 * Configures Timer32_1 to generate a periodic interrupt
 *
 * Parameters
 *      ticks  - Number of milliseconds per interrupt
 * Returns
 *      None
 *****************************************************/
void ece353_T32_1_Interrupt_Ms(uint16_t ms) {

    // ticks = desired period / core clock period
    // 20e-3/(1/3e6) = (3e6 * 20)/1000
    uint32_t ticks = ((SystemCoreClock * ms)/1000) - 1;

    // stop the timer
    TIMER32_1->CONTROL = 0;

    // Set the load register
    TIMER32_1->LOAD = ticks;

    // Enable the Timer32 interrupt in NVIC
    NVIC_EnableIRQ(T32_INT1_IRQn);
    NVIC_SetPriority(T32_INT1_IRQn, 2);

    // Start Timer32 and enable interrupt
    TIMER32_1->CONTROL =    TIMER32_CONTROL_ENABLE |    // turn timer on
                            TIMER32_CONTROL_MODE |      // periodic mode
                            TIMER32_CONTROL_SIZE |      // 32 bit timer
                            TIMER32_CONTROL_IE;         // enable interrupts

}

/******************************************************************************
* Initialize the buzzer
******************************************************************************/
void buzzer_init(uint16_t ticks_period)
{

    // Set P2.7 to be a GPIO OUTPUT Pin
    P2->DIR |= BIT7;

    // the TIMERA PWM controller will control the buzzer
    // on the MKII P2.7 <--> TA0.4
    P2->SEL0 |= BIT7;
    P2->SEL1 &= ~BIT7;

    // Turn off TA0
    TIMER_A0->CTL = 0;

    // Set the period of the timer.
    TIMER_A0->CCR[0] = ticks_period - 1;

    // Configure BUZZER Duty Cycle to 50%
    TIMER_A0->CCR[4] = (ticks_period / 2) - 1;

    // Configure TA0.4 for RESET/SET Mode
    TIMER_A0->CCTL[4] = TIMER_A_CCTLN_OUTMOD_7;

    // Select the master clock as the timer source
    TIMER_A0->CTL = TIMER_A_CTL_SSEL__SMCLK;
}

/******************************************************************************
* Turn buzzer on
******************************************************************************/
void buzzer_on(void)
{
    // Clear the current mode control bits
    TIMER_A0->CTL &= TIMER_A_CTL_MC_MASK;

    // Set mode control to up and clear the current count
    TIMER_A0->CTL |= TIMER_A_CTL_MC__UP | TIMER_A_CTL_CLR;

}

/******************************************************************************
* Turn buzzer off
******************************************************************************/
void buzzer_off(void)
{
    // Turn off timer
    TIMER_A0->CTL &= ~TIMER_A_CTL_MC_MASK;

}

















