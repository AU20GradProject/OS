/*

    Written by : Bakr
    DATE : 18/2/2020
    AUTOSAR Version : 4.3.1
    DOC Name : AUTOSAR_SWS_OS.pdf
    Target : ARM TIVA_C TM4C123GH6PM

*/



#include "..\..\Os_Headers\OsInterface_Headers\Os.h"
#include "..\..\Os_Headers\OsInternal_Headers\Os_Internal.h"

/*
   - Synchronous may cause rescheduling ,reentrant, Service ID: 0x0f
   - This service:
       - increments a software counter by one
       - if any alarm connected to this counter expires,
         the given action, e.g. task activation, is done
   - CounterID - The Counter to be incremented
   - if CounterID is valid E_OK is return after incrementing
   - Caveats: if called from a task rescheduling may take place
   - NOTES: this function is only called inside the Systick Handler
 */
FUNC( StatusType, OS_CODE) IncrementCounter( CounterType CounterID ){

    StatusType RetVal = E_OK;

#if OS_MODE == OS_STANDARD


    OsCounterInternal_Array[CounterID].OsCounterTicksValue++;

    if(OsCounterInternal_Array[CounterID].OsCounterTicksValue == OsCounter_Array[CounterID].OsCounterTicksPerBase){

        OsCounterInternal_Array[CounterID].OsCounterTicksValue = 0;

        OsCounterInternal_Array[CounterID].OsCounterVal++;

        if( OsCounterInternal_Array[CounterID].OsCounterVal >OsCounter_Array[CounterID].OsCounterMaxAllowedValue )
        {

            OsCounterInternal_Array[CounterID].OsCounterVal = 0;

        }
        CheckAlarmExpiry(CounterID);
    }

#elif OS_MODE == OS_EXTENDED

    if(COUNTERS_NUMBER <= CounterID ){

        RetVal = E_OS_ID;

    }else{
        OsCounterInternal_Array[CounterID].OsCounterTicksValue++;

        if(OsCounterInternal_Array[CounterID].OsCounterTicksValue == OsCounter_Array[CounterID].OsCounterTicksPerBase){

            OsCounterInternal_Array[CounterID].OsCounterTicksValue = 0;

            OsCounterInternal_Array[CounterID].OsCounterVal++;

            if( OsCounterInternal_Array[CounterID].OsCounterVal >=OsCounter_Array[CounterID].OsCounterMaxAllowedValue )
            {

                OsCounterInternal_Array[CounterID].OsCounterVal = OsCounter_Array[CounterID].OsCounterMinCycle;

            }
            CheckAlarmExpiry(CounterID);
            CheckScheduleTablesExpiry(CounterID);
        }
    }

#endif

    return RetVal;
}

/*************************************************************************************************/

/*
   - Synchronous ,reentrant, Service ID: 0x10
   - This service This service reads the current count value of a counter
     returning either the hardware timer ticks if counter is driven by hardware or
     the software ticks when user drives counter.

   - CounterID - The Counter to be incremented
   - if CounterID is valid E_OK is return after incrementing
   - Caveats: Caveats of GetCounterValue(): Note that for counters of OsCounterType = HARDWARE the real timer value
     is returned, whereas for counters of OsCounterType = SOFTWARE the current “software” tick value is returned.

 */
FUNC( StatusType, OS_CODE) GetCounterValue( CounterType CounterID, TickRefType Value )
{
    StatusType RetVal = E_OK;


    *Value =  OsCounterInternal_Array[CounterID].OsCounterVal;

#if OS_MODE == OS_STANDARD



#elif OS_MODE == OS_EXTENDED

    if(CounterID >= COUNTERS_NUMBER  ){

        RetVal = E_OS_ID;

    }else{

        Value = & OsCounterInternal_Array[CounterID].OsCounterVal;

    }

#endif

    return RetVal;
}

/*************************************************************************************************/

/*
   - Synchronous ,reentrant, Service ID: 0x11
   - This service gets the number of ticks between the current tick value and a previously read tick value.
   - Caveats of GetElapsedValue():If the timer already passed the <Value> value a second (or multiple) time,
     the result returned is wrong. The reason is that the service can not detect such a relative overflow.

 */
FUNC( StatusType, OS_CODE) GetElapsedValue( CounterType CounterID, TickRefType Value, TickRefType ElapsedValue ){

    StatusType RetVal = E_OK;


#if OS_MODE == OS_STANDARD


#elif  OS_MODE == OS_EXTENDED


#endif

    return RetVal;

}

/*************************************************************************************************/

FUNC(void, ISR_CODE) SysTick_Handler(void)
{

    uint8 i;
    for(i = 0; i < COUNTERS_NUMBER; i++)
    {

        IncrementCounter(i);

    }

}
