/*
 * blackjackFunctions.h
 *
 *  Created on: Dec 12, 2021
 *      Author: Luke Kolder + Grant Smith
 */

#ifndef BLACKJACKFUNCTIONS_H_
#define BLACKJACKFUNCTIONS_H_

#include "main.h"

/******************************************************************************
 * Displays the welcome screen to the user. To be called in LCD Task
 *
 * Parameters
 *      None
 * Returns
 *      None
 ******************************************************************************/
void resetScreen(void);

/******************************************************************************
 * Displays the given screen based on how many times the s1 has been pressed.
 * To be called in the task monitoring s1
 * 1 press - instructions
 * 2 press - pre deal screen
 * >= 3 press - deal cards
 *
 * Parameters
 *      None
 * Returns
 *      None
 ******************************************************************************/
void s1Function(uint8_t s1PressCount);

/******************************************************************************
 * Performs the corresponding task based on the input given to the accelerometer.
 * Forward is Double down(player draw card, give control to dealer)
 * Left is Hit(player draw card, retain control)
 * Right is Stand(give control to dealer
 *
 * Parameters
 *
 * Returns
 *      None
 ******************************************************************************/
void accelerometerFunction(uint8_t dir);

/******************************************************************************
 * Immitates the actions of a dealer once the player has given up control
 * of the board. Dealer draws on 16.
 *
 * Parameters
 *      None
 * Returns
 *      None
 ******************************************************************************/
void dealerFunc(void);

void Buzzer_Win(void);
void Buzzer_Lose(void);

#endif /* BLACKJACKFUNCTIONS_H_ */

