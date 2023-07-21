/************************************************************************************
 * @file SCB_prog.c
 * @author Musa Mahmoud
 * @brief The SCB(System Control Block) main source file, including functions' definition
 * @version 1.0
 * @date 2023-07-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdint.h>
#include "stm32f446xx.h"
#include "ErrType.h"
#include "BIT_MATH.h"

#include "SCB_interface.h"
#include "SCB_prv.h"

uint8_t SCB_u8SetPriorityGrouping(PriorityGrouping_t Copy_PriorityGrouping)
{
    /* Read AIRCR value and assign it to a temporary value */
    uint32_t Local_u32TmpReg = READ_REG(SCB->AIRCR);

    /* Check the priority group, then early return if it's not valid */
    if (Copy_PriorityGrouping > PRIORITY_GROUPING_MAX || Copy_PriorityGrouping < PRIORITY_GROUPING_MIN)
    {
        return NOK;
    }

    /* Clear the priority group and VECTKEY bits in the temporary register */
    CLR_BITS(Local_u32TmpReg, VECTKEY | PRIGROUP);
    /* Set the priority group value and write the necessary VECTKEY value */
    SET_BITS(Local_u32TmpReg, (VECTKEY_VALUE << VECTKEY_POS) | (Copy_PriorityGrouping << PRIGROUP_POS));

    /* Write all the configuration from the temporary register to the AIRCR register */
    WRITE_REG(SCB->AIRCR, Local_u32TmpReg);

    return OK;
}
