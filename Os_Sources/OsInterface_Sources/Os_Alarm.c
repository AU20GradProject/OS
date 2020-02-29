/*

    Written by : Bakr
    DATE : 18/2/2020
    AUTOSAR Version : 4.3.1
    DOC Name : AUTOSAR_SWS_OS.pdf
    Target : ARM TIVA_C TM4C123GH6PM

*/





#include "..\..\Os_Headers\OsInterface_Headers\Os.h"
#include "..\..\Os_Headers\OsInternal_Headers\Os_Internal.h"

/************************************************************************************************/

extern CONST( OsCounter, OS_CONFIG_DATA ) OsCounter_Array [ COUNTERS_NUMBER ];

extern CONST( OsAlarm, OS_CONFIG_DATA ) OsAlarm_Array [ ALARMS_NUMBER ];

extern VAR( OsAlarmInternal, OS_CONFIG_DATA ) OsAlarmInternal_Array [ALARMS_NUMBER];

extern VAR( OsCounterInternal, OS_DATA)   OsCounterInternal_Array [COUNTERS_NUMBER ];

/************************************************************************************************/

/*  - Reference to structure with constants of the alarm base

    - Description: The system service GetAlarmBase reads the alarm base characteristics.
      The return value <Info> is a structure in which the information of data type AlarmBaseType is stored.

    - Particularities: Allowed on task level, ISR, and in several hook routines.
*/


FUNC(StatusType, OS_CODE) GetAlarmBase ( AlarmType AlarmID, AlarmBaseRefType Info ) {

    StatusType RetVal  = E_OK;

    if(AlarmID > ALARMS_NUMBER){

        RetVal = E_OS_ID;

    }else{

        Info->mincycle = OsCounter_Array[OsAlarm_Array[AlarmID].OsAlarmCounterRef].OsCounterMinCycle;

        Info->maxallowedvalue = OsCounter_Array[OsAlarm_Array[AlarmID].OsAlarmCounterRef].OsCounterMaxAllowedValue;

        Info->ticksperbase = OsCounter_Array[OsAlarm_Array[AlarmID].OsAlarmCounterRef].OsCounterTicksPerBase;

    }

    return RetVal;
}

/**************************************************************************************************/

/*
     -  Description: The system service GetAlarm returns the relative value in ticks before the alarm <AlarmID> expires.
     -  Particularities: It is up to the application to decide whether for example a CancelAlarm may still be useful.
        If <AlarmID> is not in use, <Tick> is not defined.
        Allowed on task level, ISR, and in several hook routines
 */


FUNC(StatusType, OS_CODE) GetAlarm ( AlarmType AlarmID, TickRefType Tick) {

    StatusType RetVal = E_OK;

    /* return the difference between the current counter value and the alarm expiry value */

#if OS_MODE == OS_STANDARD

    if(OsAlarm_Array[AlarmID].AlarmAction.ActionType == ALARM_NOFUNC){

            RetVal = E_OS_NOFUNC;

    }else{
        if( OsAlarmInternal_Array[AlarmID].AlarmExpiryTickValue >=

        OsCounterInternal_Array[OsAlarm_Array[AlarmID].OsAlarmCounterRef].OsCounterVal ){

            *Tick = OsAlarmInternal_Array[AlarmID].AlarmExpiryTickValue -

                    OsCounterInternal_Array[OsAlarm_Array[AlarmID].OsAlarmCounterRef].OsCounterVal;

        }else{  /* Counter has passed the alarm value */

            *Tick = OsCounter_Array[OsAlarm_Array[AlarmID].OsAlarmCounterRef].OsCounterMaxAllowedValue -

                    OsCounterInternal_Array[OsAlarm_Array[AlarmID].OsAlarmCounterRef].OsCounterVal +

                    OsAlarmInternal_Array[AlarmID].AlarmExpiryTickValue;

        }
    }

#elif OS_MODE == OS_EXTENDED

    if(AlarmID > ALARMS_NUMBER){

        RetVal = E_OS_ID;
    }else if(OsAlarm_Array[AlarmID].AlarmAction.ActionType == ALARM_NOFUNC){

        RetVal = E_OS_NOFUNC;

    }else{

        if( OsAlarmInternal_Array[AlarmID].AlarmExpiryTickValue >=

        OsCounterInternal_Array[OsAlarm_Array[AlarmID].OsAlarmCounterRef].OsCounterVal ){

            *Tick = OsAlarmInternal_Array[AlarmID].AlarmExpiryTickValue -

                    OsCounterInternal_Array[OsAlarm_Array[AlarmID].OsAlarmCounterRef].OsCounterVal;

        }else{  /* Counter has passed the alarm value */

            *Tick = OsCounter_Array[OsAlarm_Array[AlarmID].OsAlarmCounterRef].OsCounterMaxAllowedValue -

                    OsCounterInternal_Array[OsAlarm_Array[AlarmID].OsAlarmCounterRef].OsCounterVal +

                    OsAlarmInternal_Array[AlarmID].AlarmExpiryTickValue;

        }

    }

#endif

    return RetVal;

}

/****************************************************************************************************/

/*
     -  Description: The system service occupies the alarm <AlarmID> element. After <increment> ticks have elapsed,
        the task assigned to the alarm <AlarmID> is activated or the assigned event (only for extended tasks)
        is set or the alarm-callback routine is called.
     -  NOTES:  - To change values of alarms already in use the alarm shall be cancelled first.
                If the alarm is already in use, this call will be ignored and the error E_OS_STATE is returned.
                Allowed on task level and in ISR, but not in hook routines.


 */
