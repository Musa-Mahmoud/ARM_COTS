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
#include "stm32f446xx.h"
#include "ErrType.h"
#include "BIT_MATH.h"

#include "EXTI_interface.h"
#include "EXTI_prv.h"

/* Static array of pointer to functions to hold callback functions */
static void(*EXTI_CallbackFunction[LINES_NUMBER])(void) = {NULL};

uint8_t EXTI_u8Init(const EXTI_Config_t *Copy_EXTIConfig)
{
    uint8_t Local_u8ErrorState = OK;

    if (NULL != Copy_EXTIConfig)
    {
        /* Set trigger source configuration */
        switch (Copy_EXTIConfig->TriggerConfig)
        {
        case RISING_EDGE: EXTI->RTSR |= 1 << (Copy_EXTIConfig->LineNumber); EXTI->FTSR &= ~(1 << (Copy_EXTIConfig->LineNumber)); break;
        case FALLING_EDGE: EXTI->FTSR |= 1 << (Copy_EXTIConfig->LineNumber); EXTI->RTSR &= ~(1 << (Copy_EXTIConfig->LineNumber)); break;
        case RISING_FALLING_EDGE: EXTI->RTSR |= 1 << (Copy_EXTIConfig->LineNumber); EXTI->FTSR |= 1 << (Copy_EXTIConfig->LineNumber); break;
        default: Local_u8ErrorState = NOK; break;
        }

        /* Set interrupt enable/disable initial state */
        if (ENABLED == Copy_EXTIConfig->InitalState)
        {
            EXTI->IMR |= (1 << Copy_EXTIConfig->LineNumber);
        }
        else if (DISABLED == Copy_EXTIConfig->InitalState)
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
            EXTI_CallbackFunction[Copy_EXTIConfig->LineNumber] = Copy_EXTIConfig->CallbackFunction;
        }
        else
        {
            Local_u8ErrorState = NULL_PTR_ERR;
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

        /* Set trigger source configuration */
        switch (Copy_TriggerSource)
        {
        case RISING_EDGE: EXTI->RTSR |= 1 << (Copy_LineNumber); EXTI->FTSR &= ~(1 << (Copy_LineNumber)); break;
        case FALLING_EDGE: EXTI->FTSR |= 1 << (Copy_LineNumber); EXTI->RTSR &= ~(1 << (Copy_LineNumber)); break;
        case RISING_FALLING_EDGE: EXTI->RTSR |= 1 << (Copy_LineNumber); EXTI->FTSR |= 1 << (Copy_LineNumber); break;
        default: Local_u8ErrorState = NOK; break;
        }

    return Local_u8ErrorState;
}

uint8_t EXTI_u8EnableINT(EXTI_LineNumber_t Copy_LineNumber)
{
    if (Copy_LineNumber > RTC_WKUP_LINE || Copy_LineNumber < EXTI0_LINE)
    {
        return NOK;
    }

    EXTI->IMR |= (1 << Copy_LineNumber);

    return OK;
}

uint8_t EXTI_u8DisableINT(EXTI_LineNumber_t Copy_LineNumber)
{
    if (Copy_LineNumber > RTC_WKUP_LINE || Copy_LineNumber < EXTI0_LINE)
    {
        return NOK;
    }

    EXTI->IMR &= ~(1 << Copy_LineNumber);

    return OK;
}

uint8_t EXTI_u8ClearPendingFlag(EXTI_LineNumber_t Copy_LineNumber)
{
    if (Copy_LineNumber > RTC_WKUP_LINE || Copy_LineNumber < EXTI0_LINE)
    {
        return NOK;
    }

    EXTI->PR = 1 << Copy_LineNumber;

    return OK;
}

uint8_t EXTI_u8ReadPendingFlag(EXTI_LineNumber_t Copy_LineNumber, uint8_t *Copy_pu8FlagStatus)
{
    if (Copy_LineNumber > RTC_WKUP_LINE || Copy_LineNumber < EXTI0_LINE)
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
    EXTI_u8ClearPendingFlag(EXTI0_LINE);

    /* Call the callback function set by the user */
    EXTI_CallbackFunction[EXTI0_LINE]();
}

void EXTI1_IRQHandler(void)
{
    /* Clear the pending flag of EXTI1 line */
    EXTI_u8ClearPendingFlag(EXTI1_LINE);

    /* Call the callback function set by the user */
    EXTI_CallbackFunction[EXTI1_LINE]();
}

void EXTI2_IRQHandler(void)
{
    /* Clear the pending flag of EXTI2 line */
    EXTI_u8ClearPendingFlag(EXTI2_LINE);

    /* Call the callback function set by the user */
    EXTI_CallbackFunction[EXTI2_LINE]();
}

void EXTI3_IRQHandler(void)
{
    /* Clear the pending flag of EXTI3 line */
    EXTI_u8ClearPendingFlag(EXTI3_LINE);

    /* Call the callback function set by the user */
    EXTI_CallbackFunction[EXTI3_LINE]();
}

void EXTI4_IRQHandler(void)
{
    /* Clear the pending flag of EXTI4 line */
    EXTI_u8ClearPendingFlag(EXTI4_LINE);

    /* Call the callback function set by the user */
    EXTI_CallbackFunction[EXTI4_LINE]();
}

void EXTI9_5_IRQHandler(void)
{
    if (1 == GET_BIT(EXTI->PR, EXTI5_LINE))
    {
        /* Clear the pending flag of EXTI5 line */
        EXTI_u8ClearPendingFlag(EXTI5_LINE);
        /* Call the callback function set by the user */
        EXTI_CallbackFunction[EXTI5_LINE]();
    }

    if (1 == GET_BIT(EXTI->PR, EXTI6_LINE))
    {
        /* Clear the pending flag of EXTI6 line */
        EXTI_u8ClearPendingFlag(EXTI6_LINE);
        /* Call the callback function set by the user */
        EXTI_CallbackFunction[EXTI6_LINE]();
    }
    
    if (1 == GET_BIT(EXTI->PR, EXTI7_LINE))
    {
        /* Clear the pending flag of EXTI7 line */
        EXTI_u8ClearPendingFlag(EXTI7_LINE);
        /* Call the callback function set by the user */
        EXTI_CallbackFunction[EXTI7_LINE]();
    }
    
    if (1 == GET_BIT(EXTI->PR, EXTI8_LINE))
    {
        /* Clear the pending flag of EXTI8 line */
        EXTI_u8ClearPendingFlag(EXTI8_LINE);
        /* Call the callback function set by the user */
        EXTI_CallbackFunction[EXTI8_LINE]();
    }
    
    if (1 == GET_BIT(EXTI->PR, EXTI9_LINE))
    {
        /* Clear the pending flag of EXTI9 line */
        EXTI_u8ClearPendingFlag(EXTI9_LINE);
        /* Call the callback function set by the user */
        EXTI_CallbackFunction[EXTI9_LINE]();
    }
}

void EXTI15_10_IRQHandler(void)
{
    if (1 == GET_BIT(EXTI->PR, EXTI10_LINE))
    {
        /* Clear the pending flag of EXTI10 line */
        EXTI_u8ClearPendingFlag(EXTI10_LINE);
        /* Call the callback function set by the user */
        EXTI_CallbackFunction[EXTI10_LINE]();
    }

    if (1 == GET_BIT(EXTI->PR, EXTI11_LINE))
    {
        /* Clear the pending flag of EXTI11 line */
        EXTI_u8ClearPendingFlag(EXTI11_LINE);
        /* Call the callback function set by the user */
        EXTI_CallbackFunction[EXTI11_LINE]();
    }
    
    if (1 == GET_BIT(EXTI->PR, EXTI12_LINE))
    {
        /* Clear the pending flag of EXTI12 line */
        EXTI_u8ClearPendingFlag(EXTI12_LINE);
        /* Call the callback function set by the user */
        EXTI_CallbackFunction[EXTI12_LINE]();
    }
    
    if (1 == GET_BIT(EXTI->PR, EXTI13_LINE))
    {
        /* Clear the pending flag of EXTI13 line */
        EXTI_u8ClearPendingFlag(EXTI13_LINE);
        /* Call the callback function set by the user */
        EXTI_CallbackFunction[EXTI13_LINE]();
    }
    
    if (1 == GET_BIT(EXTI->PR, EXTI14_LINE))
    {
        /* Clear the pending flag of EXTI14 line */
        EXTI_u8ClearPendingFlag(EXTI14_LINE);
        /* Call the callback function set by the user */
        EXTI_CallbackFunction[EXTI14_LINE]();
    }
    
    if (1 == GET_BIT(EXTI->PR, EXTI15_LINE))
    {
        /* Clear the pending flag of EXTI15 line */
        EXTI_u8ClearPendingFlag(EXTI15_LINE);
        /* Call the callback function set by the user */
        EXTI_CallbackFunction[EXTI15_LINE]();
    }
}
