#include "HAL_SysTick.h"

/*******************************************************************************
* Definitions
******************************************************************************/
static callback_ SysTick_Interrupt_CallBack = NULL;

/*******************************************************************************
* Code
******************************************************************************/

/**
 * @brief Initializes the SysTick timer using the internal CPU clock.
 *
 * This function initializes the SysTick timer using the internal CPU clock. It calculates the maximum time that can be set
 * and configures the necessary registers.
 *
 * @param timeSetUp The desired time setup value in microseconds.
 *
 * @return None.
 */
void HAL_SYSTICK_Internal_Init(uint32_t timeSetUp)
{
    float maxtime;
    /* With internal CPU clock frequency for MKE16Z4 is 'SystemCoreClock'
     * And limit 24 bit for RELOAD value
     * So the maximum time(0.1ms) can be set:
     * 1/SystemCoreClock * (2^24) * 1000 (ms)
     */
    //maxtime = (1<<24) / SystemCoreClock * 1000;
    maxtime = (1<<24)/(SystemCoreClock / 1000) ;
    if(timeSetUp > maxtime)
    {
        /* Error*/
        while (1);
    }
    else
    {
        /* Disable systick*/
        SysTick->CTRL = 0;
        /* Configuration reload value */
        SysTick->LOAD = (SystemCoreClock / 50000) * timeSetUp - 1;
        /* Set current value = 0 */
        SysTick->VAL = 0;
        /* Enable systick, system clock, enable systick interrupt  */
        SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_TICKINT_Msk;
    }
}

/**
 * @brief Initializes the SysTick timer using an external clock.
 *
 * This function initializes the SysTick timer using an external clock. It calculates the maximum time that can be set
 * and configures the necessary registers.
 *
 * @param freq The frequency of the external clock.
 * @param timeSetUp The desired time setup value in microseconds.
 *
 * @return None.
 */
void HAL_SYSTICK_External_Init(uint32_t freq, uint32_t timeSetUp)
{
    float maxtime;

    /* With external clock frequency for LPC17xx is 'freq'
     * And limit 24 bit for RELOAD value
     * So the maximum time can be set:
     * 1/freq * (2^24) * 1000 (ms)
     */
    //check time value is available or not
    maxtime = (1<<24) / freq * 1000;
    if (timeSetUp > maxtime)
        //Error Loop
        while(1);
    else
    {
        SysTick->CTRL = 0;
        //Select external clock as System Tick clock source
        SysTick->CTRL &= ~SysTick_CTRL_CLKSOURCE_Msk;
        /* Set RELOAD value (ms)
         * RELOAD = (freq/1000) * time - 1
         * with time base in milliseconds
         */
        SysTick->LOAD = (freq / 50000) * timeSetUp - 1;
        SysTick->CTRL = SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_TICKINT_Msk;
    }
}

/**
 * @brief Configures the SysTick interrupt mode.
 *
 * This function configures the SysTick interrupt mode.
 *
 * @param status The interrupt mode status (ENABLE or DISABLE).
 *
 * @return None.
 */
void HAL_SYSTICK_Interrupt_Config(MODE status)
{
    if(status == ENABLE)
    {
        SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
    }
    else
    {
        SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;
    }
}

/**
 * @brief Sets the SysTick mode.
 *
 * This function sets the SysTick mode.
 *
 * @param status The mode status (ENABLE or DISABLE).
 *
 * @return None.
 */
void HAL_SYSTICK_Mode(MODE status)
{
    if(status == ENABLE)
    {
        SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
    }
    else
    {
        SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
    }
}

/**
 * @brief Gets the SysTick flag.
 *
 * This function gets the SysTick flag.
 *
 * @return The SysTick flag value (0 or 1).
 */
uint32_t HAL_SYSTICK_Get_Flag(void)
{
    return((SysTick->CTRL >> SysTick_CTRL_COUNTFLAG_Pos) & 0x01);
}

/**
 * @brief Gets the current SysTick value.
 *
 * This function gets the current SysTick value.
 *
 * @return The current SysTick value.
 */
uint32_t HAL_SYSTICK_Get_Current_Value(void)
{
    return (SysTick->VAL);
}

/**
 * @brief Sets the SysTick interrupt callback function.
 *
 * This function sets the SysTick interrupt callback function.
 *
 * @param call_back The callback function to be set.
 *
 * @return None.
 */
void HAL_SYSTICK_Set_Interrupt_Callback(callback_ call_back)
{
    SysTick_Interrupt_CallBack = call_back;
}

/**
 * @brief SysTick interrupt handler.
 *
 * This function is the SysTick interrupt handler that calls the registered callback function.
 *
 * @return None.
 */
void SysTick_Handler()
{
    SysTick_Interrupt_CallBack();
}

/*******************************************************************************
* EOF
******************************************************************************/
