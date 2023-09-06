/************************************************************************************
 * @file CLCD_prog.c
 * @author Musa Mahmoud
 * @brief The CLCD(Character Liquid Crystal Display) main source file, including functions' definition
 * @version 1.0
 * @date 2023-09-03
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <stdint.h>
#include "stm32f103xx.h"
#include "ErrType.h"
#include "BIT_MATH.h"

#include "SYSTICK_interface.h"
#include "GPIO_interface.h"

#include "CLCD_interface.h"
#include "CLCD_prv.h"

/* Private Variables */

/* Public Functions Prototype */

void CLCD_voidSendCommand(const CLCD_Config_t *Copy_CLCDConfig, uint8_t Copy_u8Command)
{
    uint8_t Local_u8HigherBitShift = (CLCD_MODE_4BIT == Copy_CLCDConfig->Mode)? 4 : 0;
    /* Set RS pin to low for command */
    GPIO_u8SetPinValue(Copy_CLCDConfig->CtrlPorts[0], Copy_CLCDConfig->CtrlPins[0], GPIO_PIN_LOW);
    /* Set RW pin to low for write */
    // GPIO_u8SetPinValue(Copy_CLCDConfig->CtrlPorts[1], Copy_CLCDConfig->CtrlPins[1], GPIO_PIN_LOW);
    /* Set command(higher 4 bits in case of 4-bit mode) to data pins */
    for (uint8_t LoopCounter = 0; LoopCounter < Copy_CLCDConfig->Mode; LoopCounter++)
    {
        GPIO_u8SetPinValue(Copy_CLCDConfig->DataPorts[LoopCounter], Copy_CLCDConfig->DataPins[LoopCounter], GET_BIT(Copy_u8Command, (LoopCounter + Local_u8HigherBitShift)));
    }
    /* Send enable pulse */
    GPIO_u8SetPinValue(Copy_CLCDConfig->CtrlPorts[2], Copy_CLCDConfig->CtrlPins[2], GPIO_PIN_HIGH);
    Systick_DelayUs(10);
    GPIO_u8SetPinValue(Copy_CLCDConfig->CtrlPorts[2], Copy_CLCDConfig->CtrlPins[2], GPIO_PIN_LOW);

    if (CLCD_MODE_4BIT == Copy_CLCDConfig->Mode)
    {
        Systick_DelayUs(50);
        /* Set command(lower 4 bits) to data pins */
        for (uint8_t LoopCounter = 0; LoopCounter < Copy_CLCDConfig->Mode; LoopCounter++)
        {
            GPIO_u8SetPinValue(Copy_CLCDConfig->DataPorts[LoopCounter], Copy_CLCDConfig->DataPins[LoopCounter], GET_BIT(Copy_u8Command, LoopCounter));
        }
        /* Send enable pulse */
        GPIO_u8SetPinValue(Copy_CLCDConfig->CtrlPorts[2], Copy_CLCDConfig->CtrlPins[2], GPIO_PIN_HIGH);
        Systick_DelayUs(10);
        GPIO_u8SetPinValue(Copy_CLCDConfig->CtrlPorts[2], Copy_CLCDConfig->CtrlPins[2], GPIO_PIN_LOW);
    }
    /* Wait for the command */
    Systick_DelayMs(2);
}

void CLCD_voidSendData(const CLCD_Config_t *Copy_CLCDConfig, uint8_t Copy_u8Data)
{
    uint8_t Local_u8HigherBitShift = (CLCD_MODE_4BIT == Copy_CLCDConfig->Mode)? 4 : 0;
    /* Set RS pin to high for data */
    GPIO_u8SetPinValue(Copy_CLCDConfig->CtrlPorts[0], Copy_CLCDConfig->CtrlPins[0], GPIO_PIN_HIGH);
    /* Set RW pin to low for write */
    // GPIO_u8SetPinValue(Copy_CLCDConfig->CtrlPorts[1], Copy_CLCDConfig->CtrlPins[1], GPIO_PIN_LOW);
    /* Set data(higher 4 bits in case of 4-bit mode) to data pins */
    for (uint8_t LoopCounter = 0; LoopCounter < Copy_CLCDConfig->Mode; LoopCounter++)
    {
        GPIO_u8SetPinValue(Copy_CLCDConfig->DataPorts[LoopCounter], Copy_CLCDConfig->DataPins[LoopCounter], GET_BIT(Copy_u8Data, (LoopCounter + Local_u8HigherBitShift)));
    }
    /* Send enable pulse */
    GPIO_u8SetPinValue(Copy_CLCDConfig->CtrlPorts[2], Copy_CLCDConfig->CtrlPins[2], GPIO_PIN_HIGH);
    Systick_DelayUs(10);
    GPIO_u8SetPinValue(Copy_CLCDConfig->CtrlPorts[2], Copy_CLCDConfig->CtrlPins[2], GPIO_PIN_LOW);

    if (CLCD_MODE_4BIT == Copy_CLCDConfig->Mode)
    {
        Systick_DelayUs(50);
        /* Set data(lower 4 bits) to data pins */
        for (uint8_t LoopCounter = 0; LoopCounter < Copy_CLCDConfig->Mode; LoopCounter++)
        {
            GPIO_u8SetPinValue(Copy_CLCDConfig->DataPorts[LoopCounter], Copy_CLCDConfig->DataPins[LoopCounter], GET_BIT(Copy_u8Data, LoopCounter));
        }
        /* Send enable pulse */
        GPIO_u8SetPinValue(Copy_CLCDConfig->CtrlPorts[2], Copy_CLCDConfig->CtrlPins[2], GPIO_PIN_HIGH);
        Systick_DelayUs(10);
        GPIO_u8SetPinValue(Copy_CLCDConfig->CtrlPorts[2], Copy_CLCDConfig->CtrlPins[2], GPIO_PIN_LOW);
    }
    /* Wait for the data */
    Systick_DelayMs(2);
}

