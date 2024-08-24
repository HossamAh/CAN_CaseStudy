#include "COTS/MCAL/RCC/RCC_interface.h"
#include "COTS/MCAL/GPIO/GPIO_interface.h"
#include "COTS/MCAL/NVIC/NVIC_Interface.h"
#include "COTS/MCAL/CAN/CAN_config.h"
#include "COTS/MCAL/CAN/CAN_interface.h"
#include "COTS/MCAL/UART/UART_interface.h"
#include "COTS/MCAL/SYSTick/SYSTick_interface.h"
/*Callback functions prototypes*/
void CAN_Transmit_callback();
void CAN_ReceiveFIFO0_callback();
void CAN_ReceiveFIFO1_callback();
/* Error code to use in multi_error callback function in app layer*/
uint8 Error_Code;

void SysTick_callback();

CAN_RX_Frame_t RX_Frame;
uint8 Data[] = {'H','I'};
uint8 RData[8];
int main(void)
{
    MRCC_voidInitSysClock();
    MRCC_voidEnableClock(RCC_APB2,PERIPHERAL_EN_IOPA);
    MGPIO_VoidSetPinMode_TYPE(_GPIOA_PORT,pin0,OUTPUT_SPEED_10MHZ_PUSHPULL);
    MSYSTICK_VoidInit(AHB_8_CLK);
		CAN_InitTypeDef CAN_InitConfig ={
			CAN_MODE_LOOPBACK,//Mode
			CAN_DISABLE,//TimeTriggeredMode
			CAN_ENABLE,//AutoBusOff
			CAN_DISABLE,//AutoWakeUp
			CAN_DISABLE,//AutoRetransmission
			CAN_ENABLE,//ReceiveFifoLocked  //discard incoming msg
			CAN_DISABLE//TransmitFifoPriority 
		}; 
    MCAN_VoidInit(&CAN_InitConfig);
    MNVIC_VoidSetPriorityPolicy(Group16Sub0);
    MNVIC_VoidSetPriority(USB_HP_CAN1_TX,1,0);
    MNVIC_VoidSetPriority(USB_LP_CAN1_RX,1,0);
    MNVIC_VoidSetPriority(CAN_SCE,1,0);
    MNVIC_VoidEnableInterrupt(USB_HP_CAN1_TX);
    MNVIC_VoidEnableInterrupt(USB_LP_CAN1_RX);
    MNVIC_VoidEnableInterrupt(CAN_SCE);

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
    unsigned char c=0;
		MCAN_VoidEnableNotifications(TxMailbox0_completed,CAN_Transmit_callback);
    MCAN_VoidEnableNotifications(TxMailbox1_completed,CAN_Transmit_callback);
    MCAN_VoidEnableNotifications(TxMailbox2_completed,CAN_Transmit_callback);
    MCAN_VoidEnableNotifications(RX_FIFO0_FMP,CAN_ReceiveFIFO0_callback);
    MCAN_VoidEnableNotifications(RX_FIFO1_FMP,CAN_ReceiveFIFO1_callback);
    MCAN_VoidStart();
    MUSART1_voidInit();
    MUSART1_voidEnable();
    MSYSTICK_VoidStartSYSTICK(1000000,SysTick_callback);
    while (1)
    {
        MGPIO_VoidTogglePinValue(_GPIOA_PORT,pin0);

        // Rx_Receive(CAN_RX_FIFO0,&RX_Frame,RData);
				
        
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

void CAN_Transmit_callback()
{
    //MUSART1_voidSendString(Data);
}
void CAN_ReceiveFIFO0_callback()
{
    Rx_Receive(CAN_RX_FIFO0,&RX_Frame,RData,0);
    MUSART1_voidSendString(RData);
}
void CAN_ReceiveFIFO1_callback()
{

}
void SysTick_callback()
{
    static uint8  c=0;
    Data[2] = c+'0';
    c++;
    if(c>9)
        c=0;
    Tx_transmit(0x55A,Data,3,0,0);

}   