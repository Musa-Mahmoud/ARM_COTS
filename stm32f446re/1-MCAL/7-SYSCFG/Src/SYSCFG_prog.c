/************************************************************************************
 * @file SYSCFG_prog.c
 * @author Musa Mahmoud
 * @brief The SYSCFG(System Configuration) main source file, including functions' definition
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

#include "SYSCFG_interface.h"
#include "SYSCFG_prv.h"

uint8_t SYSCFG_u8SetEXTIPort(SYSCFG_LineNumber_t Copy_LineNumber, SYSCFG_Port_t Copy_Port)
{
    uint8_t Local_u8RegNum = Copy_LineNumber / EXTI_CTRL_REG_ACCESS;
    uint8_t Local_u8BitNum = (Copy_LineNumber % EXTI_CTRL_BITS_ACCESS) * EXTI_CTRL_BITS_ACCESS;

    if (Copy_LineNumber > SYSCFG_RTC_WKUP_LINE || Copy_LineNumber < SYSCFG_EXTI0_LINE)
    {
        return NOK;
    }

    /* Clear port number */
    SYSCFG->EXTICR[Local_u8RegNum] &= (EXTICR_MASK) << Local_u8BitNum;

    /* Set port number */
    SYSCFG->EXTICR[Local_u8RegNum] |= Copy_Port << Local_u8BitNum;

    return OK;
}
