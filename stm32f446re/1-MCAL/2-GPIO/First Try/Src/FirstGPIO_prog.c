// /************************************************************************************/
// /************************************************************************************/
// /************************        Author: Musa Mahmoud        ************************/
// /************************        Layer:  MCAL                ************************/
// /************************        SWC:    GPIO                ************************/
// /************************        Version:1.0                 ************************/
// /************************************************************************************/
// /************************************************************************************/


// #include <stdint.h>
// #include "../../4-LIB/stm32f446xx.h"
// #include "../../4-LIB/BIT_MATH.h"
// #include "FirstGPIO_interface.h"
// #include "FirstGPIO_prv.h"


// uint8_t static IsPinConfigValid(const PinConfig_t *PinConfig)
// {
//     if(NULL == PinConfig)
//     {
//         return NOT_VALID;
//     }

//     if((PinConfig->Port > PORTH) || (PinConfig->Port < PORTA)
//         || (PinConfig->PinNum > PIN15) || (PinConfig->PinNum < PIN0)
//         || (PinConfig->Mode > ANALOG) || (PinConfig->Mode < INPUT)
//         || (PinConfig->Speed > HIGH) || (PinConfig->Speed < LOW)
//         || (PinConfig->OutputType > OPEN_DRAIN) || (PinConfig->OutputType < PUSH_PULL)
//         || (PinConfig->PullType > PULLDOWN) || (PinConfig->PullType < NOPULL)
//         || (PinConfig->AltFunc > AF15) || (PinConfig->AltFunc < AF0))
//     {
//         return NOT_VALID;
//     }

//     return VALID;
// }


// uint8_t GPIO_u8PinInit(const PinConfig_t *PinConfig)
// {
//     GPIO_RegDef_t *Local_SelectedGpio = (GPIO_RegDef_t*) ((uint32_t)GPIOA + (0x0400UL * PinConfig->Port));

//     if(NOT_VALID == IsPinConfigValid(PinConfig))
//     {
//         return GPIO_NOT_OK;
//     }

//     /* Clear the 2 bits of mode register for the configured pin number */
//     CLR_BITS(Local_SelectedGpio->MODER, (0x03UL << (2 * PinConfig->PinNum)));
//     /* Set the 2 bits of mode register with the configured mode  */
//     SET_BITS(Local_SelectedGpio->MODER, (PinConfig->Mode << (2 * PinConfig->PinNum)));

//     if(OUTPUT == PinConfig->Mode || ALTERNATE_FUNCTION == PinConfig->Mode)
//     {
//         /* Clear the bit of port output type register for the configured pin number */
//         CLR_BITS(Local_SelectedGpio->OTYPER, (0x01UL << (PinConfig->PinNum)));
//         /* Set the bit of port output type register with the configured type */
//         SET_BITS(Local_SelectedGpio->OTYPER, (PinConfig->OutputType << (PinConfig->PinNum)));
//     }

//     if(OUTPUT == PinConfig->Mode || ALTERNATE_FUNCTION == PinConfig->Mode)
//     {
//         /* Clear the 2 bits of port output speed register for the configured pin number */
//         CLR_BITS(Local_SelectedGpio->OSPEEDR, (0x03UL << (2 * PinConfig->PinNum)));
//         /* Set the 2 bits of port output speed register with the configured speed */
//         SET_BITS(Local_SelectedGpio->OSPEEDR, (PinConfig->Speed << (2 * PinConfig->PinNum)));
//     }

//     /* Clear the 2 bits of port pull-up/pull-down register for the configured pin number */
//     CLR_BITS(Local_SelectedGpio->PUPDR, (0x03UL << (2 * PinConfig->PinNum)));
//     /* Set the 2 bits of port pull-up/pull-down register with the configured pull type */
//     SET_BITS(Local_SelectedGpio->PUPDR, (PinConfig->PullType << (2 * PinConfig->PinNum)));

//     /* Clear the 4 bits of alternate function register for the configured pin number */
//     CLR_BITS(Local_SelectedGpio->AFR[PinConfig->AltFunc >> 0x03UL], (0x0fUL << (4 * (PinConfig->PinNum % 8))));
//     /* Set the 4 bits of alternate function register with the configured alternate function */
//     SET_BITS(Local_SelectedGpio->AFR[PinConfig->AltFunc >> 0x03UL], ((0x07UL & PinConfig->AltFunc) << (4 * PinConfig->PinNum)));

//     return GPIO_OK;
// }


// uint8_t GPIO_u8SetPinValue(Port_t Port, Pin_t PinNum, PinVal_t PinVal)
// {

// }


// uint8_t GPIO_u8TogglePinValue(Port_t Port, Pin_t PinNum)
// {

// }


// uint8_t GPIO_u8ReadPinValue(Port_t Port, Pin_t PinNum, PinVal_t *PinVal)
// {

// }
