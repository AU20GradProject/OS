/*

    Written by : Bebo
    DATE : 7/2/2019
    AUTOSAR Version : 4.3.1
    DOC Name : AUTOSAR_SWS_OS.pdf
    Target : ARM TIVA_C TM4C123GH6PM

*/



#include "..\..\Os_Headers\OsInterface_Headers\Os.h"
#include "..\..\Os_Headers\OsInternal_Headers\Os_Internal.h"

extern void ToggleGreenLed(void);

CONST( OsAlarm, OS_CONFIG_DATA ) OsAlarm_Array [ ALARMS_NUMBER ] = OS_ALARMS_OBJECT_CONGIFURATION ;


extern VAR( OsCounterInternal, OS_DATA)   OsCounterInternal_Array [COUNTERS_NUMBER ];

/* Controlled by Os Alarm API */
VAR( OsAlarmInternal, OS_CONFIG_DATA ) OsAlarmInternal_Array [ALARMS_NUMBER] = OS_ALARMS_INTERNAL_OBJECT_CONFIGURATION ;

FUNC(void, OS_INTERNAL_CODE) CheckAlarmExpiry(CounterType CounterID){

    VAR(uint8, AUTOMATIC) i;
    /* know which of the alarms depend on CounterID */
    for(i = 0; i < ALARMS_NUMBER ; i++){

        /* if CounterID value equal to AlarmExpiry */
        if(OsAlarm_Array[i].OsAlarmCounterRef == CounterID && OsAlarmInternal_Array[i].InUse == TRUE
           && OsAlarmInternal_Array[i].AlarmExpiryTickValue == OsCounterInternal_Array[i].OsCounterVal){

            switch(OsAlarm_Array[i].AlarmAction.ActionType){

            case ALARM_ACTION_ACT_TASK:

                //ActivateTask(OsAlarm_Array[i].AlarmAction.Action.OsAlarmActivateTaskRef);

                break;
            case ALARM_ACTION_CALLBACK:
                OsAlarm_Array[i].AlarmAction.Action.OsAlarmCallbackName();
                break;

            case ALARM_ACTION_INC_COUNTER:
                IncrementCounter(OsAlarm_Array[i].AlarmAction.Action.OsAlarmIncrementCounterRef);
                break;

            case ALARM_ACTION_SET_EVENT:
                //SetEvent(OsAlarm_Array[i].AlarmAction.Action.AlarmEvent);
                break;

            case ALARM_NOFUNC:
                break;
            }
            OsAlarmInternal_Array[i].InUse = FALSE;

            /* check if cyclic */
            if(OsAlarmInternal_Array[i].Cycle != 0){

                SetRelAlarm ( i , OsAlarmInternal_Array[i].Cycle , OsAlarmInternal_Array[i].Cycle );

            }
        }
    }
}


FUNC(void, OS_CODE_INTERNAL) AlarmAutoStart(){

    VAR(uint8, AUTOMATIC) i;

    for(i = 0 ; i < ALARMS_NUMBER; i++){

        if( OsAlarm_Array[i].AlarmAutostart.OsAlarmAppModeRef == AUTOSTART ){

            if(OsAlarm_Array[i].AlarmAutostart.OsAlarmAutostartType == ALARM_ABSOLUTE ){

                SetAbsAlarm(i,OsAlarm_Array[i].AlarmAutostart.OsAlarmAlarmTime,OsAlarm_Array[i].AlarmAutostart.OsAlarmCycleTime);

            }else if(OsAlarm_Array[i].AlarmAutostart.OsAlarmAutostartType == ALARM_RELATIVE){

                SetRelAlarm(i,OsAlarm_Array[i].AlarmAutostart.OsAlarmAlarmTime,OsAlarm_Array[i].AlarmAutostart.OsAlarmCycleTime);

            }
        }

    }

}
