/*
 * screen.c
 *
 *  Created on: Dec 8, 2021
 *      Author: Luke Kolder + Grant Smith
 */

#include "screen.h"

uint8_t playerCount; //Global variable that keeps track of players count during a hand
uint8_t dealerCount; //Global variable that keeps track of dealers count during a hand
uint8_t cardValue; //Global variable that stores the value of the last random generated card

uint8_t game_result; //Global variable that keeps track of result of last game
//0 -no result; 1 -player win; 2 -dealer win
uint8_t handDone = 1; //Global variable that tracks whether or not a hand is in process
uint16_t FG_COLOR = 0x0F;                //Color scheme preset to white and blue
uint16_t BG_COLOR = 0xFFFF;

/******************************************************************************
 * Chooses a card to display at random. Used in any functions that draws
 * a card.
 *
 * Parameters
 *      None
 * Returns
 *      uint8_t pointer, card image
 ******************************************************************************/
uint8_t* chooseCard(void)
{

    switch (rand() % 13)
    {

    case 0:
        cardValue = 1;
        return &aceCard;
    case 1:
        cardValue = 2;
        return &twoCard;
    case 2:
        cardValue = 3;
        return &threeCard;
    case 3:
        cardValue = 4;
        return &fourCard;
    case 4:
        cardValue = 5;
        return &fiveCard;
    case 5:
        cardValue = 6;
        return &sixCard;
    case 6:
        cardValue = 7;
        return &sevenCard;
    case 7:
        cardValue = 8;
        return &eightCard;
    case 8:
        cardValue = 9;
        return &nineCard;
    case 9:
        cardValue = 10;
        return &tenCard;
    case 10:
        cardValue = 10;
        return &jackCard;
    case 11:
        cardValue = 10;
        return &queenCard;
    case 12:
        cardValue = 10;
        return &kingCard;

    }

}

/******************************************************************************
 * Used to get the bitmap for the specified count variable. Used when updating
 * the count on screen.
 *
 * Parameters
 *      uint8_t count : value whose count bitmap will be shown
 * Returns
 *      uint8_t pointer : count bitmap
 ******************************************************************************/
uint8_t* chooseCount(uint8_t count)
{

    switch (count)
    {
    case 0:
        return &num0Bitmaps;
    case 1:
        return &num1Bitmaps;
    case 2:
        return &num2Bitmaps;
    case 3:
        return &num3Bitmaps;
    case 4:
        return &num4Bitmaps;
    case 5:
        return &num5Bitmaps;
    case 6:
        return &num6Bitmaps;
    case 7:
        return &num7Bitmaps;
    case 8:
        return &num8Bitmaps;
    case 9:
        return &num9Bitmaps;
    case 10:
        return &num10Bitmaps;
    case 11:
        return &num11Bitmaps;
    case 12:
        return &num12Bitmaps;
    case 13:
        return &num13Bitmaps;
    case 14:
        return &num14Bitmaps;
    case 15:
        return &num15Bitmaps;
    case 16:
        return &num16Bitmaps;
    case 17:
        return &num17Bitmaps;
    case 18:
        return &num18Bitmaps;
    case 19:
        return &num19Bitmaps;
    case 20:
        return &num20Bitmaps;
    case 21:
        return &num21Bitmaps;

    }

}

/******************************************************************************
 * Updates the players count on screen after each card is drawn.
 *
 * Parameters
 *      None
 * Returns
 *      None
 ******************************************************************************/
void updatePlayerCount(void)
{
    playerCount = playerCount + cardValue;

    if (playerCount == 21)
    {
        //BLACKJACK ANIMATION
        game_result = 1;
        handDone = 1;
        lcd_draw_image(105, 93, numWidthPixels, numHeightPixels,
                       chooseCount(playerCount), FG_COLOR, BG_COLOR);
    }
    else if (playerCount > 21)
    {
        //BUST ANIMATION
        lcd_draw_image(105, 93, bustWidthPixels, bustHeightPixels, bustBitmaps,
                       FG_COLOR, BG_COLOR);
        game_result = 2;
        handDone = 1;
    }
    else
    {
        lcd_draw_image(105, 93, numWidthPixels, numHeightPixels,
                       chooseCount(playerCount), FG_COLOR, BG_COLOR);
        //DISPLAY NEW COUNT ON SCREEN
    }
}

