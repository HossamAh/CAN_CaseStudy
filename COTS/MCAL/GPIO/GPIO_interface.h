/*********************************************************************************/
/* Author    : Hossam Ahmed                                                     */
/* Version   : V01                                                               */
/* Data      : 26 OCT 2023                                                       */
/*********************************************************************************/
/*---------------------------------------------------------------------------------------------------------------------
 *  *  FILE DESCRIPTION
 *  --------------------
 *         File:  GPIO_interface.h
 *       Module:  GPIO Module
 *  Description:  Interface header file for GPIO Driver
---------------------------------------------------------------------------------------------------------------------*/
#ifndef _GPIO_INTERFACE_H
#define _GPIO_INTERFACE_H

/*---------------------------------------------------------------------------------------------------------------------
 *  INCLUDES
---------------------------------------------------------------------------------------------------------------------*/
#include "../../LIB/Std_Types.h"
#include "../../LIB/Bit_Math.h"

#include "GPIO_private.h"
#include "GPIO_config.h"

/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL DATA TYPES AND STRUCTURES
---------------------------------------------------------------------------------------------------------------------*/
typedef enum
{
    INPUT_ANALOG=0b0000,
    INPUT_FLOATING=0b0100,
    INPUT_PULLUP_PULLDOWN=0b1000,
    OUTPUT_SPEED_10MHZ_PUSHPULL=0b0001,
		OUTPUT_SPEED_10MHZ_OPENDRAIN=0b0101,
		OUTPUT_SPEED_10MHZ_AFPUSHPULL=0b1001,
		OUTPUT_SPEED_10MHZ_AFOPENDRAIN=0b1101,
		OUTPUT_SPEED_2MHZ_PUSHPULL=0b0010,
		OUTPUT_SPEED_2MHZ_OPENDRAIN=0b0110,
		OUTPUT_SPEED_2MHZ_AFPUSHPULL=0b1010,
		OUTPUT_SPEED_2MHZ_AFOPENDRAIN=0b1110,
		OUTPUT_SPEED_50MHZ_PUSHPULL=0b0011,
		OUTPUT_SPEED_50MHZ_OPENDRAIN=0b0111,
		OUTPUT_SPEED_50MHZ_AFPUSHPULL=0b1011,
		OUTPUT_SPEED_50MHZ_AFOPENDRAIN=0b1111
}GPIO_PinModeType;

typedef enum
{
    PIN_HIGH = 1u,
    PIN_LOW  = 0u
}GPIO_PinLevel;

typedef enum
{
    PULL_UP,
    PULL_DOWN,
    PULL_NONE
}GPIO_PinPUPDType;


typedef enum
{
    AF0,           
    AF1,           
    AF2,           
    AF3,           
    AF4,           
    AF5,           
    AF6,           
    AF7,           
    AF8,           
    AF9,           
    AF10,          
    AF11,          
    AF12,          
    AF13,          
    AF14,          
    AF15
}GPIO_PinAFType;

typedef enum
{
	_GPIOA_PORT,
	_GPIOB_PORT,
	_GPIOC_PORT,
    _GPIOD_PORT,
	_GPIOE_PORT,
	_GPIOF_PORT,
    _GPIOG_PORT
}GPIO_Num;

typedef enum
{
    pin0,
    pin1,
    pin2,
    pin3,
    pin4,
    pin5,
    pin6,
    pin7,
    pin8,
    pin9,
    pin10,
    pin11,
    pin12,
    pin13,
    pin14,
    pin15
}GPIO_PinNum;

typedef struct 
{
    GPIO_PinModeType PinMode;
    GPIO_PinLevel PinInitLevel;
    GPIO_PinPUPDType PinPUPDType;
    GPIO_PinAFType AFNum;
    GPIO_Num Port;
    GPIO_PinNum Pin;
}GPIO_Cfg_Type;

