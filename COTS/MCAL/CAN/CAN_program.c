/*********************************************************************************/
/* Author    : Hossam Ahmed                                                     */
/* Version   : V01                                                               */
/* Data      : 26 OCT 2023                                                       */
/*********************************************************************************/
/*---------------------------------------------------------------------------------------------------------------------
 *  *  FILE DESCRIPTION
 *  --------------------
 *         File:  CAN_interface.h
 *       Module:  CAN Module
 *  Description:  Interface header file for CAN Driver
---------------------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------------------
 *  INCLUDES
---------------------------------------------------------------------------------------------------------------------*/

#include "../../LIB/Std_Types.h"
#include "../../LIB/Bit_Math.h"

#include "CAN_config.h"
#include "CAN_private.h"
#include "CAN_interface.h"


#include "../GPIO/GPIO_interface.h"
#include "../RCC/RCC_interface.h"
#include "../AFIO/AFIO_interface.h"

/*---------------------------------------------------------------------------------------------------------------------
 *  Global Variables
---------------------------------------------------------------------------------------------------------------------*/
/*Tx Callback pointer to function */
void (*CAN_TxMailbox0_Completed_Callback)();
void (*CAN_TxMailbox1_Completed_Callback)();
void (*CAN_TxMailbox2_Completed_Callback)();

/*TX failed*/
void (*CAN_TxMailbox0_ArbitrationERR_Callback)();//ArbitrationError
void (*CAN_TxMailbox0_TXERR_Callback)();//transmitError
void (*CAN_TxMailbox1_ArbitrationERR_Callback)();//ArbitrationError
void (*CAN_TxMailbox1_TXERR_Callback)();//transmitError
void (*CAN_TxMailbox2_ArbitrationERR_Callback)();//ArbitrationError
void (*CAN_TxMailbox2_TXERR_Callback)();//transmitError

/*TX Abort*/
void (*CAN_TxMailbox0_Abort_Callback)();//Abort
void (*CAN_TxMailbox1_Abort_Callback)();//Abort
void (*CAN_TxMailbox2_Abort_Callback)();//Abort


/*Rx Callback pointer to function */
void (*CAN_RxFIFO0_FMP_Callback)();//receive new message
void (*CAN_RxFIFO0_FULL_Callback)();//full fifo
void (*CAN_RxFIFO0_FOVR_Callback)();//overrun 

void (*CAN_RxFIFO1_FMP_Callback)();//receive new message
void (*CAN_RxFIFO1_FULL_Callback)();//full fifo
void (*CAN_RxFIFO1_FOVR_Callback)();//overrun 

/*Errors Callbacks*/
void (*CAN_EWG_Error_Callback)();//Enter Warning Error state (Active Error)  
void (*CAN_EPV_Error_Callback)();//Enter Passive Error state (Passive Error)  
void (*CAN_BOF_Error_Callback)();//Enter Bus Off Error state (Bus Off)
void (*CAN_Multi_Error_Callback)();//Error from the errors in Error code(ack , stuffing , format, ...)

/* Error code to use in multi_error callback function in app layer*/
extern uint8 Error_Code;

