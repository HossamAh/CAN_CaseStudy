/*********************************************************************************/
/* Author    : Hossam Ahmed                                                        */
/* Version   : V01                                                               */
/* Date      : 11 may  2024                                                      */
/*********************************************************************************/
/*---------------------------------------------------------------------------------------------------------------------
 *  *  FILE DESCRIPTION
 *  --------------------
 *         File:  AFIO_interface.h
 *       Module:  AFIO Module
 *  Description:  interface funcions for AFIO Driver
---------------------------------------------------------------------------------------------------------------------*/

#ifndef AFIO_INTERFACE_H
#define AFIO_INTERFACE_H
/*---------------------------------------------------------------------------------------------------------------------
 *  INCLUDES
---------------------------------------------------------------------------------------------------------------------*/
#include "../../LIB//Std_Types.h"
#include "../../LIB//Bit_Math.h"
#include "AFIO_config.h"
#include "AFIO_private.h"
#include "../GPIO/GPIO_interface.h"
/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL MACROS
---------------------------------------------------------------------------------------------------------------------*/
#define SPI1_REMAP					 0
#define I2C1_REMAP 					 1
#define UART1_REMAP					 2
#define UART2_REMAP					 3
#define UART3_REMAP					 4
#define TIM1_REMAP					 5
#define TIM2_REMAP					 6
#define TIM3_REMAP					 7
#define TIM4_REMAP					 8
#define CAN_REMAP  					 9



/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL FUNCTION PROTOTYPES
---------------------------------------------------------------------------------------------------------------------*/ 
/******************************************************************************
* \Syntax          : void MAFIO_voidRemapPeripheralPins (uint8 Copy_u8peripheralNum)                                      
* \Description     : initialize AFIO of peripheral                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : Copy_u8peripheralNum : number of peripheral to enable remap                   
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MAFIO_voidRemapPeripheralPins (uint8 Copy_u8peripheralNum);

#endif // AFIO_INTERFACE_H
