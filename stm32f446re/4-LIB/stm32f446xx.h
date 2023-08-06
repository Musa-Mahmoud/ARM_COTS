#ifndef STM32F446xx_H_
#define STM32F446xx_H_


/**********************************     Various Memories Base Addresses     **********************************/

#define FLASH_BASE_ADDRESS      0x08000000UL
#define SRAM_BASE_ADDRESS       0x20000000UL
#define ROM_BASE_ADDRESS        0x1FFF0000UL


/**********************************     Core Peripheral Base Addresses     **********************************/

#define SYSTICK_BASE_ADDRESS    0xE000E010U

#define NVIC_BASE_ADDRESS       0xE000E100U

#define SCB_BASE_ADDRESS        0xE000ED00U


/**********************************     AHB1 Peripheral Base Addresses     **********************************/

#define GPIOA_BASE_ADDRESS      0x40020000U
#define GPIOB_BASE_ADDRESS      0x40020400U
#define GPIOC_BASE_ADDRESS      0x40020800U
#define GPIOD_BASE_ADDRESS      0X40020C00U
#define GPIOE_BASE_ADDRESS      0x40021000U
#define GPIOF_BASE_ADDRESS      0x40021400U
#define GPIOG_BASE_ADDRESS      0x40021800U
#define GPIOH_BASE_ADDRESS      0x40021C00U

#define RCC_BASE_ADDRESS        0x40023800U


/**********************************     AHB2 Peripheral Base Addresses     **********************************/


/**********************************     AHB3 Peripheral Base Addresses     **********************************/


/**********************************     APB1 Peripheral Base Addresses     **********************************/


/**********************************     APB2 Peripheral Base Addresses     **********************************/

#define SYSCFG_BASE_ADDRESS     0x40013800U
#define EXTI_BASE_ADDRESS       0x40013C00U


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
    volatile uint32_t MODER;                /* GPIO port mode register                                      */
    volatile uint32_t OTYPER;               /* GPIO port output type register                               */
    volatile uint32_t OSPEEDR;              /* GPIO port output speed register                              */
    volatile uint32_t PUPDR;                /* GPIO port pull-up/pull-down register                         */
    volatile uint32_t IDR;                  /* GPIO port input data register                                */
    volatile uint32_t ODR;                  /* GPIO port output data register                               */
    volatile uint32_t BSRR;                 /* GPIO port bit set/reset register                             */
    volatile uint32_t LCKR;                 /* GPIO port configuration lock register                        */
    volatile uint32_t AFR[2];               /* GPIO alternate function register(Low & High respectively)    */
} GPIO_RegDef_t;


/**********************************     RCC Register Definition Structure     **********************************/

typedef struct
{
    volatile uint32_t CR;                   /* RCC clock control register,                                   */
    volatile uint32_t PLLCFGR;              /* RCC PLL configuration register,                               */
    volatile uint32_t CFGR;                 /* RCC clock configuration register,                             */
    volatile uint32_t CIR;                  /* RCC clock interrupt register,                                 */
    volatile uint32_t AHB1RSTR;             /* RCC AHB1 peripheral reset register,                           */
    volatile uint32_t AHB2RSTR;             /* RCC AHB2 peripheral reset register,                           */
    volatile uint32_t AHB3RSTR;             /* RCC AHB3 peripheral reset register,                           */
    uint32_t      RESERVED0;     	        	/* Reserved, 0x1C                                                */
    volatile uint32_t APB1RSTR;             /* RCC APB1 peripheral reset register,                           */
    volatile uint32_t APB2RSTR;             /* RCC APB2 peripheral reset register,                           */
    uint32_t      RESERVED1[2];  	        	/* Reserved, 0x28-0x2C                                           */
    volatile uint32_t AHB1ENR;              /* RCC AHB1 peripheral clock register,                           */
    volatile uint32_t AHB2ENR;              /* RCC AHB2 peripheral clock register,                           */
    volatile uint32_t AHB3ENR;              /* RCC AHB3 peripheral clock register,                           */
    uint32_t      RESERVED2;     	        	/* Reserved, 0x3C                                                */
    volatile uint32_t APB1ENR;              /* RCC APB1 peripheral clock enable register,                    */
    volatile uint32_t APB2ENR;              /* RCC APB2 peripheral clock enable register,                    */
    uint32_t      RESERVED3[2];  	        	/* Reserved, 0x48-0x4C                                           */
    volatile uint32_t AHB1LPENR;            /* RCC AHB1 peripheral clock enable in low power mode register,  */
    volatile uint32_t AHB2LPENR;            /* RCC AHB2 peripheral clock enable in low power mode register,  */
    volatile uint32_t AHB3LPENR;            /* RCC AHB3 peripheral clock enable in low power mode register,  */
    uint32_t      RESERVED4;     	        	/* Reserved, 0x5C                                                */
    volatile uint32_t APB1LPENR;            /* RCC APB1 peripheral clock enable in low power mode register,  */
    volatile uint32_t APB2LPENR;            /* RCC APB2 peripheral clock enable in low power mode register,  */
    uint32_t      RESERVED5[2];  	        	/* Reserved, 0x68-0x6C                                           */
    volatile uint32_t BDCR;                 /* RCC Backup domain control register,                           */
    volatile uint32_t CSR;                  /* RCC clock control & status register,                          */
    uint32_t      RESERVED6[2];  	        	/* Reserved, 0x78-0x7C                                           */
    volatile uint32_t SSCGR;                /* RCC spread spectrum clock generation register,                */
    volatile uint32_t PLLI2SCFGR;           /* RCC PLLI2S configuration register,                            */
    volatile uint32_t PLLSAICFGR;           /* RCC PLLSAI configuration register,                            */
    volatile uint32_t DCKCFGR;              /* RCC Dedicated Clocks configuration register,                  */
    volatile uint32_t CKGATENR;             /* RCC Clocks Gated ENable Register,                             */
    volatile uint32_t DCKCFGR2;             /* RCC Dedicated Clocks configuration register 2,                */
} RCC_RegDef_t;


/**********************************     SYSCFG Register Definition Structure     **********************************/

typedef struct
{
    volatile uint32_t MEMRMP;               /* SYSCFG memory remap register                                     */
    volatile uint32_t PMC;                  /* SYSCFG peripheral mode configuration register                    */
    volatile uint32_t EXTICR[4];            /* SYSCFG external interrupt configuration register 1, 2, 3 and 4   */
    uint32_t        RESERVED0[2];           /* Reserved 8 bytes                                                 */
    volatile uint32_t CMPCR;                /* SYSCFG Compensation cell control register                        */
    uint32_t        RESERVED1[2];           /* Reserved 8 bytes                                                 */
    volatile uint32_t CFGR;                 /* SYSCFG configuration register                                    */
} SYSCFG_RegDef_t;


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
#define GPIOF               ((GPIO_RegDef_t*) GPIOF_BASE_ADDRESS)
#define GPIOG               ((GPIO_RegDef_t*) GPIOG_BASE_ADDRESS)
#define GPIOH               ((GPIO_RegDef_t*) GPIOH_BASE_ADDRESS)


/**********************************     RCC Peripheral Definition     **********************************/

#define RCC                 ((RCC_RegDef_t*) RCC_BASE_ADDRESS)


/**********************************     SYSCFG Peripheral Definition     **********************************/

#define SYSCFG              ((SYSCFG_RegDef_t*) SYSCFG_BASE_ADDRESS)


/**********************************     EXTI Peripheral Definition     **********************************/

#define EXTI                ((EXTI_RegDef_t*) EXTI_BASE_ADDRESS)


#endif
