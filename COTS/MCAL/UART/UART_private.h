/*********************************************************************************/
/* Author    : Hossam Ahmed                                                     */
/* Version   : V01                                                               */
/* Data      : 30 OCT 2023                                                       */
/*********************************************************************************/
/*---------------------------------------------------------------------------------------------------------------------
 *  *  FILE DESCRIPTION
 *  --------------------
 *         File:  UART_Private.h
 *       Module:  UART Module
 *  Description:  Private header file for UART Driver
---------------------------------------------------------------------------------------------------------------------*/
#ifndef _UART_PRIVATE_H
#define _UART_PRIVATE_H


#include "../../LIB/Std_types.h"

/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL DATA TYPES AND STRUCTURES
---------------------------------------------------------------------------------------------------------------------*/
/* Register Map for UART */
typedef struct{
    uint32  PE              :1;
    uint32  FE              :1;
    uint32  NF              :1;
    uint32  ORE             :1;
    uint32  IDLE            :1;
    uint32  RXNE            :1;
    uint32  TC              :1;
    uint32  TXE             :1;
    uint32  LBD             :1;
    uint32  CTS             :1;
    uint32                  :22;    
}UART_USART_SR_BITFIELD;

typedef union 
{
    uint32 Reg;
    UART_USART_SR_BITFIELD B;
}UART_USART_SR_TAG;

typedef struct{
    uint32  SBK              :1;
    uint32  RWU              :1;
    uint32  RE              :1;
    uint32  TE             :1;
    uint32  IDLEIE            :1;
    uint32  RXNEIE            :1;
    uint32  TCIE              :1;
    uint32  TXEIE             :1;
    uint32  PEIE             :1;
    uint32  PS             :1;
    uint32  PCE             :1;
    uint32  WAKE             :1;
    uint32  M             :1;
    uint32  UE             :1;
    uint32               :1;
    uint32  OVER8             :1;
    uint32                  :16;    
}UART_USART_CR1_BITFIELD;

typedef union 
{
    uint32 Reg;
    UART_USART_CR1_BITFIELD B;
}UART_USART_CR1_TAG;



/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL MACROS
---------------------------------------------------------------------------------------------------------------------*/
#define     USART_SR        (*((volatile UART_USART_SR_TAG*)0x40013800))
#define     USART_DR        (*((volatile uint32*)0x40013804))
#define     USART_BRR       (*((volatile uint32*)0x40013808))
#define     USART_CR1       (*((volatile UART_USART_CR1_TAG*)0x4001380C))



#endif
