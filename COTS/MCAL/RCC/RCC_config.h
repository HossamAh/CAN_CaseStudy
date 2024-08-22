/*********************************************************************************/
/* Author    : Hossam Ahmed                                                     */
/* Version   : V01                                                               */
/* Data      : 25 OCT 2023                                                       */
/*********************************************************************************/
/*---------------------------------------------------------------------------------------------------------------------
 *  *  FILE DESCRIPTION
 *  --------------------
 *         File:  RCC_config.h
 *       Module:  RCC Module
 *  Description:  Configuration header file for RCC Driver
---------------------------------------------------------------------------------------------------------------------*/

#ifndef _RCC_CONFIG_H
#define _RCC_CONFIG_H

/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL MACROS
---------------------------------------------------------------------------------------------------------------------*/
/*__________________________________________________________________________*/
/* Options:    RCC_HSE_CRYSTAL
               RCC_HSE_RC
               RCC_HSI
               RCC_PLL			   */
//#define RCC_CLOCK_TYPE    RCC_HSE_CRYSTAL
#define RCC_CLOCK_TYPE    RCC_HSI


/* Options:    0    NO_DIV
               0x8  /2
               0x9  /4
               0xA  /8
               0xB  /16
               0xC  /32
               0xD  /64
               0xE  /128
               0xF  /512
               			   */
#define RCC_CLOCK_AHB_PRESC_VALUE   0
/* Options:    0    NO_DIV
               0x8  /2
               0x9  /4
               0xA  /8
               0xB  /16
               			   */
#define RCC_CLOCK_APB1_PRESC_VALUE   0
/* Options:    0    NO_DIV
               0x8  /2
               0x9  /4
               0xA  /8
               0xB  /16
               			   */
#define RCC_CLOCK_APB2_PRESC_VALUE   0      
/*__________________________________________________________________________*/
/* Note: Select value only if you have PLL as input clock source */
#if RCC_CLOCK_TYPE == RCC_PLL

/* Options:  	RCC_PLL_IN_HSI
				RCC_PLL_IN_HSE      */
#define 	RCC_PLL_INPUT     RCC_PLL_IN_HSI

/* Options:  */ 
#define 	PLL_MUL_VALUE     	0x00033F03 	//support clk of 84MHZ --> (PLLN = 252, PLLM = 3, PLLP = 8)
#endif 

#endif
