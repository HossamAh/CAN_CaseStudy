/*********************************************************************************/
/* Author    : Hossam Ahmed                                                     */
/* Version   : V01                                                               */
/* Data      : 28 OCT 2023                                                       */
/*********************************************************************************/
/*---------------------------------------------------------------------------------------------------------------------
 *  *  FILE DESCRIPTION
 *  --------------------
 *         File:  EXTERNAL_INTERRUPT_interface.h
 *       Module:  EXTERNAL_INTERRUPT Module
 *  Description:  Interface header file for EXTERNAL_INTERRUPT Driver
---------------------------------------------------------------------------------------------------------------------*/
#ifndef _EXTERNAL_INTERRUPT_INTERFACE_H
#define _EXTERNAL_INTERRUPT_INTERFACE_H

/*---------------------------------------------------------------------------------------------------------------------
 *  INCLUDES
---------------------------------------------------------------------------------------------------------------------*/
#include "../../LIB//Std_Types.h"
#include "../../LIB//Bit_Math.h"

#include "EXTERNAL_INTERRUPT_private.h"
#include "EXTERNAL_INTERRUPT_config.h"

/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL DATA TYPES AND STRUCTURES
---------------------------------------------------------------------------------------------------------------------*/
typedef enum
{
    EXTERNAL_INTERRUPT_0,
    EXTERNAL_INTERRUPT_1,
    EXTERNAL_INTERRUPT_2,
    EXTERNAL_INTERRUPT_3,
    EXTERNAL_INTERRUPT_4,
    EXTERNAL_INTERRUPT_5,
    EXTERNAL_INTERRUPT_6,
    EXTERNAL_INTERRUPT_7,
    EXTERNAL_INTERRUPT_8,
    EXTERNAL_INTERRUPT_9,
    EXTERNAL_INTERRUPT_10,
    EXTERNAL_INTERRUPT_11,
    EXTERNAL_INTERRUPT_12,
    EXTERNAL_INTERRUPT_13,
    EXTERNAL_INTERRUPT_14,
    EXTERNAL_INTERRUPT_15,
    PVD_OUTPUT,
    RTC_ALARM_EVENT,
    USB_WAKEUP_EVENT,
    ETHERNET_WAKEUP_EVENT
    
}EXTERNAL_InterruptNumber_t;/*means the pin number*/


typedef enum{
    RISING_EDGE,
    FALLING_EDGE,
    ANY_CHANGE,
}EXTERNAL_INTERRUPT_Trigger_type_t;

typedef enum{
    EXTERNAL_INTERRUPT_PORTA,
    EXTERNAL_INTERRUPT_PORTB,
    EXTERNAL_INTERRUPT_PORTC,
    EXTERNAL_INTERRUPT_PORTD,
    EXTERNAL_INTERRUPT_PORTE,
    EXTERNAL_INTERRUPT_PORTF,
    EXTERNAL_INTERRUPT_PORTG 
    
}EXTERNAL_INTERRUPT_PORTS_t;

/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL FUNCTIONS
---------------------------------------------------------------------------------------------------------------------*/
/******************************************************************************
* \Syntax          : void MEXTERNAL_INTERRUPT_VoidSetPort(EXTERNAL_InterruptNumber_t Copy_uint8InterruptNumber,EXTERNAL_INTERRUPT_PORTS_t Copy_uint8InterruptPort )
* \Description     : Set external interrupt pin of specific port by SYSCFG_EXTICR Register according to pin number range                                                                      
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : EXTERNAL_InterruptNumber_t Copy_uint8InterruptNumber: interrupt pin number  ,EXTERNAL_INTERRUPT_PORTS_t Copy_uint8InterruptPort port of the pin
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MEXTERNAL_INTERRUPT_VoidSetPort(EXTERNAL_InterruptNumber_t Copy_uint8InterruptNumber,EXTERNAL_INTERRUPT_PORTS_t Copy_uint8InterruptPort );

/******************************************************************************
* \Syntax          : void MEXTERNAL_INTERRUPT_VoidSetTriggerType(EXTERNAL_InterruptNumber_t Copy_uint8InterruptNumber,EXTERNAL_INTERRUPT_Trigger_type_t Copy_uint8Interruptrigger)
* \Description     : Set external interrupt trigger type of specific interrupt pin                                                                      
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : EXTERNAL_InterruptNumber_t Copy_uint8InterruptNumber: interrupt pin number  ,EXTERNAL_INTERRUPT_PORTS_t Copy_uint8InterruptTrigger trigger type
*                    Options: 1- RISING_EDGE
*                             2- FALLING_EDGE
*                             3- ANY_CHANGE  
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MEXTERNAL_INTERRUPT_VoidSetTriggerType(EXTERNAL_InterruptNumber_t Copy_uint8InterruptNumber,EXTERNAL_INTERRUPT_Trigger_type_t Copy_uint8Interruptrigger);

/******************************************************************************
* \Syntax          : void MEXTERNAL_INTERRUPT_VoidEnableInterrupt(EXTERNAL_InterruptNumber_t Copy_uint8InterruptNumber)
* \Description     : Enable  specific interrupt by enabling its mask bit                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : EXTERNAL_InterruptNumber_t Copy_uint8InterruptNumber
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MEXTERNAL_INTERRUPT_VoidEnableInterrupt(EXTERNAL_InterruptNumber_t Copy_uint8InterruptNumber);


/******************************************************************************
* \Syntax          : void MEXTERNAL_INTERRUPT_VoidDisableInterrupt(EXTERNAL_InterruptNumber_t Copy_uint8InterruptNumber)
* \Description     : Disable  specific interrupt by enabling its mask bit                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : EXTERNAL_InterruptNumber_t Copy_uint8InterruptNumber
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MEXTERNAL_INTERRUPT_VoidDisableInterrupt(EXTERNAL_InterruptNumber_t Copy_uint8InterruptNumber);


/******************************************************************************
* \Syntax          : void MEXTERNAL_INTERRUPT_VoidEnableSoftwareInterrupt(EXTERNAL_InterruptNumber_t Copy_uint8InterruptNumber)
* \Description     : Enable  specific Software interrupt by enabling its mask bit                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : EXTERNAL_InterruptNumber_t Copy_uint8InterruptNumber
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MEXTERNAL_INTERRUPT_VoidEnableSoftwareInterrupt(EXTERNAL_InterruptNumber_t Copy_uint8InterruptNumber);


/******************************************************************************
* \Syntax          : void MEXTERNAL_INTERRUPT_VoidInterruptCallback(EXTERNAL_InterruptNumber_t Copy_uint8InterruptNumber,void (*callback)(void))
* \Description     : Set  specific interrupt callback function by assign arguument function to specfifc function to be called in interrupt handler.                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : EXTERNAL_InterruptNumber_t Copy_uint8InterruptNumber ,void (*callback)(void) callback function to be called in interrupt handler
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MEXTERNAL_INTERRUPT_VoidInterruptCallback(EXTERNAL_InterruptNumber_t Copy_uint8InterruptNumber,void (*callback)(void));


#endif
