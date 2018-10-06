/**
  ******************************************************************************
  * @file    OSAL_Ticks.c 
  * @author  chyq
  * @version V1.1.0
  * @date    10-9-2013
  * @brief   OSAL Ticks functions.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>

#include "OSAL.h"
#include "OSAL_Ticks.h"

uint16 OSAL_Ticks;

/*********************************************************************
 * @fn      osal_ticksConfig
 *
 * @brief   This function Config Time Ticks.
 *
 * @param   void
 *
 * @return  none
 */
void osal_ticksConfig(void)
{
	struct itimerval value, ovalue;    

	signal(SIGVTALRM, osal_ticksUpdate);  
	value.it_value.tv_sec = 0;   
	value.it_value.tv_usec = 10000;   
	value.it_interval.tv_sec = 0;   
	value.it_interval.tv_usec = 10000;  
	setitimer(ITIMER_VIRTUAL, &value, &ovalue);
}

/*********************************************************************
 * @fn      osal_ticksUpdate
 *
 * @brief   This function Update Time Ticks.
 *
 * @param   signo -
 *
 * @return  none
 */
void osal_ticksUpdate(int signo)
{
    switch (signo)
    {   
    case SIGVTALRM: 
        OSAL_Ticks ++;
        OSAL_Ticks %= OSAL_MAX_TICKS;
	 signal(SIGVTALRM, osal_ticksUpdate);       
	 break;  
    }
}

/*********************************************************************
 * @fn      osal_getTicks
 *
 * @brief   This function Get Time Ticks.
 *
 * @param   void
 *
 * @return  none
 */
uint16 osal_getTicks(void)
{
  return OSAL_Ticks;
}