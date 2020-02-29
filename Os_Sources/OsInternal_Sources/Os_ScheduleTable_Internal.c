/*

    Written by : Bakr
    DATE : 18/2/2020
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

extern VAR( ExpiryPointOffset, OS_DATA ) ScheduleTablePointsOffsets_Array[TABLES_POINTS_NUMBER ];

extern CONST( EventMaskType, OS_CONFIG_DATA ) ScheduleTableEventSet_Array [ TABLES_EVENTS_SET_NUMBER ] ;



/**************************************************************************************************/

FUNC(void, OS_INTERNAL_CODE) CheckScheduleTablesExpiry( CounterType CounterID ) {

    VAR(uint16 , AUTOMATIC ) i, pCounter;

    for( i = 0; i < TABLES_NUMBER ; i++ ){

        if( ScheduleTable_Array[i].OsScheduleTableCounterRef == CounterID && ScheduleTableInternal_Array[i].CurrentState == SCHEDULETABLE_RUNNING ) {


            if( ScheduleTableInternal_Array[i].ScheduleTableDuration == 0 ){

                /* set current schedule table to stopped */
                ScheduleTableInternal_Array[i].CurrentState  = SCHEDULETABLE_STOPPED;

                if(ScheduleTableInternal_Array[i].NextScheduleTable != EMPTY_NEXT_TABLE ){


                    ScheduleTableInternal_Array[ScheduleTableInternal_Array[i].NextScheduleTable].CurrentState = SCHEDULETABLE_STOPPED;
                    StartScheduleTableRel( ScheduleTableInternal_Array[i].NextScheduleTable, 1 );

                /* if repeating */
                }else if( ScheduleTable_Array[i].OsScheduleTableRepeating == TRUE ){

                    StartScheduleTableRel( i, 1 );

                }


            }else if(ScheduleTablePointsOffsets_Array[ScheduleTableInternal_Array[i].CurrentExpiryPointIndex].EPCurrentOffset == 0){

                /* Task Activation */

                for(pCounter = ScheduleTablePoints_Array[ScheduleTableInternal_Array[i].CurrentExpiryPointIndex].PointTasks.FirstTaskActivation;
                    pCounter < ScheduleTablePoints_Array[ScheduleTableInternal_Array[i].CurrentExpiryPointIndex].PointTasks.TaskActivationNumber;
                    pCounter++ )
                {
                    ActivateTask(ScheduleTableTaskActivation_Array[pCounter]);
                }

                /* Event Setting */
                for(pCounter = ScheduleTablePoints_Array[ScheduleTableInternal_Array[i].CurrentExpiryPointIndex].PointEvents.FirstEventSet;
                    pCounter < ScheduleTablePoints_Array[ScheduleTableInternal_Array[i].CurrentExpiryPointIndex].PointEvents.EventSetNumber;
                    pCounter++ )
                {
                    SetEvent(ScheduleTableTaskSet_Array[pCounter],ScheduleTableEventSet_Array[pCounter]);
                }

                if((ScheduleTableInternal_Array[i].CurrentExpiryPointIndex == ScheduleTable_Array[i].ExpiryPointsNumber - 1) &&
                        ((ScheduleTable_Array[i].OsScheduleTableRepeating == FALSE) && (ScheduleTableInternal_Array[i].NextScheduleTable == EMPTY_NEXT_TABLE)))
                {

                    /* don't process final delay if it's not repeating or has next table */
                    ScheduleTableInternal_Array[i].CurrentState = SCHEDULETABLE_STOPPED;

                }

                /* offset processing */
                ScheduleTablePointsOffsets_Array[ScheduleTableInternal_Array[i].CurrentExpiryPointIndex + 1].EPCurrentOffset
                            -=  ScheduleTablePointsOffsets_Array[ScheduleTableInternal_Array[i].CurrentExpiryPointIndex].EPFullOffset ;

                ScheduleTablePointsOffsets_Array[ScheduleTableInternal_Array[i].CurrentExpiryPointIndex + 1].EPFullOffset
                            = ScheduleTablePointsOffsets_Array[ScheduleTableInternal_Array[i].CurrentExpiryPointIndex + 1].EPCurrentOffset;

                ScheduleTableInternal_Array[i].CurrentExpiryPointIndex++;

            }

            ScheduleTablePointsOffsets_Array[ScheduleTableInternal_Array[i].CurrentExpiryPointIndex].EPCurrentOffset--;

            ScheduleTableInternal_Array[i].ScheduleTableDuration--;


        }

    }
}


