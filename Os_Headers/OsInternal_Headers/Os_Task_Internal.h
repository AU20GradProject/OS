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


typedef struct
{
    /* variable to carry number of multiple activation requested for basic tasks */
    VAR( uint8, AUTOMATIC ) OsTaskMultipleActivation ;

    /* priority of the task */
    VAR( uint8, AUTOMATIC ) Task_Priority ;

    /* number of resource number occupied by task */
    VAR( uint8, AUTOMATIC ) Task_ResourcesOccupied ;

    /* id of task own this PCB */
    VAR( TaskType, AUTOMATIC ) Task_ID ;

    /* state of task own this PCB */
    VAR( TaskStateType, AUTOMATIC ) Task_State ;

    /* general purpose register */
    VAR( uint32, AUTOMATIC ) Task_R0 ;
    VAR( uint32, AUTOMATIC ) Task_R1 ;
    VAR( uint32, AUTOMATIC ) Task_R2 ;
    VAR( uint32, AUTOMATIC ) Task_R3 ;
    VAR( uint32, AUTOMATIC ) Task_R4 ;
    VAR( uint32, AUTOMATIC ) Task_R5 ;
    VAR( uint32, AUTOMATIC ) Task_R6 ;
    VAR( uint32, AUTOMATIC ) Task_R7 ;
    VAR( uint32, AUTOMATIC ) Task_R8 ;
    VAR( uint32, AUTOMATIC ) Task_R9 ;
    VAR( uint32, AUTOMATIC ) Task_R10 ;
    VAR( uint32, AUTOMATIC ) Task_R11 ;
    VAR( uint32, AUTOMATIC ) Task_R12 ;

    /* PSP for task */
    VAR( uint32, AUTOMATIC ) Task_SP ;

    /* linker register of task used for return  from function calls */
    VAR( uint32, AUTOMATIC ) Task_LR ;

    /* program counter for task */
    VAR( uint32, AUTOMATIC ) Task_PC ;

    /* status register for task */
    VAR( uint32, AUTOMATIC ) Task_PSR ;

    /* flags determine states of the task set or cleared */
    VAR( EventMaskType, AUTOMATIC ) Task_EvnetsFlag ;

    /* flags determine which events task is waiting */
    VAR( EventMaskType, AUTOMATIC ) Task_EvnetsWaiting ;

    VAR( uint32, AUTOMATIC ) Task_Stack [TASK_STACK_SIZE] ;

} Task_PCB ;


extern CONSTP2FUNC( void, OS_CONFIG_DATA, OsTasksNames_Array [TASKS_NUMBER] ) (void) ;


#endif /* OS_HEADERS_OSINTERNAL_HEADERS_OS_TASK_INTERNAL_H_ */
