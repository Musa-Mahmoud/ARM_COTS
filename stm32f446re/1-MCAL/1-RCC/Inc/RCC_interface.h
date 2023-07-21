/************************************************************************************/
/************************************************************************************/
/************************        Author: Musa Mahmoud        ************************/
/************************        Layer:  MCAL                ************************/
/************************        SWC:    RCC                 ************************/
/************************        Version:1.0                 ************************/
/************************************************************************************/
/************************************************************************************/

#ifndef RCC_INTERFACE_H_
#define RCC_INTERFACE_H_


/* Types Definition */
typedef enum
{
    RCC_ErrorState_OK,
    RCC_ErrorState_NOT_OK,
    RCC_ErrorState_NULL_POINTER,
    RCC_ErrorState_WRONG_OPTION,
    RCC_ErrorState_TIMEOUT,
} RCC_ErrorState_t;

typedef enum
{
    RCC_CLOCKTYPE_HSE,
    RCC_CLOCKTYPE_HSI,
    RCC_CLOCKTYPE_PLL
} RCC_Clock_t;

typedef enum
{
    RCC_STATUSTYPE_ON,
    RCC_STATUSTYPE_OFF
} RCC_Status_t;

typedef enum
{
    RCC_AHB1_PERIPHERALTYPE_GPIOA,
    RCC_AHB1_PERIPHERALTYPE_GPIOB,
    RCC_AHB1_PERIPHERALTYPE_GPIOC,
    RCC_AHB1_PERIPHERALTYPE_GPIOD,
    RCC_AHB1_PERIPHERALTYPE_GPIOE,
    RCC_AHB1_PERIPHERALTYPE_GPIOF,
    RCC_AHB1_PERIPHERALTYPE_GPIOG,
    RCC_AHB1_PERIPHERALTYPE_GPIOH,
    RCC_AHB1_PERIPHERALTYPE_CRC = 12,
    RCC_AHB1_PERIPHERALTYPE_BKPSRAM = 18, 
    RCC_AHB1_PERIPHERALTYPE_DMA1 = 21,
    RCC_AHB1_PERIPHERALTYPE_DMA2,
    RCC_AHB1_PERIPHERALTYPE_OTGHS = 29,
    RCC_AHB1_PERIPHERALTYPE_OTGHSULPI
} RCC_AHB1_Peripheral_t;

typedef enum
{
    RCC_APB2_PERIPHERALTYPE_TIM1,
    RCC_APB2_PERIPHERALTYPE_TIM8,
    RCC_APB2_PERIPHERALTYPE_USART1=3,
    RCC_APB2_PERIPHERALTYPE_USART6,
    RCC_APB2_PERIPHERALTYPE_ADC1=6,
    RCC_APB2_PERIPHERALTYPE_ADC2,
    RCC_APB2_PERIPHERALTYPE_ADC3,
    RCC_APB2_PERIPHERALTYPE_SDIO=10,
    RCC_APB2_PERIPHERALTYPE_SPI1,
    RCC_APB2_PERIPHERALTYPE_SPI4,
    RCC_APB2_PERIPHERALTYPE_SYSCFG,
    RCC_APB2_PERIPHERALTYPE_EXTI,
    RCC_APB2_PERIPHERALTYPE_TIM9,
    RCC_APB2_PERIPHERALTYPE_TIM10,
    RCC_APB2_PERIPHERALTYPE_TIM11,
    RCC_APB2_PERIPHERALTYPE_SAI1=21,
    RCC_APB2_PERIPHERALTYPE_SAI2=23
} RCC_APB2_Peripheral_t;

