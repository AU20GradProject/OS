/*
 * Os_Alarm.h
 *
 *  Created on: Feb 11, 2020
 *      Author: ME
 */

#ifndef OS_HEADERS_OSINTERFACE_HEADERS_OS_ALARM_H_
#define OS_HEADERS_OSINTERFACE_HEADERS_OS_ALARM_H_

/* represents count values in ticks. */
typedef VAR ( uint32 ,TYPEDEF ) TickType ;

/* points to the data type TickType */
typedef P2VAR ( TickType ,TYPEDEF, TYPEDEF ) TickRefType ;

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




#endif /* OS_HEADERS_OSINTERFACE_HEADERS_OS_ALARM_H_ */
