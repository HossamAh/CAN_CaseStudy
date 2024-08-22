/*---------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------
 *         File:  Bit_Math.h
 *       Module:  Bit Math Module
 *  Description:  bit math macros definition header file    
---------------------------------------------------------------------------------------------------------------------*/
#ifndef BIT_MATH_H
#define BIT_MATH_H
/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL FUNCTION MACROS
---------------------------------------------------------------------------------------------------------------------*/
// #define SET_BIT(REG,BIT_NUM)        (REG) |= (1<<(BIT_NUM))
#define SET_BIT(REG, BIT) ((REG) |= (1 << (BIT)))

#define CLEAR_BIT(REG, BIT) ((REG) &= ~(1 << (BIT)))
#define TOGGLE_BIT(REG, BIT) ((REG) ^= (1 << (BIT)))

// #define CLEAR_BIT(REG,BIT_NUM)      (REG) &= ~(1<<(BIT_NUM))
#define READ_BIT(REG,BIT_NUM)       (((REG)>>(BIT_NUM))&0x1)

#endif
