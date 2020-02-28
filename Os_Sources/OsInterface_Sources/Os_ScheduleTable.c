/*

    Written by : Bebo
    DATE : 7/2/2019
    AUTOSAR Version : 4.3.1
    DOC Name : AUTOSAR_SWS_OS.pdf
    Target : ARM TIVA_C TM4C123GH6PM

*/



#include "..\..\Os_Headers\OsInterface_Headers\Os.h"
#include "..\..\Os_Headers\OsInternal_Headers\Os_Internal.h"


extern CONST( OsScheduleTable, OS_CONFIG_DATA ) ScheduleTable_Array [ TABLES_NUMBER ] ;

extern VAR( OsScheduleTableInternal, OS_CONFIG_DATA ) ScheduleTableInternal_Array [ TABLES_NUMBER ] ;

extern CONST( OsScheduleTableExpiryPoint, OS_CONFIG_DATA ) ScheduleTablePoints_Array [ TABLES_POINTS_NUMBER ] ;

//extern CONST( TaskType, OS_CONFIG_DATA ) ScheduleTableTaskActivation_Array [ TABLES_TASKS_NUMBER ] ;

//extern CONST( TaskType, OS_CONFIG_DATA ) ScheduleTableTaskSet_Array [ TABLES_EVENTS_SET_NUMBER ] ;

extern CONST( EventMaskType, OS_CONFIG_DATA ) ScheduleTableEventSet_Array [ TABLES_EVENTS_SET_NUMBER ] ;

extern CONST( OsCounter, OS_CONFIG_DATA ) OsCounter_Array [ COUNTERS_NUMBER ] ;

extern VAR( OsCounterInternal, OS_DATA)   OsCounterInternal_Array [COUNTERS_NUMBER ];

extern VAR( TickType, OS_DATA ) ScheduleTablePointsOffsets_Array[TABLES_POINTS_NUMBER ];

/*
     - Service: 0x07, Synchronous, Reentrant
     - This service starts the processing of a schedule table at "Offset" relative to the "Now" value on the underlying counter.
 */
