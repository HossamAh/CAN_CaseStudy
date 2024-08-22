/*********************************************************************************/
/* Author    : Hossam Ahmed                                                     */
/* Version   : V01                                                               */
/* Data      : 26 OCT 2023                                                       */
/*********************************************************************************/
/*---------------------------------------------------------------------------------------------------------------------
 *  *  FILE DESCRIPTION
 *  --------------------
 *         File:  AFIO_interface.h
 *       Module:  AFIO Module
 *  Description:  Interface header file for AFIO Driver
---------------------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------------------
 *  INCLUDES
---------------------------------------------------------------------------------------------------------------------*/

#include "AFIO_interface.h"


/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL FUNCTION Implemention
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
void MAFIO_voidRemapPeripheralPins (uint8 Copy_u8peripheralNum)
{

	switch(Copy_u8peripheralNum){
		 case UART1_REMAP:
			 AFIO->MAPR.B.USART1=0; /* PA9 TX ,PA10 RX*/
			break;
		case CAN_REMAP:
			/* CAN remap, use PB8, PB9 >> BITS 13,14   = 10*/
			AFIO->MAPR.B.CAN = 0b10;
			break;
		case I2C1_REMAP:
			AFIO->MAPR.B.I2C1 = 1;
			break;
		case SPI1_REMAP:
			AFIO->MAPR.B.SPI1=1;
			break;
	}

}