/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL FUNCTIONS
---------------------------------------------------------------------------------------------------------------------*/
/******************************************************************************
* \Syntax          : void MCAN_VoidInit(const CAN_InitTypeDef* pInitConfig)                                      
* \Description     : initialize CAN asnd check the default configuation supported                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : pInitConfig  pointer to CAN initalization configurations.                   
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MCAN_VoidInit(const CAN_InitTypeDef* pInitConfig) 
{
    /*Enable CAN clock and setup the AFIO configuarions*/
    MRCC_voidEnableClock(RCC_APB1,PERIPHERAL_EN_CAN1);
    MRCC_voidEnableClock(RCC_APB2,PERIPHERAL_EN_AFIO);
    MRCC_voidEnableClock(RCC_APB2,PERIPHERAL_EN_IOPB);

    /*set AFIO pins*/
    MAFIO_voidRemapPeripheralPins(CAN_REMAP);//Rx pinB8, TX pinB9
    /*setup AFIO pins for CAN Tx,Rx */
    MGPIO_VoidSetPinMode_TYPE(_GPIOB_PORT,pin8,INPUT_FLOATING);//RX
    MGPIO_VoidSetPinMode_TYPE(_GPIOB_PORT,pin9,OUTPUT_SPEED_2MHZ_AFPUSHPULL);//RX

    /* After Reset CAN boot up in sleep mode
    first we need to exit from it*/
    //clear SLEEP bit
    CLEAR_BIT(CAN_Control->MCR,1);	
    /* wait to exit sleep mode SLAK bit ack of sleep  */
    while (!(READ_BIT(CAN_Control->MSR,1) == 0));

    /*Switch to initialization mode for init*/
    /*set INRQ bit */
    SET_BIT(CAN_Control->MCR,0);
    /*wait until hardware set the INAK bit ack of init*/
    while (!(READ_BIT(CAN_Control->MSR,0)==1));
    
    /*from bits of control register*/

    /** CHECK Transmit FIFO priority **/
    /** CHECK Receive FIFO locked mode **/
    /** CHECK automatic retransmission **/
    /** CHECK automatic wakeup mode **/
    /** CHECK automatic bus-off management **/
    /** CHECK Time triggered communication mode **/
    
    /** CHECK Transmit FIFO priority **/
    if(pInitConfig->TransmitFifoPriority==CAN_ENABLE)
    /*by identifer:lowest ID has higher priority. if all IDs is equal then lowest number mailbox is sent */
    CLEAR_BIT(CAN_Control->MCR,2);//TXFP Transmit FIFO priority
    else
    /*by transmit request order*/
    SET_BIT(CAN_Control->MCR,2);

    /** CHECK Receive FIFO locked mode **/
    /*RFLM: Receive FIFO locked mode
    0: Receive FIFO not locked on overrun. Once a receive FIFO is full the next incoming
    message will overwrite the previous one.
    1: Receive FIFO locked against overrun. Once a receive FIFO is full the next incoming
    message will be discarded.*/
    // #if ReceiveFIFOLockedMode == CAN_ENABLE
    if(pInitConfig->ReceiveFifoLocked==CAN_ENABLE)
    SET_BIT(CAN_Control->MCR,3);//discard
    else
    CLEAR_BIT(CAN_Control->MCR,3);//overwrite
    

    /*NART: No automatic retransmission
    0: The CAN hardware will automatically retransmit the message until it has been
    successfully transmitted according to the CAN standard.
    1: A message will be transmitted only once, independently of the transmission result
    (successful, error or arbitration lost).*/
    if(pInitConfig->AutoRetransmission ==CAN_DISABLE)    
    SET_BIT(CAN_Control->MCR,4);
    else
    CLEAR_BIT(CAN_Control->MCR,4);
    
    /*AWUM: Automatic wakeup mode
    This bit controls the behavior of the CAN hardware on message reception during Sleep
    mode.
    0: The Sleep mode is left on software request by clearing the SLEEP bit of the CAN_MCR
    register.
    1: The Sleep mode is left automatically by hardware on CAN message detection.
    */
   if(pInitConfig->AutoWakeUp==CAN_ENABLE)
    SET_BIT(CAN_Control->MCR,5);
    else
    CLEAR_BIT(CAN_Control->MCR,5);
    
    /*ABOM: Automatic bus-off management
    This bit controls the behavior of the CAN hardware on leaving the Bus-Off state.
    0: The Bus-Off state is left on software request, once 128 occurrences of 11 recessive bits
    have been monitored and the software has first set and cleared the INRQ bit of the
    CAN_MCR register.
    1: The Bus-Off state is left automatically by hardware once 128 occurrences of 11 recessive
    bits have been monitored.*/
    if(pInitConfig->AutoBusOff==CAN_ENABLE)
    SET_BIT(CAN_Control->MCR,6);
    else
    CLEAR_BIT(CAN_Control->MCR,6);
    
    /*Time stamp in TX and RX mailbox*/
    if (pInitConfig->TimeTriggeredMode==CAN_ENABLE)
    SET_BIT(CAN_Control->MCR,7);
    else
    CLEAR_BIT(CAN_Control->MCR,7);
    
    CAN_BitTimingConfig CAN_bitRateConfig[7] = {{2, 13, 10}, {2, 13, 5}, {2, 13, 4}, {2, 13, 2}, {2, 13, 1},{1, 8, 1}, {1, 6, 1}};



    /** Set the bit timing register **/
    // CAN_Control->BTR = (uint32) (
	// 	  (((CAN_bitRateConfig[BAUDRATE].TS2-1) << 20) |
	// 	  ((CAN_bitRateConfig[BAUDRATE].TS1-1) << 16) |
	// 	  (CAN_bitRateConfig[BAUDRATE].BRP-1)));
    CAN_Control->BTR.B.TS2 = (CAN_bitRateConfig[BAUDRATE].TS2-1);
    CAN_Control->BTR.B.TS1 = (CAN_bitRateConfig[BAUDRATE].TS1-1);
    CAN_Control->BTR.B.BRP = (CAN_bitRateConfig[BAUDRATE].BRP-1);
    
    
			
    /*Testing mode*/
    if( pInitConfig->Mode == CAN_MODE_NORMAL)
    {
        CAN_Control->BTR.B.SILM=0;
        CAN_Control->BTR.B.LBKM=0;
    }
    else if( pInitConfig->Mode == CAN_MODE_SILENT)/*receive only*/
    {
        CAN_Control->BTR.B.SILM=1;
        CAN_Control->BTR.B.LBKM=0;
    }
    else if( pInitConfig->Mode == CAN_MODE_LOOPBACK)
    {
        CAN_Control->BTR.B.SILM=0;
        CAN_Control->BTR.B.LBKM=1;
    }
    else if( pInitConfig->Mode == CAN_MODE_SILENT_LOOPBACK)
    {
        CAN_Control->BTR.B.SILM=1;
        CAN_Control->BTR.B.LBKM=1;
    }
    else{}

}

