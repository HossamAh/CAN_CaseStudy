/*********************************************************************************/
/* Author    : Hossam Ahmed                                                     */
/* Version   : V01                                                               */
/* Data      : 28 OCT 2023                                                       */
/*********************************************************************************/
/*---------------------------------------------------------------------------------------------------------------------
 *  *  FILE DESCRIPTION
 *  --------------------
 *         File:  NVIC_interface.h
 *       Module:  NVIC Module
 *  Description:  Interface header file for NVIC Driver
---------------------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------------------
 *  INCLUDES
---------------------------------------------------------------------------------------------------------------------*/
#include "../../LIB//Std_Types.h"
#include "../../LIB//Bit_Math.h"


#include "External_Interrupt_Config.h"
#include "External_Interrupt_private.h"
#include "External_Interrupt_interface.h"

/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL DATA
---------------------------------------------------------------------------------------------------------------------*/
static void (*external_interrupt_callback[16])(void) = {};
/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL FUNCTIONS
---------------------------------------------------------------------------------------------------------------------*/
/******************************************************************************
* \Syntax          : void MEXTERNAL_INTERRUPT_VoidSetPort(EXTERNAL_InterruptNumber_t Copy_uint8InterruptNumber,EXTERNAL_INTERRUPT_PORTS_t Copy_uint8InterruptPort )
* \Description     : Set external interrupt pin of specific port by AFIO_EXTICR Register according to pin number range                                                                      
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : EXTERNAL_InterruptNumber_t Copy_uint8InterruptNumber: interrupt pin number  ,EXTERNAL_INTERRUPT_PORTS_t Copy_uint8InterruptPort port of the pin
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MEXTERNAL_INTERRUPT_VoidSetPort(EXTERNAL_InterruptNumber_t Copy_uint8InterruptNumber,EXTERNAL_INTERRUPT_PORTS_t Copy_uint8InterruptPort )
{
    uint8 Local_uint8RegIndex = 0;
    if(Copy_uint8InterruptNumber<4)/*AFIO_EXTICR1  (EXTI0,EXTII1,EXTI2,EXTI3)*/
    {
        Local_uint8RegIndex = 0;    
    }
    else if(Copy_uint8InterruptNumber<8)/*AFIO_EXTICR2*/
    {
        Copy_uint8InterruptNumber -=4;
        Local_uint8RegIndex = 1;    
    }
    else if(Copy_uint8InterruptNumber<12)/*AFIO_EXTICR2*/
    {
        Local_uint8RegIndex = 2;    
        Copy_uint8InterruptNumber -=8;
    } 
    else if(Copy_uint8InterruptNumber<16)/*AFIO_EXTICR2*/
    {
        Local_uint8RegIndex = 3;    
        Copy_uint8InterruptNumber -=12;
    }
    else{}
    /*reset first --> (avoiding overwrite)*/
    AFIO_EXTICR[Local_uint8RegIndex] &= ~((0b1111) << (Copy_uint8InterruptNumber * 4));
    /*set*/
    AFIO_EXTICR[Local_uint8RegIndex]  |= ((Copy_uint8InterruptPort) << (Copy_uint8InterruptNumber * 4));
}

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
void MEXTERNAL_INTERRUPT_VoidSetTriggerType(EXTERNAL_InterruptNumber_t Copy_uint8InterruptNumber,EXTERNAL_INTERRUPT_Trigger_type_t Copy_uint8Interruptrigger)
{
    /*interrupt nuumber is the pin number so it represents the EXTI line*/
    switch(Copy_uint8Interruptrigger)
    {
        case RISING_EDGE:
            SET_BIT(EXTI->EXTI_RTSR,Copy_uint8InterruptNumber);
        break;
        case FALLING_EDGE:
            SET_BIT(EXTI->EXTI_FTSR,Copy_uint8InterruptNumber);
        break;
        case ANY_CHANGE:
        default:
            SET_BIT(EXTI->EXTI_RTSR,Copy_uint8InterruptNumber);
            SET_BIT(EXTI->EXTI_FTSR,Copy_uint8InterruptNumber);
        break;
    }
}
/******************************************************************************
* \Syntax          : void MEXTERNAL_INTERRUPT_VoidEnableInterrupt(EXTERNAL_InterruptNumber_t Copy_uint8InterruptNumber)
* \Description     : Enable  specific interrupt by enabling its mask bit                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : EXTERNAL_InterruptNumber_t Copy_uint8InterruptNumber
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MEXTERNAL_INTERRUPT_VoidEnableInterrupt(EXTERNAL_InterruptNumber_t Copy_uint8InterruptNumber)
{
    SET_BIT(EXTI->EXTI_IMR,Copy_uint8InterruptNumber);
}


/******************************************************************************
* \Syntax          : void MEXTERNAL_INTERRUPT_VoidDisableInterrupt(EXTERNAL_InterruptNumber_t Copy_uint8InterruptNumber)
* \Description     : Disable  specific interrupt by enabling its mask bit                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : EXTERNAL_InterruptNumber_t Copy_uint8InterruptNumber
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MEXTERNAL_INTERRUPT_VoidDisableInterrupt(EXTERNAL_InterruptNumber_t Copy_uint8InterruptNumber)
{
    CLEAR_BIT(EXTI->EXTI_IMR,Copy_uint8InterruptNumber);
}

/******************************************************************************
* \Syntax          : void MEXTERNAL_INTERRUPT_VoidEnableSoftwareInterrupt(EXTERNAL_InterruptNumber_t Copy_uint8InterruptNumber)
* \Description     : Enable  specific Software interrupt by enabling its mask bit                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : EXTERNAL_InterruptNumber_t Copy_uint8InterruptNumber
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MEXTERNAL_INTERRUPT_VoidEnableSoftwareInterrupt(EXTERNAL_InterruptNumber_t Copy_uint8InterruptNumber)
{
    SET_BIT(EXTI->EXTI_IMR,Copy_uint8InterruptNumber);
    CLEAR_BIT(EXTI->EXTI_PR,Copy_uint8InterruptNumber);/*set pending bit of this interrupt*/
    SET_BIT(EXTI->EXTI_SWIER,Copy_uint8InterruptNumber);
}

