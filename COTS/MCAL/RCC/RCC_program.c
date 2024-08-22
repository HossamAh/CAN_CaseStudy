/*********************************************************************************/
/* Author    : Hossam Ahmed                                                     */
/* Version   : V01                                                               */
/* Data      : 25 OCT 2023                                                       */
/*********************************************************************************/
/*---------------------------------------------------------------------------------------------------------------------
 *  *  FILE DESCRIPTION
 *  --------------------
 *         File:  RCC_program.c
 *       Module:  RCC Module
 *  Description:  implementaion C file for RCC Driver
---------------------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------------------
 *  INCLUDES
---------------------------------------------------------------------------------------------------------------------*/
//#include "../../LIB//Std_Types.h"
//#include "../../LIB//Bit_Math.h"
//
//#include "RCC_private.h"
//#include "RCC_config.h"
#include "RCC_interface.h"

/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL FUNCTION IMPLEMENTION
---------------------------------------------------------------------------------------------------------------------*/ 
/******************************************************************************
* \Syntax          : void MRCC_voidInitSysClock(void)                                      
* \Description     : initialize RCC using configuration by parsing all 
*       its configurations to the RCC registers                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                   
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MRCC_voidInitSysClock(void)
{
	/*AHB prescaler facor 1,2 ... ,512*/
	RCC->CFGR = RCC->CFGR & (~(0b111<<4));//clear this section
	RCC->CFGR |= (RCC_CLOCK_AHB_PRESC_VALUE<<4);
	/*APB1 prescaler facor 1,2 ... ,16*/
	RCC->CFGR = RCC->CFGR & (~(0b111<<8));//clear this section
	RCC->CFGR |= (RCC_CLOCK_APB1_PRESC_VALUE<<8);
	/*APB2 prescaler facor 1,2 ... ,16*/
	RCC->CFGR = RCC->CFGR & (~(0b111<<11));//clear this section
	RCC->CFGR |= (RCC_CLOCK_APB2_PRESC_VALUE<<11);
	
	 
	#if     RCC_CLOCK_TYPE == RCC_HSE_CRYSTAL /* More accurate 4-16 MHZ OSC*/
		/* Enable HSE with no bypass  HSE_ON = 1 */
		SET_BIT(RCC->CR ,16);
		CLEAR_BIT(RCC->CR,18);
		/* HSE selected as system clock*/
		SET_BIT(RCC -> CFGR,0);
		CLEAR_BIT(RCC->CFGR,1);
	#elif   RCC_CLOCK_TYPE == RCC_HSE_RC /* External clock source (user clock source)*/
		/* Enable HSE with bypass HSE_ON = 1 , HSE_BYP = 1  */
		SET_BIT(RCC->CR ,16);
		SET_BIT(RCC->CR,18);
		/* HSE selected as system clock*/
		SET_BIT(RCC -> CFGR,0);
		CLEAR_BIT(RCC->CFGR,1);

	#elif   RCC_CLOCK_TYPE == RCC_HSI/*8 MHZ*/
		/* Enable HSI + Trimming(default) = 0 */
		SET_BIT(RCC->CR ,0);
		/* HSI selected as system clock*/
		CLEAR_BIT(RCC -> CFGR,0);
		CLEAR_BIT(RCC->CFGR,1);
	#elif   RCC_CLOCK_TYPE == RCC_PLL
		
			RCC -> PLLCFGR = PLL_MUL_VALUE;  
		
		#if   RCC_PLL_INPUT == RCC_PLL_IN_HSI
			/*HSI*/
			SET_BIT(RCC->CR ,0);
			/*PLL as system clock + HSI*/
			CLEAR_BIT(RCC->CFGR , SW0);
			SET_BIT(RCC->CFGR , SW1);
			CLEAR_BIT(RCC->PLLCFGR , PLLSRC);
			/*Enable PLL*/
			SET_BIT(RCC->CR , PLL_ON);
		
		#elif RCC_PLL_INPUT == RCC_PLL_IN_HSE
			/*HSE*/
			SET_BIT(RCC->CR ,16);
			/*PLL as system clock + HSE*/
			CLEAR_BIT(RCC->CFGR , SW0);
			SET_BIT(RCC->CFGR , SW1);
			SET_BIT(RCC->PLLCFGR , PLLSRC);
			/*Enable PLL*/
			SET_BIT(RCC->CR , PLL_ON);
		
		#endif
	
	#else
		#error("You chosed Wrong Clock type")
	#endif
}

/******************************************************************************
* \Syntax          : void MRCC_voidEnableClock(uint8 Copy_uint8BusId , uint8 Copy_uint8PeripheralId)                                      
* \Description     : Enable the clock of specific peripheral on specific bus                                                                              
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : Copy_uint8BusId Bus idenifier   Copy_uint8PeripheralId Peripherral identifier.                   
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MRCC_voidEnableClock(uint8 Copy_uint8BusId, uint8 Copy_uint8PeripheralId)
{
	/*check input validation (32 bits)*/
	if (Copy_uint8PeripheralId <= 31)     
	{
		switch (Copy_uint8BusId)
		{
			case RCC_AHB : SET_BIT(RCC->AHBENR  , Copy_uint8PeripheralId);   
			break;
			
			case RCC_APB1 : SET_BIT(RCC->APB1ENR , Copy_uint8PeripheralId);   
			break;
			
			case RCC_APB2 : SET_BIT(RCC->APB2ENR , Copy_uint8PeripheralId);   
			break;
		}
	}

}

/******************************************************************************
* \Syntax          : void MRCC_voidDisableClock(uint8 Copy_uint8BusId , uint8 Copy_uint8PeripheralId)                                      
* \Description     : Disable the clock of specific peripheral on specific bus                                                                              
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : Copy_uint8BusId Bus idenifier   Copy_uint8PeripheralId Peripherral identifier.                   
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MRCC_voidDisableClock(uint8 Copy_uint8BusId, uint8 Copy_uint8PeripheralId)
{
	/*check input validation (32 bits)*/
	if (Copy_uint8PeripheralId <= 31)
	{
		switch (Copy_uint8BusId)
		{
			case RCC_AHB : CLEAR_BIT(RCC->AHBENR  , Copy_uint8PeripheralId);   
			break;
			
			
			case RCC_APB1 : CLEAR_BIT(RCC->APB1ENR , Copy_uint8PeripheralId);   
			break;
			
			case RCC_APB2 : CLEAR_BIT(RCC->APB2ENR , Copy_uint8PeripheralId);   
			break;
		}
	}

}

