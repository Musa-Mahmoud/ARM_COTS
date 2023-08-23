#ifndef STM32F446xx_H_
#define STM32F446xx_H_


/**********************************     Various Memories Base Addresses     **********************************/

#define FLASH_BASE_ADDRESS      0x08000000UL
#define SRAM_BASE_ADDRESS       0x20000000UL
#define ROM_BASE_ADDRESS        0x1FFFF000UL


/**********************************     Core Peripheral Base Addresses     **********************************/

#define SYSTICK_BASE_ADDRESS    0xE000E010U

#define NVIC_BASE_ADDRESS       0xE000E100U

#define SCB_BASE_ADDRESS        0xE000ED00U


/**********************************     AHB Peripheral Base Addresses     **********************************/

#define RCC_BASE_ADDRESS        0x40021000U

#define DMA1_BASE_ADDRESS       0x40020000U


/**********************************     APB1 Peripheral Base Addresses     **********************************/


/**********************************     APB2 Peripheral Base Addresses     **********************************/

#define GPIOA_BASE_ADDRESS      0x40010800U
#define GPIOB_BASE_ADDRESS      0x40010C00U
#define GPIOC_BASE_ADDRESS      0x40011000U
#define GPIOD_BASE_ADDRESS      0x40011400U
#define GPIOE_BASE_ADDRESS      0x40011800U

#define EXTI_BASE_ADDRESS       0x40010400U

#define AFIO_BASE_ADDRESS       0x40010000U


/**********************************     SYSTICK Register Definition Structure     **********************************/

typedef struct 
{
    volatile uint32_t CTRL;                 /* SYSTICK control and status register  */
    volatile uint32_t LOAD;                 /* SYSTICK reload value register        */
    volatile uint32_t VAL;                  /* SYSTICK current value register       */
    volatile uint32_t CALIB;                /* SYSTICK calibration value register   */
} SYSTICK_RegDef_t;


/**********************************     NVIC Register Definition Structure     **********************************/

typedef struct 
{
    volatile uint32_t ISER[8];              /* NVIC Interrupt Set-enable Registers       */
    uint32_t        RESERVED0[24];          /* Reserved 96 bytes                         */
    volatile uint32_t ICER[8];              /* NVIC Interrupt Clear-enable Registers     */
    uint32_t        RESERVED1[24];          /* Reserved 96 bytes                         */
    volatile uint32_t ISPR[8];              /* NVIC Interrupt Set-pending Registers      */
    uint32_t        RESERVED2[24];          /* Reserved 96 bytes                         */
    volatile uint32_t ICPR[8];              /* NVIC Interrupt Clear-pending Registers    */
    uint32_t        RESERVED3[24];          /* Reserved 96 bytes                         */
    volatile uint32_t IABR[8];              /* NVIC Interrupt Active Bit Registers       */
    uint32_t        RESERVED4[56];          /* Reserved 224 bytes                        */
    volatile uint8_t IPR[240];              /* NVIC Interrupt Priority Registers         */
    uint32_t        RESERVED5[643];         /* Reserved 2573 bytes                       */
    volatile uint32_t STIR;                 /* NVIC Software Trigger Interrupt Register  */
} NVIC_RegDef_t;


/**********************************     SCB Register Definition Structure     **********************************/

typedef struct 
{
    volatile uint32_t CPUID;                /* SCB CPUID Base Register                                                          */
    volatile uint32_t ICSR;                 /* SCB Interrupt Control and State Register                                         */
    volatile uint32_t VTOR;                 /* SCB Vector Table Offset Register                                                 */
    volatile uint32_t AIRCR;                /* SCB Application Interrupt and Reset Control Register                             */
    volatile uint32_t SCR;                  /* SCB System Control Register                                                      */
    volatile uint32_t CCR;                  /* SCB Configuration and Control Register                                           */
    volatile uint8_t SHPR[12];              /* SCB System Handler Priority Registers 1, 2 and 3                                 */
    volatile uint32_t SHCRS;                /* SCB System Handler Control and State Register                                    */
    volatile uint8_t MMSR;                  /* SCB Configurable Fault Status Register(CFSR): MemManage Fault Status Register    */
    volatile uint8_t BFSR;                  /* SCB Configurable Fault Status Register(CFSR): BusFault Status Register           */
    volatile uint16_t UFSR;                 /* SCB Configurable Fault Status Register(CFSR): UsageFault Status Register         */
    volatile uint32_t HFSR;                 /* SCB HardFault Status Register                                                    */
    uint32_t        RESERVED0;              /* Reserved 8 bytes                                                                 */
    volatile uint32_t MMAR;                 /* SCB MemManage Fault Address Register                                             */
    volatile uint32_t BFAR;                 /* SCB BusFault Address Register                                                    */
    volatile uint32_t AFSR;                 /* SCB Auxiliary Fault Status Register                                              */
} SCB_RegDef_t;


/**********************************     GPIO Register Definition Structure     **********************************/