FUNC(StatusType, OS_CODE) StartScheduleTableRel( ScheduleTableType ScheduleTableID, TickType Offset ){

    VAR(StatusType, AUTOMATIC) RetVal = E_OK;

    VAR( uint16, AUTOMATIC ) i, j;


#if OS_MODE == OS_STANDARD

    /* [SWS_Os_00452] If the schedule table <ScheduleTableID> in a call of StartScheduleTableRel() is implicitely
           synchronized (OsScheduleTblSyncStrategy = IMPLICIT), StartScheduleTableRel() shall return E_OS_ID.  ( ) */
    if(ScheduleTable_Array[ScheduleTableID].OsScheduleTblSyncStrategy == IMPLICIT){

        RetVal = E_OS_ID;

    }if(ScheduleTableID >= TABLES_NUMBER){

        RetVal = E_OS_ID;

    }else if(Offset == 0 ||
            Offset > OsCounter_Array[ScheduleTable_Array[ScheduleTableID].OsScheduleTableCounterRef].OsCounterMaxAllowedValue ||
            Offset < OsCounter_Array[ScheduleTable_Array[ScheduleTableID].OsScheduleTableCounterRef].OsCounterMinCycle ||
            (Offset + ScheduleTable_Array[ScheduleTableID].OsScheduleTableDuration) > OsCounter_Array[ScheduleTable_Array[ScheduleTableID].OsScheduleTableCounterRef].OsCounterMaxAllowedValue)
    {


    }else if(ScheduleTableInternal_Array[ScheduleTableID].CurrentState != SCHEDULETABLE_STOPPED){

        /* [SWS_Os_00277] If the schedule table <ScheduleTableID> in a call of StartScheduleTableRel() is not in the state SCHEDULETABLE_STOPPED,
           StartScheduleTableRel() shall return E_OS_STATE.    ( ) */

        RetVal = E_OS_STATE;
    }else{
        /* [SWS_Os_00278] If the input parameters of StartScheduleTableRel() are valid and
           the state of schedule table <ScheduleTableID> is SCHEDULETABLE_STOPPED,
           then StartScheduleTableRel() shall start the processing of a schedule table <ScheduleTableID>.
           The Initial Expiry Point shall be processed after <Offset> + Initial Offset ticks have elapsed on the underlying counter.
           The state of <ScheduleTableID> is set to SCHEDULETABLE_RUNNING before the service returns to the caller. ( ) */

        /* store the current value of the counter */
        //ScheduleTableInternal_Array[ScheduleTableID].StartCounterVal = Offset + OsCounterInternal_Array[ScheduleTable_Array[ScheduleTableID].OsScheduleTableCounterRef].OsCounterVal;

        for(i = ScheduleTable_Array[ScheduleTableID].FirstExpiryPoint, j = 0; i < ScheduleTable_Array[ScheduleTableID].ExpiryPointsNumber ; i++, j++){

            ScheduleTablePointsOffsets_Array[j] = Offset + ScheduleTablePoints_Array[j].OsScheduleTblExpPointOffset ;

        }

        /* set index of schedule table expiry point to start */
        ScheduleTableInternal_Array[ScheduleTableID].CurrentExpiryPointIndex = ScheduleTable_Array[ScheduleTableID].FirstExpiryPoint;

        /* set schedule table state to running */
        ScheduleTableInternal_Array[ScheduleTableID].CurrentState = SCHEDULETABLE_RUNNING;

    }


#elif OS_MODE == OS_EXTENDED

    /* [SWS_Os_00275] If the schedule table <ScheduleTableID> in a call of StartScheduleTableRel()
       is not valid, StartScheduleTableRel() shall return E_OS_ID.  in EXTENDED MODE  ( )*/
    if(ScheduleTableID >= TABLES_NUMBER){

        RetVal = E_OS_ID;

    }else if(ScheduleTable_Array[ScheduleTableID].OsScheduleTblSyncStrategy == IMPLICIT){
        /* [SWS_Os_00452] If the schedule table <ScheduleTableID> in a call of StartScheduleTableRel() is implicitely
           synchronized (OsScheduleTblSyncStrategy = IMPLICIT), StartScheduleTableRel() shall return E_OS_ID.  ( ) */
        RetVal = E_OS_ID;

    }else if(Offset == 0 ||
            Offset > OsCounter_Array[ScheduleTable_Array[ScheduleTableID].OsScheduleTableCounterRef].OsCounterMaxAllowedValue ||
            Offset < OsCounter_Array[ScheduleTable_Array[ScheduleTableID].OsScheduleTableCounterRef].OsCounterMinCycle
            )
    {
        /* [SWS_Os_00332] If <Offset> in a call of StartScheduleTableRel() is zero StartScheduleTableRel() shall
           return E_OS_VALUE. in EXTENDED  ( ) */

        /* [SWS_Os_00276] If the offset <Offset>) is greater than OsCounterMaxAllowedValue of the underlying counter minus the Initial Offset,
               StartScheduleTableRel() shall return E_OS_VALUE. in EXTENDED  ( )  */

        RetVal = E_OS_VALUE;

    }else if(ScheduleTableInternal_Array[ScheduleTableID].CurrentState != SCHEDULETABLE_STOPPED){

        /* [SWS_Os_00277] If the schedule table <ScheduleTableID> in a call of StartScheduleTableRel() is not in the state SCHEDULETABLE_STOPPED,
           StartScheduleTableRel() shall return E_OS_STATE.    ( ) */

        RetVal = E_OS_STATE;

    }else{
        /* [SWS_Os_00278] If the input parameters of StartScheduleTableRel() are valid and
           the state of schedule table <ScheduleTableID> is SCHEDULETABLE_STOPPED,
           then StartScheduleTableRel() shall start the processing of a schedule table <ScheduleTableID>.
           The Initial Expiry Point shall be processed after <Offset> + Initial Offset ticks have elapsed on the underlying counter.
           The state of <ScheduleTableID> is set to SCHEDULETABLE_RUNNING before the service returns to the caller. ( ) */

        /* store the current value of the counter */
        //ScheduleTableInternal_Array[ScheduleTableID].StartCounterVal = Offset + OsCounterInternal_Array[ScheduleTable_Array[ScheduleTableID].OsScheduleTableCounterRef].OsCounterVal;


        for(i = ScheduleTable_Array[ScheduleTableID].FirstExpiryPoint, j = 0; i < ScheduleTable_Array[ScheduleTableID].ExpiryPointsNumber ; i++, j++){

            ScheduleTablePointsOffsets_Array[j] = Offset + ScheduleTablePoints_Array[j].OsScheduleTblExpPointOffset ;

        }

        /* set index of schedule table expiry point to start */
        ScheduleTableInternal_Array[ScheduleTableID].CurrentExpiryPointIndex = ScheduleTable_Array[ScheduleTableID].FirstExpiryPoint;

        /* set schedule table state to running */
        ScheduleTableInternal_Array[ScheduleTableID].CurrentState = SCHEDULETABLE_RUNNING;

    }

#endif

    return RetVal;
}

