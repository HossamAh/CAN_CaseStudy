/*********************************************************************************/
/* Author    : Hossam Ahmed                                                     */
/* Version   : V01                                                               */
/* Data      : 30 OCT 2023                                                       */
/*********************************************************************************/
/*---------------------------------------------------------------------------------------------------------------------
 *  *  FILE DESCRIPTION
 *  --------------------
 *         File:  SYSTICK_Private.h
 *       Module:  SYSTICK Module
 *  Description:  Private header file for SYSTICK Driver
---------------------------------------------------------------------------------------------------------------------*/
#ifndef _SYSTICK_PRIVATE_H
#define _SYSTICK_PRIVATE_H




/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL DATA TYPES AND STRUCTURES
---------------------------------------------------------------------------------------------------------------------*/
/* Register Map for SYSTICK */
typedef struct{
    uint32  ENABLE      :1;
    uint32  TICKINT     :1;
    uint32  CLKSOURCE   :1;
    uint32              :13;
    uint32  COUNTFLAG   :1;
    uint32              :15;    
}SYSTICK_STK_CTRL_BITFIELD;

typedef union 
{
    uint32 Reg;
    SYSTICK_STK_CTRL_BITFIELD B;
}SYSTICK_STK_CTRL_TAG;

/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL MACROS
---------------------------------------------------------------------------------------------------------------------*/
#define 	SYSTICK_STK_CTRL_Address        0xE000E010            // address of STK_CTRL


#define 	STK_CTRL 		((volatile SYSTICK_STK_CTRL_TAG *) SYSTICK_STK_CTRL_Address)
#define     STK_LOAD        ((volatile uint32*)0xE000E014)
#define     STK_VAL         ((volatile uint32*)0xE000E018)
#define     STK_CALIB       ((volatile uint32*)0xE000E01C)



#endif
