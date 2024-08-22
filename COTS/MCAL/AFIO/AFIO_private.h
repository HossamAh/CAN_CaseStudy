/*********************************************************************************/
/* Author    : Hossam Ahmed                                                        */
/* Version   : V01                                                               */
/* Date      : 11 may  2024                                                      */
/*********************************************************************************/
/*---------------------------------------------------------------------------------------------------------------------
 *  *  FILE DESCRIPTION
 *  --------------------
 *         File:  AFIO_private.h
 *       Module:  AFIO Module
 *  Description:  private header file for AFIO Driver
---------------------------------------------------------------------------------------------------------------------*/


#ifndef AFIO_PRIVATE_H
#define AFIO_PRIVATE_H


/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL DATA TYPES AND STRUCTURES
---------------------------------------------------------------------------------------------------------------------*/
/* Register Map */
typedef struct 
{
	uint32 SPI1:1;
	uint32 I2C1:1;
	uint32 USART1:1;
	uint32 USART2:1;
	uint32 USART3:2;
	uint32 TIM1:2;
	uint32 TIM2:2;
	uint32 TIM3:2;
	uint32 TIM4:1;
	uint32 CAN:2;
	uint32 PD01:1;
	uint32 TIM5CH4_I:1;
	uint32 ADC1_E_TRGINJ:1;
	uint32 ADC1_E_TRGREG:1;
	uint32 ADC2_E_TRGINJ:1;
	uint32 ADC2_E_TRGREG:1;
	uint32 :3;
	uint32 SWJ_CFG:3;
	uint32 :5;
}MAPR_TAG_t;

typedef union 
{
	MAPR_TAG_t B;
	uint32 R;
	/* data */
}MAPR_REG_t;

typedef struct
{
	volatile uint32 EVCR;
	volatile MAPR_REG_t MAPR;
	volatile uint32 EXTICR[4];
	volatile uint32 MAPR2;
}AFIO_t;

/*******************   BASE Address Definition    *********************/

#define AFIO_BASE_ADDRESS	0x40010000		//define the boundary address of AFIO

#define AFIO 		((volatile AFIO_t *) AFIO_BASE_ADDRESS)


#endif // AFIO_PRIVATE_H