/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL FUNCTIONS
---------------------------------------------------------------------------------------------------------------------*/
// /******************************************************************************
// * \Syntax          : void MGPIO_VoidInitGPIOPins(const GPIO_Cfg_Type *ConfigPtr)                                      
// * \Description     : initialize GPIO port using configuration struct by parsing all 
// *       its configurations to the port registers                                                                             
// * \Sync\Async      : Synchronous                                               
// * \Reentrancy      : Non Reentrant                                             
// * \Parameters (in) : ConfigPtr  pointer to port initalization configurations.                   
// * \Parameters (out): None                                                      
// * \Return value:   : None
// *******************************************************************************/
// void MGPIO_VoidInitGPIOPins(const GPIO_Cfg_Type *ConfigPtr);



/******************************************************************************
* \Syntax          : void MGPIO_VoidSetPinMode(GPIO_Num Copy_u8Port , GPIO_PinNum Copy_u8Pin , GPIO_PinModeType Copy_u8Mode)
* \Description     : initialize GPIO pin mode
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : Copy_u8Port: port number , Copy_u8Pin: pin number , Copy_u8Mode: mode of operation
* \Parameters (out): None
* \Return value:   : None
*******************************************************************************/
void MGPIO_VoidSetPinMode_TYPE(GPIO_Num Copy_u8Port , GPIO_PinNum Copy_u8Pin , GPIO_PinModeType Copy_u8Mode);


/******************************************************************************
* \Syntax          : void MGPIO_VoidSetPullType(GPIO_Num Copy_u8Port , GPIO_PinNum Copy_u8Pin , GPIO_PinPUPDType Copy_u8PullType)
* \Description     : initialize GPIO pin pull
* 					    PULL_OFF,
*						PULL_UP,
*						PULL_DOWN
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : Copy_u8Port: port number , Copy_u8Pin: pin number , Copy_u8Mode: mode of operation
* \Parameters (out): None
* \Return value:   : None
*******************************************************************************/
void MGPIO_VoidSetPullType(GPIO_Num Copy_u8Port , GPIO_PinNum Copy_u8Pin , GPIO_PinPUPDType Copy_u8PullType);

/******************************************************************************
* \Syntax          : void MGPIO_VoidSetPinValue(GPIO_Num Copy_uint8Port , GPIO_PinNum Copy_uint8Pin ,GPIO_PinLevel  Copy_uint8Value)                                      
* \Description     : Set pin value in GPIO Port                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : GPIO_Num Port Name , GPIO_PinNum pin number in port ,GPIO_PinLevel  High or LOW                   
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MGPIO_VoidSetPinValue(GPIO_Num Copy_uint8Port , GPIO_PinNum Copy_uint8Pin ,GPIO_PinLevel  Copy_uint8Value);

/******************************************************************************
* \Syntax          : void MGPIO_VoidTogglePinValue(GPIO_Num Copy_uint8Port , GPIO_PinNum Copy_uint8Pin)
* \Description     : Toggle pin value in GPIO Port
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : GPIO_Num Port Name , GPIO_PinNum pin number in port
* \Parameters (out): None
* \Return value:   : None
*******************************************************************************/
void MGPIO_VoidTogglePinValue(GPIO_Num Copy_uint8Port , GPIO_PinNum Copy_uint8Pin );


/******************************************************************************
* \Syntax          : GPIO_PinLevel MGPIO_GPIO_PinLevelGetPinValue(GPIO_Num Copy_uint8Port , GPIO_PinNum Copy_uint8Pin)                                      
* \Description     : Get pin value in GPIO Port                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : GPIO_Num Port Name , GPIO_PinNum pin number in port                    
* \Parameters (out): None                                                      
* \Return value:   : GPIO_PinLevel  High or LOW
*******************************************************************************/
GPIO_PinLevel MGPIO_GPIO_PinLevelGetPinValue(GPIO_Num Copy_uint8Port , GPIO_PinNum Copy_uint8Pin);

/******************************************************************************
* \Syntax          : void MGPIO_VoidLockPin(GPIO_Num Copy_uint8Port , GPIO_PinNum Copy_uint8Pin)                                      
* \Description     : Lock pin value in GPIO Port                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : GPIO_Num Port Name , GPIO_PinNum pin number in port                    
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MGPIO_VoidLockPin(GPIO_Num Copy_uint8Port , GPIO_PinNum Copy_uint8Pin);


#endif
