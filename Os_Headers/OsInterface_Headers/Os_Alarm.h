/*
    Os_Alarm.h
    Written by : Bakr
    DATE : 18/2/2020
    Created on: Feb 11, 2020
    Author: ME
 */

#ifndef OS_HEADERS_OSINTERFACE_HEADERS_OS_ALARM_H_
#define OS_HEADERS_OSINTERFACE_HEADERS_OS_ALARM_H_


/* structure for storage of counter characteristics */
typedef VAR (struct, TYPEDEF)
{

    VAR( TickType, AUTOMATIC ) ticksperbase ;

    VAR( TickType, AUTOMATIC ) maxallowedvalue ;

    VAR( TickType, AUTOMATIC ) mincycle ;


} AlarmBaseType ;

/* data type points to the data type AlarmBaseType */
typedef P2VAR ( AlarmBaseType ,TYPEDEF, TYPEDEF ) AlarmBaseRefType ;


/* data type represents an alarm object */
typedef VAR( uint8, TYPEDEF ) AlarmType ;

/************************************************************************************************/

/*  - Reference to structure with constants of the alarm base

    - Description: The system service GetAlarmBase reads the alarm base characteristics.
      The return value <Info> is a structure in which the information of data type AlarmBaseType is stored.

    - Particularities: Allowed on task level, ISR, and in several hook routines.
*/

FUNC(StatusType, OS_CODE) GetAlarmBase ( AlarmType AlarmID, AlarmBaseRefType Info ) ;

/**************************************************************************************************/

/*
     -  Description: The system service GetAlarm returns the relative value in ticks before the alarm <AlarmID> expires.
     -  Particularities: It is up to the application to decide whether for example a CancelAlarm may still be useful.
        If <AlarmID> is not in use, <Tick> is not defined.
        Allowed on task level, ISR, and in several hook routines
 */


FUNC(StatusType, OS_CODE) GetAlarm ( AlarmType AlarmID, TickRefType Tick) ;

/****************************************************************************************************/

/*
     -  Description: The system service occupies the alarm <AlarmID> element. After <increment> ticks have elapsed,
        the task assigned to the alarm <AlarmID> is activated or the assigned event (only for extended tasks)
        is set or the alarm-callback routine is called.
     -  NOTES:  To change values of alarms already in use the alarm shall be cancelled first.
                If the alarm is already in use, this call will be ignored and the error E_OS_STATE is returned.
                Allowed on task level and in ISR, but not in hook routines.

 */
FUNC(StatusType, OS_CODE) SetRelAlarm ( AlarmType AlarmID, TickType increment, TickType cycle ) ;

/*****************************************************************************************************/
/*
     -  Description: The system service occupies the alarm <AlarmID> element. When <start> ticks are reached,
                     the task assigned to the alarm <AlarmID> is activated or
                     the assigned event (only for extended tasks) is set or the alarm-callback routine is called.
     -  NOTE: - If the absolute value <start> is very close to the current counter value, the alarm may expire,
              and the task may become ready or the alarm-callback may be called before the system service returns to the user.
              - If the absolute value <start> already was reached before the system call, the alarm shall only expire when the absolute value <start> is reached again,
              i.e. after the next overrun of the counter.

 */

FUNC(StatusType, OS_CODE) SetAbsAlarm ( AlarmType AlarmID, TickType start, TickType cycle ) ;

/****************************************************************************************************/
/*
     - Description: The system service cancels the alarm <AlarmID>.
     -
 */
FUNC(StatusType, OS_CODE) CancelAlarm ( AlarmType AlarmID ) ;

#endif /* OS_HEADERS_OSINTERFACE_HEADERS_OS_ALARM_H_ */
