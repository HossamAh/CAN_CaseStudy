/*********************************************************************************/
/* Author    : Hossam Ahmed                                                     */
/* Version   : V01                                                               */
/* Data      : 26 OCT 2023                                                       */
/*********************************************************************************/
/*---------------------------------------------------------------------------------------------------------------------
 *  *  FILE DESCRIPTION
 *  --------------------
 *         File:  CAN_Private.h
 *       Module:  CAN Module
 *  Description:  Private header file for CAN Driver
---------------------------------------------------------------------------------------------------------------------*/
#ifndef _CAN_PRIVATE_H
#define _CAN_PRIVATE_H

/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL MACROS
---------------------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL DATA TYPES AND STRUCTURES
---------------------------------------------------------------------------------------------------------------------*/
/*Bit rate*/
enum BITRATE{CAN_50Kbps, CAN_100Kbps, CAN_125Kbps, CAN_250Kbps, CAN_500Kbps, CAN_800Kbps, CAN_1Mbps};

typedef const struct
{
	uint8 TS2;
	uint8 TS1;
	uint8 BRP;
} CAN_BitTimingConfig;


/*CAN registers definitions*/
/*
typedef struct
{
    uint32 LowerNibble:8;
    uint32 HigherNibble:8;
}TwoBytes_TAG_t;
typedef union
{
    uint16 r;
    TwoBytes_TAG_t B;
}TwoBytes_t;

typedef struct
{
    TwoBytes_t LowerNibble;
    TwoBytes_t HigherNibble;
}FourBytes_TAG_t;
typedef union
{
    uint32 r;
    FourBytes_TAG_t B;
}FourBytes_t;
*/
typedef struct
{
    uint32 FxR1;
    uint32 FxR2;
}FilterBank_t;

typedef struct
{
    volatile uint32 RQCP0:1;
    volatile uint32 TXOK0:1;
    volatile uint32 ALST0:1;
    volatile uint32 TERR0:1;
    volatile uint32      :3;
    volatile uint32 ABRQ0:1;
   
    volatile uint32 RQCP1:1;
    volatile uint32 TXOK1:1;
    volatile uint32 ALST1:1;
    volatile uint32 TERR1:1;
    volatile uint32      :3;
    volatile uint32 ABRQ1:1;
   
    volatile uint32 RQCP2:1;
    volatile uint32 TXOK2:1;
    volatile uint32 ALST2:1;
    volatile uint32 TERR2:1;
    volatile uint32      :3;
    volatile uint32 ABRQ2:1;
   
    volatile uint32 CODE :2;
    
    volatile uint32 TME0 :1;
    volatile uint32 TME1 :1;
    volatile uint32 TME2 :1;
    volatile uint32 LOW0 :1;
    volatile uint32 LOW1 :1;
    volatile uint32 LOW2 :1;
}TSR_Reg_t;

typedef struct
{
    volatile uint32 FMP    :2;
    volatile uint32        :1;
    volatile uint32 FULL   :1;
    volatile uint32 FOVR   :1;
    volatile uint32 RFOM   :1;
}RFR_Reg_t;

typedef union
{
    uint32 r;
    struct IER_Reg_TAG
    {
        uint32 TMEIE:1;
        uint32 FMPIE0:1;
        uint32 FFIE0:1;
        uint32 FOVIE0:1;
        uint32 FMPIE1:1;
        uint32 FFIE1:1;
        uint32 FOVIE1:1;
        uint32       :1;
        uint32 EWGIE:1;
        uint32 EPVIE:1;
        uint32 BOFIE:1;
        uint32 LECIE:1;
        uint32       :3;
        uint32 ERRIE:1;
        uint32 WKUIE:1;
        uint32 SLKIE:1;
    }B;
}IER_Reg_t;

typedef union
{
    uint32 r;
    struct ESR_Reg_TAG 
    {
        uint32 EWGF     :1;
        uint32 EPVF     :1;
        uint32 BOFF     :1;
        uint32          :1;
        uint32 LEC      :3;
        uint32          :9;
        uint32 TEC      :8;
        uint32 REC      :8;
    }B;
}ESR_Reg_t;

