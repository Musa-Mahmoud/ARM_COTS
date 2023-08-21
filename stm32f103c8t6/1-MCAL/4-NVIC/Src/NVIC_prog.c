/************************************************************************************
 * @file NVIC_prog.c
 * @author Musa Mahmoud
 * @brief The NVIC(Nested Vectored Interrupt Controller) main source file, including functions' definition
 * @version 1.0
 * @date 2023-07-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdint.h>
#include "stm32f103xx.h"
#include "ErrType.h"
#include "BIT_MATH.h"

#include "NVIC_interface.h"
#include "NVIC_prv.h"

uint8_t NVIC_u8EnableIRQ(IRQ_Number_t Copy_IRQNumber)
{
    /* Calculate the ISER register number */
    uint8_t Loacl_u8RegNum = Copy_IRQNumber >> ISER_REG_ACCESS;
    /* Calculate the ISERx bit number */
    uint8_t Loacl_u8BitNum = Copy_IRQNumber & ISER_BIT_ACCESS;

    /* Check the interrupt request number, then early return if it's not valid */
    if (Copy_IRQNumber > FMPI2C1_ERROR_IRQ_NUMBER || Copy_IRQNumber < WWDG_IRQ_NUMBER)
    {
        return NOK;
    }
    
    /* Enable the interrupt request */
    NVIC->ISER[Loacl_u8RegNum] = (1 << Loacl_u8BitNum); 

    return OK;
}

uint8_t NVIC_u8DisableIRQ(IRQ_Number_t Copy_IRQNumber)
{
    /* Calculate the ICER register number */
    uint8_t Loacl_u8RegNum = Copy_IRQNumber >> ICER_REG_ACCESS;
    /* Calculate the ICERx bit number */
    uint8_t Loacl_u8BitNum = Copy_IRQNumber & ICER_BIT_ACCESS;
    
    /* Check the interrupt request number, then early return if it's not valid */   
    if (Copy_IRQNumber > FMPI2C1_ERROR_IRQ_NUMBER || Copy_IRQNumber < WWDG_IRQ_NUMBER)
    {
        return NOK;
    }
    
    /* Disable the interrupt request */
    NVIC->ICER[Loacl_u8RegNum] = (1 << Loacl_u8BitNum);

    return OK;
}

uint8_t NVIC_u8SetPendingIRQ(IRQ_Number_t Copy_IRQNumber)
{
    /* Calculate the ISPR register number */
    uint8_t Loacl_u8RegNum = Copy_IRQNumber >> ISPR_REG_ACCESS;
    /* Calculate the ISPRx bit number */
    uint8_t Loacl_u8BitNum = Copy_IRQNumber & ISPR_BIT_ACCESS;
    
    /* Check the interrupt request number, then early return if it's not valid */
    if (Copy_IRQNumber > FMPI2C1_ERROR_IRQ_NUMBER || Copy_IRQNumber < WWDG_IRQ_NUMBER)
    {
        return NOK;
    }
    
    /* Set the interrupt request pending */
    NVIC->ISPR[Loacl_u8RegNum] = (1 << Loacl_u8BitNum);

    return OK;
}

uint8_t NVIC_u8ClearPendingIRQ(IRQ_Number_t Copy_IRQNumber)
{
    /* Calculate the ICPR register number */
    uint8_t Loacl_u8RegNum = Copy_IRQNumber >> ICPR_REG_ACCESS;
    /* Calculate the ICPRx bit number */
    uint8_t Loacl_u8BitNum = Copy_IRQNumber & ICPR_BIT_ACCESS;
    
    /* Check the interrupt request number, then early return if it's not valid */
    if (Copy_IRQNumber > FMPI2C1_ERROR_IRQ_NUMBER || Copy_IRQNumber < WWDG_IRQ_NUMBER)
    {
        return NOK;
    }
    
    /* Clear the interrupt request pending */
    NVIC->ICPR[Loacl_u8RegNum] = (1 << Loacl_u8BitNum);
    
    return OK;
}

uint8_t NVIC_u8GetPendingIRQ(IRQ_Number_t Copy_IRQNumber, PendingFlag_t *Copy_pPendingFlag)
{
    /* Calculate the ISPR register number */
    uint8_t Loacl_u8RegNum = Copy_IRQNumber >> ISPR_REG_ACCESS;
    /* Calculate the ISPRx bit number */
    uint8_t Loacl_u8BitNum = Copy_IRQNumber & ISPR_BIT_ACCESS;
    
    /* Check the interrupt request number, then early return if it's not valid */
    if (Copy_IRQNumber > FMPI2C1_ERROR_IRQ_NUMBER || Copy_IRQNumber < WWDG_IRQ_NUMBER)
    {
        return NOK;
    }
    
    /* Get the interrupt request pending flag */
    *Copy_pPendingFlag = GET_BIT(NVIC->ISPR[Loacl_u8RegNum], Loacl_u8BitNum);

    return OK;
}

uint8_t NVIC_u8GetActiveIRQ(IRQ_Number_t Copy_IRQNumber, ActiveFlag_t *Copy_pActiveFlag)
{
    /* Calculate the IABR register number */
    uint8_t Local_u8RegNum = Copy_IRQNumber >> IABR_REG_ACCESS;
    /* Calculate the IABRx bit number */
    uint8_t Local_u8BitNum = Copy_IRQNumber & IABR_BIT_ACCESS;

    /* Check the interrupt request number, then early return if it's not valid */
    if (Copy_IRQNumber > FMPI2C1_ERROR_IRQ_NUMBER || Copy_IRQNumber < WWDG_IRQ_NUMBER)
    {
        return NOK;
    }
    
    /* Get the interrupt active flag */
    *Copy_pActiveFlag = GET_BIT(NVIC->IABR[Local_u8RegNum], Local_u8BitNum);

    return OK;
}

uint8_t NVIC_u8SetIRQPriority(IRQ_Number_t Copy_IRQNumber, uint8_t Copy_u8Priority)
{
    /* Check the interrupt request number, then early return if it's not valid */
    if (Copy_IRQNumber > FMPI2C1_ERROR_IRQ_NUMBER || Copy_IRQNumber < WWDG_IRQ_NUMBER)
    {
        return NOK;
    }

    /* Check the interrupt priority, then early return if it's not valid */
    if (Copy_u8Priority > PRIORITY_MAX_VALUE || Copy_u8Priority < PRIORITY_MIN_VALUE)
    {
        return NOK;
    }
    
    /* Set the interrupt priority */
    NVIC->IPR[Copy_IRQNumber] = Copy_u8Priority << USED_PRIORITY_BITS;

    return OK;
}

uint8_t NVIC_u8GetIRQPriority(IRQ_Number_t Copy_IRQNumber, uint8_t *Copy_pu8Priority)
{
    /* Check the interrupt request number, then early return if it's not valid */
    if (Copy_IRQNumber > FMPI2C1_ERROR_IRQ_NUMBER || Copy_IRQNumber < WWDG_IRQ_NUMBER)
    {
        return NOK;
    }

    /* Check the null pointer, then early return if it's not valid */
    if (NULL == Copy_pu8Priority)
    {
        return NULL_PTR_ERR;
    }
    
    /* Get the interrupt priority */
    *Copy_pu8Priority = NVIC->IPR[Copy_IRQNumber] >> USED_PRIORITY_BITS;

    return OK;
}
