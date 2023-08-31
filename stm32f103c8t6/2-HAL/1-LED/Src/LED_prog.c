/************************************************************************************
 * @file LED_prog.c
 * @author Musa Mahmoud
 * @brief The LED(Light Emitting Diode) main source file, including functions' definition
 * @version 1.0
 * @date 2023-08-31
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdint.h>
#include "stm32f103xx.h"
#include "ErrType.h"

#include "GPIO_interface.h"

#include "LED_interface.h"
#include "LED_prv.h"

/* Public Functions */

uint8_t LED_u8TurnOn(LED_t *LedConfig)
{
    uint8_t Local_u8ErrorState = OK;

    /* Check LED config, then early return if it's not valid */
    if (NULL == LedConfig)
    {
        return NULL_PTR_ERR;
    }
    else if ((LedConfig->Port > GPIO_PORTE) || (LedConfig->Port < GPIO_PORTA) || (LedConfig->Pin > GPIO_PIN15) || (LedConfig->Pin < GPIO_PIN0))
    {
        return NOK;
    }
    else if (LedConfig->ConnectionType != LED_SOURCE_CONNECTION && LedConfig->ConnectionType != LED_SINK_CONNECTION)
    {
        return NOK;
    }

    if (LED_SOURCE_CONNECTION == LedConfig->ConnectionType)
    {
        Local_u8ErrorState = GPIO_u8SetPinValue(LedConfig->Port, LedConfig->Pin, GPIO_PIN_HIGH);
    }
    else if (LED_SINK_CONNECTION == LedConfig->ConnectionType)
    {
        Local_u8ErrorState = GPIO_u8SetPinValue(LedConfig->Port, LedConfig->Pin, GPIO_PIN_LOW);
    }

    return Local_u8ErrorState;
}

uint8_t LED_u8TurnOff(LED_t *LedConfig)
{
    uint8_t Local_u8ErrorState = OK;

    /* Check LED config, then early return if it's not valid */
    if (NULL == LedConfig)
    {
        return NULL_PTR_ERR;
    }
    else if ((LedConfig->Port > GPIO_PORTE) || (LedConfig->Port < GPIO_PORTA) || (LedConfig->Pin > GPIO_PIN15) || (LedConfig->Pin < GPIO_PIN0))
    {
        return NOK;
    }
    else if (LedConfig->ConnectionType != LED_SOURCE_CONNECTION && LedConfig->ConnectionType != LED_SINK_CONNECTION)
    {
        return NOK;
    }

    if (LED_SOURCE_CONNECTION == LedConfig->ConnectionType)
    {
        Local_u8ErrorState = GPIO_u8SetPinValue(LedConfig->Port, LedConfig->Pin, GPIO_PIN_LOW);
    }
    else if (LED_SINK_CONNECTION == LedConfig->ConnectionType)
    {
        Local_u8ErrorState = GPIO_u8SetPinValue(LedConfig->Port, LedConfig->Pin, GPIO_PIN_HIGH);
    }

    return Local_u8ErrorState;
}

uint8_t LED_u8Toggle(LED_t *LedConfig)
{
    uint8_t Local_u8ErrorState = OK;

    /* Check LED config, then early return if it's not valid */
    if (NULL == LedConfig)
    {
        return NULL_PTR_ERR;
    }
    else if ((LedConfig->Port > GPIO_PORTE) || (LedConfig->Port < GPIO_PORTA) || (LedConfig->Pin > GPIO_PIN15) || (LedConfig->Pin < GPIO_PIN0))
    {
        return NOK;
    }
    else if (LedConfig->ConnectionType != LED_SOURCE_CONNECTION && LedConfig->ConnectionType != LED_SINK_CONNECTION)
    {
        return NOK;
    }

    Local_u8ErrorState = GPIO_u8TogglePinValue(LedConfig->Port, LedConfig->Pin);

    return Local_u8ErrorState;
}
