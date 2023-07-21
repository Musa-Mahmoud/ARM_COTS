/************************************************************************************
 * @file RCC_prog.c
 * @author Musa Mahmoud
 * @brief The RCC(Reset and Clock Control) main source file, including functions' definition
 * @version 1.0
 * @date 2023-07-14
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdint.h>
#include "stm32f446xx.h"
#include "ErrType.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "RCC_prv.h"


RCC_ErrorState_t RCC_SetClkSts(RCC_Clock_t Copy_ClockType, RCC_Status_t Copy_StatusType)
{
    uint32_t Local_TimeoutAmount = TIMEOUT_AMOUNT;
    
    if(RCC_STATUSTYPE_ON == Copy_StatusType)
    {
        switch (Copy_ClockType)
        {
        case RCC_CLOCKTYPE_PLL: SET_BIT(RCC->CR, RCC_CR_PLLON_POS); while(!GET_BIT(RCC->CR, RCC_CR_PLLRDY_POS) && --Local_TimeoutAmount) break;
        case RCC_CLOCKTYPE_HSE: SET_BIT(RCC->CR, RCC_CR_HSEON_POS); while(!GET_BIT(RCC->CR, RCC_CR_HSERDY_POS) && --Local_TimeoutAmount) break;
        case RCC_CLOCKTYPE_HSI: SET_BIT(RCC->CR, RCC_CR_HSION_POS); while(!GET_BIT(RCC->CR, RCC_CR_HSIRDY_POS) && --Local_TimeoutAmount) break;
        default: return RCC_ErrorState_WRONG_OPTION;
        }
    }
    else if(RCC_STATUSTYPE_OFF == Copy_StatusType)
    {
        switch (Copy_ClockType)
        {
        case RCC_CLOCKTYPE_PLL: CLR_BIT(RCC->CR, RCC_CR_PLLON_POS); break;
        case RCC_CLOCKTYPE_HSE: CLR_BIT(RCC->CR, RCC_CR_HSEON_POS); break;
        case RCC_CLOCKTYPE_HSI: CLR_BIT(RCC->CR, RCC_CR_HSION_POS); break;
        default: return RCC_ErrorState_WRONG_OPTION;
        }
    }
    else
    {
        return RCC_ErrorState_WRONG_OPTION;
    }

    if(0 == Local_TimeoutAmount)
    {
        return RCC_ErrorState_TIMEOUT;
    }

    return RCC_ErrorState_OK;
}


RCC_ErrorState_t RCC_SetSysClk(RCC_Clock_t Copy_ClockType)
{
    switch (Copy_ClockType)
    {
    case RCC_CLOCKTYPE_PLL: SET_BITS(RCC->CFGR, RCC_CFGR_SW_BIT1); break;
    case RCC_CLOCKTYPE_HSE: SET_BITS(RCC->CFGR, RCC_CFGR_SW_BIT0); break;
    case RCC_CLOCKTYPE_HSI: CLR_BITS(RCC->CFGR, RCC_CFGR_SW); break;
    default: return RCC_ErrorState_WRONG_OPTION;
    }

    return RCC_ErrorState_OK;
}


RCC_ErrorState_t RCC_SetHSEConfig(RCC_HSE_DivFactor Copy_DivFactor)
{
    if(Copy_DivFactor == RCC_HSE_DIVFACTOR_DIV0)
    {
        CLR_BIT(RCC->CFGR, RCC_CFGR_PLLXTPRE_POS);
    }
    else if(Copy_DivFactor == RCC_HSE_DIVFACTOR_DIV2)
    {
        SET_BIT(RCC->CFGR, RCC_CFGR_PLLXTPRE_POS);
    }
    else
    {
        return RCC_ErrorState_WRONG_OPTION;
    }

    return RCC_ErrorState_OK;
}


RCC_ErrorState_t RCC_SetPLLConfig(RCC_PLL_MulFactor Copy_PllMulFactor, RCC_PLL_ClkSrc_t Copy_PllSource)
{
    uint32_t Local_TmpReg = READ_REG(RCC->CFGR);

    if(Copy_PllMulFactor > RCC_PLL_MULFACTOR_MUL16 || Copy_PllMulFactor < RCC_PLL_MULFACTOR_MUL2)
    {
        return RCC_ErrorState_WRONG_OPTION;
    }
    
    if((Copy_PllSource != RCC_PLL_CLKSRC_HSI) && (Copy_PllSource != RCC_PLL_CLKSRC_HSE))
    {
        return RCC_ErrorState_WRONG_OPTION;
    }

    SET_BITS(Local_TmpReg, (Copy_PllMulFactor << RCC_CFGR_PLLMUL_POS));

    SET_BITS(Local_TmpReg, (Copy_PllSource << RCC_CFGR_PLLSRC_POS));

    WRITE_REG(RCC->CFGR, Local_TmpReg);

    return RCC_ErrorState_OK;
}


RCC_ErrorState_t RCC_AHB1EnableClock(RCC_AHB1_Peripheral_t Copy_Ahb1PeripheralName)
{
    SET_BIT(RCC->AHB1ENR, Copy_Ahb1PeripheralName);

    return RCC_ErrorState_OK;
}


RCC_ErrorState_t RCC_AHB1DisableClock(RCC_AHB1_Peripheral_t Copy_Ahb1PeripheralName)
{
    CLR_BIT(RCC->AHB1ENR, Copy_Ahb1PeripheralName);

    return RCC_ErrorState_OK;
}


RCC_ErrorState_t RCC_APB1EnableClock(RCC_APB1_Peripheral_t Copy_Apb1PeripheralName)
{
    SET_BIT(RCC->APB1ENR, Copy_Apb1PeripheralName);

    return RCC_ErrorState_OK;
}


RCC_ErrorState_t RCC_APB1DisableClock(RCC_APB1_Peripheral_t Copy_Apb1PeripheralName)
{
    CLR_BIT(RCC->APB1ENR, Copy_Apb1PeripheralName);

    return RCC_ErrorState_OK;
}


RCC_ErrorState_t RCC_APB2EnableClock(RCC_APB2_Peripheral_t Copy_Apb2PeripheralName)
{
    SET_BIT(RCC->APB2ENR, Copy_Apb2PeripheralName);

    return RCC_ErrorState_OK;
}


RCC_ErrorState_t RCC_APB2DisableClock(RCC_APB2_Peripheral_t Copy_Apb2PeripheralName)
{
    CLR_BIT(RCC->APB2ENR, Copy_Apb2PeripheralName);

    return RCC_ErrorState_OK;
}
