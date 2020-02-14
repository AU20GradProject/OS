/*

    Written by : Bebo
    DATE : 7/2/2019
    AUTOSAR Version : 4.3.1
    DOC Name : AUTOSAR_SWS_OS.pdf
    Target : ARM TIVA_C TM4C123GH6PM

*/

#ifndef OS_HEADERS_OSINTERNAL_HEADERS_OS_TASK_INTERNAL_H_
#define OS_HEADERS_OSINTERNAL_HEADERS_OS_TASK_INTERNAL_H_


typedef struct
{

    /* OsTaskSchedule attribute defines the preemptability of the task.
     * If this attribute is set to NON, no internal resources may be assigned to this task */
    VAR( uint8, AUTOMATIC ) OsTaskSchedule ;

    /* defines the maximum number of queued activation requests for the task
     * 1" means that at any time only a single activation is permitted for this task
     * for basic tasks in BCC2,ECC2 */
    VAR( uint8, AUTOMATIC ) OsTaskActivation ;

    /* priority of a task is defined by the value of this,
     * larger values correspond to higher priorities 0 is lowest */
    VAR( uint8, AUTOMATIC ) OsTaskPriority ;

    /*  ceiling priority if no resources accessed by the task value will be = OsTaskPriority */
    VAR( uint8, AUTOMATIC ) OsTaskCeillingPriority ;

    /* defines number of resources accessed by task */
    VAR( uint8, AUTOMATIC ) OsTaskResourcesNumber ;

    /* Reference to application modes in which that task is activated on startup of the OS , as a mask for modes of this task
     * defined by orring all values of app modes defined to the task to autostart within
     * if = NOT_AUTOSTART then it won't be in autostart */
    VAR( AppModeType, AUTOMATIC ) OsTaskAppModeRef ;

    /* defines index of first resource accessed by task in TaskReources list */
    VAR( uint16, AUTOMATIC ) OsTaskResourceRef ;

    /* defines the list of events the extended task may react on, as a mask for events of this task  */
    VAR( EventMaskType, AUTOMATIC ) OsTaskEventRef ;


} OsTask ;


extern CONSTP2FUNC( void, OS_CONFIG_DATA, OsTasksNames_Array [TASKS_NUMBER] ) (void) ;


#endif /* OS_HEADERS_OSINTERNAL_HEADERS_OS_TASK_INTERNAL_H_ */
