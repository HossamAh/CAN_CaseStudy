/*********************************************************************************/
/* Author    : Hossam Ahmed                                                     */
/* Version   : V01                                                               */
/* Data      : 28 OCT 2023                                                       */
/*********************************************************************************/
/*---------------------------------------------------------------------------------------------------------------------
 *  *  FILE DESCRIPTION
 *  --------------------
 *         File:  NVIC_Private.h
 *       Module:  NVIC Module
 *  Description:  Private header file for NVIC Driver
---------------------------------------------------------------------------------------------------------------------*/
#ifndef _NVIC_PRIVATE_H
#define _NVIC_PRIVATE_H

/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL DATA TYPES AND STRUCTURES
---------------------------------------------------------------------------------------------------------------------*/
/* Register Map for NVIC */
typedef struct{
    /*interrupt set-enable register x*/
	volatile uint32 NVIC_ISER[3];/*from 0x100 - 0x11f*/
    uint32 Reserved1[29];/* from 0x11f -0x180 exclusive*/
    /*interrupt clear-enable register x*/
    volatile uint32 NVIC_ICER[3];
    uint32 Reserved2[29]; /* ISPRx starts at 0xE200 and ICER ends at 19f  that means in decimal there is 24 registers of 4 bytes between them*/
    /*interrupt set-pending register x*/
    volatile uint32 NVIC_ISPR[3];
    uint32 Reserved3[29]; 
    /*interrupt clear-pending register x*/
    volatile uint32 NVIC_ICPR[3];
    uint32 Reserved4[29];
    /*interrupt active bit register x*/
    volatile uint32 NVIC_IABR[3];
    uint32 Reserved5[61];
    /*interrupt priority register x*/
    volatile uint8 NVIC_IPR[80];/*conrol priority of each interrupt of the possible 240 interrupts*/     
}NVIC_MemoryMap_t;

/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL MACROS
---------------------------------------------------------------------------------------------------------------------*/
#define 	NVIC_Base_Address        0xE000E100            // Base address of NVIC


#define 	NVIC 		((NVIC_MemoryMap_t *) NVIC_Base_Address)
#define     NVIC_STIR   ((volatile uint32*)0xE000EF00)            

#define SCB_AIRCR *((volatile uint32*)(0xE000ED0C))
#define NVIC_VECTKEY   0x05FA000


#endif
