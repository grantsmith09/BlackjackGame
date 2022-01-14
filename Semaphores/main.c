
/*
 *  ======== main_freertos.c ========
 */
#include "main.h"

SemaphoreHandle_t Sem_UART;
SemaphoreHandle_t Sem_MKII_RGB;
SemaphoreHandle_t Sem_LAUNCHPAD_RGB;

/*
 *  ======== main ========
 */
int main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    ece353_staff_init(true);

    printf("\n\r");
    printf("*********************************************\n\r");
    printf("* ICE-14-Semaphores\n\r");
    printf("*********************************************\n\r");
    printf("\n\r");

    // ADD CODE -- Create the Semaphore used to control the UART
    Sem_UART = xSemaphoreCreateBinary();

    // ADD CODE --  Create the Semaphore used to control the RGB LED on the MKII
    Sem_MKII_RGB = xSemaphoreCreateBinary();

    // ADD CODE --  Create the Semaphore used to control the RGB LED on the Launchpad
    Sem_LAUNCHPAD_RGB = xSemaphoreCreateBinary();

    // ADD CODE --  Give the Semaphore for the UART
    xSemaphoreGive(Sem_UART);

    xTaskCreate
    (   Task_MKII_S1,
        "Task_MKII_S1",
        configMINIMAL_STACK_SIZE,
        NULL,
        1,
        &TaskHandle_MKII_S1
    );

    xTaskCreate
    (   Task_MKII_S2,
        "Task_MKII_S2",
        configMINIMAL_STACK_SIZE,
        NULL,
        1,
        &TaskHandle_MKII_S2
    );

    xTaskCreate
     (   Task_MKII_RGB,
         "Task_MKII_RGB",
         configMINIMAL_STACK_SIZE,
         NULL,
         1,
         &TaskHandle_MKII_RGB
     );

    xTaskCreate
     (   Task_LAUNCHPAD_RGB,
         "Task_LAUNCHPAD_RGB",
         configMINIMAL_STACK_SIZE,
         NULL,
         1,
         &TaskHandle_LAUNCHPAD_RGB
     );

    /* Start the FreeRTOS scheduler */
    vTaskStartScheduler();

    while(1){};
    return (0);
}

//*****************************************************************************
//
//! \brief Application defined malloc failed hook
//!
//! \param  none
//!
//! \return none
//!
//*****************************************************************************
void vApplicationMallocFailedHook()
{
    /* Handle Memory Allocation Errors */
    while(1)
    {
    }
}

//*****************************************************************************
//
//! \brief Application defined stack overflow hook
//!
//! \param  none
//!
//! \return none
//!
//*****************************************************************************
void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName)
{
    //Handle FreeRTOS Stack Overflow
    while(1)
    {
    }
}