/******************************************************************************
* \Syntax          : void MCAN_VoidConfigureIDFilter(CAN_Filter_t *pFilterConfig)                                      
* \Description     : initialize CAN filter banks and filers modes based on configuraion parameters                                                                          
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : CAN_Filter_t *pFilterConfig                   
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MCAN_VoidConfigureIDFilter(CAN_Filter_t *pFilterConfig)
{
    /*at first we enter initalization mode for filter banks FINIT=1 in CAN_FMR*/
    SET_BIT(CAN_Filter->FMR,0);
    /*deactivate the filter bank to start the init  in CAN_FA1R filter number bit*/
    CLEAR_BIT(CAN_Filter->FA1R,pFilterConfig->FilterBank);

		
		/*set the Mode*/
			if(pFilterConfig->filterMode == CAN_IDENTIFIERLIST_MODE)
			{
				SET_BIT(CAN_Filter->FM1R,pFilterConfig->FilterBank);
			}
			else if( pFilterConfig->filterMode == CAN_MASK_MODE)
			{
				CLEAR_BIT(CAN_Filter->FM1R,pFilterConfig->FilterBank);
			}
			else{}
	
    /*configure filter bank according to mode and scalable width*/
    if(pFilterConfig->filterScalableWidth == CAN_ONE_32BIT_FILTER)
    {
        /*set scale width*/
        SET_BIT(CAN_Filter->FS1R,pFilterConfig->FilterBank);
			/*ID in mask mode or first ID in ID List*/
			/*																																STDID -EXTID[17:13]				                 EXTID[12:5]	<-RTR		*/
				CAN_Filter->FiRx[pFilterConfig->FilterBank].FxR1 = (((0x0000FFFF & pFilterConfig->FilterIdHigh) <<16) | pFilterConfig->FilterIdLow);
			/*Mask in mask mode or second ID in ID List*/
			/*																																STDID -EXTID[17:13]				                 EXTID[12:5]	<-RTR		*/
				CAN_Filter->FiRx[pFilterConfig->FilterBank].FxR2 = (((0x0000FFFF & pFilterConfig->FilterMaskIdHigh) <<16) | pFilterConfig->FilterMaskIdLow);
			
    }
    else if(pFilterConfig->filterScalableWidth==CAN_TWO16BIT_FILTER)
    {
        /*set scale width*/
        CLEAR_BIT(CAN_Filter->FS1R,pFilterConfig->FilterBank);
				
			/*two IDs in ID List mode and Mask(FilterMaskIdLow) and ID(FilterIdLow) in ID Mask mode*/
			/*																		ID:				STDID-RTR-IDE-EXTID[17:15]																																*/
				CAN_Filter->FiRx[pFilterConfig->FilterBank].FxR1 = (((0x0000FFFF & pFilterConfig->FilterMaskIdLow) <<16) | pFilterConfig->FilterIdLow);
			/*two IDs in ID List mode and Mask(FilterMaskIdHigh) and ID(FilterMaskIdLow) in ID Mask mode*/
			/*																		ID:				STDID-RTR-IDE-EXTID[17:15]																																*/
				CAN_Filter->FiRx[pFilterConfig->FilterBank].FxR2 = (((0x0000FFFF & pFilterConfig->FilterMaskIdHigh) <<16) | pFilterConfig->FilterIdHigh);
			
    }
    else{}

    /*after configure filter bank registers add it to specific FIFO*/
    if(pFilterConfig->FilterFIFOAssignment==0)
    {
        /*assign this filter bank to fifo 0*/
        CLEAR_BIT(CAN_Filter->FFA1R,pFilterConfig->FilterBank);
    }
    else
    {
        /*assign this filter bank to fifo 1*/
        SET_BIT(CAN_Filter->FFA1R,pFilterConfig->FilterBank);
    }

    /*filter Acivate*/
    SET_BIT(CAN_Filter->FA1R,pFilterConfig->FilterBank);

    /*leave init mode of filterbank */
    CLEAR_BIT(CAN_Filter->FMR,0);
}

