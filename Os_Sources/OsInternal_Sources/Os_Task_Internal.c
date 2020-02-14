/*

    Written by : Bebo
    DATE : 7/2/2019
    AUTOSAR Version : 4.3.1
    DOC Name : AUTOSAR_SWS_OS.pdf
    Target : ARM TIVA_C TM4C123GH6PM

*/

#include "..\..\Os_Headers\OsInterface_Headers\Os.h"
#include "..\..\Os_Headers\OsInternal_Headers\Os_Internal.h"

/* list of resources accessed by every task */
CONST( ResourceType, OS_CONFIG_DATA ) OsTasksResources_Array [ TOTAL_TASKS_RESOURCES_NUMBER ] = OS_TASKS_RESOURCES_OBJECT_CONGIFURATION ;

/* represent configuration data of every task */
CONST( OsTask, OS_CONFIG_DATA ) OsTasks_Array [ TASKS_NUMBER ]  = OS_TASKS_OBJECT_CONGIFURATION ;


