#include "COTS/MCAL/RCC/RCC_interface.h"
#include "COTS/MCAL/GPIO/GPIO_interface.h"
#include "COTS/MCAL/CAN/CAN_config.h"
#include "COTS/MCAL/CAN/CAN_interface.h"
uint8 Error_Code;
int main(void)
{
    MRCC_voidInitSysClock();
    MRCC_voidEnableClock(RCC_APB2,PERIPHERAL_EN_IOPA);
    MGPIO_VoidSetPinMode_TYPE(_GPIOA_PORT,pin0,OUTPUT_SPEED_10MHZ_PUSHPULL);
    
		CAN_InitTypeDef CAN_InitConfig ={
			CAN_MODE_LOOPBACK,//Mode
			CAN_DISABLE,//TimeTriggeredMode
			CAN_ENABLE,//AutoBusOff
			CAN_DISABLE,//AutoWakeUp
			CAN_DISABLE,//AutoRetransmission
			CAN_ENABLE,//ReceiveFifoLocked  //discard incoming msg
			CAN_ENABLE//TransmitFifoPriority 
		}; 
    MCAN_VoidInit(&CAN_InitConfig);
    //Read Data from these two IDs (STDId only) on fifo 0 and the filter bank is 0 then two filter numbers 0,1. 0-> Temp ,1->speed
    CAN_Filter_t CAN_config =
    {
        (CAN_filterMode_t)CAN_IDENTIFIERLIST_MODE,//filterMode 
        (CAN_SCALABLEWIDTH_t)CAN_ONE_32BIT_FILTER,//filterScalableWidth
        (0x55A << 5),//FilterIdHigh Higher of ID 1 STDID
        0,//FilterIdLow Lower of ID 1 STDID
        (0x56A << 5),//FilterMaskIdHigh Higher of ID 2 STDID
        0,//FilterMaskIdLow Lower of ID 2 STDID
        0,//FilterFIFOAssignment
        0//FilterBank
    };
    MCAN_VoidConfigureIDFilter(&CAN_config);
    unsigned int c=0;
		CAN_RX_Frame_t RX_Frame;
    uint8 Data[] = {'H','I'};
		uint8 RData[8];
		

    
    MCAN_VoidStart();
    while (1)
    {
        MGPIO_VoidTogglePinValue(_GPIOA_PORT,pin0);
        Data[2] = c;
        c++;
        Tx_transmit(0x55A,Data,3,0,1);

        Rx_Receive(CAN_RX_FIFO0,&RX_Frame,RData,1);
				
        
    }
    
    return 0;
}

void Tx_transmit(uint16 stdId,uint8* pData,uint8 DLC,uint8 RTR,uint8 polling)
{
  CAN_TX_Frame_t Tx_Frame = 
    {
        stdId,//  StdId    
        0,//  ExtId  /*Txframe->ExtId is the 29 bit Id contains standard and extended*/  
        0,//  IDE      
        RTR,//  RTR  write    
        DLC,//  DLC      
        0,//  TransmitGlobalTime 	/*!< Specifies whether the time stamp counter value captured on start of frame transmission*/
    };
    /*check if there is free mailboxes*/
    while(MCAN_u8FreeMailboxes()<=0);
    uint8 local_u8mailbox_used = MCAN_u8Transmission(&Tx_Frame,pData);
    if(polling)
    /*wait until transmission is completed*/
    while(MCAN_u8MailboxPendingStatus(local_u8mailbox_used)==0);
}


void Rx_Receive(uint8 RX_FIFO,CAN_RX_Frame_t* RX_frame,uint8* pData,uint8 polling)
{
    if(polling)
    /*check if FIFO has messages*/
    while(MCAN_u8RX_FIFOMeassages(RX_FIFO)<=0);
    MCAN_VoidReception(RX_FIFO,RX_frame,pData);
}