void CLCD_voidInit(const CLCD_Config_t *Copy_CLCDConfig)
{
    /* Wait for more than 30 ms */
    Systick_DelayMs(40);
    if (CLCD_MODE_8BIT == Copy_CLCDConfig->Mode)
    {
        /* Function set command: 2 lines, 5x8 font size */
        CLCD_voidSendCommand(Copy_CLCDConfig, 0b00111000);
    }
    else if (CLCD_MODE_4BIT == Copy_CLCDConfig->Mode)
    {
        /* Function set command: 2 lines, 5x8 font size */
        CLCD_voidSendCommand(Copy_CLCDConfig, 0b00000010);
        CLCD_voidSendCommand(Copy_CLCDConfig, 0b00101000);
    }
    /* Display on/off control: display enable, disable cursor, no blink cursor */
    CLCD_voidSendCommand(Copy_CLCDConfig, 0b00001100);
    /* Clear display */
    CLCD_voidSendCommand(Copy_CLCDConfig, 0b00000001);
}

void CLCD_voidSendString(const CLCD_Config_t *Copy_CLCDConfig, const char *Copy_pcString)
{
    while (NULL_CHARACTER != *Copy_pcString)
    {
        /* Send the current char then increment the pointer to the next char */
        CLCD_voidSendData(Copy_CLCDConfig, *Copy_pcString++);
    }
}

void CLCD_voidGoToXY(const CLCD_Config_t *Copy_CLCDConfig, uint8_t Copy_u8XPos, uint8_t Copy_u8YPos)
{
    uint8_t Local_u8Address;

    if (0 == Copy_u8XPos)
    {
        /* Location is at first line */
        Local_u8Address = Copy_u8YPos;
    }
    else if (1 == Copy_u8XPos)
    {
        /* Location is at second line */
        Local_u8Address = Copy_u8YPos + 0x40;
    }

    /* Set bit number 7 for set DDRAM Address command then send the command */
    CLCD_voidSendCommand(Copy_CLCDConfig, Local_u8Address + 128);
}

void CLCD_voidWriteSpecialCharacter(const CLCD_Config_t *Copy_CLCDConfig, uint8_t *Copy_pu8Pattern, uint8_t Copy_u8PatternNumber, uint8_t Copy_u8XPos, uint8_t Copy_u8YPos)
{
    uint8_t Local_u8CGRAMAddress = 0;

    /* Calculate the CGRAM address whose each block is 8-bytes */
    Local_u8CGRAMAddress = Copy_u8PatternNumber * 8;

    /* Send CGRAM address command to LCD, with setting bit 6, clearing bit 7 */
    CLCD_voidSendCommand(Copy_CLCDConfig, Local_u8CGRAMAddress + 64);

    /* Write the pattern into CGRAM */
    for (uint8_t Local_u8Iterator = 0; Local_u8Iterator < 8; Local_u8Iterator++)
    {
        CLCD_voidSendData(Copy_CLCDConfig, Copy_pu8Pattern[Local_u8Iterator]);
    }

    /* Go back to DDRAM to display the pattern */
    CLCD_voidGoToXY(Copy_CLCDConfig, Copy_u8XPos, Copy_u8YPos);

    /* Display the pattern written in the CGRAM */
    CLCD_voidSendData(Copy_CLCDConfig, Copy_u8PatternNumber);
}

void CLCD_voidWriteNumber(const CLCD_Config_t *Copy_CLCDConfig, uint32_t Copy_u32Number)
{
    /* Initialized with 1 to append 1 to the end of the number after reversing it to overcome the leading zeros problem */
    uint32_t Local_u32ReversedNumber = 1;

    if (0 == Copy_u32Number)
    {
        CLCD_voidSendData(Copy_CLCDConfig, '0');
    }
    else
    {
        /* Reverse the number */
        while (Copy_u32Number != 0)
        {
            Local_u32ReversedNumber = (Local_u32ReversedNumber * 10) + (Copy_u32Number % 10);
            Copy_u32Number /= 10;
        }

        /* Sending the number to the LCD after reversing it again without the first digit as we append it at the beginning */
        while (Local_u32ReversedNumber != 1)
        {
            /* Sending the ASCII of the number's digits to the LCD */
            CLCD_voidSendData(Copy_CLCDConfig, Local_u32ReversedNumber % 10 + '0');
            Local_u32ReversedNumber /= 10;
        }
    }
}

void CLCD_voidClearDisplay(const CLCD_Config_t *Copy_CLCDConfig)
{
    CLCD_voidSendCommand(Copy_CLCDConfig, 0b00000001);
}
