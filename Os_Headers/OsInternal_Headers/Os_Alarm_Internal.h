/*

    Written by : Bebo
    DATE : 7/2/2019
    AUTOSAR Version : 4.3.1
    DOC Name : AUTOSAR_SWS_OS.pdf
    Target : ARM TIVA_C TM4C123GH6PM

*/

#ifndef OS_HEADERS_OSINTERNAL_HEADERS_OS_ALARM_INTERNAL_H_
#define OS_HEADERS_OSINTERNAL_HEADERS_OS_ALARM_INTERNAL_H_

/***************************************************************/


typedef struct
{
    /*  Reference to the task that event will be set to by the alarm */
    VAR( TaskType, AUTOMATIC ) OsAlarmSetEventTaskRef ;


    /* Reference to the event in case of expiration action is setting event */
    VAR( EventMaskType, AUTOMATIC ) OsAlarmSetEventRef ;

} OsAlarmSetEvent ;

/*
    Internal Function to check alarms waiting on Counter ID value for expiring by searching for alarms with CounterID
    and checking the tick value for expiry with OsCounterInternal OsCounterVal
*/

/***************************************************************/

typedef union
{

    /* Reference to the counter that will be incremented by that alarm action */
    VAR( CounterType, AUTOMATIC ) OsAlarmIncrementCounterRef ;

    /* Reference to the task that will be activated by that alarm action */
    VAR( TaskType, AUTOMATIC ) OsAlarmActivateTaskRef ;

    /* Name of the function that is called when this alarm callback is triggered. */
    P2FUNC( void, AUTOMATIC, OsAlarmCallbackName ) (void) ;

    VAR( OsAlarmSetEvent, AUTOMATIC )   AlarmEvent ;

} OsAlarmActions ;

typedef struct{

    /* Enum holds ID for action taken on alarm expiry */
    VAR (uint8, AUTOMATIC) ActionType; /* Actions*/

    /* Action to be executed on alarm expiry */
    VAR (OsAlarmActions, AUTOMATIC) Action;

} OsAlarmAction;

/***************************************************************/

typedef struct
{

    /* Reference to application modes in which that alarm is activated on startup of the OS , as a mask for modes of this task
     * if = NOT_AUTOSTART then it won't be in autostart */
    VAR( uint8, AUTOMATIC ) OsAlarmAppModeRef ;

    /* specifies the type of autostart for the alarm absolute or alarm */
    VAR( uint8, AUTOMATIC ) OsAlarmAutostartType ;

    /* relative or absolute tick value when the alarm expires for the first time.
     * for an alarm which is RELATIVE the value must be at bigger than 0 */
    VAR( TickType, AUTOMATIC ) OsAlarmAlarmTime ;

    /* Cycle time of a cyclic alarm in ticks. If the value is 0 than the alarm is not cyclic */
    VAR( TickType, AUTOMATIC ) OsAlarmCycleTime ;

} OsAlarmAutostart ;

/***************************************************************/

typedef struct
{

    /* Reference to the assigned counter for that alarm */
    VAR( CounterType, AUTOMATIC ) OsAlarmCounterRef ;

    VAR (OsAlarmAction, AUTOMATIC ) AlarmAction ;

    VAR (OsAlarmAutostart, AUTOMATIC ) AlarmAutostart ;

} OsAlarm ;

/**************************************************************/

typedef struct
{
    /* Holds the value the Software/Hardware Counter will expire at
       either is ABSOLUTE or RELATIVE which is added to the current counter value
       then stored here
    */
    VAR ( TickType, AUTOMATIC ) AlarmExpiryTickValue;

    /* Holds Cycle value (FINISHED,ONE_SHOT,CYCLIC) */
    VAR ( TickType, AUTOMATIC ) Cycle; /* 0 if not cyclic */

    VAR ( uint8 , AUTOMATIC ) InUse;

} OsAlarmInternal ;

/***************************************************************/

FUNC(void, OS_INTERNAL_CODE) CheckAlarmExpiry(CounterType CounterID);


#endif /* OS_HEADERS_OSINTERNAL_HEADERS_OS_ALARM_INTERNAL_H_ */
