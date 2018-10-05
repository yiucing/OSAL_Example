#ifndef OSAL_TICKS_H
#define OSAL_TICKS_H

#ifdef __cplusplus
extern "C"
{
#endif

/*********************************************************************
 * INCLUDES
 */

/*********************************************************************
 * MACROS
 */
#define OSAL_MSEC_PER_TICK    10  
#define OSAL_TICKS_PER_SEC     100
#define OSAL_MAX_TICKS            10000
/*********************************************************************
 * CONSTANTS
 */


/*********************************************************************
 * TYPEDEFS
 */


/*********************************************************************
 * GLOBAL VARIABLES
 */

/*********************************************************************
 * FUNCTIONS
 */

extern void osal_ticksConfig(void);  
extern void osal_ticksUpdate(int signo);
extern uint16 osal_getTicks(void);
/*********************************************************************
*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* OSAL_TICKS_H */