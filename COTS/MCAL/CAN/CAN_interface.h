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
#ifndef _CAN_INTERFACE_H
#define _CAN_INTERFACE_H

/*---------------------------------------------------------------------------------------------------------------------
 *  INCLUDES
---------------------------------------------------------------------------------------------------------------------*/
//#include "../../LIB//Std_Types.h"
//#include "../../LIB//Bit_Math.h"

//#include "CAN_private.h"
//#include "CAN_config.h"
/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL MACROS
---------------------------------------------------------------------------------------------------------------------*/
/** @defgroup CAN_identifier_type CAN Identifier Type **/
#define CAN_ID_STD                  (0x0)  /*!< Standard Id */
#define CAN_ID_EXT                  (0x1)  /*!< Extended Id */

/** @defgroup CAN_remote_transmission_request CAN Remote Transmission Request **/
#define CAN_RTR_DATA                (0x0)  /*!< Data frame   */
#define CAN_RTR_REMOTE              (0x1)  /*!< Remote frame */

/** @defgroup CAN_receive_FIFO_number CAN Receive FIFO Number **/
#define CAN_RX_FIFO0                (0x0)  /*!< CAN receive FIFO 0 */
#define CAN_RX_FIFO1                (0x1)  /*!< CAN receive FIFO 1 */


#define CAN_ENABLE 1
#define CAN_DISABLE 0

/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL DATA TYPES AND STRUCTURES
---------------------------------------------------------------------------------------------------------------------*/
typedef enum
{
    CAN_MASK_MODE,
    CAN_IDENTIFIERLIST_MODE,
}CAN_filterMode_t;
typedef enum
{
    CAN_ONE_32BIT_FILTER,
    CAN_TWO16BIT_FILTER,
}CAN_SCALABLEWIDTH_t;

/**
  * @brief  CAN init structure definition
  */
typedef struct
{

  uint8 Mode;                       /*!< Specifies the CAN operating mode.
                                            This parameter can be a value of @ref CAN_operating_mode */
	/*Enable 1 Disable 0*/
  uint8 TimeTriggeredMode;   /*!< Enable or disable the time triggered communication mode.
                                            This parameter can be set to ENABLE or DISABLE. */

  uint8 AutoBusOff;          /*!< Enable or disable the automatic bus-off management.
                                            This parameter can be set to ENABLE or DISABLE. */

  uint8 AutoWakeUp;          /*!< Enable or disable the automatic wake-up mode.
                                            This parameter can be set to ENABLE or DISABLE. */

  uint8 AutoRetransmission;  /*!< Enable or disable the non-automatic retransmission mode.
                                            This parameter can be set to ENABLE or DISABLE. */

  uint8 ReceiveFifoLocked;   /*!< Enable or disable the Receive FIFO Locked mode.
                                            This parameter can be set to ENABLE or DISABLE. */

  uint8 TransmitFifoPriority; /*!< Enable or disable the transmit FIFO priority.
                                            This parameter can be set to ENABLE or DISABLE. */

} CAN_InitTypeDef;

typedef struct
{
CAN_filterMode_t filterMode;
CAN_SCALABLEWIDTH_t filterScalableWidth;

uint32 FilterIdHigh;          /*!< Specifies the filter identification number :
																		- higher of ID in 32-bit IDList and ID Mask
																		- ID in 16-bit IDList and IDMask
                                       This parameter must be a number between Min_Data = 0x0000 and Max_Data = 0xFFFF. */

uint32 FilterIdLow;           /*!< Specifies the filter identification number:                 
																		-lower of ID in 32-bit IDList and IDMask
																		- Id in 16-bit IDList
                                    This parameter must be a number between Min_Data = 0x0000 and Max_Data = 0xFFFF. */

uint32 FilterMaskIdHigh;      /*!< Specifies the filter mask number or identification number,
                                    according to the mode:
																		-higher of second id in 32-bit IDList 
																		- higher of mask in 32-bit IDMask
																		- mask of second Id in 16-bit IDMask
																		- ID in 16-bit IDList 
                                    This parameter must be a number between Min_Data = 0x0000 and Max_Data = 0xFFFF. */

uint32 FilterMaskIdLow;       /*!< Specifies the filter mask number or identification number,
                                    according to the mode
																		-Lower of second id in 32-bit IDList 
																		- Lower of mask in 32-bit IDMask
																		- mask of first Id in 16-bit IDMask
																		- ID in 16-bit IDList
                                    This parameter must be a number between Min_Data = 0x0000 and Max_Data = 0xFFFF. */ 

uint32 FilterFIFOAssignment;  /*!< Specifies the Recevier FIFO (0 or 1U) which will be assigned to the filter.*/
                                       
uint32 FilterBank;            /*!< Specifies the filter bank which will be initialized.*/  
}CAN_Filter_t;


typedef struct 
{
  uint32 StdId;    
  uint32 ExtId;  /*Txframe->ExtId is the 29 bit Id contains standard and extended*/  
  uint32 IDE;      
  uint32 RTR;      
  uint32 DLC;      
  uint8 TransmitGlobalTime; 	/*!< Specifies whether the time stamp counter value captured on start
									of frame transmission*/
}CAN_TX_Frame_t;

