/*

    Written by : Bebo
    DATE : 7/2/2019
    AUTOSAR Version : 4.3.1
    DOC Name : AUTOSAR_SWS_OS.pdf
    Target : ARM TIVA_C TM4C123GH6PM

*/


#ifndef OS_HEADERS_OSINTERNAL_HEADERS_OS_EXTERNAL_VARIABLES_H_
#define OS_HEADERS_OSINTERNAL_HEADERS_OS_EXTERNAL_VARIABLES_H_

/**************************************************************************/


extern CONSTP2FUNC( void, OS_CONFIG_DATA, OsTasksNames_Array [TASKS_NUMBER] ) (void) ;


/**************************************************************************/

/* used to hold pc of tasks which will be called inside task frame */
extern P2FUNC( void, OS_VAR_CLEARED, OsTaskCode_Ptr ) (void)  ;


/* used for define OS object in the system */
extern CONST( OsOS, OS_CONFIG_DATA ) OS ;

/* represent configuration data of every app mode Auto start hold informations of Auto start tasks,alarms,schedule tables  */
extern CONST( OsAppMode, OS_CONFIG_DATA ) OsAppModes_Array[ OS_APPMODES_NUMBER ]  ;


/* hold all tasks' IDs that will be activated in Auto start in all APP modes ordered by order of APP modes */
extern CONST( TaskType, OS_CONFIG_DATA ) OsAutoStartTasks_Array [ AUTOSTART_TASKS_NUMBER ]  ;


/* hold all alarms' IDs that will be activated in Auto start in all APP modes ordered by order of APP modes */
extern CONST( AlarmType, OS_CONFIG_DATA ) OsAutoStartAlarms_Array [ AUTOSTART_ALARMS_NUMBER ]  ;

/* hold all alarms' auto start settings that will be activated in Auto start in all APP modes ordered by order of APP modes */
extern CONST( OsAlarmAutostart, OS_CONFIG_DATA ) OsAutoStartAlarms_SettingArray [ AUTOSTART_ALARMS_NUMBER ]  ;


/* hold all ScheduleTables' IDs that will be activated in Auto start in all APP modes ordered by order of APP modes */
extern CONST( ScheduleTableStatusType, OS_CONFIG_DATA ) OsAutoStartTabless_Array [ AUTOSTART_TABLESS_NUMBER ]  ;

/* hold all tables' auto start settings  that will be activated in Auto start in all APP modes ordered by order of APP modes */
extern CONST( OsScheduleTableAutostart, OS_CONFIG_DATA ) OsAutoStartTables_SettingArray [ AUTOSTART_TABLESS_NUMBER ]  ;


/* used to save app mode used inside system and passed to StartOS service */
extern VAR( AppModeType, OS_CONFIG_DATA )  AppMode ;

/* used to insure that nested critical section will be in right way */
extern VAR ( uint16, OS_VAR_CLEARED) CriticalSection_Semaphore ;
/* used to take a copy of ReadyTaskPCB_Index inside dispatcher */
extern VAR ( uint8, OS_VAR_CLEARED ) DispatcherLocal_Variable ;

/**************************************************************************/

/* list of resources accessed by every task */
extern CONST( ResourceType, OS_CONFIG_DATA ) OsTasksResources_Array [ TOTAL_TASKS_RESOURCES_NUMBER ] ;

/* represent configuration data of every task */
extern CONST( OsTask, OS_CONFIG_DATA ) OsTasks_Array [ TASKS_NUMBER ] ;

/* array of PCBs of not suspended tasks*/
extern VAR( OsTask_PCB, OS_VAR_CLEARED ) OsTasksPCB_Array [ TASK_PCBS_NUMBER ] ;

/* used to scheduling and determine next running task, every element carry the index of task PCB in OsTasksPCB_Array
 * OsTasksPriority_Array [ 0 ] is array of tasks' PCB index */
extern VAR( uint8, OS_VAR_INIT ) OsTasksPriority_Array [ TASK_PRIORITIES_NUMBER ] [ TASKS_PER_PRIORITY] ;

/* used to carry index of first element in OsTasksPriority_Array,
 * this element will be chosen for running if its array priority is currently largest priority */
extern VAR( uint8, OS_VAR_CLEARED) OsTasksPriorityIndex_Array  [TASK_PRIORITIES_NUMBER] ;

/* used to carry index of available element to the newly coming task to OsTasksPriority_Array
 * OsTasksPriorityNext_Array  [0] = x, determine index of OsTasksPriority_Array [ 0 ][x] to carry the PCB index to new task of priority 0 */
extern VAR( uint8, OS_VAR_CLEARED) OsTasksPriorityNext_Array  [TASK_PRIORITIES_NUMBER] ;

extern VAR( uint8, OS_VAR_CLEARED ) OsTaskResourceAllocation [TASK_PRIORITIES_NUMBER] ;