FUNC(StatusType, OS_CODE) SetRelAlarm ( AlarmType AlarmID, TickType increment, TickType cycle ) {

    VAR( StatusType, AUTOMATIC )   RetVal = E_OK;

#if OS_MODE == OS_STANDARD

        if( OsAlarmInternal_Array[AlarmID].InUse == FALSE ){

            OsAlarmInternal_Array[AlarmID].AlarmExpiryTickValue = (OsCounterInternal_Array[OsAlarm_Array[AlarmID].OsAlarmCounterRef].OsCounterVal + increment) %

                                                                    OsCounter_Array[OsAlarm_Array[AlarmID].OsAlarmCounterRef].OsCounterMaxAllowedValue;

            OsAlarmInternal_Array[AlarmID].Cycle = cycle;

            OsAlarmInternal_Array[AlarmID].InUse = TRUE;

        }else{

            RetVal = E_OS_STATE;

        }

#elif OS_MODE == OS_EXTENDED

    if(AlarmID > ALARMS_NUMBER){

        RetVal = E_OS_ID;
    }else if( OsAlarmInternal_Array[AlarmID].InUse != FALSE ){

        RetVal = E_OS_STATE;

    }else if(increment > OsCounter_Array[OsAlarm_Array[AlarmID].OsAlarmCounterRef].OsCounterMaxAllowedValue ){

        RetVal = E_OS_VALUE;

    }else if(((cycle < OsCounter_Array[OsAlarm_Array[AlarmID].OsAlarmCounterRef].OsCounterMinCycle) && cycle != 0)

            || cycle > OsCounter_Array[OsAlarm_Array[AlarmID].OsAlarmCounterRef].OsCounterMaxAllowedValue ){

        RetVal = E_OS_VALUE;

    }else{

        OsAlarmInternal_Array[AlarmID].AlarmExpiryTickValue = (OsCounterInternal_Array[OsAlarm_Array[AlarmID].OsAlarmCounterRef].OsCounterVal + increment) %

                                                                OsCounter_Array[OsAlarm_Array[AlarmID].OsAlarmCounterRef].OsCounterMaxAllowedValue;

        OsAlarmInternal_Array[AlarmID].Cycle = cycle;

        OsAlarmInternal_Array[AlarmID].InUse = TRUE;



        RetVal = E_OS_STATE;



    }

#endif


    return RetVal;

    }

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

FUNC(StatusType, OS_CODE) SetAbsAlarm ( AlarmType AlarmID, TickType start, TickType cycle ) {

    StatusType RetVal = E_OK;

#if OS_MODE == OS_STANDARD

    /* Make sure alarm is not already in use */
    if(OsAlarmInternal_Array[AlarmID].InUse != FALSE ){

            RetVal = E_OS_STATE;

    }else{

        OsAlarmInternal_Array[AlarmID].AlarmExpiryTickValue = start;

        OsAlarmInternal_Array[AlarmID].Cycle = cycle;

        OsAlarmInternal_Array[AlarmID].InUse = TRUE;


    }

#elif OS_MODE == OS_EXTENDED

    if(AlarmID > ALARMS_NUMBER){

        RetVal = E_OS_ID;

    }if(OsAlarmInternal_Array[AlarmID].InUse != FALSE ){

        RetVal = E_OS_STATE;

    }else if(start > OsCounter_Array[OsAlarm_Array[AlarmID].OsAlarmCounterRef].OsCounterMaxAllowedValue ){

        RetVal = E_OS_VALUE;

    }else if(((cycle < OsCounter_Array[OsAlarm_Array[AlarmID].OsAlarmCounterRef].OsCounterMinCycle) && cycle != 0)

            || cycle > OsCounter_Array[OsAlarm_Array[AlarmID].OsAlarmCounterRef].OsCounterMaxAllowedValue ){

        RetVal = E_OS_VALUE;

    }else{

            if( OsAlarmInternal_Array[AlarmID].InUse == FALSE ){

                    OsAlarmInternal_Array[AlarmID].AlarmExpiryTickValue = start;

                    OsAlarmInternal_Array[AlarmID].Cycle = cycle;

                    OsAlarmInternal_Array[AlarmID].InUse = TRUE;

            }else{

                    RetVal = E_OS_STATE;

            }
    }

#endif

    return RetVal;

}

/****************************************************************************************************/
/*
     - Description: The system service cancels the alarm <AlarmID>.
     -
 */
FUNC(StatusType, OS_CODE) CancelAlarm ( AlarmType AlarmID ) {

    StatusType RetVal = E_OK;

#if OS_MODE == OS_STANDARD

    if(OsAlarmInternal_Array[AlarmID].InUse == FALSE){

        RetVal = E_OS_NOFUNC;

    }else{

        OsAlarmInternal_Array[AlarmID].InUse = FALSE;

    }


#elif OS_MODE == OS_EXTENDED

    if(OsAlarmInternal_Array[AlarmID].InUse == FALSE){

            RetVal = E_OS_NOFUNC;

    }else if(AlarmID > ALARMS_NUMBER){

            RetVal = E_OS_ID;

    }else{

            OsAlarmInternal_Array[AlarmID].InUse = FALSE;

     }

#endif

    return RetVal;

}