FUNC( StatusType, OS_CODE ) StartScheduleTableAbs( ScheduleTableType ScheduleTableID, TickType Start ) {

    VAR(StatusType, AUTOMATIC) RetVal = E_OK;

    VAR( uint16, AUTOMATIC ) i, j;

    VAR( TickType, AUTOMATIC ) Offset;

#if OS_MODE == OS_STANDARD

    /* [SWS_Os_00452] If the schedule table <ScheduleTableID> in a call of StartScheduleTableRel() is implicitely
           synchronized (OsScheduleTblSyncStrategy = IMPLICIT), StartScheduleTableRel() shall return E_OS_ID.  ( ) */
    if(ScheduleTable_Array[ScheduleTableID].OsScheduleTblSyncStrategy == IMPLICIT){

        RetVal = E_OS_ID;

    }else if(ScheduleTableID >= TABLES_NUMBER){


    }else if(Start > OsCounter_Array[ScheduleTable_Array[ScheduleTableID].OsScheduleTableCounterRef].OsCounterMaxAllowedValue ||
            Start < OsCounter_Array[ScheduleTable_Array[ScheduleTableID].OsScheduleTableCounterRef].OsCounterMinCycle ||
            (Start + ScheduleTable_Array[ScheduleTableID].OsScheduleTableDuration) > OsCounter_Array[ScheduleTable_Array[ScheduleTableID].OsScheduleTableCounterRef].OsCounterMaxAllowedValue)
    {

    }else if(ScheduleTableInternal_Array[ScheduleTableID].CurrentState != SCHEDULETABLE_STOPPED){

        /* [SWS_Os_00350] If the schedule table <ScheduleTableID> in a call of StartScheduleTableAbs() is not in the state SCHEDULETABLE_STOPPED,
           StartScheduleTableAbs() shall return E_OS_STATE. ( ) */

        RetVal = E_OS_STATE;
    }else{
        /* [SWS_Os_00351] If the input parameters of StartScheduleTableAbs() are valid and <ScheduleTableID> is in the state SCHEDULETABLE_STOPPED, StartScheduleTableAbs() shall start the processing of schedule table <ScheduleTableID> when the underlying counter next equals <Start> and shall set the state of <ScheduleTableID> to
                - SCHEDULETABLE_RUNNING (for a non-synchronized / Explicitly synchronized schedule table) OR
                - SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS (for implicitly synchronized schedule table) before returning to the user.
                (The Initial Expiry Point will be processed when the underlying counter next equals <Start>+Initial Offset).  ( ) */

        /* store the current value of the counter */
        //ScheduleTableInternal_Array[ScheduleTableID].StartCounterVal = Start;

        if(OsCounterInternal_Array[ScheduleTable_Array[ScheduleTableID].OsScheduleTableCounterRef].OsCounterVal > Start){
           Offset = OsCounter_Array[ScheduleTable_Array[ScheduleTableID].OsScheduleTableCounterRef].OsCounterMaxAllowedValue - OsCounterInternal_Array[ScheduleTable_Array[ScheduleTableID].OsScheduleTableCounterRef].OsCounterVal
                   + Start;
       }else if(OsCounterInternal_Array[ScheduleTable_Array[ScheduleTableID].OsScheduleTableCounterRef].OsCounterVal <= Start){

           Offset = Start - OsCounterInternal_Array[ScheduleTable_Array[ScheduleTableID].OsScheduleTableCounterRef].OsCounterVal;

       }

       for(i = ScheduleTable_Array[ScheduleTableID].FirstExpiryPoint, j = 0; i < ScheduleTable_Array[ScheduleTableID].ExpiryPointsNumber ; i++, j++){

           ScheduleTablePointsOffsets_Array[j] = Offset + ScheduleTablePoints_Array[j].OsScheduleTblExpPointOffset ;

       }
        /* set index of schedule table expiry point to start */
        ScheduleTableInternal_Array[ScheduleTableID].CurrentExpiryPointIndex = ScheduleTable_Array[ScheduleTableID].FirstExpiryPoint;

        /* set schedule table state to running */
        ScheduleTableInternal_Array[ScheduleTableID].CurrentState = SCHEDULETABLE_RUNNING;

    }


#elif OS_MODE == OS_EXTENDED

    /* [SWS_Os_00452] If the schedule table <ScheduleTableID> in a call of StartScheduleTableRel() is implicitely
           synchronized (OsScheduleTblSyncStrategy = IMPLICIT), StartScheduleTableRel() shall return E_OS_ID.  ( ) */
    if(ScheduleTable_Array[ScheduleTableID].OsScheduleTblSyncStrategy == IMPLICIT){

        RetVal = E_OS_ID;

    }else if(ScheduleTableID >= TABLES_NUMBER){

        /*[SWS_Os_00348] If the schedule table <ScheduleTableID> in a call of StartScheduleTableAbs() is not valid,
         StartScheduleTableAbs() shall return E_OS_ID.  ( )*/

        RetVal = E_OS_ID;

    }else if(Start > OsCounter_Array[ScheduleTable_Array[ScheduleTableID].OsScheduleTableCounterRef].OsCounterMaxAllowedValue ||
            Start < OsCounter_Array[ScheduleTable_Array[ScheduleTableID].OsScheduleTableCounterRef].OsCounterMinCycle ||
            (Start + ScheduleTable_Array[ScheduleTableID].OsScheduleTableDuration) >= OsCounter_Array[ScheduleTable_Array[ScheduleTableID].OsScheduleTableCounterRef].OsCounterMaxAllowedValue)
    {

        /*[SWS_Os_00349] If the <Start> in a call of StartScheduleTableAbs() is greater than the OsCounterMaxAllowedValue of the underlying counter,
                StartScheduleTableAbs() shall return E_OS_VALUE. ( )*/
        RetVal = E_OS_VALUE;

    }else if(ScheduleTableInternal_Array[ScheduleTableID].CurrentState != SCHEDULETABLE_STOPPED){

        /* [SWS_Os_00350] If the schedule table <ScheduleTableID> in a call of StartScheduleTableAbs() is not in the state SCHEDULETABLE_STOPPED,
           StartScheduleTableAbs() shall return E_OS_STATE. ( ) */

        RetVal = E_OS_STATE;
    }else{
        /* [SWS_Os_00351] If the input parameters of StartScheduleTableAbs() are valid and <ScheduleTableID> is in the state SCHEDULETABLE_STOPPED, StartScheduleTableAbs() shall start the processing of schedule table <ScheduleTableID> when the underlying counter next equals <Start> and shall set the state of <ScheduleTableID> to
                - SCHEDULETABLE_RUNNING (for a non-synchronized / Explicitly synchronized schedule table) OR
                - SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS (for implicitly synchronized schedule table) before returning to the user.
                (The Initial Expiry Point will be processed when the underlying counter next equals <Start>+Initial Offset).  ( ) */

        /* store the current value of the counter */
        //ScheduleTableInternal_Array[ScheduleTableID].StartCounterVal = Start;

        if(OsCounterInternal_Array[ScheduleTable_Array[ScheduleTableID].OsScheduleTableCounterRef].OsCounterVal > Start){
            Offset = OsCounter_Array[ScheduleTable_Array[ScheduleTableID].OsScheduleTableCounterRef].OsCounterMaxAllowedValue - OsCounterInternal_Array[ScheduleTable_Array[ScheduleTableID].OsScheduleTableCounterRef].OsCounterVal
                    + Start;
        }else if(OsCounterInternal_Array[ScheduleTable_Array[ScheduleTableID].OsScheduleTableCounterRef].OsCounterVal <= Start){

            Offset = Start - OsCounterInternal_Array[ScheduleTable_Array[ScheduleTableID].OsScheduleTableCounterRef].OsCounterVal;

        }


        for(i = ScheduleTable_Array[ScheduleTableID].FirstExpiryPoint, j = 0; i < ScheduleTable_Array[ScheduleTableID].ExpiryPointsNumber ; i++, j++){

            ScheduleTablePointsOffsets_Array[j] = Offset + ScheduleTablePoints_Array[j].OsScheduleTblExpPointOffset ;

        }
        /* set index of schedule table expiry point to start */
        ScheduleTableInternal_Array[ScheduleTableID].CurrentExpiryPointIndex = ScheduleTable_Array[ScheduleTableID].FirstExpiryPoint;

        /* set schedule table state to running */
        ScheduleTableInternal_Array[ScheduleTableID].CurrentState = SCHEDULETABLE_RUNNING;

    }

#endif

    return RetVal;
}