/******************************************************************************
* \Syntax          : uint8 MCAN_u8Transmission(CAN_TX_Frame_t * TXframe,uint8 Data[])                                      
* \Description     : initialize CAN Frame to be send and put it in Tx mailbox and                                                                           
* \Sync\Async      : ASynchronous (when tx is transmitted interrupt notify the app)                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : CAN_TX_Frame * TXframe , Data array represent the data bytes                  
* \Parameters (out): None                                                      
* \Return value:   : return the mailbox number used to transmit
*******************************************************************************/
uint8 MCAN_u8Transmission(CAN_TX_Frame_t * TXframe,uint8 Data[])
{
    /*get the empty mailbox number (CODE in CAN TSR)*/
    /*In case at least one transmit mailbox is free, the code value is equal to the number of the
    *next transmit mailbox free.
    *In case all transmit mailboxes are pending, the code value is equal to the number of the
    *transmit mailbox with the lowest priority.*/
    uint8 Local_u8EmptyMailboxNumber = (uint8)CAN_Control->TSR.CODE;

    /*check if there is any empty mailbox not to overwrite any pending mailbox  */
    if(CAN_Control->TSR.TME0==1||CAN_Control->TSR.TME1==1||CAN_Control->TSR.TME2==1)
    {
        CAN_Mailbox->Txmailbox[Local_u8EmptyMailboxNumber].TIR.IDE=TXframe->IDE;
        if(TXframe->IDE==CAN_ID_STD)
        {
            CAN_Mailbox->Txmailbox[Local_u8EmptyMailboxNumber].TIR.STD_EXID18_28 = TXframe->StdId;
        }
        else if(TXframe->IDE==CAN_ID_EXT)
        {
            /*Txframe->ExtId is the 29 bit Id contains standard and extended*/
            CAN_Mailbox->Txmailbox[Local_u8EmptyMailboxNumber].TIR.EXID = TXframe->ExtId;
            CAN_Mailbox->Txmailbox[Local_u8EmptyMailboxNumber].TIR.STD_EXID18_28 = (TXframe->ExtId>>18);
        }
        CAN_Mailbox->Txmailbox[Local_u8EmptyMailboxNumber].TIR.RTR = TXframe->RTR;
        CAN_Mailbox->Txmailbox[Local_u8EmptyMailboxNumber].TDTR.DLC = TXframe->DLC;
        /*Enable or Disable sending time stamp*/
        CAN_Mailbox->Txmailbox[Local_u8EmptyMailboxNumber].TDTR.TGT = TXframe->TransmitGlobalTime;


        uint8 Local_u8itr=0;
        for(Local_u8itr=0;Local_u8itr<TXframe->DLC;Local_u8itr++)
        {
            if(Local_u8itr<=3)
            {
                CAN_Mailbox->Txmailbox[Local_u8EmptyMailboxNumber].TDLR.DATA[Local_u8itr] = Data[Local_u8itr];
            }
            else
            {
                CAN_Mailbox->Txmailbox[Local_u8EmptyMailboxNumber].TDHR.DATA[Local_u8itr-4] = Data[Local_u8itr];
            }
        }

        /*Request to send*/
        CAN_Mailbox->Txmailbox[Local_u8EmptyMailboxNumber].TIR.TXRQ=1;
        //return the mailbox number to be used for polling
        return Local_u8EmptyMailboxNumber;
        //while(CAN_Mailbox->Txmailbox[Local_u8EmptyMailboxNumber].TIR.TXRQ == 1); // clear by hardware when mailbox empty
    }
}


