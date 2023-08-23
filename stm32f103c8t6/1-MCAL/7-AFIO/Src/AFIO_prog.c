/************************************************************************************
 * @file AFIO_prog.c
 * @author Musa Mahmoud
 * @brief The AFIO(Alternate functions Input Output) main source file, including functions' definition
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

#include "AFIO_interface.h"
#include "AFIO_prv.h"

uint8_t AFIO_u8SetEXTIPort(AFIO_LineNumber_t Copy_LineNumber, AFIO_Port_t Copy_Port)
{
    uint8_t Local_u8RegNum = Copy_LineNumber >> EXTI_CTRL_REG_ACCESS;
    uint8_t Local_u8BitNum = (Copy_LineNumber & EXTI_CTRL_BITS_MASK) << EXTI_CTRL_BITS_ACCESS;

    if ((Copy_LineNumber > AFIO_USB_WAKEUP_LINE) || (Copy_LineNumber < AFIO_EXTI0_LINE) || (Copy_Port > AFIO_PORTE) || (Copy_Port < AFIO_PORTA))
    {
        return NOK;
    }

    /* Clear port number */
    AFIO->EXTICR[Local_u8RegNum] &= ~((EXTICR_MASK) << Local_u8BitNum);

    /* Set port number */
    AFIO->EXTICR[Local_u8RegNum] |= Copy_Port << Local_u8BitNum;

    return OK;
}