FUNC( StatusType, OS_CODE ) StopScheduleTable( ScheduleTableType ScheduleTableID ){

    StatusType RetVal = E_OK;

#if OS_MODE == OS_STANDARD

    if(ScheduleTableID >= TABLES_NUMBER){


    }else if(ScheduleTableInternal_Array[ScheduleTableID].CurrentState != SCHEDULETABLE_STOPPED){

        /* [SWS_Os_00280] If the schedule table with identifier <ScheduleTableID> is in state SCHEDULETABLE_STOPPED when calling StopScheduleTable(),
           StopScheduleTable() shall return E_OS_NOFUNC. ( ) */

        RetVal = E_OS_NOFUNC;

    }else{

        ScheduleTableInternal_Array[ScheduleTableID].CurrentState = SCHEDULETABLE_STOPPED;

        if(ScheduleTableInternal_Array[ScheduleTableID].CurrentState != EMPTY_NEXT_TABLE){

            ScheduleTableInternal_Array[ScheduleTableInternal_Array[ScheduleTableID].NextScheduleTable].CurrentState = SCHEDULETABLE_STOPPED;

        }
    }


#elif OS_MODE == OS_EXTENDED

    if(ScheduleTableID >= TABLES_NUMBER){

            /*[SWS_Os_00279] If the schedule table identifier <ScheduleTableID> in a call of StopScheduleTable() is not valid,
              StopScheduleTable() shall return E_OS_ID. ( )*/

            RetVal = E_OS_ID;

    }else if(ScheduleTableInternal_Array[ScheduleTableID].CurrentState != SCHEDULETABLE_STOPPED){

        /* [SWS_Os_00280] If the schedule table with identifier <ScheduleTableID> is in state SCHEDULETABLE_STOPPED when calling StopScheduleTable(),
           StopScheduleTable() shall return E_OS_NOFUNC. ( ) */

        RetVal = E_OS_NOFUNC;
    }else{

        ScheduleTableInternal_Array[ScheduleTableID].CurrentState = SCHEDULETABLE_STOPPED;

        if(ScheduleTableInternal_Array[ScheduleTableID].CurrentState != EMPTY_NEXT_TABLE){

            ScheduleTableInternal_Array[ScheduleTableInternal_Array[ScheduleTableID].NextScheduleTable].CurrentState = SCHEDULETABLE_STOPPED;

        }
    }

#endif



    return RetVal;

}

