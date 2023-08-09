/************************************************************************************
 * @file BIT_MATH.h
 * @author Musa Mahmoud
 * @brief The bit math main header file, including functions macros to manipulate bits 
 * @version 0.1
 * @date 2023-03-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */

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
