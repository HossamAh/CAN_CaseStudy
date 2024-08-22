/*********************************************************************************/
/* Author    : Hossam Ahmed                                                     */
/* Version   : V01                                                               */
/* Data      : 26 OCT 2023                                                       */
/*********************************************************************************/
/*---------------------------------------------------------------------------------------------------------------------
 *  *  FILE DESCRIPTION
 *  --------------------
 *         File:  GPIO_Private.h
 *       Module:  GPIO Module
 *  Description:  Private header file for GPIO Driver
---------------------------------------------------------------------------------------------------------------------*/
#ifndef _GPIO_PRIVATE_H
#define _GPIO_PRIVATE_H

/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL DATA TYPES AND STRUCTURES
---------------------------------------------------------------------------------------------------------------------*/
/* Register Map for GPIO */
typedef struct 
{
	volatile uint32 CR_MODE_CNF0:4;
	volatile uint32 CR_MODE_CNF1:4;
	volatile uint32 CR_MODE_CNF2:4;
	volatile uint32 CR_MODE_CNF3:4;
	volatile uint32 CR_MODE_CNF4:4;
	volatile uint32 CR_MODE_CNF5:4;
	volatile uint32 CR_MODE_CNF6:4;
	volatile uint32 CR_MODE_CNF7:4;
	
}CR_TAG_t;

typedef union
{
	CR_TAG_t B;
	volatile uint32 R;
}CR_REG_t;

typedef struct{
	
	volatile CR_REG_t CRL;
	volatile CR_REG_t CRH;
	volatile uint32 IDR;
	volatile uint32 ODR;
	volatile uint32 BSRR;
	volatile uint32 BRR;
	volatile uint32 LCKR;
}GPIO_t;


/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL MACROS
---------------------------------------------------------------------------------------------------------------------*/
#define 	GPIOA_Base_Address        0x40010800            // Base address of GPIO port A
#define 	GPIOB_Base_Address        0x40010C00            // Base address of GPIO port B
#define 	GPIOC_Base_Address        0x40011000           // Base address of GPIO port C
#define 	GPIOD_Base_Address        0x40011400            // Base address of GPIO port D
#define 	GPIOE_Base_Address        0x40011800            // Base address of GPIO port E
#define 	GPIOF_Base_Address        0x40011C00           // Base address of GPIO port F
#define 	GPIOG_Base_Address        0x40012000           // Base address of GPIO port G

#define 	GPIOA 		((GPIO_t *) GPIOA_Base_Address)
#define 	GPIOB 		((GPIO_t *) GPIOB_Base_Address)
#define 	GPIOC 		((GPIO_t *) GPIOC_Base_Address)
#define 	GPIOD 		((GPIO_t *) GPIOD_Base_Address)
#define 	GPIOE 		((GPIO_t *) GPIOE_Base_Address)
#define 	GPIOF 		((GPIO_t *) GPIOF_Base_Address)
#define 	GPIOG 		((GPIO_t *) GPIOG_Base_Address)



/*lock key bit*/
#define LCKK  16




#endif