/* used to carry PCB index of all tasks
 * OsTasksPCB_Index_Array[ TaskId ] will return index of PCB of this task OsTasksPCB_Array in if not suspended  */
extern VAR( uint8, OS_VAR_INIT) OsTasksPCB_Index_Array  [ TASKS_NUMBER ] ;

/* carry the highest priority of all current ready/running tasks
 * depending on it ReadyTaskPCB_Index will determined    */
extern VAR ( uint8, OS_VAR_INIT ) ReadyHighestPriority ;

/* used to handle internal and standard resources
 * depending on it new tasks arriving ready queue will be determine if preempt running task or not*/
extern VAR ( uint8, OS_VAR_INIT ) PreemptionPriority ;


/* carry PCB index of ready task that will preempt currently running task */
extern VAR ( uint8, OS_VAR_INIT ) ReadyTaskPCB_Index ;

/* carry the PCB index of currently running task */
extern VAR ( uint8, OS_VAR_INIT ) RunningTaskPCB_Index ;

/* used in context swithcing and preemption to easily modify value of stack frame */
extern volatile CONSTP2VAR ( OsStackFrame, OS_VAR_INIT, OS_APPL_CONST ) OsMSP_StackFrame_ptr ;

extern VAR ( uint8, OS_VAR_CLEARED ) NotSuspendedTasks_Number ;

/**************************************************************************/


/* used to carry ISR_ID of current runnign ISR, set at the beginning of the ISR
    if no ISR is active, INVALID_ISR is the default value. */
extern VAR( ISRType, OS_VAR_CLEARED ) IsrID ;


/* represent configuration data of every task */
extern CONST( OsIsr, OS_CONFIG_DATA ) OsIsr_Array [ ISRS_NUMBER ] ;

/* used to hold resource id of last resource occupied by isr */
extern VAR ( ResourceType, OS_CONFIG_DATA ) OsIsr_LastResource [ ISRS_NUMBER ] ;


/**************************************************************************/

/* used to define events configurations */
extern CONST( EventMaskType, OS_CONFIG_DATA ) OsEvents_Array [ EVENTS_NUMBER ] ;

/**************************************************************************/

/* define configurations of resources in system */
extern CONST( OsResource, OS_CONFIG_DATA ) OsResource_Array [ RESOURCES_NUMBER ] ;

/* define array contain all resources PCBs with index of thier id */
extern VAR( OsResource_PCB, OS_VAR_INIT) OsResourcePCB_Array [ RESOURCES_NUMBER ] ;

/* define if the first task in priority queue allocate resource or not if 0 then no, if non 0 then hold the ceiling priority  */
extern VAR( uint8, OS_VAR_CLEARED ) OsTaskResourceAllocation [TASK_PRIORITIES_NUMBER] ;


/**************************************************************************/


/* used to counter Alarms configurations */
extern CONST( OsCounter, OS_CONFIG_DATA ) OsCounter_Array [ COUNTERS_NUMBER ] ;

extern VAR( OsCounterInternal, OS_DATA)   OsCounterInternal_Array [COUNTERS_NUMBER ];

/**************************************************************************/

/* used to define Alarms configurations */
extern CONST( OsAlarm, OS_CONFIG_DATA ) OsAlarm_Array [ ALARMS_NUMBER ];

extern VAR( OsAlarmInternal, OS_CONFIG_DATA ) OsAlarmInternal_Array [ALARMS_NUMBER];

/**************************************************************************/


/* define configuration of schedule tables in system */
extern CONST( OsScheduleTable, OS_CONFIG_DATA ) ScheduleTable_Array [ TABLES_NUMBER ] ;

/* define configuration of expiry points in system */
extern CONST( OsScheduleTableExpiryPoint, OS_CONFIG_DATA ) ScheduleTablePoints_Array [ TABLES_POINTS_NUMBER ] ;

/* define configuration of tasks to be activated by tables in system */
extern CONST( TaskType, OS_CONFIG_DATA ) j [ TABLES_TASKS_NUMBER ] ;

/* define configuration of tasks to be set its events by tables in system */
extern CONST( TaskType, OS_CONFIG_DATA ) ScheduleTableTaskSet_Array [ TABLES_EVENTS_SET_NUMBER ] ;

/* define configuration of events to be set by tables in system */
extern CONST( EventMaskType, OS_CONFIG_DATA ) ScheduleTableEventSet_Array [ TABLES_EVENTS_SET_NUMBER ];

extern VAR( OsScheduleTableInternal, OS_DATA ) ScheduleTableInternal_Array [ TABLES_NUMBER ] ;

extern VAR( ExpiryPointOffset, OS_DATA ) ScheduleTablePointsOffsets_Array[TABLES_POINTS_NUMBER ];

/**************************************************************************/


#endif /* OS_HEADERS_OSINTERNAL_HEADERS_OS_EXTERNAL_VARIABLES_H_ */
