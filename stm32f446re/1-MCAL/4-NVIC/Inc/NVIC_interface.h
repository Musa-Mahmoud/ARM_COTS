#ifndef NVIC_INTERFACE_H_
#define NVIC_INTERFACE_H_

#include <stdint.h>

typedef enum
{
    NOT_PENDING = 0,
    PENDING
} PendingFlag_t;

typedef enum
{
    NOT_ACTIVE = 0,
    ACTIVE
} ActiveFlag_t;

// typedef enum
// {
//     LEVEL0 = 0,     /* Highest Priority */
//     LEVEL1,
//     LEVEL2,
//     LEVEL3,
//     LEVEL4,
//     LEVEL5,
//     LEVEL6,
//     LEVEL7,
//     LEVEL8,
//     LEVEL9,
//     LEVEL10,
//     LEVEL11,
//     LEVEL12,
//     LEVEL13,
//     LEVEL14,
//     LEVEL15     /* Lowest Priority */
// } PriorityLevel_t;

typedef enum
{
    WWDG_IRQ_NUMBER = 0,                /* Window WatchDog Interrupt                                           */
    PVD_IRQ_NUMBER,                     /* PVD through EXTI Line detection Interrupt                           */
    TAMP_STAMP_IRQ_NUMBER,              /* Tamper and TimeStamp interrupts through the EXTI line               */
    RTC_WKUP_IRQ_NUMBER,                /* RTC Wakeup interrupt through the EXTI line                          */
    FLASH_IRQ_NUMBER,                   /* FLASH global Interrupt                                              */
    RCC_IRQ_NUMBER,                     /* RCC global Interrupt                                                */
    EXTI0_IRQ_NUMBER,                   /* EXTI Line0 Interrupt                                                */
    EXTI1_IRQ_NUMBER,                   /* EXTI Line1 Interrupt                                                */
    EXTI2_IRQ_NUMBER,                   /* EXTI Line2 Interrupt                                                */
    EXTI3_IRQ_NUMBER,                   /* EXTI Line3 Interrupt                                                */
    EXTI4_IRQ_NUMBER,                   /* EXTI Line4 Interrupt                                                */
    DMA1_STREAM0_IRQ_NUMBER,            /* DMA1 Stream 0 global Interrupt                                      */
    DMA1_STREAM1_IRQ_NUMBER,            /* DMA1 Stream 1 global Interrupt                                      */
    DMA1_STREAM2_IRQ_NUMBER,            /* DMA1 Stream 2 global Interrupt                                      */
    DMA1_STREAM3_IRQ_NUMBER,            /* DMA1 Stream 3 global Interrupt                                      */
    DMA1_STREAM4_IRQ_NUMBER,            /* DMA1 Stream 4 global Interrupt                                      */
    DMA1_STREAM5_IRQ_NUMBER,            /* DMA1 Stream 5 global Interrupt                                      */
    DMA1_STREAM6_IRQ_NUMBER,            /* DMA1 Stream 6 global Interrupt                                      */
    ADC_IRQ_NUMBER,                     /* ADC1, ADC2 and ADC3 global Interrupts                               */
    CAN1_TX_IRQ_NUMBER,                 /* CAN1 TX Interrupt                                                   */
    CAN1_RX0_IRQ_NUMBER,                /* CAN1 RX0 Interrupt                                                  */
    CAN1_RX1_IRQ_NUMBER,                /* CAN1 RX1 Interrupt                                                  */
    CAN1_SCE_IRQ_NUMBER,                /* CAN1 SCE Interrupt                                                  */
    EXTI9_5_IRQ_NUMBER,                 /* External Line[9:5] Interrupts                                       */
    TIM1_BRK_TIM9_IRQ_NUMBER,           /* TIM1 Break interrupt and TIM9 global interrupt                      */
    TIM1_UP_TIM10_IRQ_NUMBER,           /* TIM1 Update Interrupt and TIM10 global interrupt                    */
    TIM1_TRG_COM_TIM11_IRQ_NUMBER,      /* TIM1 Trigger and Commutation Interrupt and TIM11 global interrupt   */
    TIM1_CC_IRQ_NUMBER,                 /* TIM1 Capture Compare Interrupt                                      */
    TIM2_IRQ_NUMBER,                    /* TIM2 global Interrupt                                               */
    TIM3_IRQ_NUMBER,                    /* TIM3 global Interrupt                                               */
    TIM4_IRQ_NUMBER,                    /* TIM4 global Interrupt                                               */
    I2C1_EV_IRQ_NUMBER,                 /* I2C1 Event Interrupt                                                */
    I2C1_ER_IRQ_NUMBER,                 /* I2C1 Error Interrupt                                                */
    I2C2_EV_IRQ_NUMBER,                 /* I2C2 Event Interrupt                                                */
    I2C2_ER_IRQ_NUMBER,                 /* I2C2 Error Interrupt                                                */
    SPI1_IRQ_NUMBER,                    /* SPI1 global Interrupt                                               */
    SPI2_IRQ_NUMBER,                    /* SPI2 global Interrupt                                               */
    USART1_IRQ_NUMBER,                  /* USART1 global Interrupt                                             */
    USART2_IRQ_NUMBER,                  /* USART2 global Interrupt                                             */
    USART3_IRQ_NUMBER,                  /* USART3 global Interrupt                                             */
    EXTI15_10_IRQ_NUMBER,               /* External Line[15:10] Interrupts                                     */
    RTC_ALARM_IRQ_NUMBER,               /* RTC Alarm (A and B) through EXTI Line Interrupt                     */
    OTG_FS_WKUP_IRQ_NUMBER,             /* USB OTG FS Wakeup through EXTI line interrupt                       */
    TIM8_BRK_TIM12_IRQ_NUMBER,          /* TIM8 Break Interrupt and TIM12 global interrupt                     */
    TIM8_UP_TIM13_IRQ_NUMBER,           /* TIM8 Update Interrupt and TIM13 global interrupt                    */
    TIM8_TRG_COM_TIM14_IRQ_NUMBER,      /* TIM8 Trigger and Commutation Interrupt and TIM14 global interrupt   */
    TIM8_CC_IRQ_NUMBER,                 /* TIM8 Capture Compare global interrupt                               */
    DMA1_STREAM7_IRQ_NUMBER,            /* DMA1 Stream7 Interrupt                                              */
    FMC_IRQ_NUMBER,                     /* FMC global Interrupt                                                */
    SDIO_IRQ_NUMBER,                    /* SDIO global Interrupt                                               */
    TIM5_IRQ_NUMBER,                    /* TIM5 global Interrupt                                               */
    SPI3_IRQ_NUMBER,                    /* SPI3 global Interrupt                                               */
    UART4_IRQ_NUMBER,                   /* UART4 global Interrupt                                              */
    UART5_IRQ_NUMBER,                   /* UART5 global Interrupt                                              */
    TIM6_DAC_IRQ_NUMBER,                /* TIM6 global and DAC1&2 underrun error  interrupts                   */
    TIM7_IRQ_NUMBER,                    /* TIM7 global interrupt                                               */
    DMA2_STREAM0_IRQ_NUMBER,            /* DMA2 Stream 0 global Interrupt                                      */
    DMA2_STREAM1_IRQ_NUMBER,            /* DMA2 Stream 1 global Interrupt                                      */
    DMA2_STREAM2_IRQ_NUMBER,            /* DMA2 Stream 2 global Interrupt                                      */
    DMA2_STREAM3_IRQ_NUMBER,            /* DMA2 Stream 3 global Interrupt                                      */
    DMA2_STREAM4_IRQ_NUMBER,            /* DMA2 Stream 4 global Interrupt                                      */
    CAN2_TX_IRQ_NUMBER = 63,            /* CAN2 TX Interrupt                                                   */
    CAN2_RX0_IRQ_NUMBER,                /* CAN2 RX0 Interrupt                                                  */
    CAN2_RX1_IRQ_NUMBER,                /* CAN2 RX1 Interrupt                                                  */
    CAN2_SCE_IRQ_NUMBER,                /* CAN2 SCE Interrupt                                                  */
    OTG_FS_IRQ_NUMBER,                  /* USB OTG FS global Interrupt                                         */
    DMA2_STREAM5_IRQ_NUMBER,            /* DMA2 Stream 5 global interrupt                                      */
    DMA2_STREAM6_IRQ_NUMBER,            /* DMA2 Stream 6 global interrupt                                      */
    DMA2_STREAM7_IRQ_NUMBER,            /* DMA2 Stream 7 global interrupt                                      */
    USART6_IRQ_NUMBER,                  /* USART6 global interrupt                                             */
    I2C3_EV_IRQ_NUMBER,                 /* I2C3 event interrupt                                                */
    I2C3_ER_IRQ_NUMBER,                 /* I2C3 error interrupt                                                */
    HS_EP1_OUT_IRQ_NUMBER,              /* USB OTG HS End Point 1 Out global interrupt                         */
    OTG_HS_EP1_IN_IRQ_NUMBER,           /* USB OTG HS End Point 1 In global interrupt                          */
    OTG_HS_WKUP_IRQ_NUMBER,             /* USB OTG HS Wakeup through EXTI interrupt                            */
    OTG_HS_IRQ_NUMBER,                  /* USB OTG HS global interrupt                                         */
    DCMI_IRQ_NUMBER,                    /* DCMI global interrupt                                               */
    FPU_IRQ_NUMBER = 81,                /* FPU global interrupt                                                */
    SPI4_IRQ_NUMBER = 84,               /* SPI4 global Interrupt                                               */
    SAI1_IRQ_NUMBER = 87,               /* SAI1 global Interrupt                                               */
    SAI2_IRQ_NUMBER = 91,               /* SAI2 global Interrupt                                               */
    QUADSPI_IRQ_NUMBER,                 /* QuadSPI global Interrupt                                            */
    HDMI_CEC_IRQ_NUMBER,                /* CEC global Interrupt                                                */
    SPDIF_RX_IRQ_NUMBER,                /* SPDIF-RX global Interrupt                                           */
    FMPI2C1_IRQ_NUMBER,                 /* FMPI2C1 Event Interrupt                                             */
    FMPI2C1_ERROR_IRQ_NUMBER            /* FMPI2C1 Error Interrupt                                             */
} IRQ_Number_t;


uint8_t NVIC_u8EnableIRQ(IRQ_Number_t Copy_IRQNumber);

uint8_t NVIC_u8DisableIRQ(IRQ_Number_t Copy_IRQNumber);

uint8_t NVIC_u8SetPendingIRQ(IRQ_Number_t Copy_IRQNumber);

uint8_t NVIC_u8ClearPendingIRQ(IRQ_Number_t Copy_IRQNumber);

uint8_t NVIC_u8GetPendingIRQ(IRQ_Number_t Copy_IRQNumber, PendingFlag_t *Copy_pPendingFlag);

uint8_t NVIC_u8GetActiveIRQ(IRQ_Number_t Copy_IRQNumber, ActiveFlag_t *Copy_pActiveFlag);

uint8_t NVIC_u8SetIRQPriority(IRQ_Number_t Copy_IRQNumber, uint8_t Copy_u8Priority);

uint8_t NVIC_u8GetIRQPriority(IRQ_Number_t Copy_IRQNumber, uint8_t *Copy_pu8Priority);

#endif /* NVIC_INTERFACE_H_ */