/************************************************************************************
 * @file SYSTICK_prog.c
 * @author Musa Mahmoud
 * @brief The SysTick main source file, including functions' definition
 * @version 1.0
 * @date 2023-07-12
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <stdint.h>
#include "stm32f446xx.h"
#include "ErrType.h"
#include "BIT_MATH.h"

#include "SYSTICK_interface.h"
#include "SYSTICK_prv.h"

static uint8_t IsSysTickInitialized = NOT_INITIALIZED;

static void Systick_Init(void)
{
	/* Read the CTRL register */
	uint32_t Local_TmpReg = READ_REG(SYSTICK->CTRL);

	/* Clear the CLKSOURCE, TICKINT and ENABLE bits */
	CLR_BITS(Local_TmpReg, CLKSOURCE_TICKINT_ENABLE_MASK);

	/* Set the CLKSOURCE, TICKINT and ENABLE bits options */
	SET_BITS(Local_TmpReg, (AHB_DIV_8 << CLKSOURCE_POS) | (TICK_INT_DISABLE << TICKINT_POS) | (ENABLE_SYSTICK << ENABLE_POS));

	/* Write the configuration to the CTRL register */
	WRITE_REG(SYSTICK->CTRL, Local_TmpReg);

	/* Clear the current value register by writing any value */
	WRITE_REG(SYSTICK->VAL, 1);

	/* Rise the initialized flag  */
	IsSysTickInitialized = INITIALIZED;

	return;
}

void Systick_DelayMs(uint32_t Copy_u32DelayMs)
{
	uint8_t Local_u8FlagState = FLAG_DOWN;
	uint32_t Local_u32TicksNumber = ((Copy_u32DelayMs * 1000UL) / TICK_TIME_NS) * 1000UL;
	uint32_t Local_u32UnderflowNumbers = Local_u32TicksNumber / TIMER_TOP_VALUE;
	uint32_t Local_u32ReloadValue;

	/* Initialize the SysTick if it's not initialized */
	if (!IsSysTickInitialized)
	{
		Systick_Init();
	}

	do
	{
		/* Calculate the reload value and make sure that is in the possible range of the LOAD register */
		Local_u32ReloadValue = Local_u32TicksNumber % (TIMER_TOP_VALUE + 1UL);
		/* Write the reload value to LOAD register */
		SYSTICK->LOAD = Local_u32ReloadValue;

		/* Decrement the number of total underflows if one occurs */
		if ((FLAG_UP == Local_u8FlagState) && (ZERO_UNDERFLOWS != Local_u32UnderflowNumbers))
		{
			Local_u32UnderflowNumbers--;
			/* Decrement the number of ticks by the timer top value that is needed if the ticks number is greater than the top value */
			Local_u32TicksNumber -= TIMER_TOP_VALUE;
		}
		/* Get the count flag */
		Local_u8FlagState = GET_BIT(SYSTICK->CTRL, COUNTFLAG_POS);
	} while ((FLAG_DOWN == Local_u8FlagState) || (ZERO_UNDERFLOWS != Local_u32UnderflowNumbers));

	return;
}

void Systick_DelayUs(uint32_t Copy_u32DelayUs)
{
	uint8_t Local_u8FlagState = FLAG_DOWN;
	uint32_t Local_u32TicksNumber = (Copy_u32DelayUs * 1000UL) / TICK_TIME_NS;
	uint32_t Local_u32UnderflowNumbers = Local_u32TicksNumber / TIMER_TOP_VALUE;
	uint32_t Local_u32ReloadValue;

	/* Initialize the SysTick if it's not initialized */
	if (!IsSysTickInitialized)
	{
		Systick_Init();
	}

	do
	{
		/* Calculate the reload value and make sure that is in the possible range of the LOAD register */
		Local_u32ReloadValue = Local_u32TicksNumber % (TIMER_TOP_VALUE + 1UL);
		/* Write the reload value to LOAD register */
		SYSTICK->LOAD = Local_u32ReloadValue;

		/* Decrement the number of total underflows if one occurs */
		if ((FLAG_UP == Local_u8FlagState) && (ZERO_UNDERFLOWS != Local_u32UnderflowNumbers))
		{
			Local_u32UnderflowNumbers--;
			/* Decrement the number of ticks by the timer top value that is needed if the ticks number is greater than the top value */
			Local_u32TicksNumber -= TIMER_TOP_VALUE;
		}
		/* Get the count flag */
		Local_u8FlagState = GET_BIT(SYSTICK->CTRL, COUNTFLAG_POS);
	} while ((FLAG_DOWN == Local_u8FlagState) || (ZERO_UNDERFLOWS != Local_u32UnderflowNumbers));

	return;
}
