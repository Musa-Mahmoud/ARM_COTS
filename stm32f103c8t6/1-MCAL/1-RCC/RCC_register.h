/************************************************************************************/
/************************************************************************************/
/************************        Author: Musa Mahmoud        ************************/
/************************        Layer:  MCAL                ************************/
/************************        SWC:    RCC                 ************************/
/************************        Version:1.0                 ************************/
/************************************************************************************/
/************************************************************************************/

#ifndef RCC_REGISTER_H_
#define RCC_REGISTER_H_

/* RCC Base Address */
#define RCC_BASE_ADDRESS    0x40021000

/* Register Definition */
typedef struct
{
    uint32_t CR;            /* Clock control register                   */
    uint32_t CFGR;          /* Clock configuration register             */
    uint32_t CIR;           /* Clock interrupt register                 */
    uint32_t APB2RSTR;      /* APB2 peripheral reset register           */
    uint32_t APB1RSTR;      /* APB1 peripheral reset register           */
    uint32_t AHBENR;        /* AHB peripheral clock enable register     */
    uint32_t APB2ENR;       /* APB2 peripheral clock enable register    */
    uint32_t APB1ENR;       /* APB1 peripheral clock enable register    */
    uint32_t BDCR;          /* Backup domain control register           */
    uint32_t CSR;           /* Control/status register                  */
} RCC_Reg_t;


#define RCC ((volatile RCC_Reg_t*) RCC_BASE_ADDRESS)


#endif /* RCC_REGISTER_H_ End */