/*

    Written by : Bebo
    DATE : 7/2/2019
    AUTOSAR Version : 4.3.1
    DOC Name : AUTOSAR_SWS_OS.pdf
    Target : ARM TIVA_C TM4C123GH6PM

*/

#include "Os.h"

/*******************************************************************/

typedef struct
{
    VAR( boolean, AUTOMATIC )   OsStackMonitoring ;         /* Select stack monitoring of Tasks/Category 2 ISRs (true: Stacks are monitored) */
    VAR( boolean, AUTOMATIC )   OsUseGetServiceId ;         /* determine whether access macros to get service id which caused last error is defined or not */
    VAR( boolean, AUTOMATIC )   OsUseParameterAccess ;      /* determine whether access macros to get values of parameter of service which caused last error is defined or not */
    VAR( boolean, AUTOMATIC )   OsUseResScheduler ;         /* defines whether the resource RES_SCHEDULER is used within the application. */
    VAR( boolean, AUTOMATIC )   OsErrorHook ;               /* whether Error hook as defined by OSEK called in case of error ( true: Hook is called ) */
    VAR( boolean, AUTOMATIC )   OsPostTaskHook ;            /* as post hook but here before old task is leave running state */
    VAR( boolean, AUTOMATIC )   OsPreTaskHook ;             /* as pre hook but here after new task is enter running state */
    VAR( boolean, AUTOMATIC )   OsProtectionHook ;          /* enable/disable the call to the (user supplied) protection hook ( true: hook is called )*/
    VAR( boolean, AUTOMATIC )   OsShutdownHook ;            /* as previous hooks but for hook called when shutdown is requested */
    VAR( boolean, AUTOMATIC )   OsStartupHook ;             /* as previous hooks but for hook called after os startup and before scheduler */
    VAR( uint8, AUTOMATIC )     OsNumberOfCores ;           /* Maximum number of cores that are controlled by the OS */
    VAR( uint8, AUTOMATIC )     OsScalabilityClass ;        /* determine supported scalability class by OS */
    VAR( uint8, AUTOMATIC )     OsStatus ;                  /* The Status attribute specifies whether a system with standard or extended status has to be used */

} OsOS ;

/*******************************************************************/

typedef struct
{
    /*This specifies the type of the resource*/
    VAR( boolean, AUTOMATIC ) OsResourceProperty ;

    /* link to the resource. Must be valid if OsResourceProperty is LINKED.
     * If OsResourceProperty is not LINKED the value is ignored */
    VAR( uint8, AUTOMATIC ) OsResourceLinkedResourceRef ;



} OsResource ;

/*******************************************************************/


typedef struct
{

    /* determines whether the task is activated during the system start-up procedure or not
     * for some specific application modes*/
    VAR( boolean, AUTOMATIC ) OsTaskAutostart ;

    /* OsTaskSchedule attribute defines the preemptability of the task.
     * If this attribute is set to NON, no internal resources may be assigned to this task */
    VAR( uint8, AUTOMATIC ) OsTaskSchedule ;

    /* defines the maximum number of queued activation requests for the task
     * 1" means that at any time only a single activation is permitted for this task
     * for basic tasks in BCC2,ECC2 */
    VAR( uint8, AUTOMATIC ) OsTaskActivation ;

    /* priority of a task is defined by the value of this,
     * larger values correspond to higher priorities 0 is lowest */
    VAR( uint8, AUTOMATIC ) OsTaskPriority ;

    /* defines a list of resources accessed by this task  represented as ceiling priority */
    VAR( uint8, AUTOMATIC ) OsTaskResourceRef ;

    /* Reference to application modes in which that task is activated on startup of the OS , as a mask for modes of this task */
    VAR( uint8, AUTOMATIC ) OsTaskAppModeRef ;

    /* defines the list of events the extended task may react on, as a mask for events of this task  */
    VAR( EventMaskType, AUTOMATIC ) OsTaskEventRef ;


} OsTask ;

/*******************************************************************/

