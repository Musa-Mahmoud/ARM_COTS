/************************************************************************************
 * @file BZR_prog.c
 * @author Musa Mahmoud
 * @brief The buzzer main source file, including functions' definition
 * @version 1.0
 * @date 2023-09-03
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdint.h>
#include "stm32f103xx.h"
#include "ErrType.h"

#include "SYSTICK_interface.h"
#include "GPIO_interface.h"

#include "BZR_interface.h"
#include "BZR_prv.h"

/* Private Functions */

static uint8_t IsBzrConfigValid(BZR_t *BzrConfig)
{
    if ((BzrConfig->Port > GPIO_PORTE) || (BzrConfig->Port < GPIO_PORTA) || (BzrConfig->Pin > GPIO_PIN15) || (BzrConfig->Pin < GPIO_PIN0)
        || (BzrConfig->ConnectionType > BZR_SOURCE_CONNECTION) || (BzrConfig->ConnectionType < BZR_SINK_CONNECTION)
        )
    {
        return INVALID;
    }
    
    return VALID;
}

/* Public Functions */

uint8_t BZR_u8TurnOn(BZR_t *BzrConfig)
{
    uint8_t Local_u8ErrorState = OK;

    /* Check buzzer config, then early return if it's not valid */
    if (NULL == BzrConfig)
    {
        return NULL_PTR_ERR;
    }
    else if (!IsBzrConfigValid(BzrConfig))
    {
        return NOK;
    }

    Local_u8ErrorState = GPIO_u8SetPinValue(BzrConfig->Port, BzrConfig->Pin, BzrConfig->ConnectionType);

    return Local_u8ErrorState;
}

uint8_t BZR_u8TurnOff(BZR_t *BzrConfig)
{
    uint8_t Local_u8ErrorState = OK;

    /* Check buzzer config, then early return if it's not valid */
    if (NULL == BzrConfig)
    {
        return NULL_PTR_ERR;
    }
    else if (!IsBzrConfigValid(BzrConfig))
    {
        return NOK;
    }

    Local_u8ErrorState = GPIO_u8SetPinValue(BzrConfig->Port, BzrConfig->Pin, !(BzrConfig->ConnectionType));

    return Local_u8ErrorState;
}

uint8_t BZR_u8Toggle(BZR_t *BzrConfig)
{
    uint8_t Local_u8ErrorState = OK;

    /* Check buzzer config, then early return if it's not valid */
    if (NULL == BzrConfig)
    {
        return NULL_PTR_ERR;
    }
    else if (!IsBzrConfigValid(BzrConfig))
    {
        return NOK;
    }

    Local_u8ErrorState = GPIO_u8TogglePinValue(BzrConfig->Port, BzrConfig->Pin);

    return Local_u8ErrorState;
}

uint8_t BZR_u8Beep(BZR_t *BzrConfig, uint16_t Copy_u16BeepsNumber, uint16_t Copy_u16BeepTimeMs)
{
    uint8_t Local_u8ErrorState = OK;

    /* Check buzzer config, then early return if it's not valid */
    if (NULL == BzrConfig)
    {
        return NULL_PTR_ERR;
    }
    else if (!IsBzrConfigValid(BzrConfig))
    {
        return NOK;
    }

    for (uint16_t LoopCounter = 0; LoopCounter < Copy_u16BeepsNumber; LoopCounter++)
    {
        /* Turn the buzzer on. The pin value depends on the connection type */
        Local_u8ErrorState = GPIO_u8SetPinValue(BzrConfig->Port, BzrConfig->Pin, BzrConfig->ConnectionType);
        /* Keep the buzzer on for the desired amount of time */
        Systick_DelayMs(Copy_u16BeepTimeMs);
        /* Turn the buzzer off. The pin value depends on the connection type */
        Local_u8ErrorState = GPIO_u8SetPinValue(BzrConfig->Port, BzrConfig->Pin, !(BzrConfig->ConnectionType));
        /* Keep the buzzer off for the desired amount of time */
        Systick_DelayMs(Copy_u16BeepTimeMs);
    }
    
    return Local_u8ErrorState;
}
