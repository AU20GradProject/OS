/*

    Written by : Bebo
    DATE : 7/2/2019
    AUTOSAR Version : 4.3.1
    DOC Name : AUTOSAR_SWS_OS.pdf
    Target : ARM TIVA_C TM4C123GH6PM

*/



#include "..\..\Os_Headers\OsInterface_Headers\Os.h"
#include "..\..\Os_Headers\OsInternal_Headers\Os_Internal.h"
#include "..\..\Os_Headers\OsInternal_Headers\Os_ExternalVariables.h"


FUNC(void, OS_INTERNAL_CODE) CheckAlarmExpiry(CounterType CounterID){

    VAR(uint8, AUTOMATIC) i;
    /* know which of the alarms depend on CounterID */
    for(i = 0; i < ALARMS_NUMBER ; i++){

        /* if CounterID value equal to AlarmExpiry */
        if(OsAlarm_Array[i].OsAlarmCounterRef == CounterID && OsAlarmInternal_Array[i].InUse == TRUE
           && OsAlarmInternal_Array[i].AlarmExpiryTickValue == OsCounterInternal_Array[i].OsCounterVal){

            switch(OsAlarm_Array[i].AlarmAction.ActionType){

            case ALARM_ACTION_ACT_TASK:

                ActivateTask(OsAlarm_Array[i].AlarmAction.Action.OsAlarmActivateTaskRef);

                break;
            case ALARM_ACTION_CALLBACK:
                OsAlarm_Array[i].AlarmAction.Action.OsAlarmCallbackName();
                break;

            case ALARM_ACTION_INC_COUNTER:
                IncrementCounter(OsAlarm_Array[i].AlarmAction.Action.OsAlarmIncrementCounterRef);
                break;

            case ALARM_ACTION_SET_EVENT:
                SetEvent(OsAlarm_Array[i].AlarmAction.Action.AlarmEvent.OsAlarmSetEventTaskRef,OsAlarm_Array[i].AlarmAction.Action.AlarmEvent.OsAlarmSetEventRef);
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