/******************************************************************************
 * Updates the dealers count on screen after each card is drawn.
 *
 * Parameters
 *      None
 * Returns
 *      None
 ******************************************************************************/
void updateDealerCount(void)
{
    dealerCount = dealerCount + cardValue;

    if (dealerCount == 21)
    {
        lcd_draw_image(105, 30, numWidthPixels, numHeightPixels,
                       chooseCount(dealerCount), FG_COLOR, BG_COLOR);
        //LOSE ANIMATION
    }
    else if (dealerCount > 21)
    {
        //WIN ANIMATION
        game_result = 1;
        lcd_draw_image(105, 30, bustWidthPixels, bustHeightPixels, bustBitmaps,
                       FG_COLOR, BG_COLOR);
    }
    else
    {
        //DISPLAY NEW COUNT ON SCREEN
        lcd_draw_image(105, 30, numWidthPixels, numHeightPixels,
                       chooseCount(dealerCount), FG_COLOR, BG_COLOR);
    }

}
/******************************************************************************
 * Displays the welcome screen for the blackjack game. The initial display
 * on a reset.
 *
 * Parameters
 *      None
 * Returns
 *      None
 ******************************************************************************/
void welcomeScreen_init(void)
{
    lcd_draw_rectangle(0, 0, 512, 512, BG_COLOR);
    lcd_draw_image(65, 65, startScreenWidthPixels, startScreenHeightPixels,
                   startScreenBitmaps, FG_COLOR, BG_COLOR);
    lcd_draw_image(70, 74, cardWidthPixels, cardHeightPixels, blankCard,
                   FG_COLOR, BG_COLOR);
    lcd_draw_image(60, 72, cardWidthPixels, cardHeightPixels, aceCard, FG_COLOR,
                   BG_COLOR);
}

/******************************************************************************
 * Displays the instruction screen for the blackjack game. Displays after the
 * welcome screen.
 *
 * Parameters
 *      None
 * Returns
 *      None
 ******************************************************************************/
void instructionScreen_init(void)
{
    lcd_draw_rectangle(0, 0, 512, 512, BG_COLOR);
    lcd_draw_image(65, 65, instructionsWidthPixels, instructionsHeightPixels,
                   instructionsBitmaps, FG_COLOR, BG_COLOR);
}

/******************************************************************************
 * Displays the game screen before deal of cards for the blackjack game.
 *
 * Parameters
 *      None
 * Returns
 *      None
 ******************************************************************************/
void preDealScreen_init(void)
{
    lcd_draw_rectangle(0, 0, 512, 512, BG_COLOR);
    dealerCount = 0;
    playerCount = 0;
    game_result = 0;

    //Headers for the current sum of dealer cards and player cards
    lcd_draw_image(105, 15, dealerCountWidthPixels, dealerCountHeightPixels,
                   dealerCountBitmaps, FG_COLOR, BG_COLOR);
    lcd_draw_image(105, 78, playerCountWidthPixels, playerCountHeightPixels,
                   playerCountBitmaps, FG_COLOR, BG_COLOR);
    lcd_draw_image(105, 30, numWidthPixels, numHeightPixels,
                   chooseCount(dealerCount), FG_COLOR, BG_COLOR);
    lcd_draw_image(105, 93, numWidthPixels, numHeightPixels,
                   chooseCount(playerCount), FG_COLOR, BG_COLOR);
    //Represents the deck of cards that is being drawn from
    lcd_draw_image(25, 25, cardWidthPixels, cardHeightPixels, blankCard,
                   FG_COLOR, BG_COLOR);
    //Instruction reminders on the bottom of the screen at all times
    lcd_draw_image(18, 120, hitWidthPixels, hitHeightPixels, hitBitmaps,
                   FG_COLOR, BG_COLOR);
    lcd_draw_image(63, 120, doubleWidthPixels, doubleHeightPixels,
                   doubleBitmaps, FG_COLOR, BG_COLOR);
    lcd_draw_image(110, 120, standWidthPixels, standHeightPixels, standBitmaps,
                   FG_COLOR, BG_COLOR);
}

/******************************************************************************
 * Deals the initial cards to the dealer and the player. 2 face up cards to
 * player, 1 face up and 1 face down to the dealer.
 *
 * Parameters
 *      None
 * Returns
 *      None
 ******************************************************************************/
