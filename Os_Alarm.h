/*
 * Os_Alarm.h
 *
 *  Created on: Feb 11, 2020
 *      Author: ME
 */

#ifndef OS_ALARM_H_
#define OS_ALARM_H_

/* represents count values in ticks. */
typedef VAR ( uint64 ,TYPEDEF ) TickType ;

/* points to the data type TickType */
typedef P2VAR ( TickType ,TYPEDEF, TYPEDEF ) TickRefType ;

/* structure for storage of counter characteristics */
typedef struct
{

    VAR( uint32, AUTOMATIC ) ticksperbase ;

    VAR( TickType, AUTOMATIC ) maxallowedvalue ;

    VAR( TickType, AUTOMATIC ) mincycle ;


} AlarmBaseType ;


#endif /* OS_ALARM_H_ */
