/*********************************************************************************/
/* Author    : Hossam Ahmed                                                     */
/* Version   : V01                                                               */
/* Data      : 30 OCT 2023                                                       */
/*********************************************************************************/
/*---------------------------------------------------------------------------------------------------------------------
 *  *  FILE DESCRIPTION
 *  --------------------
 *         File:  UART_interface.h
 *       Module:  UART Module
 *  Description:  Interface header file for UART Driver
---------------------------------------------------------------------------------------------------------------------*/
#ifndef _UART_INTERFACE_H
#define _UART_INTERFACE_H

/*---------------------------------------------------------------------------------------------------------------------
 *  INCLUDES
---------------------------------------------------------------------------------------------------------------------*/
#include "../../LIB//Std_Types.h"
#include "../../LIB//Bit_Math.h"
#include "UART_config.h"

#include "UART_private.h"

/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL FUNCTIONS
---------------------------------------------------------------------------------------------------------------------*/

/******************************************************************************
* \Syntax          : void MUSART1_voidInit(void)                                      
* \Description     : Initialize UART by determine baud rate and frame details                                                                              
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                 
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MUSART1_voidInit(void);

/******************************************************************************
* \Syntax          : void MUSART1_voidEnable(void)                                     
* \Description     : Enable UART1                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None               
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MUSART1_voidEnable(void);

/******************************************************************************
* \Syntax          : void MUSART1_voidDisable(void)                                      
* \Description     : Disable  UART timer by clear its ENABLE bit                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                    
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MUSART1_voidDisable(void);


/******************************************************************************
* \Syntax          : void MUSART1_voidSendData(u8 Copy_u16Data)                                     
* \Description     : Sending byte of data by loading it to data register and wait until transmission complete                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : uint8 Copy_u8Data: byte of data to be sent                   
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MUSART1_voidSendData(uint8 Copy_u8Data);

/******************************************************************************
* \Syntax          : void MUSART1_voidSendString(u8 *Copy_u8String)                                  
* \Description     : Sending string byte by byte  by loading it to data register and wait until transmission complete                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : uint8 *Copy_u8Data: pointer to character array to be sent                   
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MUSART1_voidSendString(const uint8 *Copy_u8String);

/******************************************************************************
* \Syntax          : void MUSART1_voidSendNumbers(s32 Copy_s32Number)                                 
* \Description     : Sending string representation of number byte by byte  by loading it to data register and wait until transmission complete                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : sint32 Copy_s32Number: number to be sent                   
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MUSART1_voidSendNumbers(sint32 Copy_s32Number);


/******************************************************************************
* \Syntax          : uint8 MUSART1_u8ReceiveData(void)                                 
* \Description     : Receive byte of data
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                   
* \Parameters (out): None                                                      
* \Return value:   : byte of data
*******************************************************************************/
uint8 MUSART1_u8ReceiveData(void);

/******************************************************************************
* \Syntax          : uint8 MUSART1_u8ReceiveDataBlock(uint8* Copy_u8DataArr)                                 
* \Description     : Receive block of data
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : pointer to array                   
* \Parameters (out): pointer to array after modify array elements                                                      
* \Return value:   : uint8 -> number of elements in array.
*******************************************************************************/
uint8 MUSART1_u8ReceiveDataBlock(uint8* Copy_u8DataArr);


#endif