void dealCards_init(void)
{
    handDone = 0;
    int i;
    //Deals dealer first card(down)
    for (i = 0; i <= 40; i = i + 1)
    {

        lcd_draw_image(25 + i, 25, cardWidthPixels, cardHeightPixels, blankCard,
                       FG_COLOR, BG_COLOR);
        lcd_draw_image(10 + i, 25, 1, cardHeightPixels, blankCard, BG_COLOR,
                       BG_COLOR);
        lcd_draw_image(25, 25, cardWidthPixels, cardHeightPixels, blankCard,
                       FG_COLOR, BG_COLOR);
    }

    lcd_draw_image(65, 25, cardWidthPixels, cardHeightPixels, blankCard,
                   FG_COLOR, BG_COLOR);
    //Deals player first card
    for (i = 0; i <= 65; i = i + 1)
    {
        lcd_draw_image(25, 25, cardWidthPixels, cardHeightPixels, blankCard,
                       FG_COLOR, BG_COLOR);
        lcd_draw_image(25, 25 + i, cardWidthPixels, cardHeightPixels, blankCard,
                       FG_COLOR, BG_COLOR);
        lcd_draw_image(25, 5 + i, cardWidthPixels, 1, blankCard, BG_COLOR,
                       BG_COLOR);

    }
    for (i = 0; i <= 40; i = i + 1)
    {

        lcd_draw_image(25 + i, 90, cardWidthPixels, cardHeightPixels, blankCard,
                       FG_COLOR, BG_COLOR);
        lcd_draw_image(10 + i, 90, 2, cardHeightPixels, blankCard, BG_COLOR,
                       BG_COLOR);
    }
    uint8_t *card1 = chooseCard();

    lcd_draw_image(65, 90, cardWidthPixels, cardHeightPixels, card1, FG_COLOR,
                   BG_COLOR);
    updatePlayerCount();

    //Deals dealer second card(up)
    for (i = 0; i <= 5; i = i + 1)
    {
        lcd_draw_image(25, 25, cardWidthPixels, cardHeightPixels, blankCard,
                       FG_COLOR, BG_COLOR);
        lcd_draw_image(25, 25 + i, cardWidthPixels, cardHeightPixels, blankCard,
                       FG_COLOR, BG_COLOR);
        lcd_draw_image(25, 5 + i, cardWidthPixels, 1, blankCard, BG_COLOR,
                       BG_COLOR);

    }
    for (i = 0; i <= 35; i = i + 1)
    {

        lcd_draw_image(25 + i, 30, cardWidthPixels, cardHeightPixels, blankCard,
                       FG_COLOR, BG_COLOR);
        lcd_draw_image(10 + i, 30, 1, cardHeightPixels, blankCard, BG_COLOR,
                       BG_COLOR);
        lcd_draw_image(25, 25, cardWidthPixels, cardHeightPixels, blankCard,
                       FG_COLOR, BG_COLOR);
    }
    uint8_t *card2 = chooseCard();

    lcd_draw_image(60, 30, cardWidthPixels, cardHeightPixels, card2, FG_COLOR,
                   BG_COLOR);
    updateDealerCount();
    //Deals player second card
    for (i = 0; i <= 70; i = i + 1)
    {
        lcd_draw_image(25, 25, cardWidthPixels, cardHeightPixels, blankCard,
                       FG_COLOR, BG_COLOR);
        lcd_draw_image(25, 25 + i, cardWidthPixels, cardHeightPixels, blankCard,
                       FG_COLOR, BG_COLOR);
        lcd_draw_image(25, 5 + i, cardWidthPixels, 1, blankCard, BG_COLOR,
                       BG_COLOR);

    }
    for (i = 0; i <= 35; i = i + 1)
    {

        lcd_draw_image(25 + i, 95, cardWidthPixels, cardHeightPixels, blankCard,
                       FG_COLOR, BG_COLOR);
        lcd_draw_image(10 + i, 95, 2, cardHeightPixels, blankCard, BG_COLOR,
                       BG_COLOR);
    }
    uint8_t *card3 = chooseCard();

    lcd_draw_image(60, 95, cardWidthPixels, cardHeightPixels, card3, FG_COLOR,
                   BG_COLOR);
    updatePlayerCount();
}

/******************************************************************************
 * Gives the dealer a single card. Increases the dealers count.
 *
 * Parameters
 *      None
 * Returns
 *      None
 ******************************************************************************/