typedef struct
{
    volatile uint32_t CR[2];                /* GPIO Port configuration register(low and high)               */
    volatile uint32_t IDR;                  /* GPIO port input data register                                */
    volatile uint32_t ODR;                  /* GPIO port output data register                               */
    volatile uint32_t BSRR;                 /* GPIO port bit set/reset register                             */
    volatile uint32_t BRR;                  /* GPIO port bit reset register                                 */
    volatile uint32_t LCKR;                 /* GPIO port configuration lock register                        */
} GPIO_RegDef_t;


/**********************************     RCC Register Definition Structure     **********************************/

typedef struct
{
    volatile uint32_t CR;            /* Clock control register                   */
    volatile uint32_t CFGR;          /* Clock configuration register             */
    volatile uint32_t CIR;           /* Clock interrupt register                 */
    volatile uint32_t APB2RSTR;      /* APB2 peripheral reset register           */
    volatile uint32_t APB1RSTR;      /* APB1 peripheral reset register           */
    volatile uint32_t AHBENR;        /* AHB peripheral clock enable register     */
    volatile uint32_t APB2ENR;       /* APB2 peripheral clock enable register    */
    volatile uint32_t APB1ENR;       /* APB1 peripheral clock enable register    */
    volatile uint32_t BDCR;          /* Backup domain control register           */
    volatile uint32_t CSR;           /* Control/status register                  */
} RCC_RegDef_t;


/**********************************     DMA Register Definition Structure     **********************************/

typedef struct
{
    volatile uint32_t ISR[2];               /* DMA interrupt status register(low and high)                                          */
    volatile uint32_t IFCR[2];              /* DMA interrupt flag clear register(low and high)                                      */
    volatile uint32_t SxR[8][6];            /* DMA stream x(0:7) registers: CR(configuration register), NDTR(number of data register),
                                                PAR(peripheral address register), M0AR(memory 0 address register),
                                                M1AR(memory 1 address register) and FCR(FIFO control register)                      */
} DMA_RegDef_t;


/**********************************     EXTI Register Definition Structure     **********************************/

typedef struct
{
    volatile uint32_t IMR;                  /* EXTI Interrupt mask register              */
    volatile uint32_t EMR;                  /* EXTI Event mask register                  */
    volatile uint32_t RTSR;                 /* EXTI Rising trigger selection register    */
    volatile uint32_t FTSR;                 /* EXTI Falling trigger selection register   */
    volatile uint32_t SWIER;                /* EXTI Software interrupt event register    */
    volatile uint32_t PR;                   /* EXTI Pending register                     */
} EXTI_RegDef_t;


/**********************************     AFIO Register Definition Structure     **********************************/

typedef struct
{
    volatile uint32_t EVCR;                 /* AFIO Event control register                                  */
    volatile uint32_t MAPR;                 /* AFIO AF remap and debug I/O configuration register           */
    volatile uint32_t EXTICR[4];            /* AFIO External interrupt configuration register 1, 2, 3 and 4 */
    uint32_t        RESERVED0;              /* Reserved 4 bytes                                                                 */
    volatile uint32_t MAPR2;                /* AFIO AF remap and debug I/O configuration register2          */
} AFIO_RegDef_t;


/**********************************     SYSTICK Peripheral Definition     **********************************/

#define SYSTICK             ((SYSTICK_RegDef_t*) SYSTICK_BASE_ADDRESS)


/**********************************     NVIC Peripheral Definition     **********************************/

#define NVIC                ((NVIC_RegDef_t*) NVIC_BASE_ADDRESS)


/**********************************     SCB Peripheral Definition     **********************************/

#define SCB                 ((SCB_RegDef_t*) SCB_BASE_ADDRESS)


/**********************************     GPIO Peripheral Definition     **********************************/

#define GPIOA               ((GPIO_RegDef_t*) GPIOA_BASE_ADDRESS)
#define GPIOB               ((GPIO_RegDef_t*) GPIOB_BASE_ADDRESS)
#define GPIOC               ((GPIO_RegDef_t*) GPIOC_BASE_ADDRESS)
#define GPIOD               ((GPIO_RegDef_t*) GPIOD_BASE_ADDRESS)
#define GPIOE               ((GPIO_RegDef_t*) GPIOE_BASE_ADDRESS)


/**********************************     RCC Peripheral Definition     **********************************/

#define RCC                 ((RCC_RegDef_t*) RCC_BASE_ADDRESS)


/**********************************     DMA Peripheral Definition     **********************************/

#define DMA1                ((DMA_RegDef_t*) DMA1_BASE_ADDRESS)


/**********************************     EXTI Peripheral Definition     **********************************/

#define EXTI                ((EXTI_RegDef_t*) EXTI_BASE_ADDRESS)


/**********************************     AFIO Peripheral Definition     **********************************/

#define AFIO                ((AFIO_RegDef_t*) AFIO_BASE_ADDRESS)

#endif