typedef enum
{
    RCC_APB1_PERIPHERALTYPE_TIM2,
    RCC_APB1_PERIPHERALTYPE_TIM3,
    RCC_APB1_PERIPHERALTYPE_TIM4,
    RCC_APB1_PERIPHERALTYPE_TIM5,
    RCC_APB1_PERIPHERALTYPE_TIM6,
    RCC_APB1_PERIPHERALTYPE_TIM7,
    RCC_APB1_PERIPHERALTYPE_TIM12,
    RCC_APB1_PERIPHERALTYPE_TIM13,
    RCC_APB1_PERIPHERALTYPE_TIM14,
    RCC_APB1_PERIPHERALTYPE_WWDG = 11,
    RCC_APB1_PERIPHERALTYPE_SPI2 = 14,
    RCC_APB1_PERIPHERALTYPE_SPI3,
    RCC_APB1_PERIPHERALTYPE_USART2 = 17,
    RCC_APB1_PERIPHERALTYPE_USART3,
    RCC_APB1_PERIPHERALTYPE_USART4,
    RCC_APB1_PERIPHERALTYPE_USART5,
    RCC_APB1_PERIPHERALTYPE_I2C1,
    RCC_APB1_PERIPHERALTYPE_I2C2,
    RCC_APB1_PERIPHERALTYPE_USB,
    RCC_APB1_PERIPHERALTYPE_CAN = 25,
    RCC_APB1_PERIPHERALTYPE_BKP = 27,
    RCC_APB1_PERIPHERALTYPE_PWR,
    RCC_APB1_PERIPHERALTYPE_DAC
} RCC_APB1_Peripheral_t;

typedef enum 
{
    RCC_HSE_DIVFACTOR_DIV0,
    RCC_HSE_DIVFACTOR_DIV2
} RCC_HSE_DivFactor;

typedef enum 
{
    RCC_PLL_MULFACTOR_MUL2,
    RCC_PLL_MULFACTOR_MUL3,
    RCC_PLL_MULFACTOR_MUL4,
    RCC_PLL_MULFACTOR_MUL5,
    RCC_PLL_MULFACTOR_MUL6,
    RCC_PLL_MULFACTOR_MUL7,
    RCC_PLL_MULFACTOR_MUL8,
    RCC_PLL_MULFACTOR_MUL9,
    RCC_PLL_MULFACTOR_MUL10,
    RCC_PLL_MULFACTOR_MUL11,
    RCC_PLL_MULFACTOR_MUL12,
    RCC_PLL_MULFACTOR_MUL13,
    RCC_PLL_MULFACTOR_MUL14,
    RCC_PLL_MULFACTOR_MUL15,
    RCC_PLL_MULFACTOR_MUL16
} RCC_PLL_MulFactor;

typedef enum 
{
    RCC_PLL_CLKSRC_HSI,
    RCC_PLL_CLKSRC_HSE
} RCC_PLL_ClkSrc_t;



/* RCC Function Prototypes*/
RCC_ErrorState_t RCC_SetClkSts(RCC_Clock_t Copy_ClockType, RCC_Status_t Copy_StatusType);

RCC_ErrorState_t RCC_SetSysClk(RCC_Clock_t Copy_ClockType);

RCC_ErrorState_t RCC_SetHSEConfig(RCC_HSE_DivFactor Copy_DivFactor);

RCC_ErrorState_t RCC_SetPLLConfig(RCC_PLL_MulFactor Copy_PllMulFactor, RCC_PLL_ClkSrc_t Copy_PllSource);

RCC_ErrorState_t RCC_AHB1EnableClock(RCC_AHB1_Peripheral_t Copy_Ahb1PeripheralName);

RCC_ErrorState_t RCC_AHB1DisableClock(RCC_AHB1_Peripheral_t Copy_Ahb1PeripheralName);

RCC_ErrorState_t RCC_APB1EnableClock(RCC_APB1_Peripheral_t Copy_Apb1PeripheralName);

RCC_ErrorState_t RCC_APB1DisableClock(RCC_APB1_Peripheral_t Copy_Apb1PeripheralName);

RCC_ErrorState_t RCC_APB2EnableClock(RCC_APB2_Peripheral_t Copy_Apb2PeripheralName);

RCC_ErrorState_t RCC_APB2DisableClock(RCC_APB2_Peripheral_t Copy_Apb2PeripheralName);


#endif /* RCC_INTERFACE_H_ End */