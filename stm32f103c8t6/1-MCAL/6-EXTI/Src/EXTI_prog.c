/************************************************************************************
 * @file EXTI_prog.c
 * @author Musa Mahmoud
 * @brief The EXTI(External Interrupt) main source file, including functions' definition
 * @version 1.0
 * @date 2023-07-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdint.h>
#include "stm32f103xx.h"
#include "ErrType.h"
#include "BIT_MATH.h"

#include "EXTI_interface.h"
#include "EXTI_prv.h"

/* Static array of pointer to functions to hold callback functions */
static void(*EXTI_CallbackFunctions[LINES_NUMBER])(void) = {NULL};

uint8_t EXTI_u8Init(const EXTI_Config_t *Copy_EXTIConfig)
{
    uint8_t Local_u8ErrorState = OK;

    if (NULL != Copy_EXTIConfig)
    {
        if (Copy_EXTIConfig->LineNumber <= EXTI_USB_WAKEUP_LINE && Copy_EXTIConfig->LineNumber >= EXTI_EXTI0_LINE)
        {
            /* Set trigger source configuration */
            switch (Copy_EXTIConfig->TriggerConfig)
            {
            case EXTI_RISING_EDGE: EXTI->RTSR |= 1 << (Copy_EXTIConfig->LineNumber); EXTI->FTSR &= ~(1 << (Copy_EXTIConfig->LineNumber)); break;
            case EXTI_FALLING_EDGE: EXTI->FTSR |= 1 << (Copy_EXTIConfig->LineNumber); EXTI->RTSR &= ~(1 << (Copy_EXTIConfig->LineNumber)); break;
            case EXTI_RISING_FALLING_EDGE: EXTI->RTSR |= 1 << (Copy_EXTIConfig->LineNumber); EXTI->FTSR |= 1 << (Copy_EXTIConfig->LineNumber); break;
            default: Local_u8ErrorState = NOK; break;
            }

            /* Set interrupt enable/disable initial state */
            if (EXTI_ENABLED == Copy_EXTIConfig->InitalState)
            {
                EXTI->IMR |= (1 << Copy_EXTIConfig->LineNumber);
            }
            else if (EXTI_DISABLED == Copy_EXTIConfig->InitalState)
            {
                EXTI->IMR &= ~(1 << Copy_EXTIConfig->LineNumber);
            }
            else
            {
                Local_u8ErrorState = NOK;
            }

            /* Set callback function pointer */
            if (NULL != Copy_EXTIConfig->CallbackFunction)
            {
                EXTI_CallbackFunctions[Copy_EXTIConfig->LineNumber] = Copy_EXTIConfig->CallbackFunction;
            }
            else
            {
                Local_u8ErrorState = NULL_PTR_ERR;
            }
        }
        else
        {
            Local_u8ErrorState = NOK;
        }
    }
    else
    {
        Local_u8ErrorState = NULL_PTR_ERR;
    }

    return Local_u8ErrorState;
}

uint8_t EXTI_u8SetTrigSrc(EXTI_LineNumber_t Copy_LineNumber, EXTI_TriggerSource_t Copy_TriggerSource)
{
    uint8_t Local_u8ErrorState = OK;

    if (Copy_LineNumber <= EXTI_USB_WAKEUP_LINE && Copy_LineNumber >= EXTI_EXTI0_LINE)
    {
        /* Set trigger source configuration */
        switch (Copy_TriggerSource)
        {
        case EXTI_RISING_EDGE: EXTI->RTSR |= 1 << (Copy_LineNumber); EXTI->FTSR &= ~(1 << (Copy_LineNumber)); break;
        case EXTI_FALLING_EDGE: EXTI->FTSR |= 1 << (Copy_LineNumber); EXTI->RTSR &= ~(1 << (Copy_LineNumber)); break;
        case EXTI_RISING_FALLING_EDGE: EXTI->RTSR |= 1 << (Copy_LineNumber); EXTI->FTSR |= 1 << (Copy_LineNumber); break;
        default: Local_u8ErrorState = NOK; break;
        }
    }
    else
    {
        Local_u8ErrorState = NOK;
    }

    return Local_u8ErrorState;
}

