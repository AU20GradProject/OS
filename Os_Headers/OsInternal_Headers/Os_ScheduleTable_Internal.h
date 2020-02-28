/*

    Written by : Bebo
    DATE : 7/2/2019
    AUTOSAR Version : 4.3.1
    DOC Name : AUTOSAR_SWS_OS.pdf
    Target : ARM TIVA_C TM4C123GH6PM

*/

#ifndef OS_HEADERS_OSINTERNAL_HEADERS_OS_SCHEDULETABLE_INTERNAL_H_
#define OS_HEADERS_OSINTERNAL_HEADERS_OS_SCHEDULETABLE_INTERNAL_H_






typedef struct
{
    /* specifies the type of the autostart for the schedule table */
    VAR( uint8, AUTOMATIC ) OsScheduleTableAutostartType ;

    /* which application modes the schedule table should be started during startup
     * if = NOT_AUTOSTART then it won't be in autostart */
    VAR( AppModeType, AUTOMATIC ) OsScheduleTableAppModeRef ;

    /* Absolute autostart tick value when the schedule table starts.
     * Only used if the OsScheduleTableAutostartType is ABSOLUTE.
     * Relative offset in ticks when the schedule table starts.
     * Only used if the OsScheduleTableAutostartType is RELATIVE*/
    VAR( TickType, AUTOMATIC ) OsScheduleTableStartValue ;

} OsScheduleTableAutostart ;


typedef struct
{

    /* number of events to be set contained in the point */
    VAR( uint16, AUTOMATIC ) EventSetNumber ;

    /* pointer to first event to set in the point */
    P2VAR( uint16, AUTOMATIC, AUTOMATIC ) FirstEventSet ;

    /*index of first first task to set its event in the point */
    VAR( uint16, AUTOMATIC ) FirstEventSetTask_Ptr ;

} OsScheduleTableEventSetting ;

typedef struct
{

    /* number of tasks activation contained in the point */
    VAR( uint16, AUTOMATIC ) TaskActivationNumber ;

    /* index of first first task activation in the point */
    VAR( uint16, AUTOMATIC ) FirstTaskActivation ;


} OsScheduleTableTaskActivation ;


typedef struct
{
    /* maximum negative adjustment that can be made to the expiry point offset (in ticks */
    VAR( TickType, AUTOMATIC )  OsScheduleTableMaxShorten ;

    /* maximum positive adjustment that can be made to the expiry point offset (in ticks */
    VAR( TickType, AUTOMATIC )  OsScheduleTableMaxLengthen ;

} OsScheduleTblAdjustableExpPoint ;


typedef struct
{

    /* offset from zero (in ticks) at which the expiry point is to be processed */
    VAR( TickType, AUTOMATIC )  OsScheduleTblExpPointOffset ;

    /* define tasks will be activated in this point expiration */
    VAR( OsScheduleTableTaskActivation, AUTOMATIC ) PointTasks;

    /* define events will be set in this point expiration */
    VAR( OsScheduleTableEventSetting, AUTOMATIC ) PointEvents ;

    /* if 0 value for its parameter then point not adjustable */
    VAR( OsScheduleTblAdjustableExpPoint, AUTOMATIC ) OsScheduleTblAdjustableExpPoint ;


} OsScheduleTableExpiryPoint ;

typedef struct
{

    /* true: first expiry point on the schedule table shall be processed at
     * final expiry point delay ticks after the final expiry point is processed.
     * false: the schedule table processing stops when the final expiry point is processed */
    VAR( boolean, AUTOMATIC ) OsScheduleTableRepeating ;

    /* Reference to the assigned counter for that alarm */
    VAR( CounterType, AUTOMATIC ) OsScheduleTableCounterRef ;

    /* number of expiry points contained in the table */
    VAR( uint16, AUTOMATIC ) ExpiryPointsNumber ;

    /* index of first expiry point in the table in expiry points list */
    VAR( uint16, AUTOMATIC ) FirstExpiryPoint ;

    /* defines the modulus of the schedule table (in ticks). */
    VAR( TickType, AUTOMATIC ) OsScheduleTableDuration ;

    /*
         IMPLICIT: synchronization, EXPLICIT: no synchronization
     */
    VAR(boolean, AUTOMATIC ) OsScheduleTblSyncStrategy ;

} OsScheduleTable ;

typedef struct{

    /* Last accessed expiry point */
    VAR( uint16, AUTOMATIC ) CurrentExpiryPointIndex;

    /* Schedule table current state */
    VAR( uint8, AUTOMATIC ) CurrentState;

    /* Offset to start from current counter */
    VAR( TickType, AUTOMATIC ) StartCounterVal;

    /* Next schedule ID if there is */
    VAR ( sint16 , AUTOMATIC ) NextScheduleTable;

} OsScheduleTableInternal ;
/***********************************************************************************************************************/


FUNC(void, OS_INTERNAL_CODE) CheckScheduleTablesExpiry( CounterType CounterID ) ;

//FUNC(StatusType, OS_INTERNAL_CODE) CheckCounter
#endif /* OS_HEADERS_OSINTERNAL_HEADERS_OS_SCHEDULETABLE_INTERNAL_H_ */
