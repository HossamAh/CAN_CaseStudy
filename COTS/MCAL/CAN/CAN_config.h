/*********************************************************************************/
/* Author    : Hossam Ahmed                                                     */
/* Version   : V01                                                               */
/* Data      : 26 OCT 2023                                                       */
/*********************************************************************************/
/*---------------------------------------------------------------------------------------------------------------------
 *  *  FILE DESCRIPTION
 *  --------------------
 *         File:  CAN_config.h
 *       Module:  CAN Module
 *  Description:  Configuration header file for CAN Driver
---------------------------------------------------------------------------------------------------------------------*/
#ifndef _CAN_CONFIG_H
#define _CAN_CONFIG_H

/*---------------------------------------------------------------------------------------------------------------------
 *  INCLUDES
---------------------------------------------------------------------------------------------------------------------*/
// #include "CAN_interface.h"

/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL MACROS
---------------------------------------------------------------------------------------------------------------------*/
#define CAN_MODE_NORMAL 0           			                          			       
#define CAN_MODE_LOOPBACK 1        		 	                  					   
#define CAN_MODE_SILENT   2         			                  					   
#define CAN_MODE_SILENT_LOOPBACK 3 
/*Testing mode Options:
* CAN_MODE_NORMAL 0           			                          			       
* CAN_MODE_LOOPBACK 1        		 	                  					   
* CAN_MODE_SILENT   2         			                  					   
* CAN_MODE_SILENT_LOOPBACK 3 			   	   
*/
#define MODE		CAN_MODE_LOOPBACK
/********** option : CAN_50KBPS
 * 					 CAN_100KBPS
 * 					 CAN_125KBPS
 * 					 CAN_250KBPS
 * 					 CAN_500KBPS
 * 					 CAN_800KBPS,
 * 					 CAN_1MBPS
 	 	 	 	 	 	 	 	 	 	 	 	 *************************/
#define BAUDRATE		CAN_500Kbps
/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL DATA
---------------------------------------------------------------------------------------------------------------------*/

/******** BoudRate value rating to table at web site {http://www.bittiming.can-wiki.info/}
 * 1. select ST Microelectronics bxCAN
 * 2. put freq with 8Mhz (APB1 freq)
 * 3. click Request Table						        ***********************************/
// CAN_BitTimingConfig CAN_bitRateConfig[7] = {{2, 13, 10}, {2, 13, 5}, {2, 13, 4}, {2, 13, 2}, {2, 13, 1},{1, 8, 1}, {1, 6, 1}};







#endif