uint8_t EXTI_u8EnableINT(EXTI_LineNumber_t Copy_LineNumber)
{
    if (Copy_LineNumber > EXTI_USB_WAKEUP_LINE || Copy_LineNumber < EXTI_EXTI0_LINE)
    {
        return NOK;
    }

    EXTI->IMR |= (1 << Copy_LineNumber);

    return OK;
}

uint8_t EXTI_u8DisableINT(EXTI_LineNumber_t Copy_LineNumber)
{
    if (Copy_LineNumber > EXTI_USB_WAKEUP_LINE || Copy_LineNumber < EXTI_EXTI0_LINE)
    {
        return NOK;
    }

    EXTI->IMR &= ~(1 << Copy_LineNumber);

    return OK;
}

uint8_t EXTI_u8ClearPendingFlag(EXTI_LineNumber_t Copy_LineNumber)
{
    if (Copy_LineNumber > EXTI_USB_WAKEUP_LINE || Copy_LineNumber < EXTI_EXTI0_LINE)
    {
        return NOK;
    }

    EXTI->PR = 1 << Copy_LineNumber;

    return OK;
}

uint8_t EXTI_u8ReadPendingFlag(EXTI_LineNumber_t Copy_LineNumber, uint8_t *Copy_pu8FlagStatus)
{
    if (Copy_LineNumber > EXTI_USB_WAKEUP_LINE || Copy_LineNumber < EXTI_EXTI0_LINE)
    {
        return NOK;
    }
    else if (NULL == Copy_pu8FlagStatus)
    {
        return NULL_PTR_ERR;
    }

    *Copy_pu8FlagStatus = ((EXTI->PR >> Copy_LineNumber) & 0x01);

    return OK;
}

/* EXTI IRQ Handler */
void EXTI0_IRQHandler(void)
{
    /* Clear the pending flag of EXTI0 line */
    EXTI_u8ClearPendingFlag(EXTI_EXTI0_LINE);

    /* Call the callback function set by the user */
    EXTI_CallbackFunctions[EXTI_EXTI0_LINE]();
}

void EXTI1_IRQHandler(void)
{
    /* Clear the pending flag of EXTI1 line */
    EXTI_u8ClearPendingFlag(EXTI_EXTI1_LINE);

    /* Call the callback function set by the user */
    EXTI_CallbackFunctions[EXTI_EXTI1_LINE]();
}

void EXTI2_IRQHandler(void)
{
    /* Clear the pending flag of EXTI2 line */
    EXTI_u8ClearPendingFlag(EXTI_EXTI2_LINE);

    /* Call the callback function set by the user */
    EXTI_CallbackFunctions[EXTI_EXTI2_LINE]();
}

void EXTI3_IRQHandler(void)
{
    /* Clear the pending flag of EXTI3 line */
    EXTI_u8ClearPendingFlag(EXTI_EXTI3_LINE);

    /* Call the callback function set by the user */
    EXTI_CallbackFunctions[EXTI_EXTI3_LINE]();
}

void EXTI4_IRQHandler(void)
{
    /* Clear the pending flag of EXTI4 line */
    EXTI_u8ClearPendingFlag(EXTI_EXTI4_LINE);

    /* Call the callback function set by the user */
    EXTI_CallbackFunctions[EXTI_EXTI4_LINE]();
}

