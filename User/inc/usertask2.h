/**************************************************************************************************
  Filename:       usertask2.h
  Revised:        $Date: 2014-06-19 08:38:22 -0700 (Thu, 19 Jun 2014) $
  Revision:       $Revision: 39101 $

  Description:    This file contains the ZigBee Cluster Library Home
                  Automation Sample Application.


  Copyright 2006-2014 Texas Instruments Incorporated. All rights reserved.

  IMPORTANT: Your use of this Software is limited to those specific rights
  granted under the terms of a software license agreement between the user
  who downloaded the software, his/her employer (which must be your employer)
  and Texas Instruments Incorporated (the "License").  You may not use this
  Software unless you agree to abide by the terms of the License. The License
  limits your use, and you acknowledge, that the Software may not be modified,
  copied or distributed unless embedded on a Texas Instruments microcontroller
  or used solely and exclusively in conjunction with a Texas Instruments radio
  frequency transceiver, which is integrated into your product.  Other than for
  the foregoing purpose, you may not use, reproduce, copy, prepare derivative
  works of, modify, distribute, perform, display or sell this Software and/or
  its documentation for any purpose.

  YOU FURTHER ACKNOWLEDGE AND AGREE THAT THE SOFTWARE AND DOCUMENTATION ARE
  PROVIDED �AS IS� WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED,
  INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE,
  NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL
  TEXAS INSTRUMENTS OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT,
  NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER
  LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
  INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE
  OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT
  OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
  (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

  Should you have any questions regarding your right to use this Software,
  contact Texas Instruments Incorporated at www.TI.com.
**************************************************************************************************/

#ifndef USERTASK2_H
#define USERTASK2_H

#ifdef __cplusplus
extern "C"
{
#endif

/*********************************************************************
 * INCLUDES
 */

/*********************************************************************
 * CONSTANTS
 */

// Application Events
#define USERTASK2_MSG_EVT          0x0001
  
/*********************************************************************
 * MACROS
 */
/*********************************************************************
 * TYPEDEFS
 */

/*********************************************************************
 * VARIABLES
 */

// GENERICAPP_TODO: Declare application specific attributes here

extern uint8 usertask2_TaskID;
/*********************************************************************
 * FUNCTIONS
 */

 /*
  * Initialization for the task
  */
extern void usertask2_Init( uint8 task_id );

/*
 *  Event Process for the task
 */
extern uint16 usertask2_event_loop( uint8 task_id, uint16 events );


/*********************************************************************
*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* USERTASK2_H */