/******************************************************************************
* \Syntax          : void MCAN_VoidReception(uint8 RX_FIFO,CAN_RX_Frame_t * RXframe,uint8 Data[])                                      
* \Description     : Read CAN frame from RX FIFO and store its data in Data Array.                                                                           
* \Sync\Async      : Synchronous                                                
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) :  RX_ FIFO number of fifo to read from,CAN_RX_Frame * RXframe , Data array represent the data bytes                  
* \Parameters (out): CAN_RX_Frame * RXframe , Data array represent the data bytes                                                      
* \Return value:   : None
*******************************************************************************/
void MCAN_VoidReception(uint8 RX_FIFO,CAN_RX_Frame_t * RXframe,uint8 Data[])
{
    /*we enter this function after RX interrupt and the callback of specific FIFO call this function
    * so the Frame is ready in the FIFO mailbox*/
    /*FIFO Registers Contain the frame to be read (the first received one)*/
    uint8 msg_count=CAN_Control->RFR[RX_FIFO].FMP;
		// while(msg_count<=0);
    /*Read the IDE from received frame*/
    RXframe->IDE = CAN_Mailbox->RXFIFO[RX_FIFO].RIR.IDE;
    if(CAN_Mailbox->RXFIFO[RX_FIFO].RIR.IDE==CAN_ID_STD)
    {
        RXframe->StdId = CAN_Mailbox->RXFIFO[RX_FIFO].RIR.STD_EXID18_28;
    }
    else if(CAN_Mailbox->RXFIFO[RX_FIFO].RIR.IDE==CAN_ID_EXT)
    {
        RXframe->ExtId = (CAN_Mailbox->RXFIFO[RX_FIFO].RIR.STD_EXID18_28<<18)|CAN_Mailbox->RXFIFO[RX_FIFO].RIR.EXID;
    }
    else{}
    RXframe->RTR = CAN_Mailbox->RXFIFO[RX_FIFO].RIR.RTR;
    RXframe->DLC = CAN_Mailbox->RXFIFO[RX_FIFO].RDTR.DLC;
    /*this index indicates which filter is accept this frame then it tells us this data related to which variable according to out mapping (index->variable)*/
    RXframe->FilterMatchIndex = CAN_Mailbox->RXFIFO[RX_FIFO].RDTR.FMI;
    RXframe->TimeStamp = CAN_Mailbox->RXFIFO[RX_FIFO].RDTR.TIME;
    uint8 Local_u8Itr;
		for(Local_u8Itr=0;Local_u8Itr<8;Local_u8Itr++)
				Data[Local_u8Itr]=0;
    for(Local_u8Itr=0;Local_u8Itr<RXframe->DLC;Local_u8Itr++)
    {
        if(Local_u8Itr<=3)
            Data[Local_u8Itr] = CAN_Mailbox->RXFIFO[RX_FIFO].RDLR.DATA[Local_u8Itr];
        else
            Data[Local_u8Itr] = CAN_Mailbox->RXFIFO[RX_FIFO].RDHR.DATA[Local_u8Itr-4];
    }
    
    /*After reading the frame ,Release the FIFO to reduce the msgs count and receive another one*/
    CAN_Control->RFR[RX_FIFO].RFOM=1;   
}

/******************************************************************************
* \Syntax          : void MCAN_VoidStart()                                      
* \Description     : Start CAN by leaving the initialization mode to normal mode                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MCAN_VoidStart()
{  
    /*Clearing the INRQ bit in CAN_MCR Register*/
    CLEAR_BIT(CAN_Control->MCR,0);
    /*confirm that normal mode is start when INAK bit in CAN_MSR Register is cleared*/
    while(!(READ_BIT(CAN_Control->MSR,0)==0));
    
}
/******************************************************************************
* \Syntax          : uint8 MCAN_u8FreeMailboxes(void)                                      
* \Description     : Return the number of free mailboxes to start transmit                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                
* \Parameters (out): None                                                      
* \Return value:   : number of free mailboxes-> 0-3
*******************************************************************************/
uint8 MCAN_u8FreeMailboxes(void)
{
    uint8 local_u8counter=0;
    if(CAN_Control->TSR.TME0==1)
        local_u8counter++;
    if(CAN_Control->TSR.TME1==1)
        local_u8counter++;
    if(CAN_Control->TSR.TME2==1)
            local_u8counter++;
    return local_u8counter;
}


/******************************************************************************
* \Syntax          : uint8 MCAN_u8MailboxPendingStatus(uint8 mailboxNumber)                                      
* \Description     : Return whether the transmission is completed or not                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : uint8 mailboxNumber:number of the mailbox                
* \Parameters (out): None                                                      
* \Return value:   : status of mailbox 0->pending,1->not pending(completed)
*******************************************************************************/
uint8 MCAN_u8MailboxPendingStatus(uint8 mailboxNumber)
{
    switch (mailboxNumber)
    {
    case 0:
        return CAN_Control->TSR.RQCP0;
        break;
        case 1:
        return CAN_Control->TSR.RQCP1;
        break;
        case 2:
        return CAN_Control->TSR.RQCP2;
        break;
    }
}

