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
#include "NVIC_Config.h"

#include "NVIC_Private.h"
#include "NVIC_Interface.h"

/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL DATA
---------------------------------------------------------------------------------------------------------------------*/
NVIC_GROUP_t global_grouping;



/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL FUNCTIONS
---------------------------------------------------------------------------------------------------------------------*/

/******************************************************************************
* \Syntax          : void MNVIC_VoidSetPriorityPolicy(NVIC_PriorityPolicy Copy_uint8PriorityPolicy )                                      
* \Description     : Set Priority policy of NVIC Determine number of preemption priority level and sub_priority levels                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : NVIC_GROUP_t Copy_uint8PriorityPolicy : enum of group and sub_group options                  
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MNVIC_VoidSetPriorityPolicy(NVIC_GROUP_t Copy_uint8PriorityPolicy )
{
    global_grouping = Copy_uint8PriorityPolicy;
    /*write the AIRCR Key*/
    SCB_AIRCR = NVIC_VECTKEY;
    /*set priority Policy*/
    SCB_AIRCR |= (Copy_uint8PriorityPolicy<<8);
}

/******************************************************************************
* \Syntax          : void MNVIC_VoidSetPriority(NVIC_InterruptType_t Copy_uint8InterruptType , uint8 Copy_uint8Priority,uint8 Copy_uint8SubPriority)                                      
* \Description     : Set priority and sub_priority to specific interrupt                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : NVIC_InterruptType_t Copy_uint8InterruptType Interrupt name , uint8 Copy_uint8Priority number of group ,uint8 Copy_uint8SubPriority number of sub priority                   
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MNVIC_VoidSetPriority(NVIC_InterruptType_t Copy_uint8InterruptType , uint8 Copy_uint8Priority,uint8 Copy_uint8SubPriority)
{
    switch(global_grouping){
	case(Group16Sub0):
        NVIC -> NVIC_IPR[Copy_uint8InterruptType] = Copy_uint8Priority<<4;
        break;
	case(Group8Sub2):
        NVIC -> NVIC_IPR[Copy_uint8InterruptType] = Copy_uint8Priority<<5 | Copy_uint8SubPriority<<4 ;
        break;
	case(Group4Sub4):
		NVIC -> NVIC_IPR[Copy_uint8InterruptType] = Copy_uint8Priority<<6 | Copy_uint8SubPriority<<4 ;
		break;
	case(Group2Sub8):
		NVIC -> NVIC_IPR[Copy_uint8InterruptType] = Copy_uint8Priority<<7 | Copy_uint8SubPriority<<4 ;
		break;
	case(Group0Sub16):
		NVIC -> NVIC_IPR[Copy_uint8InterruptType] = Copy_uint8Priority<<8 | Copy_uint8SubPriority<<4 ;
		break;
	default:
		break;

	}
}

/******************************************************************************
* \Syntax          : void MNVIC_VoidEnableInterrupt(NVIC_InterruptType_t Copy_uint8InterruptType)                                      
* \Description     : Enable  specific interrupt by enabling its mask bit                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : NVIC_InterruptType_t Copy_uint8InterruptType Interrupt name                    
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MNVIC_VoidEnableInterrupt(NVIC_InterruptType_t Copy_uint8InterruptType)
{
    SET_BIT(NVIC->NVIC_ISER[Copy_uint8InterruptType/reg_div],Copy_uint8InterruptType%reg_div); 
}
/******************************************************************************
* \Syntax          : void MNVIC_VoidDisableInterrupt(NVIC_InterruptType_t Copy_uint8InterruptType)                                      
* \Description     : Disable  specific interrupt by enabling its mask bit                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : NVIC_InterruptType_t Copy_uint8InterruptType Interrupt name                    
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MNVIC_VoidDisableInterrupt(NVIC_InterruptType_t Copy_uint8InterruptType)
{
    SET_BIT(NVIC->NVIC_ICER[Copy_uint8InterruptType/reg_div],Copy_uint8InterruptType%reg_div);
}
/******************************************************************************
* \Syntax          : void MNVIC_VoidSetPendingInterrupt(NVIC_InterruptType_t Copy_uint8InterruptType)                                      
* \Description     : Set Pending bit of specific interrupt by enabling its mask bit                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : NVIC_InterruptType_t Copy_uint8InterruptType Interrupt name                    
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MNVIC_VoidSetPendingInterrupt(NVIC_InterruptType_t Copy_uint8InterruptType)
{
    SET_BIT(NVIC->NVIC_ISPR[Copy_uint8InterruptType/reg_div],Copy_uint8InterruptType%reg_div);
}
/******************************************************************************
* \Syntax          : void MNVIC_VoidClearPendingInterrupt(NVIC_InterruptType_t Copy_uint8InterruptType)                                      
* \Description     : Clear Pending bit of specific interrupt by enabling its mask bit                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : NVIC_InterruptType_t Copy_uint8InterruptType Interrupt name                    
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MNVIC_VoidClearPendingInterrupt(NVIC_InterruptType_t Copy_uint8InterruptType)
{
    SET_BIT(NVIC->NVIC_ICPR[Copy_uint8InterruptType/reg_div],Copy_uint8InterruptType%reg_div);
}
