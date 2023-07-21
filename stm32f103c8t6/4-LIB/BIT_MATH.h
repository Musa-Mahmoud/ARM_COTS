/************************************************************************************/
/************************************************************************************/
/************************        Author: Musa Mahmoud        ************************/
/************************        Layer:  LIB                 ************************/
/************************        SWC:    BIT_MATH            ************************/
/************************        Version:1.0                 ************************/
/************************************************************************************/
/************************************************************************************/

#ifndef BIT_MATH_H_
#define BIT_MATH_H_


#define SET_BIT(VAR, BIT_NO)    (VAR |=  (1 << BIT_NO))
#define CLR_BIT(VAR, BIT_NO)    (VAR &= ~(1 << BIT_NO))
#define TOGGLE_BIT(VAR, BIT_NO) (VAR ^=  (1 << BIT_NO))
#define GET_BIT(VAR, BIT_NO)    ((VAR >> BIT_NO) & 0x01)

#define SET_BITS(REG, MSK)      (REG |= MSK)
#define CLR_BITS(REG, MSK)      (REG &= ~MSK)
#define GET_BITS(REG, MSK)      (REG & MSK)

#define CLR_REG(REG)            (REG = 0x0)
#define READ_REG(REG)           (REG)
#define WRITE_REG(REG, VAL)     (REG = VAL)

// #define GET_ALIAS_ADDRESS(BITBAND_ADDRESS, BIT_NO)	(ALIAS_BASE + (((uint32_t)BITBAND_ADDRESS - BITBAND_BASE) * 32) +(BIT_NO * 4))


#endif /* BIT_MATH_H_ End */

/*

#define SET_BIT(VAR, BIT_NO)    (VAR |=  (1 << BIT_NO))
#define CLR_BIT(VAR, BIT_NO)    (VAR &= ~(1 << BIT_NO))
#define TOGGLE_BIT(VAR, BIT_NO) (VAR ^=  (1 << BIT_NO))
#define GET_BIT(VAR, BIT_NO)    ((VAR >> BIT_NO) & 0x01)

*/
