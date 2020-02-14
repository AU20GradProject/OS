/*

    Written by : Bebo
    DATE : 7/2/2019
    AUTOSAR Version : 4.3.1
    DOC Name : AUTOSAR_SWS_OS.pdf
    Target : ARM TIVA_C TM4C123GH6PM

*/




#include "..\..\Os_Headers\OsInterface_Headers\Os.h"
#include "..\..\Os_Headers\OsInternal_Headers\Os_Internal.h"


/*******************************************************************/



CONST( OsScheduleTable, OS_CONFIG_DATA ) ScheduleTable_Array [ TABLES_NUMBER ] = OS_TABLESS_OBJECT_CONGIFURATION ;

CONST( OsScheduleTableExpiryPoint, OS_CONFIG_DATA ) ScheduleTablePoints_Array [ TABLES_POINTS_NUMBER ] = OS_TABLESS_POINTS_OBJECT_CONGIFURATION ;

CONST( OsTask, OS_CONFIG_DATA ) ScheduleTableTaskActivation_Array [ TABLES_TASKS_NUMBER ] = OS_TABLESS_TASKS_OBJECT_CONGIFURATION ;

CONST( OsTask, OS_CONFIG_DATA ) ScheduleTableTaskSet_Array [ TABLES_EVENTS_SET_NUMBER ] = OS_TABLESS_TASKS_SET_OBJECT_CONGIFURATION ;

CONST( EventMaskRefType, OS_CONFIG_DATA ) ScheduleTableEventSet_Array [ TABLES_EVENTS_SET_NUMBER ] = OS_TABLESS_EVENTS_SET_OBJECT_CONGIFURATION ;




/*******************************************************************/