FUNC( StatusType, OS_CODE ) NextScheduleTable( ScheduleTableType ScheduleTableID_From, ScheduleTableType ScheduleTableID_To ) {

    StatusType RetVal = E_OK;


#if OS_MODE == OS_STANDARD

    if(ScheduleTableID_From >= TABLES_NUMBER || ScheduleTableID_To >= TABLES_NUMBER ){


    }else if(ScheduleTable_Array[ScheduleTableID_From].OsScheduleTableCounterRef != ScheduleTable_Array[ScheduleTableID_To].OsScheduleTableCounterRef){


    }else if(ScheduleTableInternal_Array[ScheduleTableID_From].CurrentState != SCHEDULETABLE_RUNNING){

        /* [SWS_Os_00330] If in a call of NextScheduleTable() schedule table <ScheduleTableID_To> is driven by different counter
           than schedule table <ScheduleTableID_From> then NextScheduleTable() shall return an error E_OS_ID.  ( )*/

        RetVal = E_OS_NOFUNC;

    }else if(ScheduleTableInternal_Array[ScheduleTableID_To].CurrentState != SCHEDULETABLE_STOPPED){

        /* [SWS_Os_00309] If the schedule table <ScheduleTableID_To> in a call of NextScheduleTable() is not in state SCHEDULETABLE_STOPPED,
           NextScheduleTable() shall leave the state of <ScheduleTable_From> and <ScheduleTable_To> unchanged and return E_OS_STATE. ( ) */

        RetVal = E_OS_STATE;

    }else if(ScheduleTable_Array[ScheduleTableID_To].OsScheduleTblSyncStrategy != ScheduleTable_Array[ScheduleTableID_From].OsScheduleTblSyncStrategy){


    }else{

        if(ScheduleTableInternal_Array[ScheduleTableID_From].NextScheduleTable != EMPTY_NEXT_TABLE){

            /* change the state of the previous next table */
            ScheduleTableInternal_Array[ScheduleTableInternal_Array[ScheduleTableID_From].NextScheduleTable].CurrentState = SCHEDULETABLE_STOPPED;

            /* set the next schedule table  */
            ScheduleTableInternal_Array[ScheduleTableID_From].NextScheduleTable = ScheduleTableID_To;

            /* change the state of ScheduleTableID_To*/
            ScheduleTableInternal_Array[ScheduleTableID_To].CurrentState = SCHEDULETABLE_NEXT;

        }

    }


#elif OS_MODE == OS_EXTENDED

    if(ScheduleTableID_From >= TABLES_NUMBER || ScheduleTableID_To >= TABLES_NUMBER ){

            /* [SWS_Os_00282] If the input parameter <ScheduleTableID_From> or <ScheduleTableID_To> in a call of NextScheduleTable() is not valid,
               NextScheduleTable() shall return E_OS_ID.  ( ) */

            RetVal = E_OS_ID;

    }else if(ScheduleTable_Array[ScheduleTableID_From].OsScheduleTableCounterRef != ScheduleTable_Array[ScheduleTableID_To].OsScheduleTableCounterRef){

        /* [SWS_Os_00330] If in a call of NextScheduleTable() schedule table <ScheduleTableID_To> is driven by different counter
           than schedule table <ScheduleTableID_From> then NextScheduleTable() shall return an error E_OS_ID. ( ) */

        RetVal = E_OS_ID;
    }else if(ScheduleTableInternal_Array[ScheduleTableID_From].CurrentState != SCHEDULETABLE_RUNNING){

        /* [SWS_Os_00330] If in a call of NextScheduleTable() schedule table <ScheduleTableID_To> is driven by different counter
           than schedule table <ScheduleTableID_From> then NextScheduleTable() shall return an error E_OS_ID.  ( )*/

        RetVal = E_OS_NOFUNC;

    }else if(ScheduleTableInternal_Array[ScheduleTableID_To].CurrentState != SCHEDULETABLE_STOPPED){

        /* [SWS_Os_00309] If the schedule table <ScheduleTableID_To> in a call of NextScheduleTable() is not in state SCHEDULETABLE_STOPPED,
           NextScheduleTable() shall leave the state of <ScheduleTable_From> and <ScheduleTable_To> unchanged and return E_OS_STATE. ( ) */

        RetVal = E_OS_STATE;

    }else if(ScheduleTable_Array[ScheduleTableID_To].OsScheduleTblSyncStrategy != ScheduleTable_Array[ScheduleTableID_From].OsScheduleTblSyncStrategy){

        /* [SWS_Os_00484] If OsScheduleTblSyncStrategy of <ScheduleTableID_To> in a call of NextScheduleTable() is not equal
           to the OsScheduleTblSyncStrategy of <ScheduleTableID_From> then NextScheduleTable() shall return E_OS_ID. ( ) */

        RetVal = E_OS_ID;

    }else{

        if(ScheduleTableInternal_Array[ScheduleTableID_From].NextScheduleTable != EMPTY_NEXT_TABLE){

            /* change the state of the previous next table */
            ScheduleTableInternal_Array[ScheduleTableInternal_Array[ScheduleTableID_From].NextScheduleTable].CurrentState = SCHEDULETABLE_STOPPED;

            /* set the next schedule table  */
            ScheduleTableInternal_Array[ScheduleTableID_From].NextScheduleTable = ScheduleTableID_To;

            /* change the state of ScheduleTableID_To*/
            ScheduleTableInternal_Array[ScheduleTableID_To].CurrentState = SCHEDULETABLE_NEXT;

        }

    }

#endif


    return RetVal;

}

FUNC( StatusType, OS_CODE ) GetScheduleTableStatus( ScheduleTableType ScheduleTableID, ScheduleTableStatusRefType ScheduleStatus ) {

    StatusType RetVal = E_OK;

#if OS_MODE == OS_STANDARD

    * ScheduleStatus = ScheduleTableInternal_Array[ScheduleTableID].CurrentState;

#elif OS_MODE == OS_EXTENDED

    if(ScheduleTableID > TABLES_NUMBER){

        RetVal = E_OS_ID;

    }else{

        * ScheduleStatus = ScheduleTableInternal_Array[ScheduleTableID].CurrentState;

    }

#endif

    return RetVal;

}
