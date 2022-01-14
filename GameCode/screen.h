/*
 * screen.h
 *
 *  Created on: Dec 8, 2021
 *      Author: Luke Kolder + Grant Smith
 */

#ifndef IMAGE_H_
#define IMAGE_H_

#include "main.h"

extern uint8_t playerCount; //Global variable that keeps track of players count during a hand
extern uint8_t dealerCount; //Global variable that keeps track of dealers count during a hand
extern uint8_t cardValue; //Global variable that stores the value of the last random generated card

extern uint8_t game_result; //Global variable that keeps track of result of last game
//0 -no result; 1 -player win; 2 -dealer win
extern uint8_t handDone; //Global variable that tracks whether or not a hand is in process
extern uint16_t FG_COLOR;                //Color scheme preset to white and blue
extern uint16_t BG_COLOR;
/******************************************************************************
 * Chooses a card to display at random. Used in any functions that draws
 * a card.
 *
 * Parameters
 *      None
 * Returns
 *      uint8_t pointer, card image
 ******************************************************************************/
uint8_t* chooseCard(void);

/******************************************************************************
 * Used to get the bitmap for the specified count variable. Used when updating
 * the count on screen.
 *
 * Parameters
 *      uint8_t count : value whose count bitmap will be shown
 * Returns
 *      uint8_t pointer : count bitmap
 ******************************************************************************/
uint8_t* chooseCount(uint8_t count);

/******************************************************************************
 * Displays the welcome screen for the blackjack game. The initial display
 * on a reset.
 *
 * Parameters
 *      None
 * Returns
 *      None
 ******************************************************************************/
void welcomeScreen_init(void);

/******************************************************************************
 * Displays the instruction screen for the blackjack game. Displays after the
 * welcome screen.
 *
 * Parameters
 *      None
 * Returns
 *      None
 ******************************************************************************/
void instructionScreen_init(void);

/******************************************************************************
 * Displays the game screen before deal of cards for the blackjack game.
 *
 * Parameters
 *      None
 * Returns
 *      None
 ******************************************************************************/
void preDealScreen_init(void);

/******************************************************************************
 * Deals the initial cards to the dealer and the player. 2 face up cards to
 * player, 1 face up and 1 face down to the dealer.
 *
 * Parameters
 *      None
 * Returns
 *      None
 ******************************************************************************/
void dealCards_init(void);

/******************************************************************************
 * Gives the dealer a single card. Increases the dealers count.
 *
 * Parameters
 *      None
 * Returns
 *      None
 ******************************************************************************/
void drawDealer(void);

/******************************************************************************
 * Gives the player a single card. Increases the players count.
 *
 * Parameters
 *      None
 * Returns
 *      None
 ******************************************************************************/
void drawPlayer(void);

/******************************************************************************
 * Flips the dealers down card over. Increases dealer count.
 *
 * Parameters
 *      None
 * Returns
 *      None
 ******************************************************************************/
void dealerShow(void);

/******************************************************************************
 * Updates the players count on screen after each card is drawn.
 *
 * Parameters
 *      None
 * Returns
 *      None
 ******************************************************************************/
void updatePlayerCount(void);

/******************************************************************************
 * Updates the dealers count on screen after each card is drawn.
 *
 * Parameters
 *      None
 * Returns
 *      None
 ******************************************************************************/
void updateDealerCount(void);

/**
 * Sets the color of the background and foreground to be colored
 *
 * Parameters
 *      uint8_t, number representing color scheme to be chosen
 * Returns
 *      None
 **/
void changeColors(uint8_t color);

/*******************************************************************************
 * Displays the results of the game on screen after the hand is finished.
 * Also plays the winner or loser song.
 * 0 - Player has lost
 * 1 - Player has won
 *
 * Parameters
 *      uint8_t that represents a player win or loss
 * Returns
 *      None
 ********************************************************************************/
void gameResults(uint8_t result);

#endif /* IMAGE_H_ */