void drawDealer(void)
{
    int i;
    for (i = 0; i <= 5; i = i + 1)
    {
        lcd_draw_image(25, 25, cardWidthPixels, cardHeightPixels, blankCard,
                       FG_COLOR, BG_COLOR);
        lcd_draw_image(25, 25 + i, cardWidthPixels, cardHeightPixels, blankCard,
                       FG_COLOR, BG_COLOR);
        lcd_draw_image(25, 5 + i, cardWidthPixels, 1, blankCard, BG_COLOR,
                       BG_COLOR);

    }
    for (i = 0; i <= 35; i = i + 1)
    {

        lcd_draw_image(25 + i, 30, cardWidthPixels, cardHeightPixels, blankCard,
                       FG_COLOR, BG_COLOR);
        lcd_draw_image(10 + i, 30, 1, cardHeightPixels, blankCard, BG_COLOR,
                       BG_COLOR);
        lcd_draw_image(25, 25, cardWidthPixels, cardHeightPixels, blankCard,
                       FG_COLOR, BG_COLOR);
    }

    uint8_t *card1 = chooseCard();

    lcd_draw_image(60, 30, cardWidthPixels, cardHeightPixels, card1, FG_COLOR,
                   BG_COLOR);
    updateDealerCount();

}

/******************************************************************************
 * Gives the player a single card. Increases the players count.
 *
 * Parameters
 *      None
 * Returns
 *      None
 ******************************************************************************/
void drawPlayer(void)
{
    int i;
    for (i = 0; i <= 70; i = i + 1)
    {
        lcd_draw_image(25, 25, cardWidthPixels, cardHeightPixels, blankCard,
                       FG_COLOR, BG_COLOR);
        lcd_draw_image(25, 25 + i, cardWidthPixels, cardHeightPixels, blankCard,
                       FG_COLOR, BG_COLOR);
        lcd_draw_image(25, 5 + i, cardWidthPixels, 1, blankCard, BG_COLOR,
                       BG_COLOR);

    }
    for (i = 0; i <= 35; i = i + 1)
    {

        lcd_draw_image(25 + i, 95, cardWidthPixels, cardHeightPixels, blankCard,
                       FG_COLOR, BG_COLOR);
        lcd_draw_image(10 + i, 95, 2, cardHeightPixels, blankCard, BG_COLOR,
                       BG_COLOR);
    }
    uint8_t *card1 = chooseCard();
    lcd_draw_image(60, 95, cardWidthPixels, cardHeightPixels, card1, FG_COLOR,
                   BG_COLOR);
    updatePlayerCount();
}

/******************************************************************************
 * Flips the dealers down card over. Increases dealer count.
 *
 * Parameters
 *      None
 * Returns
 *      None
 ******************************************************************************/
void dealerShow(void)
{
    lcd_draw_image(65, 25, cardWidthPixels, cardHeightPixels, twoCard, FG_COLOR,
                   BG_COLOR);
    uint8_t *card1 = chooseCard();
    lcd_draw_image(60, 30, cardWidthPixels, cardHeightPixels, card1, FG_COLOR,
                   BG_COLOR);
    updateDealerCount();
}

/**
 * Sets the color of the background and foreground to be a specific color
 * scheme based on user input
 * 0 : White and Blue
 * 1 : Black and Red
 * Parameters
 *      uint8_t color : parameter to choose color scheme
 * Returns
 *      None
 **/
void changeColors(uint8_t color)
{

    if (color == 0)
    {
        BG_COLOR = 0xFFFF;
        FG_COLOR = 0x0F;
    }
    else if (color == 1)
    {
        BG_COLOR = 0x0000;
        FG_COLOR = 0x1F << 11;
    }

}
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
void gameResults(uint8_t result)
{
    game_result = 0;
    lcd_draw_rectangle(0, 0, 512, 512, BG_COLOR);
    if (result == 1)
    {
        lcd_draw_image(65, 65, winnerWidthPixels, winnerHeightPixels,
                       winnerBitmaps, FG_COLOR, BG_COLOR);
        Buzzer_Win();
    }
    else
    {
        lcd_draw_image(65, 65, loserWidthPixels, loserHeightPixels,
                       loserBitmaps, FG_COLOR, BG_COLOR);
        Buzzer_Lose();
    }
}
