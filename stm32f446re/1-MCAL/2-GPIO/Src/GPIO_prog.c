/************************************************************************************
 * @file GPIO_prog.c
 * @author Musa Mahmoud
 * @brief The GPIO main source file, including functions' definition
 *
 */

#include <stdint.h>
#include "stm32f446xx.h"
#include "ErrType.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"
#include "GPIO_prv.h"


static GPIO_RegDef_t *GPIOPort[GPIO_PERIPHERLA_NUM] = {GPIOA, GPIOB , GPIOC, GPIOD, GPIOE, GPIOF, GPIOG, GPIOH};


/******************************************************************
 * @fn GPIO_u8PinInit
 * @brief The function initialize the GPIO pin according to the input parameters
 * @param[in] PinConfig : The initialization values of the pin
 * @retval ErrorStatus
 *
 */
uint8_t GPIO_u8PinInit(const GPIO_PinConfig_t *PinConfig)
{
	uint8_t Local_u8ErrorState = OK;

	if(PinConfig != NULL)
	{
		if((PinConfig->Port <= PORTH) && (PinConfig->PinNum <= PIN15) && (PinConfig->Mode <= ANALOG) && (PinConfig->Speed <= HIGH) && (PinConfig->OutputType <= OPEN_DRAIN) && (PinConfig->PullType <= PULLDOWN) && (PinConfig->AltFunc <= AF15))
		{
			/* Select GPIO mode : Input, Output, Analog, Alternate function */
			(GPIOPort[PinConfig->Port])->MODER &= ~(MODER_MASK << ((PinConfig->PinNum) * MODER_PIN_ACCESS)); /* Clear the mode bits */
			(GPIOPort[PinConfig->Port])->MODER |= ((PinConfig->Mode) << ((PinConfig->PinNum) * MODER_PIN_ACCESS));

			/* Select GPIO pull state : Pull-up, Pull-down, NoPull */
			(GPIOPort[PinConfig->Port])->PUPDR &= ~(PUPDR_MASK << ((PinConfig->PinNum) * PUPDR_PIN_ACCESS));
			(GPIOPort[PinConfig->Port])->PUPDR |= ((PinConfig->PullType) << ((PinConfig->PinNum) * PUPDR_PIN_ACCESS));

			/* Select GPIO output type & output speed in case of general purpose output or alternate function */
			if((PinConfig->Mode == OUTPUT) || (PinConfig->Mode == ALTERNATE_FUNCTION))
			{
				/* Select GPIO output type : PushPull, Open drain */
				(GPIOPort[PinConfig->Port])->OTYPER &= ~(OTYPER_MASK << (PinConfig->PinNum));
				(GPIOPort[PinConfig->Port])->OTYPER |= ((PinConfig->OutputType) << (PinConfig->PinNum));

				/* Select GPIO output speed : Low, Medium, Fast, High */
				(GPIOPort[PinConfig->Port])->OSPEEDR &= ~(OSPEEDR_MASK << ((PinConfig->PinNum) * OSPEEDR_PIN_ACCESS));
				(GPIOPort[PinConfig->Port])->OSPEEDR |= ((PinConfig->Speed) << ((PinConfig->PinNum) * OSPEEDR_PIN_ACCESS));
			}

			/* Select GPIO pin alternate function */
			if(PinConfig->Mode == ALTERNATE_FUNCTION)
			{
				uint8_t Local_u8RegNum = (PinConfig->PinNum) / AFR_PIN_SHIFTING;
				uint8_t Local_u8BitNum = (PinConfig->PinNum) % AFR_PIN_SHIFTING;

				(GPIOPort[PinConfig->Port])->AFR[Local_u8RegNum] &= ~(AFR_MASK << (Local_u8BitNum * AFR_PIN_ACCESS));
				(GPIOPort[PinConfig->Port])->AFR[Local_u8RegNum] |= ((PinConfig->AltFunc << (Local_u8BitNum * AFR_PIN_ACCESS)));
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


/******************************************************************
 * @fn GPIO_u8SetPinValue
 * @brief The function outputs a certain value on an output pin
 * @param[in] Port : The port number, get options @Port_t enum
 * @param[in] PinNum : The pin number, get options @Pin_t enum
 * @param[in] PinVal : The pin output value, get options @PinVal_t enum
 * @retval ErrorStatus
 *
 */
uint8_t GPIO_u8SetPinValue(Port_t Port, Pin_t PinNum, PinVal_t PinVal)
{
	uint8_t Local_u8ErrorState = OK;

	if((Port <= PORTH) && (PinNum <= PIN15))
	{
		if(PinVal == PIN_LOW)
		{
			// GPIOPort[Port]->ODR &= ~(1 << PinNum);
			GPIOPort[Port]->BSRR = (1 << (BSRR_RESET_POS + PinNum));
		}
		else if(PinVal == PIN_HIGH)
		{
			// GPIOPort[Port]->ODR |= (1 << PinNum);
			GPIOPort[Port]->BSRR = (1 << (PinNum));
		}
		else
		{
			Local_u8ErrorState = NOK;
		}
	}
	else
	{
		Local_u8ErrorState = NOK;
	}

	return Local_u8ErrorState;
}


/******************************************************************
 * @fn GPIO_u8TogglePinValue
 * @brief The function toggles a certain value on an output pin
 * @param[in] Port : The port number, get options @Port_t enum
 * @param[in] PinNum : The pin number, get options @Pin_t enum
 * @retval ErrorStatus
 *
 */
uint8_t GPIO_u8TogglePinValue(Port_t Port, Pin_t PinNum)
{
	uint8_t Local_u8ErrorState = OK;

	if ((Port > PORTH) || (Port < PORTA) || (PinNum > PIN15) || (PinNum < PIN0))
	{
		return NOK;
	}

	TOGGLE_BIT(GPIOPort[Port]->ODR, PinNum);

	return Local_u8ErrorState;
}


/******************************************************************
 * @fn GPIO_u8ReadPinValue
 * @brief The function reads a certain value on an input pin
 * @param[in] Port : The port number, get options @Port_t enum
 * @param[in] PinNum : The pin number, get options @Pin_t enum
 * @param[out] PinVal : The reading(value) of a certain pin, get options @PinVal_t enum
 * @retval ErrorStatus
 *
 */
uint8_t GPIO_u8ReadPinValue(Port_t Port, Pin_t PinNum, PinVal_t *PinVal)
{
	uint8_t Local_u8ErrorState = OK;

	if (NULL == PinVal)
	{
		return NULL_PTR_ERR;
	}

	if ((Port > PORTH) || (Port < PORTA) || (PinNum > PIN15) || (PinNum < PIN0))
	{
		return NOK;
	}

	*PinVal = GET_BIT(GPIOPort[Port]->IDR, PinNum);

	return Local_u8ErrorState;
}
