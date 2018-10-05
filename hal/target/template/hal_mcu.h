/**************************************************************************************************
  Filename:       hal_mcu.h
  Revised:        $Date: 2013-10-07 09:18:37 -0700 (Mon, 07 Oct 2013) $
  Revision:       $Revision: 35584 $

  Description:    Describe the purpose and contents of the file.


  Copyright 2006-2013 Texas Instruments Incorporated. All rights reserved.

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
#ifndef HAL_MCU_H
#define HAL_MCU_H

/* ------------------------------------------------------------------------------------------------
 *                                           Includes
 * ------------------------------------------------------------------------------------------------
 */
#include "hal_types.h"
#include "hal_defs.h"

/* ------------------------------------------------------------------------------------------------
 *                                     Compiler Abstraction
 * ------------------------------------------------------------------------------------------------
 */

/* ---------------------- IAR Compiler ---------------------- */
#if defined (ewarm)
#define HAL_COMPILER_IAR
#define HAL_MCU_LITTLE_ENDIAN()   __LITTLE_ENDIAN__

/* ---------------------- Keil Compiler ---------------------- */
#elif defined (__KEIL__)
#define HAL_COMPILER_KEIL
#define HAL_MCU_LITTLE_ENDIAN()   0


/* ------------------ Unrecognized Compiler ------------------ */
#elif defined (ccs)
#define HAL_MCU_LITTLE_ENDIAN()   0
//do nothig for now
#else
//#error "ERROR: Unknown compiler."
#endif

/* ------------------------------------------------------------------------------------------------
 *                                       Interrupt Macros
 * ------------------------------------------------------------------------------------------------
 */

typedef bool halIntState_t;

/* Enable interrupts */
#define HAL_ENABLE_INTERRUPTS()    

/* Disable interrupts */
#define HAL_DISABLE_INTERRUPTS()   

#define HAL_ENTER_CRITICAL_SECTION(x)  \
  do {  } while (0)

#define HAL_EXIT_CRITICAL_SECTION(x) \
  do { if (x) { } } while (0)

/* Hal Critical statement definition */
#define HAL_CRITICAL_STATEMENT(x)       st (halIntState_t s; HAL_ENTER_CRITICAL_SECTION(s); x; HAL_EXIT_CRITICAL_SECTION(s); )

#define HAL_ENTER_ISR()     
#define HAL_EXIT_ISR()   

#define HAL_SYSTEM_RESET()  st (HAL_DISABLE_INTERRUPTS(); )

#define CLEAR_SLEEP_MODE()
#define ALLOW_SLEEP_MODE()

/**************************************************************************************************
 */
#endif

