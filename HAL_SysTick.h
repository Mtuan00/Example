#ifndef _HAL_SYSTICK_H_
#define _HAL_SYSTICK_H_

#include "HAL_Common.h"

/*******************************************************************************
* Definitions
******************************************************************************/

/*******************************************************************************
* Variables
******************************************************************************/
/**
 * @brief Mode enumeration for SYSTICK.
 */
typedef enum{
    DISABLE = 0,
    ENABLE = 1
} MODE;

/*******************************************************************************
* API
******************************************************************************/
/**
 * @brief Initializes the internal SYSTICK timer.
 *
 * @param timeSetUp The time setup value for the internal SYSTICK timer.
 */
void HAL_SYSTICK_Internal_Init(uint32_t timeSetUp);

/**
 * @brief Initializes the external SYSTICK timer.
 *
 * @param freq The frequency of the external SYSTICK timer.
 * @param timeSetUp The time setup value for the external SYSTICK timer.
 */
void HAL_SYSTICK_External_Init(uint32_t freq, uint32_t timeSetUp);

/**
 * @brief Configures the SYSTICK interrupt.
 *
 * @param status The status of the SYSTICK interrupt (ENABLE/DISABLE).
 */
void HAL_SYSTICK_Interrupt_Config(MODE status);

/**
 * @brief Sets the mode of SYSTICK.
 *
 * @param status The status of the SYSTICK mode (ENABLE/DISABLE).
 */
void HAL_SYSTICK_Mode(MODE status);

/**
 * @brief Gets the current value of SYSTICK.
 *
 * @return The current value of SYSTICK.
 */
uint32_t HAL_SYSTICK_Get_Current_Value(void);

/**
 * @brief Gets the flag status of SYSTICK.
 *
 * @return The flag status of SYSTICK.
 */
uint32_t HAL_SYSTICK_Get_Flag(void);

/**
 * @brief Sets the interrupt callback function for SYSTICK.
 *
 * @param call_back The callback function to be set.
 */
void HAL_SYSTICK_Set_Interrupt_Callback(callback_ call_back);

/**
 * @brief Clears the mode.
 *
 * @param mode The mode to be cleared.
 */
void DRIVER_ClearMode(uint8_t mode);

#endif /* _HAL_SYSTICK_H_ */

/*******************************************************************************
* EOF
******************************************************************************/
