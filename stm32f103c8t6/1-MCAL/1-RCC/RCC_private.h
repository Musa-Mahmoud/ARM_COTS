/************************************************************************************/
/************************************************************************************/
/************************        Author: Musa Mahmoud        ************************/
/************************        Layer:  MCAL                ************************/
/************************        SWC:    RCC                 ************************/
/************************        Version:1.0                 ************************/
/************************************************************************************/
/************************************************************************************/

#ifndef RCC_PRIVATE_H_
#define RCC_PRIVATE_H_

/* Magic Numbers Definition */
#define TIMEOUT_AMOUNT      1000
#define READY               1
#define NOT_READY           0

/* Bit Definition for RCC_CR Register */
#define RCC_CR_PLLRDY_POS   (25U)
#define RCC_CR_PLLRDY_MSK   (0x1UL << RCC_CR_PLLRDY_POS)
#define RCC_CR_PLLRDY       RCC_CR_PLLRDY_MSK   

#define RCC_CR_PLLON_POS    (24U)
#define RCC_CR_PLLON_MSK    (0x1UL << RCC_CR_PLLON_POS)
#define RCC_CR_PLLON        RCC_CR_PLLON_MSK   

#define RCC_CR_HSEBYP_POS   (18U)
#define RCC_CR_HSEBYP_MSK   (0x1UL << RCC_CR_HSEBYP_POS)
#define RCC_CR_HSEBYP       RCC_CR_HSEBYP_MSK   

#define RCC_CR_HSERDY_POS   (17U)
#define RCC_CR_HSERDY_MSK   (0x1UL << RCC_CR_HSERDY_POS)
#define RCC_CR_HSERDY       RCC_CR_HSERDY_MSK   

#define RCC_CR_HSEON_POS    (16U)
#define RCC_CR_HSEON_MSK    (0x1UL << RCC_CR_HSEON_POS)
#define RCC_CR_HSEON        RCC_CR_HSEON_MSK   

#define RCC_CR_HSIRDY_POS   (1U)
#define RCC_CR_HSIRDY_MSK   (0x1UL << RCC_CR_HSIRDY_POS)
#define RCC_CR_HSIRDY       RCC_CR_HSIRDY_MSK   

#define RCC_CR_HSION_POS    (0U)
#define RCC_CR_HSION_MSK    (0x1UL << RCC_CR_HSION_POS)
#define RCC_CR_HSION        RCC_CR_HSION_MSK   

/* Bit Definition for RCC_CFGR Register */
#define RCC_CFGR_PLLMUL_POS     (18U)
#define RCC_CFGR_PLLMUL_MSK     (0xfUL << RCC_CFGR_PLLMUL_POS)
#define RCC_CFGR_PLLMUL_BIT0    (0x1UL << RCC_CFGR_PLLMUL_POS)
#define RCC_CFGR_PLLMUL_BIT1    (0x2UL << RCC_CFGR_PLLMUL_POS)
#define RCC_CFGR_PLLMUL_BIT2    (0x4UL << RCC_CFGR_PLLMUL_POS)
#define RCC_CFGR_PLLMUL_BIT3    (0x8UL << RCC_CFGR_PLLMUL_POS)
#define RCC_CFGR_PLLMUL         RCC_CFGR_PLLMUL_MSK

#define RCC_CFGR_PLLXTPRE_POS     (17U)
#define RCC_CFGR_PLLXTPRE_MSK     (0x1UL << RCC_CFGR_PLLXTPRE_POS)
#define RCC_CFGR_PLLXTPRE         RCC_CFGR_PLLXTPRE_MSK

#define RCC_CFGR_PLLSRC_POS     (16U)
#define RCC_CFGR_PLLSRC_MSK     (0x1UL << RCC_CFGR_PLLSRC_POS)
#define RCC_CFGR_PLLSRC         RCC_CFGR_PLLSRC_MSK

#define RCC_CFGR_SWS_POS     (2U)
#define RCC_CFGR_SWS_MSK     (0x3UL << RCC_CFGR_SWS_POS)
#define RCC_CFGR_SWS_BIT0    (0x1UL << RCC_CFGR_SWS_POS)
#define RCC_CFGR_SWS_BIT1    (0x2UL << RCC_CFGR_SWS_POS)
#define RCC_CFGR_SWS         RCC_CFGR_SWS_MSK

#define RCC_CFGR_SW_POS     (0U)
#define RCC_CFGR_SW_MSK     (0x3UL << RCC_CFGR_SW_POS)
#define RCC_CFGR_SW_BIT0    (0x1UL << RCC_CFGR_SW_POS)
#define RCC_CFGR_SW_BIT1    (0x2UL << RCC_CFGR_SW_POS)
#define RCC_CFGR_SW         RCC_CFGR_SW_MSK

#endif /* RCC_PRIVATE_H_ End */