typedef struct 
{
  uint32 StdId;
  uint32 ExtId;    
  uint32 IDE;      
  uint32 RTR;      
  uint32 DLC;      
  uint32 TimeStamp; 
  uint32 FilterMatchIndex; /*!< Specifies the index of matching acceptance filter element.
                          This parameter must be a number between Min_Data = 0 and Max_Data = 0xFF. */

}CAN_RX_Frame_t;

typedef enum
{
  TxMailbox0_completed,
  TxMailbox1_completed,
  TxMailbox2_completed,
  TxMailbox0_Abort,
  TxMailbox1_Abort,
  TxMailbox2_Abort,
  TxMailbox0_TXERR,
  TxMailbox1_TXERR,
  TxMailbox2_TXERR,
  
  
  RX_FIFO0_FMP,
  RX_FIFO0_FULL,
  RX_FIFO0_FOVR,
  RX_FIFO1_FMP,
  RX_FIFO1_FULL,
  RX_FIFO1_FOVR,
  CAN_EWG_Error,//Enter Warning Error state (Active Error)  
  CAN_EPV_Error,//Enter Passive Error state (Passive Error)  
  CAN_BOF_Error,//Enter Bus Off Error state (Bus Off)
  CAN_Multi_Error,//Error from the errors in Error code(ack , stuffing , format, ...)
}CAN_notifications_t;
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
void MCAN_VoidInit(const CAN_InitTypeDef* pInitConfig) ;

/******************************************************************************
* \Syntax          : void MCAN_VoidConfigureIDFilter(CAN_Filter_t *pFilterConfig)                                      
* \Description     : initialize CAN filter banks and filers modes based on configuraion parameters                                                                          
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : CAN_Filter_t *pFilterConfig                   
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MCAN_VoidConfigureIDFilter(CAN_Filter_t *pFilterConfig);

/******************************************************************************
* \Syntax          : uint8 MCAN_u8Transmission(CAN_TX_Frame_t * TXframe,uint8 Data[])                                      
* \Description     : initialize CAN Frame to be send and put it in Tx mailbox and                                                                           
* \Sync\Async      : ASynchronous (when tx is transmitted interrupt notify the app)                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : CAN_TX_Frame * TXframe , Data array represent the data bytes                  
* \Parameters (out): None                                                      
* \Return value:   : return the mailbox number used to transmit
*******************************************************************************/
uint8 MCAN_u8Transmission(CAN_TX_Frame_t * TXframe,uint8 Data[]);

/******************************************************************************
* \Syntax          : void MCAN_VoidReception(uint8 RX_FIFO,CAN_RX_Frame_t * RXframe,uint8 Data[])                                      
* \Description     : Read CAN frame from RX FIFO and store its data in Data Array.                                                                           
* \Sync\Async      : Synchronous                                                
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) :  RX_ FIFO number of fifo to read from,CAN_RX_Frame * RXframe , Data array represent the data bytes                  
* \Parameters (out): CAN_RX_Frame * RXframe , Data array represent the data bytes                                                      
* \Return value:   : None
*******************************************************************************/
void MCAN_VoidReception(uint8 RX_FIFO,CAN_RX_Frame_t * RXframe,uint8 Data[]);

/******************************************************************************
* \Syntax          : void MCAN_VoidStart()                                      
* \Description     : Start CAN by leaving the initialization mode to normal mode                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MCAN_VoidStart(void);

/******************************************************************************
* \Syntax          : uint8 MCAN_u8FreeMailboxes(void)                                      
* \Description     : Return the number of free mailboxes to start transmit                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                
* \Parameters (out): None                                                      
* \Return value:   : number of free mailboxes-> 0-3
*******************************************************************************/
uint8 MCAN_u8FreeMailboxes(void);


/******************************************************************************
* \Syntax          : uint8 MCAN_u8MailboxPendingStatus(uint8 mailboxNumber)                                      
* \Description     : Return whether the transmission is completed or not                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : uint8 mailboxNumber:number of the mailbox                
* \Parameters (out): None                                                      
* \Return value:   : status of mailbox 0->pending,1->not pending(completed)
*******************************************************************************/
uint8 MCAN_u8MailboxPendingStatus(uint8 mailboxNumber);

/******************************************************************************
* \Syntax          : uint8 MCAN_u8RX_FIFOMeassages(uint8 RX_FIFO)                                      
* \Description     : Return the number of messages in fifo                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : uint8 RX_FIFO number of FIFO 0->FIFO0,1->FIFO1                
* \Parameters (out): None                                                      
* \Return value:   : number of messages in FIFO
*******************************************************************************/
uint8 MCAN_u8RX_FIFOMeassages(uint8 RX_FIFO);

/******************************************************************************
* \Syntax          : void MCAN_VoidEnableNotifications(CAN_notifications_t notification,void (*callback_ptr)())                                      
* \Description     : Enable interrupt enable of CAN interrupt and set the callback function                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : notification : type of notification to enable , callback_ptr ptr to callback function               
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MCAN_VoidEnableNotifications(CAN_notifications_t notification,void (*callback_ptr)());

/******************************************************************************
* \Syntax          : void MCAN_VoidDisableNotifications(CAN_notifications_t notification)                                      
* \Description     : Disable interrupt disable of CAN interrupt                                                                            
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : notification : type of notification to disable                
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MCAN_VoidDisableNotifications(CAN_notifications_t notification);

#endif
