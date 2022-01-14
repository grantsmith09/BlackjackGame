/*
 * blackjackFunctions.c
 *
 *  Created on: Dec 12, 2021
 *      Author: Luke Kolder + Grant Smith
 */

#include "blackjackFunctions.h"

/******************************************************************************
 * Displays the welcome screen to the user. To be called in LCD Task
 *
 * Parameters
 *      None
 * Returns
 *      None
 ******************************************************************************/
void resetScreen(void)
{
    welcomeScreen_init();
}

/******************************************************************************
 * Displays the given screen based on how many times the s1 has been pressed.
 * To be called in the task monitoring s1
 * 1 press - instructions
 * 2 press - pre deal screen
 * else - deal cards
 *
 * Parameters
 *      uint8_t s1PressCount : parameter to choose proper behavior on a button
 *      press
 * Returns
 *      None
 ******************************************************************************/
void s1Function(uint8_t s1PressCount)
{

    if (s1PressCount == 1)
    {
        instructionScreen_init();
    }
    else if (s1PressCount == 2)
    {
        preDealScreen_init();
    }
    else
    {
        dealCards_init();
    }
}

/******************************************************************************
 * Performs the actions of a dealer once the player has given up control
 * of the board. Dealer draws on 16.
 *
 * Parameters
 *      None
 * Returns
 *      None
 ******************************************************************************/
void dealerFunc(void)
{
    vTaskDelay(pdMS_TO_TICKS(1000));
    dealerShow();
    vTaskDelay(pdMS_TO_TICKS(1000));
    handDone = 1;
    while (dealerCount < 17)
    {
        drawDealer();
    }
    if (dealerCount >= playerCount && dealerCount <= 21)
    {
        game_result = 2;
    }
    else if (dealerCount < playerCount)
    {
        game_result = 1;
    }
}

/**
 * Performs the corresponding task based on the input given to the accelerometer.
 * Forward is Double down(player draw card, give control to dealer)
 * Left is Hit(player draw card, retain control)
 * Right is Stand(give control to dealer
 *
 * Parameters
 *      uint8_t dir : parameter to choose proper behavior on input from
 *      accelerometer
 * Returns
 *      None
 **/
void accelerometerFunction(uint8_t dir)
{
    if (dir == 0)
    {
        drawPlayer();
        if (handDone == 0)
        {
            dealerFunc();
        }
    }
    else if (dir == 1)
    {
        drawPlayer();
    }
    else if (dir == 2)
    {
        dealerFunc();
    }
}

/******************************************************************************
 * Plays a happy song for when a player wins a game
 *
 * Parameters
 *      None
 * Returns
 *      None
 ******************************************************************************/
void Buzzer_Win(void)
{
    buzzer_init(6377);
    buzzer_on();
    vTaskDelay(pdMS_TO_TICKS(336));
    buzzer_off();

    buzzer_init(4778);
    buzzer_on();
    vTaskDelay(pdMS_TO_TICKS(336));
    buzzer_off();

    buzzer_init(3792);
    buzzer_on();
    vTaskDelay(pdMS_TO_TICKS(336));
    buzzer_off();

    buzzer_init(3188);
    buzzer_on();
    vTaskDelay(pdMS_TO_TICKS(504));
    buzzer_off();

    buzzer_init(3792);
    buzzer_on();
    vTaskDelay(pdMS_TO_TICKS(168));
    buzzer_off();

    buzzer_init(3188);
    buzzer_on();
    vTaskDelay(pdMS_TO_TICKS(672));
    buzzer_off();
}

/******************************************************************************
 * Plays a sad song when the player loses a game
 *
 * Parameters
 *      None
 * Returns
 *      None
 ******************************************************************************/
void Buzzer_Lose(void)
{
    buzzer_init(30000);
    buzzer_on();
    vTaskDelay(pdMS_TO_TICKS(400));
    buzzer_off();

    buzzer_init(50000);
    buzzer_on();
    vTaskDelay(pdMS_TO_TICKS(800));
    buzzer_off();
}