void EXTI9_5_IRQHandler(void)
{
    if (FLAG_RAISED == GET_BIT(EXTI->PR, EXTI_EXTI5_LINE))
    {
        /* Clear the pending flag of EXTI5 line */
        EXTI_u8ClearPendingFlag(EXTI_EXTI5_LINE);
        /* Call the callback function set by the user */
        EXTI_CallbackFunctions[EXTI_EXTI5_LINE]();
    }

    if (FLAG_RAISED == GET_BIT(EXTI->PR, EXTI_EXTI6_LINE))
    {
        /* Clear the pending flag of EXTI6 line */
        EXTI_u8ClearPendingFlag(EXTI_EXTI6_LINE);
        /* Call the callback function set by the user */
        EXTI_CallbackFunctions[EXTI_EXTI6_LINE]();
    }
    
    if (FLAG_RAISED == GET_BIT(EXTI->PR, EXTI_EXTI7_LINE))
    {
        /* Clear the pending flag of EXTI7 line */
        EXTI_u8ClearPendingFlag(EXTI_EXTI7_LINE);
        /* Call the callback function set by the user */
        EXTI_CallbackFunctions[EXTI_EXTI7_LINE]();
    }
    
    if (FLAG_RAISED == GET_BIT(EXTI->PR, EXTI_EXTI8_LINE))
    {
        /* Clear the pending flag of EXTI8 line */
        EXTI_u8ClearPendingFlag(EXTI_EXTI8_LINE);
        /* Call the callback function set by the user */
        EXTI_CallbackFunctions[EXTI_EXTI8_LINE]();
    }
    
    if (FLAG_RAISED == GET_BIT(EXTI->PR, EXTI_EXTI9_LINE))
    {
        /* Clear the pending flag of EXTI9 line */
        EXTI_u8ClearPendingFlag(EXTI_EXTI9_LINE);
        /* Call the callback function set by the user */
        EXTI_CallbackFunctions[EXTI_EXTI9_LINE]();
    }
}

void EXTI15_10_IRQHandler(void)
{
    if (FLAG_RAISED == GET_BIT(EXTI->PR, EXTI_EXTI10_LINE))
    {
        /* Clear the pending flag of EXTI10 line */
        EXTI_u8ClearPendingFlag(EXTI_EXTI10_LINE);
        /* Call the callback function set by the user */
        EXTI_CallbackFunctions[EXTI_EXTI10_LINE]();
    }

    if (FLAG_RAISED == GET_BIT(EXTI->PR, EXTI_EXTI11_LINE))
    {
        /* Clear the pending flag of EXTI11 line */
        EXTI_u8ClearPendingFlag(EXTI_EXTI11_LINE);
        /* Call the callback function set by the user */
        EXTI_CallbackFunctions[EXTI_EXTI11_LINE]();
    }
    
    if (FLAG_RAISED == GET_BIT(EXTI->PR, EXTI_EXTI12_LINE))
    {
        /* Clear the pending flag of EXTI12 line */
        EXTI_u8ClearPendingFlag(EXTI_EXTI12_LINE);
        /* Call the callback function set by the user */
        EXTI_CallbackFunctions[EXTI_EXTI12_LINE]();
    }
    
    if (FLAG_RAISED == GET_BIT(EXTI->PR, EXTI_EXTI13_LINE))
    {
        /* Clear the pending flag of EXTI13 line */
        EXTI_u8ClearPendingFlag(EXTI_EXTI13_LINE);
        /* Call the callback function set by the user */
        EXTI_CallbackFunctions[EXTI_EXTI13_LINE]();
    }
    
    if (FLAG_RAISED == GET_BIT(EXTI->PR, EXTI_EXTI14_LINE))
    {
        /* Clear the pending flag of EXTI14 line */
        EXTI_u8ClearPendingFlag(EXTI_EXTI14_LINE);
        /* Call the callback function set by the user */
        EXTI_CallbackFunctions[EXTI_EXTI14_LINE]();
    }
    
    if (FLAG_RAISED == GET_BIT(EXTI->PR, EXTI_EXTI15_LINE))
    {
        /* Clear the pending flag of EXTI15 line */
        EXTI_u8ClearPendingFlag(EXTI_EXTI15_LINE);
        /* Call the callback function set by the user */
        EXTI_CallbackFunctions[EXTI_EXTI15_LINE]();
    }
}
