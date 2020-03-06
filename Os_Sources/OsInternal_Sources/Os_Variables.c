/*

    Written by : Bebo
    DATE : 7/2/2019
    AUTOSAR Version : 4.3.1
    DOC Name : AUTOSAR_SWS_OS.pdf
    Target : ARM TIVA_C TM4C123GH6PM

*/




#include "..\..\Os_Headers\OsInterface_Headers\Os.h"
#include "..\..\Os_Headers\OsInternal_Headers\Os_Internal.h"

/**************************************************************************/
/* used to hold pc of tasks which will be called inside task frame */
P2FUNC( void, OS_VAR_CLEARED, OsTaskCode_Ptr ) (void)  ;

/* used for define OS object in the system */
CONST( OsOS, OS_CONFIG_DATA ) OS = OS_OS_OBJECT_CONGIFURATION ;

/* represent configuration data of every app mode Auto start hold informations of Auto start tasks,alarms,schedule tables  */
CONST( OsAppMode, OS_CONFIG_DATA ) OsAppModes_Array[ OS_APPMODES_NUMBER ] = OS_APPMODES_OBJECT_CONGIFURATION ;


/* hold all tasks' IDs that will be activated in Auto start in all APP modes ordered by order of APP modes */
CONST( TaskType, OS_CONFIG_DATA ) OsAutoStartTasks_Array [ AUTOSTART_TASKS_NUMBER ]  = OS_AUTOSTART_TASKS_OBJECT_CONGIFURATION ;


/* hold all alarms' IDs that will be activated in Auto start in all APP modes ordered by order of APP modes */
CONST( AlarmType, OS_CONFIG_DATA ) OsAutoStartAlarms_Array [ AUTOSTART_ALARMS_NUMBER ]  = OS_AUTOSTART_ALARMS_OBJECT_CONGIFURATION ;

/* hold all alarms' auto start settings that will be activated in Auto start in all APP modes ordered by order of APP modes */
CONST( OsAlarmAutostart, OS_CONFIG_DATA ) OsAutoStartAlarms_SettingArray [ AUTOSTART_ALARMS_NUMBER ]  = OS_AUTOSTART_SETTING_ALARMS_OBJECT_CONGIFURATION ;


/* hold all ScheduleTables' IDs that will be activated in Auto start in all APP modes ordered by order of APP modes */
CONST( ScheduleTableStatusType, OS_CONFIG_DATA ) OsAutoStartTabless_Array [ AUTOSTART_TABLESS_NUMBER ]  = OS_AUTOSTART_TABLES_OBJECT_CONGIFURATION ;

/* hold all tables' auto start settings  that will be activated in Auto start in all APP modes ordered by order of APP modes */
CONST( OsScheduleTableAutostart, OS_CONFIG_DATA ) OsAutoStartTables_SettingArray [ AUTOSTART_TABLESS_NUMBER ]  = OS_AUTOSTART_SETTING_TABLES_OBJECT_CONGIFURATION ;


/* used to save app mode used inside system and passed to StartOS service */
VAR( AppModeType, OS_CONFIG_DATA )  AppMode ;


/* used to insure that nested critical section will be in right way */
VAR ( uint16, OS_VAR_CLEARED) CriticalSection_Semaphore ;

/* used to take a copy of ReadyTaskPCB_Index inside dispatcher */
VAR ( uint8, OS_VAR_CLEARED ) DispatcherLocal_Variable ;





/**************************************************************************/

/* represent configuration data of every task */
CONST( OsTask, OS_CONFIG_DATA ) OsTasks_Array [ TASKS_NUMBER ]  = OS_TASKS_OBJECT_CONGIFURATION ;

/* array of PCBs of not suspended tasks*/
VAR( OsTask_PCB, OS_VAR_CLEARED ) OsTasksPCB_Array [ TASK_PCBS_NUMBER ] ;

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

/* carry the highest priority of all current ready/running tasks
 * depending on it ReadyTaskPCB_Index will determined    */
VAR ( uint8, OS_VAR_INIT ) ReadyHighestPriority = INVALID_TASK ;

/* used to handle internal and standard resources
 * depending on it new tasks arriving ready queue will be determine if preempt running task or not*/
VAR ( uint8, OS_VAR_INIT ) PreemptionPriority = INVALID_TASK ;


/* carry PCB index of ready task that will preempt currently running task */
VAR ( uint8, OS_VAR_INIT ) ReadyTaskPCB_Index = INVALID_TASK ;

/* carry the PCB index of currently running task */
VAR ( uint8, OS_VAR_INIT ) RunningTaskPCB_Index = INVALID_TASK ;

