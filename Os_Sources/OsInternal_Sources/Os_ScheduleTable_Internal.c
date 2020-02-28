/*

    Written by : Bebo
    DATE : 7/2/2019
    AUTOSAR Version : 4.3.1
    DOC Name : AUTOSAR_SWS_OS.pdf
    Target : ARM TIVA_C TM4C123GH6PM

*/




#include "..\..\Os_Headers\OsInterface_Headers\Os.h"
#include "..\..\Os_Headers\OsInternal_Headers\Os_Internal.h"


/*************************************************************************************************/


extern VAR( OsCounterInternal, OS_DATA)   OsCounterInternal_Array [COUNTERS_NUMBER ];

extern CONST( OsScheduleTable, OS_CONFIG_DATA ) ScheduleTable_Array [ TABLES_NUMBER ] ;

extern VAR( OsScheduleTableInternal, OS_DATA ) ScheduleTableInternal_Array [ TABLES_NUMBER ] ;

extern CONST( OsScheduleTableExpiryPoint, OS_CONFIG_DATA ) ScheduleTablePoints_Array [ TABLES_POINTS_NUMBER ] ;

extern VAR( TickType, OS_DATA ) ScheduleTablePointsOffsets_Array[TABLES_POINTS_NUMBER ];


//extern CONST( TaskType, OS_CONFIG_DATA ) ScheduleTableTaskActivation_Array [ TABLES_TASKS_NUMBER ] ;
//extern CONST( TaskType, OS_CONFIG_DATA ) ScheduleTableTaskSet_Array [ TABLES_EVENTS_SET_NUMBER ] ;

//extern CONST( TaskType, OS_CONFIG_DATA ) ScheduleTableTaskActivation_Array [ TABLES_TASKS_NUMBER ] ;
//
//extern CONST( TaskType, OS_CONFIG_DATA ) ScheduleTableTaskSet_Array [ TABLES_EVENTS_SET_NUMBER ] ;


extern CONST( EventMaskType, OS_CONFIG_DATA ) ScheduleTableEventSet_Array [ TABLES_EVENTS_SET_NUMBER ] ;



/**************************************************************************************************/

FUNC(void, OS_INTERNAL_CODE) CheckScheduleTablesExpiry( CounterType CounterID ) {

    VAR(uint16 , AUTOMATIC ) i, pCounter;

    for( i = 0; i < TABLES_NUMBER ; i++ ){

        if( ScheduleTable_Array[i].OsScheduleTableCounterRef == CounterID && ScheduleTableInternal_Array[i].CurrentState == SCHEDULETABLE_RUNNING ) {


            /* check for end of table duration */
            if( (OsCounterInternal_Array[ScheduleTable_Array[i].OsScheduleTableCounterRef].OsCounterVal - ScheduleTableInternal_Array[i].StartCounterVal) >=
                 ScheduleTable_Array[i].OsScheduleTableDuration){

                /* if repeating */
                if( ScheduleTable_Array[i].OsScheduleTableRepeating == TRUE ){

                    /* reset expiry point index */
                    ScheduleTableInternal_Array[i].CurrentExpiryPointIndex = ScheduleTable_Array[i].FirstExpiryPoint;

                    /* update StartCounterVal to the next counter increment */
                    ScheduleTableInternal_Array[i].StartCounterVal = OsCounterInternal_Array[ScheduleTable_Array[i].OsScheduleTableCounterRef].OsCounterVal + 1;


                }else if(ScheduleTableInternal_Array[i].NextScheduleTable != EMPTY_NEXT_TABLE ){

                    /* set current schedule table to stopped */
                    ScheduleTableInternal_Array[i].CurrentState  = SCHEDULETABLE_STOPPED;

                    /* set next schedule table to running */
                    ScheduleTableInternal_Array[ScheduleTableInternal_Array[i].NextScheduleTable].CurrentState = SCHEDULETABLE_RUNNING;

                    /* update its start counter value */
                    ScheduleTableInternal_Array[ScheduleTableInternal_Array[i].NextScheduleTable].StartCounterVal = OsCounterInternal_Array[ScheduleTable_Array[i].OsScheduleTableCounterRef].OsCounterVal + 1;

                    /* reset expiry point index */
                    ScheduleTableInternal_Array[ScheduleTableInternal_Array[i].NextScheduleTable].CurrentExpiryPointIndex = ScheduleTable_Array[ScheduleTableInternal_Array[i].NextScheduleTable].FirstExpiryPoint;
                }


            }else if((ScheduleTableInternal_Array[i].CurrentExpiryPointIndex == ScheduleTable_Array[i].ExpiryPointsNumber - 1) &&
               ((ScheduleTable_Array[i].OsScheduleTableRepeating == TRUE) || (ScheduleTableInternal_Array[i].NextScheduleTable != EMPTY_NEXT_TABLE))){

                /* check for last point */
                /* process the delay and do nothing */

            }else if(ScheduleTableInternal_Array[i].CurrentExpiryPointIndex == ScheduleTable_Array[i].ExpiryPointsNumber - 1) {

                /* if it's the last point and it's not repeating stop the processing of the final delay */
                ScheduleTableInternal_Array[i].CurrentState  = SCHEDULETABLE_STOPPED;

            }else if(OsCounterInternal_Array[CounterID].OsCounterVal == (ScheduleTableInternal_Array[i].StartCounterVal + ScheduleTablePoints_Array[ScheduleTableInternal_Array[i].CurrentExpiryPointIndex].OsScheduleTblExpPointOffset)){

                /* execute expiry point */

                /* Task Activation */

                for(pCounter = ScheduleTablePoints_Array[ScheduleTableInternal_Array[i].CurrentExpiryPointIndex].PointTasks.FirstTaskActivation;
                    pCounter < ScheduleTablePoints_Array[ScheduleTableInternal_Array[i].CurrentExpiryPointIndex].PointTasks.TaskActivationNumber;
                    pCounter++ )
                {
                    //ActivateTask(ScheduleTableTaskActivation_Array[pCounter]);
                    if(ScheduleTableInternal_Array[i].CurrentExpiryPointIndex == 0){

                    }else{

                    }
                }

                /* Event Setting */
                for(pCounter = ScheduleTablePoints_Array[ScheduleTableInternal_Array[i].CurrentExpiryPointIndex].PointEvents.FirstEventSet;
                    pCounter < ScheduleTablePoints_Array[ScheduleTableInternal_Array[i].CurrentExpiryPointIndex].PointEvents.EventSetNumber;
                    pCounter++ )
                {
                    //SetEvent(ScheduleTableTaskSet_Array[pCounter],ScheduleTableEventSet_Array[pCounter]);
                    if(ScheduleTableInternal_Array[i].CurrentExpiryPointIndex == 0){

                    }else{

                    }
                }
                ScheduleTableInternal_Array[i].CurrentExpiryPointIndex++;

            }


        }

    }
}

