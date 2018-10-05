/**************************************************************************************************
  Filename:       hal_flash.c
  Revised:        $Date: 2010-10-07 02:19:52 -0700 (Thu, 07 Oct 2010) $
  Revision:       $Revision: 24049 $

  Description: This file contains the interface to the H/W Flash driver.


  Copyright 2006-2010 Texas Instruments Incorporated. All rights reserved.

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
  PROVIDED “AS IS” WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED,
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

/* ------------------------------------------------------------------------------------------------
 *                                          Includes
 * ------------------------------------------------------------------------------------------------
 */

#include "hal_board_cfg.h"
#include "hal_flash.h"
#include "hal_mcu.h"
#include "hal_types.h"

uint8 nvDataBuf[HAL_NV_PAGE_CNT][HAL_FLASH_PAGE_SIZE];
/**************************************************************************************************
 * @fn          HalFlashInit
 *
 * @brief       This function writes 'cnt' bytes to the internal flash.
 *
 * input parameters
 *
 * None.
 *
 * output parameters
 *
 * None.
 *
 * @return      None.
 **************************************************************************************************
 */
void HalFlashInit(void)
{
  halIntState_t is;
  uint16 offset;
  uint8 pg;

  HAL_ENTER_CRITICAL_SECTION(is);
  for (pg = 0; pg < HAL_NV_PAGE_CNT; pg ++)
  {
    for (offset = 0; offset < HAL_FLASH_PAGE_SIZE; offset ++)
    {
      nvDataBuf[pg][offset] = 0xFF ;
    }
  }
  HAL_EXIT_CRITICAL_SECTION(is);
}
/**************************************************************************************************
 * @fn          HalFlashRead
 *
 * @brief       This function reads 'cnt' bytes from the internal flash.
 *
 * input parameters
 *
 * @param       pg - A valid flash page number.
 * @param       offset - A valid offset into the page.
 * @param       buf - A valid buffer space at least as big as the 'cnt' parameter.
 * @param       cnt - A valid number of bytes to read.
 *
 * output parameters
 *
 * None.
 *
 * @return      None.
 **************************************************************************************************
 */
void HalFlashRead(uint8 pg, uint16 offset, uint8 *buf, uint16 cnt)
{
  if (offset >= HAL_FLASH_PAGE_SIZE ) 
  	return;

   if (pg < HAL_NV_PAGE_BEG || pg >= HAL_NV_PAGE_CNT + HAL_NV_PAGE_BEG) 
  	return;
   
  pg -= HAL_NV_PAGE_BEG;

  if (pg * HAL_FLASH_PAGE_SIZE + offset + cnt > HAL_FLASH_PAGE_SIZE * HAL_NV_PAGE_CNT) 
  	return;
  
  halIntState_t is;
  uint8 *pData = &nvDataBuf[pg][offset];

  //printf("HalFlashRead\n");
  HAL_ENTER_CRITICAL_SECTION(is);
  while (cnt--)
  {
    *buf++ = *pData++;
  }
  HAL_EXIT_CRITICAL_SECTION(is);
}

/**************************************************************************************************
 * @fn          HalFlashWrite
 *
 * @brief       This function writes 'cnt' bytes to the internal flash.
 *
 * input parameters
 *
 * @param       addr - Valid HAL flash write address: actual addr / 4 and quad-aligned.
 * @param       buf - Valid buffer space at least as big as 'cnt' X 4.
 * @param       cnt - Number of 4-byte blocks to write.
 *
 * output parameters
 *
 * None.
 *
 * @return      None.
 **************************************************************************************************
 */
void HalFlashWrite(uint16 addr, uint8 *buf, uint16 cnt)
{
  if (addr * HAL_FLASH_WORD_SIZE < HAL_NV_START_ADDR)
  	return;
  
  addr = addr * HAL_FLASH_WORD_SIZE -HAL_NV_START_ADDR;
  cnt = cnt * HAL_FLASH_WORD_SIZE;
  
  if (addr + cnt >= HAL_FLASH_PAGE_SIZE * HAL_NV_PAGE_CNT) 
  	return;

  halIntState_t is;
  uint16 offset = addr % HAL_FLASH_PAGE_SIZE;
  uint8 pg = addr / HAL_FLASH_PAGE_SIZE;
  uint8 *pData = &nvDataBuf[pg][offset];

  HAL_ENTER_CRITICAL_SECTION(is);
  while (cnt--)
  {
    *pData++ = *buf++ ;
  }
  HAL_EXIT_CRITICAL_SECTION(is);
}

/**************************************************************************************************
 * @fn          HalFlashErase
 *
 * @brief       This function erases the specified page of the internal flash.
 *
 * input parameters
 *
 * @param       pg - A valid flash page number to erase.
 *
 * output parameters
 *
 * None.
 *
 * @return      None.
 **************************************************************************************************
 */
void HalFlashErase(uint8 pg)
{
  if (pg < HAL_NV_PAGE_BEG || pg >= HAL_NV_PAGE_CNT + HAL_NV_PAGE_BEG) 
  	return;
   
  pg -= HAL_NV_PAGE_BEG;

  halIntState_t is;
  uint16 cnt = HAL_FLASH_PAGE_SIZE;
  uint8 *pData = nvDataBuf[pg];

  HAL_ENTER_CRITICAL_SECTION(is);
  while (cnt--)
  {
    *pData++ = 0xFF;
  }
  HAL_EXIT_CRITICAL_SECTION(is);
}

/**************************************************************************************************
*/
