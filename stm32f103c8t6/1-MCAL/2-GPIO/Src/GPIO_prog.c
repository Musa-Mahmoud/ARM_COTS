/************************************************************************************
 * @file GPIO_prog.c
 * @author Musa Mahmoud
 * @brief The GPIO main source file, including functions' definition
 *
 */

#include <stdint.h>
#include "stm32f103xx.h"
#include "ErrType.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"
#include "GPIO_prv.h"


static GPIO_RegDef_t *GPIOPort[GPIO_PERIPHERLA_NUM] = {GPIOA, GPIOB , GPIOC, GPIOD, GPIOE};


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
		if((PinConfig->Port <= GPIO_PORTE) && (PinConfig->PinNum <= GPIO_PIN15) && (PinConfig->Mode <= GPIO_OUTPUT_50MHZ) && (PinConfig->PinCnf <= GPIO_ALT_FUNC_OPEN_DRAIN) && (PinConfig->PinInitValue <= GPIO_PIN_HIGH) && (PinConfig->PullType <= GPIO_PULLUP))
		{
			/* Select GPIO mode : Input, Output 10MHz, Output 2MHz, Output 50MHz */
			(GPIOPort[PinConfig->Port])->CR[CR_REG_NUM] &= ~(MODE_MASK << (CR_BIT_NUM * MODE_PIN_ACCESS)); /* Clear the mode bits */
			(GPIOPort[PinConfig->Port])->CR[CR_REG_NUM] |= ((PinConfig->Mode) << (CR_BIT_NUM * MODE_PIN_ACCESS));

			/* Select GPIO configuration :  Input -> Analog, Floating, Input pulled up/down 
											Output -> GP output push-pull, GP output Open-drain, AF output Push-pull, AF output Open-drain */
			(GPIOPort[PinConfig->Port])->CR[CR_REG_NUM] &= ~(CNF_MASK << ((CR_BIT_NUM * CNF_PIN_ACCESS) + CNF_POS)); /* Clear the cnf bits */
			(GPIOPort[PinConfig->Port])->CR[CR_REG_NUM] |= ((PinConfig->PinCnf) << ((CR_BIT_NUM * CNF_PIN_ACCESS ) + CNF_POS));

			/* Select GPIO pin pulling type(if input) */
			if((GPIO_INPUT == PinConfig->Mode && GPIO_INPUT_PULL_UP_DOWN == PinConfig->PinCnf))
			{
				uint8_t Local_u8ShiftAmount = (GPIO_PULLUP == PinConfig->PullType)? (PinConfig->PinNum) : (PinConfig->PinNum + BSRR_RESET_POS);

				(GPIOPort[PinConfig->Port])->BSRR = (1U << Local_u8ShiftAmount);
			}
			/* Select GPIO pin initial value(if output) */
			else if((GPIO_OUTPUT_PUSH_PULL == PinConfig->PinCnf) || (GPIO_OUTPUT_OPEN_DRAIN == PinConfig->PinCnf))
			{
				uint8_t Local_u8ShiftAmount = (GPIO_PIN_HIGH == PinConfig->PinInitValue)? (PinConfig->PinNum) : (PinConfig->PinNum + BSRR_RESET_POS);

				(GPIOPort[PinConfig->Port])->BSRR = (1U << Local_u8ShiftAmount);
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

	if((Port <= GPIO_PORTE) && (PinNum <= GPIO_PIN15))
	{
		if(PinVal == GPIO_PIN_LOW)
		{
			// GPIOPort[Port]->ODR &= ~(1 << PinNum);
			GPIOPort[Port]->BSRR = (1U << (BSRR_RESET_POS + PinNum));
		}
		else if(PinVal == GPIO_PIN_HIGH)
		{
			// GPIOPort[Port]->ODR |= (1 << PinNum);
			GPIOPort[Port]->BSRR = (1U << (PinNum));
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

	if ((Port > GPIO_PORTE) || (Port < GPIO_PORTA) || (PinNum > GPIO_PIN15) || (PinNum < GPIO_PIN0))
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

	if ((Port > GPIO_PORTE) || (Port < GPIO_PORTA) || (PinNum > GPIO_PIN15) || (PinNum < GPIO_PIN0))
	{
		return NOK;
	}

	*PinVal = GET_BIT(GPIOPort[Port]->IDR, PinNum);

	return Local_u8ErrorState;
}
