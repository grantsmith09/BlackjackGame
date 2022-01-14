/*
 * task_mkII_s1.c
 *
 *  Created on: Oct 14, 2020
 *      Author: Joe Krachey
 */

#include "task_mkII_s1.h"
#include "ece353_staff.h"

TaskHandle_t task_mkII_s1_Handle = NULL;

/******************************************************************************
 * De-bounce switch S1.  If is has been pressed, change the tri-Color LED on
 * the MSP432 Launchpad. Everytime S1 is pressed, the color should change in
 * the following order:
 *      RED->GREEN->BLUE->RED->GREEN....
 *****************************************************************************/
void task_mkII_s1(void *pvParameters)
{
    // Declare a uint8_t variable that will be used to de-bounce S1
    uint8_t debounce_state = 0x00;
    int color = 0;

    while(1)
    {

        // Shift the de-bounce variable to the left 
        debounce_state = debounce_state << 1;

        // If S1 is being pressed, set the LSBit of debounce_state to a 1;
        if (ece353_staff_MKII_S1()) {
            debounce_state |= 0x01;
        }

        // If the de-bounce variable is equal to 0x7F, change the color of the tri-color LED.
        if (debounce_state == 0x7F) {

            if (color == 0) {
                ece353_staff_RGB_LED(true, false, false);
                color++;
            }

            else if (color == 1) {
                ece353_staff_RGB_LED(false, true, false);
                color++;
            }
            else if (color == 2) {
                ece353_staff_RGB_LED(false, false, true);
                color = 0;
            }
        }
        // Delay for 10mS using vTaskDelay
        vTaskDelay(pdMS_TO_TICKS(10));
    }

}
