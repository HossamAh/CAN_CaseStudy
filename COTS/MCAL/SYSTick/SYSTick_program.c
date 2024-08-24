/*********************************************************************************/
/* Author    : Hossam Ahmed                                                     */
/* Version   : V01                                                               */
/* Data      : 30 OCT 2023                                                       */
/*********************************************************************************/
/*---------------------------------------------------------------------------------------------------------------------
 *  *  FILE DESCRIPTION
 *  --------------------
 *         File:  SYSTICK_program.c
 *       Module:  SYSTICK Module
 *  Description:  implementaion C file for SYSTICK Driver
---------------------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------------------
 *  INCLUDES
---------------------------------------------------------------------------------------------------------------------*/
#include "SYSTick_interface.h"

/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL DATA
---------------------------------------------------------------------------------------------------------------------*/
static void (*SysTick_CallBack)(void) = NULL;

/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL FUNCTION IMPLEMENTION
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
void MSYSTICK_VoidInit(SYSTICK_CLKSOURCE_t Copy_uint8CLKSource)
{
    /*select clock source*/
    STK_CTRL->B.CLKSOURCE = Copy_uint8CLKSource;
}

/******************************************************************************
* \Syntax          : void MSYSTICK_VoidStartSYSTICK(uint32 Copy_uint8ReloadValue)                                      
* \Description     : Start Timer with reload value which Timer starts count down from and  regiister callback function                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : uint32 Copy_uint8ReloadValue : reload value which Timer starts count down from. MAX->24^2 -1   ,void (*SysTick_CallBack)(void):callback interrupt function               
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MSYSTICK_VoidStartSYSTICK(uint32 Copy_uint8ReloadValue,void (*SysTick_CallBack_ptr)(void))
{
    /*Set reload value to start decrement from*/
    (*STK_LOAD) = Copy_uint8ReloadValue;
    /*clear current value*/
    (*STK_VAL) = 0U;
    /*clear count flag*/
    STK_CTRL->B.COUNTFLAG =0U;
    /* Enable interrupt*/
    STK_CTRL->B.TICKINT = 1U;
    /*set callback function*/
    SysTick_CallBack = SysTick_CallBack_ptr;
    /*enable SysTick*/
    STK_CTRL->B.ENABLE = 1U;
}

/******************************************************************************
* \Syntax          : void MSYSTICK_VoidDisableSysTick()                                      
* \Description     : Disable  systick timer by clear its ENABLE bit                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                    
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MSYSTICK_VoidDisableSysTick()
{
    /*disable systick*/
    STK_CTRL->B.ENABLE = 0U;
    /*disable systick interrupt*/
    STK_CTRL->B.TICKINT = 0U;
    (*STK_LOAD) = 0U;
    (*STK_VAL) = 0U;
}

/******************************************************************************
* \Syntax          : uint32 MSYSTICK_u32GetTick()                                      
* \Description     : return the current timer value                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                    
* \Parameters (out): None                                                      
* \Return value:   : uint32 timer current value
*******************************************************************************/
uint32 MSYSTICK_u32GetTick()
{
    return (*STK_VAL);
}

/******************************************************************************
* \Syntax          : uint32 MSYSTICK_VoidDelay(uint32 Delay)                                      
* \Description     : busy waiting delay in ms                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : uint32 Delay: delay in ms                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
uint32 MSYSTICK_VoidDelay(uint32 Delay)
{
    uint32 start_time = MSYSTICK_u32GetTick();
    while(MSYSTICK_u32GetTick()>start_time-Delay);
}

/*SysTick Handler */ 
void SysTick_Handler(void)
{
    if(SysTick_CallBack != NULL)
    {
        SysTick_CallBack();
    }
	STK_CTRL->B.COUNTFLAG = 0U;/*clear interrupt flag*/
}
