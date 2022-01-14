/*
 * task_button.c
 *
 *  Created on: Dec 12, 2021
 *      Author: grant
 */

#include <task_button.h>

TaskHandle_t Task_Button_Timer_Handle;
TaskHandle_t Task_Button_Bottom_Half_Handle;

volatile bool ALERT_S1;

/******************************************************************************
 * De-bounce switch S1.
 *****************************************************************************/
bool debounce_s1(void)
{
    static uint8_t debounce_state = 0x00;

    // Shift the de-bounce variable to the left
    debounce_state = debounce_state << 1;

    // If S1 is being pressed, set the LSBit of debounce_state to a 1;
    if(ece353_MKII_S1())
    {
        debounce_state |= 0x01;
    }

    // If the de-bounce variable is equal to 0x7F, play song.
    if(debounce_state == 0x7F)
    {
        return true;
    }
    else
    {
        return false;
    }

}

/******************************************************************************
* Used to start a Timer 32 Interrupt
******************************************************************************/
void Task_Button_Timer(void *pvParameters)
{

    while(1)
    {

        ece353_T32_1_Interrupt_Ms(2);

        /*
         * Delay 50mS
        */
        vTaskDelay(pdMS_TO_TICKS(50));

    }
}

/******************************************************************************
 * De-bounce switch S1.  If is has been pressed, change the tri-Color LED on
 * the MKIIEDU . Everytime S1 is pressed, the color should change in
 * the following order:
 *      RED->GREEN->BLUE->RED->GREEN....
 *****************************************************************************/
void Task_Button_Bottom_Half(void *pvParameters)
{
    BaseType_t status;
    BUTTON_STATUS s1;
    uint16_t count = 0;

    while(1)
    {

        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        if(count == 0) {
            s1 = PRESSED;
            count = 1;
        }
        else if(count == 1){
            s1 = PRESSED1;
            count = 2;
        }
        else if(count == 2){
            s1 = PRESSED2;
            count = 0;
        }

        xQueueSendToBack(Queue_LED, &s1, portMAX_DELAY);
    }

}

/******************************************************************************
* Top Half of T32 Handler.
******************************************************************************/
void T32_INT1_IRQHandler(void)
{

    BaseType_t xHigherPriorityTaskWoken;

    ALERT_S1 = debounce_s1();

    TIMER32_1->INTCLR = BIT0;

    if(ALERT_S1)
    {
    /*
     * Send a task notification to Task_Ambient_Light_Bottom_Half
    */
    vTaskNotifyGiveFromISR(Task_Button_Bottom_Half_Handle, &xHigherPriorityTaskWoken);

    portYIELD_FROM_ISR( xHigherPriorityTaskWoken );

    }

}


