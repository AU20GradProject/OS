/*

    Written by : Bebo
    DATE : 7/2/2019
    AUTOSAR Version : 4.3.1
    DOC Name : AUTOSAR_SWS_OS.pdf
    Target : ARM TIVA_C TM4C123GH6PM

*/

#include "..\..\Os_Headers\OsInterface_Headers\Os.h"
#include "..\..\Os_Headers\OsInternal_Headers\Os_Internal.h"

/* used for initialize all elements of array with value x */
#define VAL_1(x)        x
#define VAL_2(x)        VAL_1(x), VAL_1(x)
#define VAL_4(x)        VAL_2(x), VAL_2(x)
#define VAL_8(x)        VAL_4(x), VAL_4(x)
#define VAL_16(x)       VAL_8(x), VAL_8(x)
#define VAL_32(x)       VAL_16(x), VAL_16(x)
#define VAL_64(x)       VAL_32(x), VAL_32(x)
#define VAL_128(x)      VAL_64(x), VAL_64(x)
#define VAL_256(x)      VAL_128(x), VAL_128(x)



/* list of resources accessed by every task */
CONST( ResourceType, OS_CONFIG_DATA ) OsTasksResources_Array [ TOTAL_TASKS_RESOURCES_NUMBER ] = OS_TASKS_RESOURCES_OBJECT_CONGIFURATION ;

/* represent configuration data of every task */
CONST( OsTask, OS_CONFIG_DATA ) OsTasks_Array [ TASKS_NUMBER ]  = OS_TASKS_OBJECT_CONGIFURATION ;

/* array of PCBs of not suspended tasks*/
VAR( Task_PCB, OS_VAR_CLEARED ) OsTasksPCB_Array [ TASK_PCBS_NUMBER ] ;

/* used to scheduling and determine next running task, every element carry the index of task PCB in OsTasksPCB_Array
 * OsTasksPriority_Array [ 0 ] is array of tasks' PCB index */
VAR( uint8, OS_VAR_INIT ) OsTasksPriority_Array [ TASK_PRIORITIES_NUMBER ] [ TASKS_PER_PRIORITY] = { VAL_256(0xFF), VAL_8(0xFF) } ;

/* used to carry index of first element in OsTasksPriority_Array,
 * this element will be chosen for running if its array priority is currently largest priority */
VAR( uint8, OS_VAR_CLEARED) OsTasksPriorityIndex_Array  [TASK_PRIORITIES_NUMBER] ;

/* used to carry index of available element to the newly coming task to OsTasksPriority_Array
 * OsTasksPriorityNext_Array  [0] = x, determine index of OsTasksPriority_Array [ 0 ][x] to carry the PCB index to new task of priority 0 */
VAR( uint8, OS_VAR_CLEARED) OsTasksPriorityNext_Array  [TASK_PRIORITIES_NUMBER] ;

/* used to carry PCB index of all tasks
 * OsTasksPCB_Index_Array[ TaskId ] will return index of PCB of this task OsTasksPCB_Array in if not suspended  */
VAR( uint8, OS_VAR_INIT) OsTasksPCB_Index_Array  [ TASKS_NUMBER ] = TASKS_PCB_INDEX_ARRAY_CONFIGURATION ;








