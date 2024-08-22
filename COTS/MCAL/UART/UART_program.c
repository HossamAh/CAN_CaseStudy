/*********************************************************************************/
/* Author    : Hossam Ahmed                                                     */
/* Version   : V01                                                               */
/* Data      : 30 OCT 2023                                                       */
/*********************************************************************************/
/*---------------------------------------------------------------------------------------------------------------------
 *  *  FILE DESCRIPTION
 *  --------------------
 *         File:  UART_program.c
 *       Module:  UART Module
 *  Description:  implementaion C file for UART Driver
---------------------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------------------
 *  INCLUDES
---------------------------------------------------------------------------------------------------------------------*/
#include "UART_interface.h"
#include "../RCC/RCC_interface.h"
#include "../../LIB/Bit_Math.h"
#include "../AFIO/AFIO_interface.h"
#include "../GPIO/GPIO_interface.h"
/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL FUNCTION IMPLEMENTION
---------------------------------------------------------------------------------------------------------------------*/ 

/******************************************************************************
* \Syntax          : void MUSART1_voidInit(void)                                      
* \Description     : Initialize UART by determine baud rate and frame details                                                                              
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                 
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MUSART1_voidInit(void)
{
    /*enable clock of UART1*/
    MRCC_voidEnableClock(RCC_APB2,PERIPHERAL_EN_USART1);
    MRCC_voidEnableClock(RCC_APB2,PERIPHERAL_EN_AFIO);
    MRCC_voidEnableClock(RCC_APB2,PERIPHERAL_EN_IOPA);
    /*set AFIO pins*/
    MAFIO_voidRemapPeripheralPins(UART1_REMAP);//Rx pinA10, TX pinA9
    /*setup AFIO pins for CAN Tx,Rx */
    MGPIO_VoidSetPinMode_TYPE(_GPIOA_PORT,pin10,INPUT_FLOATING);//RX
    MGPIO_VoidSetPinMode_TYPE(_GPIOA_PORT,pin9,OUTPUT_SPEED_50MHZ_AFPUSHPULL);//TX
    /*set baud rate*/
    USART_BRR = BAUD_RATE;
    /*specify frame bits*/
    #if BIT_WORD_8==1
    USART_CR1.B.M = 0;
    #else
    /*9 bit */
    USART_CR1.B.M = 1;
    #endif

    #if PARITY_ENABLED==0
    /*disabled*/
    USART_CR1.B.PCE = 0;
    #else
    /*enabled */
    USART_CR1.B.PCE = 1;
    #endif

    #if EVEN_PARITY==0
    /*ODD*/
    USART_CR1.B.PS = 1;
    #else
    /*EVEN */
    USART_CR1.B.PS = 0;
    #endif

    /*enable transmitter and receiver*/
    USART_CR1.B.TE =1;
    USART_CR1.B.RE =1;

    /*clear status register*/
    USART_SR.Reg=0;
}

/******************************************************************************
* \Syntax          : void MUSART1_voidEnable(void)                                     
* \Description     : Enable UART1                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None               
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MUSART1_voidEnable(void)
{
    /*enable uart*/
    USART_CR1.B.UE =1;
}

/******************************************************************************
* \Syntax          : void MUSART1_voidDisable(void)                                      
* \Description     : Disable  UART timer by clear its ENABLE bit                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                    
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MUSART1_voidDisable(void)
{
    /*disable uart*/
    USART_CR1.B.UE =0;
}


/******************************************************************************
* \Syntax          : void MUSART1_voidSendData(u8 Copy_u16Data)                                     
* \Description     : Sending byte of data by loading it to data register and wait until transmission complete                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : uint8 Copy_u8Data: byte of data to be sent                   
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MUSART1_voidSendData(uint8 Copy_u8Data)
{
    /*check if data register completes transfering data to the shift register and data register is empty*/
    while(USART_SR.B.TXE==0);
    USART_DR = Copy_u8Data;
    /*wait until data is transfered*/
    while (USART_SR.B.TC==0);
    /*clear transmission complete flag*/
    USART_SR.B.TC=0;
}

/******************************************************************************
* \Syntax          : void MUSART1_voidSendString(u8 *Copy_u8String)                                  
* \Description     : Sending string byte by byte  by loading it to data register and wait until transmission complete                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : uint8 *Copy_u8Data: pointer to character array to be sent                   
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MUSART1_voidSendString(const uint8 *Copy_u8String)
{
    while ((*Copy_u8String) != '\0')
    {
        MUSART1_voidSendData(*Copy_u8String);
        Copy_u8String++;
    }
    MUSART1_voidSendData('\0');
}

/******************************************************************************
* \Syntax          : void MUSART1_voidSendNumbers(s32 Copy_s32Number)                                 
* \Description     : Sending string representation of number byte by byte  by loading it to data register and wait until transmission complete                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : sint32 Copy_s32Number: number to be sent                   
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MUSART1_voidSendNumbers(sint32 Copy_s32Number)
{
    uint8 num[15];
    uint8 i=0;
    while(Copy_s32Number!=0)
    {
        uint8 c = '0' + Copy_s32Number%10;
        Copy_s32Number/=10;
        num[i++] = c;   
    }
    MUSART1_voidSendString(num);
}

/******************************************************************************
* \Syntax          : uint8 MUSART1_u8ReceiveData(void)                                 
* \Description     : Receive byte of data
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                   
* \Parameters (out): None                                                      
* \Return value:   : byte of data
*******************************************************************************/
uint8 MUSART1_u8ReceiveData(void)
{
    while(USART_SR.B.RXNE==0);/*wait until reciver shift register data is completely transfered to data register*/
    USART_SR.B.RXNE=0;
    return (uint8)(USART_DR);
}

/******************************************************************************
* \Syntax          : uint8 MUSART1_u8ReceiveDataBlock(uint8* Copy_u8DataArr)                                 
* \Description     : Receive block of data
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : pointer to array                   
* \Parameters (out): pointer to array after modify array elements                                                      
* \Return value:   : uint8 -> number of elements in array.
*******************************************************************************/
uint8 MUSART1_u8ReceiveDataBlock(uint8* Copy_u8DataArr)
{
    uint8 u8data =0;
    uint8 u8count=0;

    do
    {
        u8data = MUSART1_u8ReceiveData();
        Copy_u8DataArr[u8count++]=u8data;
    }while(u8data!='\0');
    Copy_u8DataArr[u8count++]='\0';
}