/* used in context swithcing and preemption to easily modify value of stack frame */
volatile CONSTP2VAR ( OsStackFrame, OS_VAR_INIT, OS_APPL_CONST ) OsMSP_StackFrame_ptr = OS_MSP_STACK_FRAME_ADDRESS ;

VAR ( uint8, OS_VAR_CLEARED ) NotSuspendedTasks_Number ;

/**************************************************************************/


/* used to carry ISR_ID of current runnign ISR */
VAR( ISRType, OS_VAR_CLEARED ) IsrID = INVALID_ISR ;

/* represent configuration data of every task */
CONST( OsIsr, OS_CONFIG_DATA ) OsIsr_Array [ ISRS_NUMBER ] = OS_ISRS_OBJECT_CONGIFURATION ;

/* used to hold resource id of last resource occupied by isr */
VAR ( ResourceType, OS_CONFIG_DATA ) OsIsr_LastResource [ ISRS_NUMBER ] = OS_ISRS_RESOURCES_OBJECT_CONGIFURATION ;

/**************************************************************************/

/* used to carry HOOK_ID of current runnign Hook routine */
VAR( HOOKType, OS_VAR_CLEARED ) HookID = INVALID_HOOK ;

/**************************************************************************/

/* used to define events configurations */
CONST( EventMaskType, OS_CONFIG_DATA ) OsEvents_Array [ EVENTS_NUMBER ] = OS_EVENTS_OBJECT_CONGIFURATION ;

/**************************************************************************/

/* define configurations of resources in system */
CONST( OsResource, OS_CONFIG_DATA ) OsResource_Array [ RESOURCES_NUMBER ] = OS_RESOURCES_OBJECT_CONGIFURATION ;

/* define array contain all resources PCBs with index of thier id */
VAR( OsResource_PCB, OS_VAR_INIT) OsResourcePCB_Array [ RESOURCES_NUMBER ] = OS_RESOURCES_PCB_OBJECT_CONGIFURATION ;

/* define if the first task in priority queue allocate resource or not */
VAR( uint8, OS_VAR_CLEARED ) OsTaskResourceAllocation [TASK_PRIORITIES_NUMBER] ;


/**************************************************************************/


/* used to counter Alarms configurations */
CONST( OsCounter, OS_CONFIG_DATA ) OsCounter_Array [ COUNTERS_NUMBER ] = OS_COUNTERS_OBJECT_CONGIFURATION ;

VAR( OsCounterInternal, OS_DATA)   OsCounterInternal_Array [COUNTERS_NUMBER ];

/**************************************************************************/

/* used to define Alarms configurations */
CONST( OsAlarm, OS_CONFIG_DATA ) OsAlarm_Array [ ALARMS_NUMBER ] = OS_ALARMS_OBJECT_CONGIFURATION ;

VAR( OsAlarmInternal, OS_CONFIG_DATA ) OsAlarmInternal_Array [ALARMS_NUMBER] ;

/**************************************************************************/





/* define configuration of schedule tables in system */
CONST( OsScheduleTable, OS_CONFIG_DATA ) ScheduleTable_Array [ TABLES_NUMBER ] = OS_TABLESS_OBJECT_CONGIFURATION ;

VAR( OsScheduleTableInternal, OS_DATA ) ScheduleTableInternal_Array [ TABLES_NUMBER ] ;

/* define configuration of expiry points in system */
CONST( OsScheduleTableExpiryPoint, OS_CONFIG_DATA ) ScheduleTablePoints_Array [ TABLES_POINTS_NUMBER ] = OS_TABLESS_POINTS_OBJECT_CONGIFURATION ;

VAR( ExpiryPointOffset, OS_DATA ) ScheduleTablePointsOffsets_Array[TABLES_POINTS_NUMBER ];

/* define configuration of tasks to be activated by tables in system */
CONST( TaskType, OS_CONFIG_DATA ) ScheduleTableTaskActivation_Array [ TABLES_TASKS_NUMBER ] = OS_TABLESS_TASKS_OBJECT_CONGIFURATION ;

/* define configuration of tasks to be set its events by tables in system */
CONST( TaskType, OS_CONFIG_DATA ) ScheduleTableTaskSet_Array [ TABLES_EVENTS_SET_NUMBER ] = OS_TABLESS_TASKS_SET_OBJECT_CONGIFURATION ;

/* define configuration of events to be set by tables in system */
CONST( EventMaskType, OS_CONFIG_DATA ) ScheduleTableEventSet_Array [ TABLES_EVENTS_SET_NUMBER ] = OS_TABLESS_EVENTS_SET_OBJECT_CONGIFURATION ;

/**************************************************************************/