typedef struct
{

    /* contains the natural type or unit of the counter. */
    VAR( uint8, AUTOMATIC ) OsCounterType ;

    /* specifies the number of ticks required to reach a counterspecific unit.
     * The interpretation is implementation-specific */
    VAR( uint32, AUTOMATIC ) OsCounterTicksPerBase ;

    /* Maximum possible allowed value of the system counter in ticks */
    VAR( uint64, AUTOMATIC ) OsCounterMaxAllowedValue ;

    /* specifies the minimum allowed number of counter ticks for a cyclic alarm linked to the counter */
    VAR( uint64, AUTOMATIC ) OsCounterMinCycle ;

} OsCounter ;

/*******************************************************************/

typedef struct
{
    /* determines whether the task is activated during the system start-up procedure or not
     * for some specific application modes*/
    VAR( boolean, AUTOMATIC ) OsAlarmAutostart ;

    /* specifies the type of autostart for the alarm absoulte or alarm */
    VAR( uint8, AUTOMATIC ) OsAlarmAutostartType ;

    /* Reference to application modes in which that task is activated on startup of the OS , as a mask for modes of this task */
    VAR( uint8, AUTOMATIC ) OsTaskAppModeRef ;

    /* defines which type of notification is used when the alarm expires. */
    VAR( uint8, AUTOMATIC ) OsAlarmAction ;

    /* Reference to the assigned counter for that alarm */
    VAR( uint8, AUTOMATIC ) OsAlarmCounterRef ;

    /* Reference to the counter that will be incremented by that alarm action */
    VAR( uint8, AUTOMATIC ) OsAlarmIncrementCounterRef ;

    /* Reference to the task that will be activated by that alarm action */
    VAR( TaskType, AUTOMATIC ) OsAlarmActivateTaskRef ;

    /* Reference to the task that will be activated by that event  in case of expiration action is setting event */
    VAR( TaskType, AUTOMATIC ) OsAlarmSetEventTaskRef ;

    /* Name of the function that is called when this alarm callback is triggered. */
    P2FUNC( void, AUTOMATIC, OsAlarmCallbackName ) (void) ;

    /* Reference to the event in case of expiration action is setting event */
    VAR( EventMaskType, AUTOMATIC ) OsAlarmSetEventRef ;

    /* relative or absolute tick value when the alarm expires for the first time.
     * for an alarm which is RELATIVE the value must be at bigger than 0 */
    VAR( TickType, AUTOMATIC ) OsAlarmAlarmTime ;

    /* Cycle time of a cyclic alarm in ticks. If the value is 0 than the alarm is not cyclic */
    VAR( TickType, AUTOMATIC ) OsAlarmCycleTime ;

} OsAlarm ;


/*******************************************************************/

typedef struct
{
    /*  specifies the category of this ISR. */
    VAR( uint8, AUTOMATIC ) OsIsrCategory ;

    /* defines a list of resources accessed by this task  represented as ceiling priority */
    VAR( uint8, AUTOMATIC ) OsTaskResourceRef ;

} OsIsr;

/***********************************************************************************************************************/

extern CONSTP2FUNC( void, OS_CONFIG_DATA, OsTasksNames_Array [TASKS_NUMBER] ) (void) ;

CONST( OsOS, OS_CONFIG_DATA ) OS = OS_OS_OBJECT_CONGIFURATION ;

CONST( EventMaskType, OS_CONFIG_DATA ) OsEvents_Array [ EVENTS_NUMBER ] = OS_EVENTS_OBJECT_CONGIFURATION ;

CONST( OsTask, OS_CONFIG_DATA ) OsTasks_Array [ TASKS_NUMBER ] = OS_TASKS_OBJECT_CONGIFURATION ;

CONST( OsResource, OS_CONFIG_DATA ) OsResource_Array [ RESOURCES_NUMBER ] = OS_RESOURCES_OBJECT_CONGIFURATION ;

CONST( OsCounter, OS_CONFIG_DATA ) OsCounter_Array [ COUNTERS_NUMBER ] = OS_COUNTERS_OBJECT_CONGIFURATION ;

CONST( OsAlarm, OS_CONFIG_DATA ) OsAlarmr_Array [ ALARMS_NUMBER ] = OS_ALARMS_OBJECT_CONGIFURATION ;

CONST( OsIsr, OS_CONFIG_DATA ) OsIsr_Array [ ISRS_NUMBER ] = OS_ISRS_OBJECT_CONGIFURATION ;



/*******************************************************************/








