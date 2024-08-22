/*********************************************************************************/
/* Author    : Hossam Ahmed                                                     */
/* Version   : V01                                                               */
/* Data      : 30 OCT 2023                                                       */
/*********************************************************************************/
/*---------------------------------------------------------------------------------------------------------------------
 *  *  FILE DESCRIPTION
 *  --------------------
 *         File:  SYSTICK_interface.h
 *       Module:  SYSTICK Module
 *  Description:  Interface header file for SYSTICK Driver
---------------------------------------------------------------------------------------------------------------------*/
#ifndef _SYSTICK_INTERFACE_H
#define _SYSTICK_INTERFACE_H

/*---------------------------------------------------------------------------------------------------------------------
 *  INCLUDES
---------------------------------------------------------------------------------------------------------------------*/
#include "../../LIB//Std_Types.h"
#include "../../LIB//Bit_Math.h"
#include "SYSTICK_config.h"

#include "SYSTICK_private.h"

/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL DATA TYPES AND STRUCTURES
---------------------------------------------------------------------------------------------------------------------*/
/*
SYSTICK_CLKSOURCE_t :select clock source of systick timer
Options:
    AHB/8: AHB_8_CLK
    AHB : AHB_CLK
*/
typedef enum{
    AHB_8_CLK,
    AHB_CLK
}SYSTICK_CLKSOURCE_t;




/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL FUNCTIONS
---------------------------------------------------------------------------------------------------------------------*/

/******************************************************************************
* \Syntax          : void MSYSTICK_VoidInit(SYSTICK_CLKSOURCE_t Copy_uint8CLKSource)                                      
* \Description     : Initialize SysTick by determine wherther its run on AHB clock or AHB/8                                                                              
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : SYSTICK_CLKSOURCE_t Copy_uint8CLKSource : enum of CLK sources options (AHB/8 ->AHB_8_CLK  , AHB-> AHB_CLK )                  
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MSYSTICK_VoidInit(SYSTICK_CLKSOURCE_t Copy_uint8CLKSource);

/******************************************************************************
* \Syntax          : void MSYSTICK_VoidStartSYSTICK(uint32 Copy_uint8ReloadValue)                                      
* \Description     : Start Timer with reload value which Timer starts count down from and  regiister callback function                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : uint32 Copy_uint8ReloadValue : reload value which Timer starts count down from. MAX->24^2 -1   ,void (*SysTick_CallBack)(void):callback interrupt function               
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MSYSTICK_VoidStartSYSTICK(uint32 Copy_uint8ReloadValue,void (*SysTick_CallBack)(void));

/******************************************************************************
* \Syntax          : void MSYSTICK_VoidDisableSysTick()                                      
* \Description     : Disable  systick timer by clear its ENABLE bit                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                    
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MSYSTICK_VoidDisableSysTick();

#endif