typedef union
{
    uint32 r;
    struct BTR_Reg_TAG 
    {
        uint32 BRP      :10;
        uint32          :6;
        uint32 TS1      :4;
        uint32 TS2      :3;
        uint32          :1;
        uint32 SJW      :2;
        uint32          :4;
        uint32 LBKM     :1;
        uint32 SILM     :1;
    }B;
}BTR_Reg_t;
typedef struct
{
    volatile uint32 MCR;
    volatile uint32 MSR;
    volatile TSR_Reg_t TSR;
    volatile RFR_Reg_t RFR[2];
    volatile IER_Reg_t IER;
    volatile ESR_Reg_t ESR;
    volatile BTR_Reg_t BTR;
}CAN_CONTROL_STATUS_t;

/*******************************TX Mailbox Registers********************************************** */
typedef struct
{
    volatile uint32 TXRQ:1;
    volatile uint32 RTR:1;
    volatile uint32 IDE:1;
    volatile uint32 EXID:18;
    volatile uint32 STD_EXID18_28:11;
}TIR_Reg_t;
typedef struct
{
    volatile uint32 DLC:4;
    volatile uint32    :4;
    volatile uint32 TGT:1;/*this bit determine if the time stamp is send in the last 2 bytes of 8-bytes data or not
    DLC must be 8 for timestamp transfer*/
    volatile uint32    :7;
    volatile uint32 TIME:16;
}TDTR_Reg_t;
typedef struct
{
    volatile uint8 DATA[4];
}TDLR_Reg_t;
typedef struct
{
    volatile uint8 DATA[4];
}TDHR_Reg_t;

typedef struct
{
    volatile TIR_Reg_t TIR;
    volatile TDTR_Reg_t TDTR;
    volatile TDLR_Reg_t TDLR;
    volatile TDHR_Reg_t TDHR;
}CAN_TXMailBoxes_t;

/****************************************************************************************************************** */
/***********************************RX FIFO Registers**************************************************** */
typedef struct
{
    volatile uint32    :1;
    volatile uint32 RTR:1;
    volatile uint32 IDE:1;
    volatile uint32 EXID:18;
    volatile uint32 STD_EXID18_28:11;
}RIR_Reg_t;
typedef struct
{
    volatile uint32 DLC:4;
    volatile uint32    :4;
    volatile uint32 FMI:8;/*The Filter Match index can be used in two ways:
                            • Compare the Filter Match index with a list of expected values.
                            • Use the Filter Match Index as an index on an array to access the data destination
                            location.*/
                            /*each filter bank according to its configuration there is a filter number with it , 
                            when receiving frame and pass through this filter ,filter number is the filter match index.
                            we defines filters to pass frame with needed Data , then the data with specific filter index match 
                            we gonna store it in related data variable in the app */
    
    volatile uint32 TIME:16;
}RDTR_Reg_t;
typedef struct
{
    volatile RIR_Reg_t RIR;
    volatile RDTR_Reg_t RDTR;
    volatile TDLR_Reg_t RDLR;
    volatile TDHR_Reg_t RDHR;
}CAN_RXFIFO_t;
typedef struct
{
    volatile CAN_TXMailBoxes_t Txmailbox[3];
    volatile CAN_RXFIFO_t RXFIFO[2];
}CAN_MAILBOX_REGISTERS_t;

typedef struct
{
    volatile uint32 FMR;
    volatile uint32 FM1R;
    uint32 ReservedReg;
    volatile uint32 FS1R;
    uint32 ReservedReg1;
    volatile uint32 FFA1R;
    uint32 ReservedReg2;
    volatile uint32 FA1R;
     uint32 reserved3[8];
    volatile FilterBank_t FiRx[14];
}CAN_FILTER_REGISTERS_t;


/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL MACROS
---------------------------------------------------------------------------------------------------------------------*/
#define 	CAN_Base_Address        0x40006400          // Base address of bxCAN1

#define 	CAN_Control 		((volatile CAN_CONTROL_STATUS_t *) CAN_Base_Address)
#define 	CAN_Mailbox 		((volatile CAN_MAILBOX_REGISTERS_t *) (CAN_Base_Address +0x180 ) )
#define 	CAN_Filter 		((volatile CAN_FILTER_REGISTERS_t *) (CAN_Base_Address +0x200 ) )

#endif