/******************************************************************************
* \Syntax          : uint8 MCAN_u8RX_FIFOMeassages(uint8 RX_FIFO)                                      
* \Description     : Return the number of messages in fifo                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : uint8 RX_FIFO number of FIFO 0->FIFO0,1->FIFO1                
* \Parameters (out): None                                                      
* \Return value:   : number of messages in FIFO
*******************************************************************************/
uint8 MCAN_u8RX_FIFOMeassages(uint8 RX_FIFO)
{
    return CAN_Control->RFR[RX_FIFO].FMP;    
}

/******************************************************************************
* \Syntax          : void MCAN_VoidEnableNotifications(CAN_notifications_t notification,void (*callback_ptr)())                                      
* \Description     : Enable interrupt enable of CAN interrupt and set the callback function                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : notification : type of notification to enable , callback_ptr ptr to callback function               
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MCAN_VoidEnableNotifications(CAN_notifications_t notification,void (*callback_ptr)())
{
    switch (notification)
    {
    case TxMailbox0_completed:
        CAN_Control->IER.B.TMEIE=1;
        CAN_TxMailbox0_Completed_Callback=callback_ptr;
        break;
    
    case TxMailbox1_completed:
        CAN_Control->IER.B.TMEIE=1;
        CAN_TxMailbox1_Completed_Callback=callback_ptr;
        break;
    
    case TxMailbox2_completed:
        CAN_TxMailbox2_Completed_Callback=callback_ptr;
        CAN_Control->IER.B.TMEIE=1;
        break;
    case TxMailbox0_Abort:
        CAN_Control->IER.B.TMEIE=1;
        CAN_TxMailbox0_Abort_Callback=callback_ptr;
        break;
    
    case TxMailbox1_Abort:
        CAN_Control->IER.B.TMEIE=1;
        CAN_TxMailbox1_Abort_Callback=callback_ptr;
        break;
    
    case TxMailbox2_Abort:
        CAN_TxMailbox2_Abort_Callback=callback_ptr;
        CAN_Control->IER.B.TMEIE=1;
        break;
    case TxMailbox0_TXERR:
        CAN_Control->IER.B.TMEIE=1;
        CAN_TxMailbox0_TXERR_Callback=callback_ptr;
        break;
    
    case TxMailbox1_TXERR:
        CAN_Control->IER.B.TMEIE=1;
        CAN_TxMailbox1_TXERR_Callback=callback_ptr;
        break;
    
    case TxMailbox2_TXERR:
        CAN_TxMailbox2_TXERR_Callback=callback_ptr;
        CAN_Control->IER.B.TMEIE=1;
        break;
    
    case RX_FIFO0_FMP:
        CAN_RxFIFO0_FMP_Callback=callback_ptr;
        CAN_Control->IER.B.FMPIE0=1;
        break;
    case RX_FIFO0_FULL:
        CAN_RxFIFO0_FULL_Callback=callback_ptr;
        CAN_Control->IER.B.FFIE0=1;
        break;
    case RX_FIFO0_FOVR:
        CAN_RxFIFO0_FOVR_Callback=callback_ptr;
        CAN_Control->IER.B.FOVIE0=1;
        break;
    case RX_FIFO1_FMP:
        CAN_RxFIFO1_FMP_Callback=callback_ptr;
        CAN_Control->IER.B.FMPIE1=1;
        break;
    case RX_FIFO1_FULL:
        CAN_RxFIFO1_FULL_Callback=callback_ptr;
        CAN_Control->IER.B.FFIE1=1;
        break;
    case RX_FIFO1_FOVR:
        CAN_RxFIFO1_FOVR_Callback=callback_ptr;
        CAN_Control->IER.B.FOVIE1=1;
        break;
    case CAN_EWG_Error:
        CAN_EWG_Error_Callback=callback_ptr;
        CAN_Control->IER.B.ERRIE=1;
        CAN_Control->IER.B.EWGIE=1;
        break;
    case CAN_EPV_Error:
        CAN_EPV_Error_Callback=callback_ptr;
        CAN_Control->IER.B.ERRIE=1;
        CAN_Control->IER.B.EPVIE=1;
        break;
    case CAN_BOF_Error:
        CAN_BOF_Error_Callback=callback_ptr;
        CAN_Control->IER.B.ERRIE=1;
        CAN_Control->IER.B.BOFIE=1;
        break;
    case CAN_Multi_Error:
        CAN_Multi_Error_Callback=callback_ptr;
        CAN_Control->IER.B.ERRIE=1;
        CAN_Control->IER.B.LECIE=1;
        break;
    default:
        break;
    }
}


/******************************************************************************
* \Syntax          : void MCAN_VoidDisableNotifications(CAN_notifications_t notification)                                      
* \Description     : Disable interrupt disable of CAN interrupt                                                                            
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : notification : type of notification to disable                
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MCAN_VoidDisableNotifications(CAN_notifications_t notification)
{
    switch (notification)
    {
    case TxMailbox0_completed:
        CAN_Control->IER.B.TMEIE=0;
        break;
    
    case TxMailbox1_completed:
        CAN_Control->IER.B.TMEIE=0;
        break;
    
    case TxMailbox2_completed:
        CAN_Control->IER.B.TMEIE=0;
        break;
    case TxMailbox0_Abort:
        CAN_Control->IER.B.TMEIE=0;
        break;
    
    case TxMailbox1_Abort:
        CAN_Control->IER.B.TMEIE=0;
        break;
    
    case TxMailbox2_Abort:
        CAN_Control->IER.B.TMEIE=0;
        break;
    case TxMailbox0_TXERR:
        CAN_Control->IER.B.TMEIE=0;
        break;
    
    case TxMailbox1_TXERR:
        CAN_Control->IER.B.TMEIE=0;
        break;
    
    case TxMailbox2_TXERR:
        CAN_Control->IER.B.TMEIE=0;
        break;
    
    case RX_FIFO0_FMP:
        CAN_Control->IER.B.FMPIE0=0;
        break;
    case RX_FIFO0_FULL:
        CAN_Control->IER.B.FFIE0=0;
        break;
    case RX_FIFO0_FOVR:
        CAN_Control->IER.B.FOVIE0=0;
        break;
    case RX_FIFO1_FMP:
        CAN_Control->IER.B.FMPIE1=0;
        break;
    case RX_FIFO1_FULL:
        CAN_Control->IER.B.FFIE1=0;
        break;
    case RX_FIFO1_FOVR:
        CAN_Control->IER.B.FOVIE1=0;
        break;
    case CAN_EWG_Error:
        CAN_Control->IER.B.ERRIE=0;
        CAN_Control->IER.B.EWGIE=0;
        break;
    case CAN_EPV_Error:
        CAN_Control->IER.B.ERRIE=0;
        CAN_Control->IER.B.EPVIE=0;
        break;
    case CAN_BOF_Error:
        CAN_Control->IER.B.ERRIE=0;
        CAN_Control->IER.B.BOFIE=0;
        break;
    case CAN_Multi_Error:
        CAN_Control->IER.B.ERRIE=0;
        CAN_Control->IER.B.LECIE=0;
        break;
    default:
        break;
    }
}

/*---------------------------------------------------------------------------------------------------------------------
 *  Interrupt Handlers
---------------------------------------------------------------------------------------------------------------------*/
  void USB_HP_CAN1_TX_IRQHandler()
  {
    /*according to the state of the flags determine which callback to call*/
    if(CAN_Control->TSR.RQCP0==1)
    {
        /*After transmit mailbox state turns from transmit to empty in both cases : passed or failed or aborted*/
        if(CAN_Control->TSR.TXOK0==1)
        {
            if(CAN_TxMailbox0_Completed_Callback!=NULL)
            {
                CAN_TxMailbox0_Completed_Callback();
            }
        }
        else if(CAN_Control->TSR.ALST0==1)
        {
            CAN_TxMailbox0_ArbitrationERR_Callback();
        }
        else if(CAN_Control->TSR.TERR0==1)
        {
            CAN_TxMailbox0_TXERR_Callback();
        }
        else if(CAN_Control->TSR.ABRQ0==1)
        {
            CAN_TxMailbox0_Abort_Callback();
        }
        /*clear flag*/
        CAN_Control->TSR.RQCP0 = 1;
    }
    else if(CAN_Control->TSR.RQCP1==1)
    {
        if(CAN_Control->TSR.TXOK1==1)
        {
            if(CAN_TxMailbox1_Completed_Callback!=NULL)
            {
                CAN_TxMailbox1_Completed_Callback();
            }
        }
        else if(CAN_Control->TSR.ALST1==1)
        {
            CAN_TxMailbox1_ArbitrationERR_Callback();
        }
        else if(CAN_Control->TSR.TERR1==1)
        {
            CAN_TxMailbox1_TXERR_Callback();
        }
        else if(CAN_Control->TSR.ABRQ1==1)
        {
            CAN_TxMailbox1_Abort_Callback();
        }
        /*clear flag*/
        CAN_Control->TSR.RQCP1 = 1;
    }
    else if(CAN_Control->TSR.RQCP2==1)
    {
        if(CAN_Control->TSR.TXOK2==1)
        {
            if(CAN_TxMailbox2_Completed_Callback!=NULL)
            {
                CAN_TxMailbox2_Completed_Callback();
            }
        }
        else if(CAN_Control->TSR.ALST2=1)
        {
            CAN_TxMailbox2_ArbitrationERR_Callback();
        }
        else if(CAN_Control->TSR.TERR2==1)
        {
            CAN_TxMailbox2_TXERR_Callback();
        }
        else if(CAN_Control->TSR.ABRQ2==1)
        {
            CAN_TxMailbox2_Abort_Callback();
        }
        /*clear flag*/
        CAN_Control->TSR.RQCP2 = 1;
    }
  }
  void USB_LP_CAN1_RX0_IRQHandler()
  {
    if(CAN_Control->IER.B.FMPIE0==1 &&CAN_Control->RFR[CAN_RX_FIFO0].FMP<3)
    {
        if(CAN_RxFIFO0_FMP_Callback!=NULL)
        {
            CAN_RxFIFO0_FMP_Callback();
        }
    }
    else if(CAN_Control->IER.B.FFIE0==1 &&CAN_Control->RFR[CAN_RX_FIFO0].FULL==1)
    {
        if(CAN_RxFIFO0_FULL_Callback!=NULL)
        {
            CAN_RxFIFO0_FULL_Callback();
        }
        /*clear flag*/
        CAN_Control->RFR[CAN_RX_FIFO0].FULL=0;
    }
    else if(CAN_Control->IER.B.FOVIE0==1 &&CAN_Control->RFR[CAN_RX_FIFO0].FOVR==1)
    {
        if(CAN_RxFIFO0_FOVR_Callback!=NULL)
        {
            CAN_RxFIFO0_FOVR_Callback();
        }
        /*clear flag*/
        CAN_Control->RFR[CAN_RX_FIFO0].FOVR=0;
    } 
  }
  void CAN1_RX1_IRQHandler()
  {
        if(CAN_Control->IER.B.FMPIE1==1 &&CAN_Control->RFR[CAN_RX_FIFO1].FMP<3)
    {
        if(CAN_RxFIFO1_FMP_Callback!=NULL)
        {
            CAN_RxFIFO1_FMP_Callback();
        }
    }
    else if(CAN_Control->IER.B.FFIE1==1 &&CAN_Control->RFR[CAN_RX_FIFO1].FULL==1)
    {
        if(CAN_RxFIFO1_FULL_Callback!=NULL)
        {
            CAN_RxFIFO1_FULL_Callback();
        }
        /*clear flag*/
        CAN_Control->RFR[CAN_RX_FIFO1].FULL=0;
    }
    else if(CAN_Control->IER.B.FOVIE1==1 &&CAN_Control->RFR[CAN_RX_FIFO1].FOVR==1)
    {
        if(CAN_RxFIFO1_FOVR_Callback!=NULL)
        {
            CAN_RxFIFO1_FOVR_Callback();
        }
        /*clear flag*/
        CAN_Control->RFR[CAN_RX_FIFO1].FOVR=0;
    } 
  }
  void CAN1_SCE_IRQHandler()
  {
    if(CAN_Control->IER.B.ERRIE==1 && CAN_Control->IER.B.EWGIE==1)
    {
        if(CAN_EWG_Error_Callback!=NULL)
        {
            CAN_EWG_Error_Callback();
        }
        CAN_Control->ESR.B.EWGF=0;
    }
    else  if(CAN_Control->IER.B.ERRIE==1 && CAN_Control->IER.B.EPVIE==1)
    {
        if(CAN_EPV_Error_Callback!=NULL)
        {
            CAN_EPV_Error_Callback();
        }
        CAN_Control->ESR.B.EPVF=0;
    }
    else if(CAN_Control->IER.B.ERRIE==1 && CAN_Control->IER.B.BOFIE==1)
    {
        if(CAN_BOF_Error_Callback!=NULL)
        {
            CAN_BOF_Error_Callback();
        }
        CAN_Control->ESR.B.BOFF=0;
    }
    else if(CAN_Control->IER.B.ERRIE==1 && CAN_Control->IER.B.LECIE>0)
    {
        if(CAN_Multi_Error_Callback!=NULL)
        {
            CAN_Multi_Error_Callback();
            Error_Code = CAN_Control->ESR.B.LEC;
        }
        CAN_Control->ESR.B.LEC=0;
    }
  }