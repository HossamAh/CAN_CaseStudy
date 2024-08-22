/*********************************************************************************/
/* Author    : Hossam Ahmed                                                     */
/* Version   : V01                                                               */
/* Data      : 25 OCT 2023                                                       */
/*********************************************************************************/
/*---------------------------------------------------------------------------------------------------------------------
 *  *  FILE DESCRIPTION
 *  --------------------
 *         File:  RCC_private.h
 *       Module:  RCC Module
 *  Description:  private header file for RCC Driver
---------------------------------------------------------------------------------------------------------------------*/
#ifndef RCC_PRIVATE_H
#define RCC_PRIVATE_H

/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL DATA TYPES AND STRUCTURES
---------------------------------------------------------------------------------------------------------------------*/
/* Register Map */
typedef struct{
	
	volatile uint32 CR;
	volatile uint32 CFGR;
	volatile uint32 CIR;
	volatile uint32 APB2RSTR;
	volatile uint32 APB1RSTR;
	volatile uint32 AHBENR;
	volatile uint32 APB2ENR;
	volatile uint32 APB1ENR;
	volatile uint32 BDCR;
	volatile uint32 CSR;
}RCC_t;


/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL CONSTANT MACROS
---------------------------------------------------------------------------------------------------------------------*/

#define 	RCC_Base_Address		(0x40021000)

#define 	RCC 		((volatile RCC_t*) RCC_Base_Address)
//#define RCC ((volatile RCC_t*) RCC_Base_Address)

/* Clock Types */
#define RCC_HSE_CRYSTAL      0
#define RCC_HSE_RC           1
#define RCC_HSI              2
#define RCC_PLL              3

/* PLL Options */
#define RCC_PLL_IN_HSI       0
#define RCC_PLL_IN_HSE       1

/*RCC_CFGR Register Bits*/
#define SW0        			 0
#define SW1        			 1
#define PLLSRC     			 22

/*RCC_CR Register Bits*/
#define PLL_ON     			 24


/*Bus Id*/
#define RCC_AHB      0 
#define RCC_APB1      1
#define RCC_APB2      2

#endif
