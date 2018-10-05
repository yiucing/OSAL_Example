/**************************************************************************************************
  Filename:       usertask1.c
  Revised:        $Date: 2014-10-24 16:04:46 -0700 (Fri, 24 Oct 2014) $
  Revision:       $Revision: 40796 $


  Description:    Zigbee Cluster Library - sample device application.


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
  PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED,
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

/*********************************************************************
  This application is a template to get started writing an application
  from scratch.

  Look for the sections marked with "GENERICAPP_TODO" to add application
  specific code.

  Note: if you would like your application to support automatic attribute
  reporting, include the BDB_REPORTING compile flag.
*********************************************************************/

/*********************************************************************
 * INCLUDES
 */
#include "OSAL.h"
#include "OSAL_Nv.h"
#include "OSAL_Tasks.h"
#include "usertask1.h"

/*********************************************************************
 * MACROS
 */


/*********************************************************************
 * CONSTANTS
 */


/*********************************************************************
 * TYPEDEFS
 */

/*********************************************************************
 * GLOBAL VARIABLES
 */
uint8 usertask1_TaskID;


/*********************************************************************
 * GLOBAL FUNCTIONS
 */
 
/*********************************************************************
 * LOCAL VARIABLES
 */


/*********************************************************************
 * LOCAL FUNCTIONS
 */

/*********************************************************************
 * @fn          usertask1_Init
 *
 * @brief       Initialization function for usertask1.
 *
 * @param       none
 *
 * @return      none
 */
void usertask1_Init( uint8 task_id )
{
  usertask1_TaskID = task_id;
  osal_start_reload_timer(usertask1_TaskID, USERTASK1_MSG_EVT, 100);
  printf("task1!\n");
}

/*********************************************************************
 * @fn          usertask1_event_loop
 *
 * @brief       Event Loop Processor for usertask1.
 *
 * @param       none
 *
 * @return      none
 */
uint16 usertask1_event_loop( uint8 task_id, uint16 events )
{
  user_message_t *msgPtr;

  (void)task_id;  // Intentionally unreferenced parameter

  if ( events & SYS_EVENT_MSG )
  {
    while ((msgPtr = (user_message_t *)osal_msg_receive(usertask1_TaskID)) != NULL)
    {
      /* Do something here - for now, just deallocate the msg and move on */

      /* De-allocate */
      osal_msg_deallocate( (uint8 *)msgPtr );
    }

    // return unprocessed events
    return (events ^ SYS_EVENT_MSG);
  }

  if ( events & USERTASK1_MSG_EVT )
  {
  	user_message_t *userMsgPtr = (user_message_t *)osal_msg_allocate(32);
	char nvData1[16] = {0};
	char nvData2[16] = {0};
	
	static uint16 flag = 0;
	
	sprintf(nvData1, "nv%06d\n", flag ++);
	osal_nv_item_init(100, 10, nvData1);
	osal_nv_write(100, 0, 10, nvData1);
	osal_nv_read(100, 0, 10, nvData2);
	sprintf(userMsgPtr->msg,  "msg_%s", nvData2);
	userMsgPtr->hdr.event = 100;
	osal_msg_send( usertask2_TaskID, (uint8 *)userMsgPtr );
  	
  	printf("send msg in task1!\n");

  	return (events ^ USERTASK1_MSG_EVT);
  }
  
  // Discard unknown events
  return 0;
}

/****************************************************************************
****************************************************************************/