/******************************************************************************
* \Syntax          : void MEXTERNAL_INTERRUPT_VoidInterruptCallback(EXTERNAL_InterruptNumber_t Copy_uint8InterruptNumber,void (*callback)(void))
* \Description     : Set  specific interrupt callback function by assign arguument function to specfifc function to be called in interrupt handler.                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : EXTERNAL_InterruptNumber_t Copy_uint8InterruptNumber ,void (*callback)(void) callback function to be called in interrupt handler
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MEXTERNAL_INTERRUPT_VoidInterruptCallback(EXTERNAL_InterruptNumber_t Copy_uint8InterruptNumber,void (*callback)(void))
{
    external_interrupt_callback[Copy_uint8InterruptNumber] = callback;
}

void EXTI0_IRQHandler(void)
{
	external_interrupt_callback[0]();
	/*clear pending bit*/
	SET_BIT(EXTI->EXTI_PR , 0);
}


void EXTI1_IRQHandler(void)
{
	external_interrupt_callback[1]();
	/*clear pending bit*/
	SET_BIT(EXTI->EXTI_PR , 1);
}

void EXTI2_IRQHandler(void)
{
	external_interrupt_callback[2]();
	/*clear pending bit*/
	SET_BIT(EXTI->EXTI_PR , 2);
}

void EXTI3_IRQHandler(void)
{
	external_interrupt_callback[3]();
	/*clear pending bit*/
	SET_BIT(EXTI->EXTI_PR , 3);
}

void EXTI4_IRQHandler(void)
{
	external_interrupt_callback[4]();
	/*clear pending bit*/
	SET_BIT(EXTI->EXTI_PR , 4);
}

void EXTI9_5_IRQHandler(void)
{
	uint8 PinValue_5 , PinValue_6 , PinValue_7 , PinValue_8 , PinValue_9;

	PinValue_6 = READ_BIT(EXTI->EXTI_PR,6);
	PinValue_7 = READ_BIT(EXTI->EXTI_PR,7);
	PinValue_8 = READ_BIT(EXTI->EXTI_PR,8);
	PinValue_9 = READ_BIT(EXTI->EXTI_PR,9);

	if (PinValue_5 == 1)
	{
		external_interrupt_callback[5]();
		SET_BIT(EXTI->EXTI_PR , 5);
	}

	if (PinValue_6 == 1)
	{
		external_interrupt_callback[6]();
		SET_BIT(EXTI->EXTI_PR , 6);
	}

	if (PinValue_7 == 1)
	{
		external_interrupt_callback[7]();
		SET_BIT(EXTI->EXTI_PR , 7);
	}

	if (PinValue_8 == 1)
	{
		external_interrupt_callback[8]();
		SET_BIT(EXTI->EXTI_PR , 8);
	}

	if (PinValue_9 == 1)
	{
		external_interrupt_callback[9]();
		SET_BIT(EXTI->EXTI_PR , 9);
	}

}

void EXTI15_10_IRQHandler(void)
{
	uint8 PinValue_10 , PinValue_11 , PinValue_12 , PinValue_13 , PinValue_14 , PinValue_15;

	PinValue_10 = READ_BIT(EXTI->EXTI_PR,10);
	PinValue_11 = READ_BIT(EXTI->EXTI_PR,11);
	PinValue_12 = READ_BIT(EXTI->EXTI_PR,12);
	PinValue_13 = READ_BIT(EXTI->EXTI_PR,13);
	PinValue_14 = READ_BIT(EXTI->EXTI_PR,14);
	PinValue_15 = READ_BIT(EXTI->EXTI_PR,14);

	if (PinValue_10 == 1)
	{
		external_interrupt_callback[10]();
		SET_BIT(EXTI->EXTI_PR , 10);
	}

	if (PinValue_11 == 1)
	{
		external_interrupt_callback[11]();
		SET_BIT(EXTI->EXTI_PR , 11);
	}

	if (PinValue_12 == 1)
	{
		external_interrupt_callback[12]();
		SET_BIT(EXTI->EXTI_PR , 12);
	}

	if (PinValue_13 == 1)
	{
		external_interrupt_callback[13]();
		SET_BIT(EXTI->EXTI_PR , 13);
	}

	if (PinValue_14 == 1)
	{
		external_interrupt_callback[14]();
		SET_BIT(EXTI->EXTI_PR , 14);
	}

	if (PinValue_15 == 1)
	{
		external_interrupt_callback[15]();
		SET_BIT(EXTI->EXTI_PR , 15);
	}

}
