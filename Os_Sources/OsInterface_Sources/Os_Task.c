/*

    Written by : Bebo
    DATE : 7/2/2019
    AUTOSAR Version : 4.3.1
    DOC Name : AUTOSAR_SWS_OS.pdf
    Target : ARM TIVA_C TM4C123GH6PM

*/


#include "..\..\Os_Headers\OsInterface_Headers\Os.h"
#include "..\..\Os_Headers\OsInternal_Headers\Os_Internal.h"
#include "..\..\Os_Headers\OsInternal_Headers\Os_ExternalVariables.h"



/*****************************************************************************/


/* task <TaskID> is transferred from the suspended state into the ready state
 * Rescheduling after the call to ActivateTask depends on the place it is called from (ISR, non preemptable task, preemptable task)
 * When an extended task is transferred from suspended state into ready state all its events are cleared
 * No error, E_OK
 * Too many task activations of <TaskID>, E_OS_LIMIT
 * Task <TaskID> is invalid, E_OS_ID */
FUNC (StatusType, OS_CODE) ActivateTask ( TaskType TaskID )
{
    CS_ON ;

    VAR( uint8, AUTOMATIC ) LocalCounter = 0 ;
    VAR( StatusType, AUTOMATIC ) ReturnResult = E_OK;

    if ( TaskID < TASKS_NUMBER ) /* valid task id */
    {


        /* determine empty PCB to place the task */
        /* critical section to ready modify write for Task_ID of PCB & NotSuspendedTasks_Number
         * OsTasksPCB_Index_Array is shared resource and ready modify write sequence will happen  */

        if( INVALID_TASK == OsTasksPCB_Index_Array[TaskID] )    /* task is suspended */
        {


            if (  NotSuspendedTasks_Number < TASK_PCBS_NUMBER )
            {

                NotSuspendedTasks_Number ++ ;

                while (  0 != ( OsTasksPCB_Array[LocalCounter].OsTaskMultipleActivation )  )
                {
                    LocalCounter++ ;
                }

                /* update pcb index of the task */
                OsTasksPCB_Index_Array[TaskID] = LocalCounter ;


                /* initialize task PCB */
                OsTasksPCB_Array[LocalCounter].Task_ID = TaskID ;
                OsTasksPCB_Array[LocalCounter].Task_Priority = OsTasks_Array[TaskID].OsTaskPriority ;
                OsTasksPCB_Array[LocalCounter].OsTaskMultipleActivation = 1 ;
                OsTasksPCB_Array[LocalCounter].Task_ResourcesOccupied = 0 ;
                OsTasksPCB_Array[LocalCounter].Task_LastResourceOccupied = NO_RESOURCE ;
                OsTasksPCB_Array[LocalCounter].Task_State = READY ;
                OsTasksPCB_Array[LocalCounter].Task_SP = ( VAR( uint32, AUTOMATIC ) ) ( &( ( (OsTasksPCB_Array[LocalCounter]).Task_Stack ) [TASK_STACK_SIZE] ) ) ;
                OsTasksPCB_Array[LocalCounter].Task_LR = 0xFFFFFFFD ;
                OsTasksPCB_Array[LocalCounter].Task_PSR = 0x01000000 ;
                OsTasksPCB_Array[LocalCounter].Task_PC = OsTasksNames_Array[TaskID] ;
                OsTasksPCB_Array[LocalCounter].Task_CONTROL = 0x01u ;
                OsTasksPCB_Array[LocalCounter].Task_R9 = 0x00u ;


                /* add new task's pcb index to proper priority queue*/
                OsInternalScheduler ( LocalCounter, TRUE ) ;

            }
            else
            {

                /* system reach to maximum not suspended tasks */
                ReturnResult = E_OS_LIMIT ;

            }/* else */

        }/* if */
        else    /* multiple activation request for task */
        {

            LocalCounter = OsTasksPCB_Index_Array[TaskID] ; /* get task PCB index*/

            /* critical section to read modify write OsTaskMultipleActivation */

            if(  OsTasksPCB_Array[LocalCounter].OsTaskMultipleActivation <  OsTasks_Array[TaskID].OsTaskActivation  )
            {
                OsTasksPCB_Array[LocalCounter].OsTaskMultipleActivation ++ ;
            }
            else
            {
                /* task reach to maximum multiple activation request */
                ReturnResult = E_OS_LIMIT ;
            }/* else */


        }/* else */

    } /* if */
    else
    {
        /* invalid task ID*/
        ReturnResult = E_OS_ID ;
    }

    CS_OFF ;

    return ReturnResult ;

}



/*****************************************************************************/

/* service causes the termination of the calling task. The calling task is transferred from the running state into the suspended state
 * internal resource assigned to the calling task is automatically released
 * Other resources occupied by the task shall have been released before the call to TerminateTask
 * TerminateTask is called successfully, it enforces a rescheduling.
 * Task still occupies resources, E_OS_RESOURCE
 * Call at interrupt level, E_OS_CALLEVEL */

FUNC (StatusType, OS_CODE) TerminateTask ( void )
{

    CS_ON ;

    VAR( StatusType, AUTOMATIC ) ReturnResult = E_OK;
    VAR( uint8, AUTOMATIC ) TaskPriority = OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_Priority ;

    if ( INVALID_ISR== IsrID)   /* check if called form ISR level */
    {
        /* no need to critical section because RunningTaskPCB_Index won't be corrupted by other task */
        if ( 0 == OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_ResourcesOccupied )
        {

            OsTasksPCB_Array[ RunningTaskPCB_Index ].OsTaskMultipleActivation -- ;

            if ( OsTasksPCB_Array[ RunningTaskPCB_Index ].OsTaskMultipleActivation >= 1 ) /* task has multiple activation request */
            {

                /* critical section to modify priority queue */

                /* remove PCB index from ready queue and shift first element in queue
                 * done in critical section just before calling dispatcher, because if preempted
                 * how will it return after pcb index in ready priority queue is removed */
                OsTasksPriority_Array [TaskPriority] [ (OsTasksPriorityIndex_Array[TaskPriority]) ] = INVALID_TASK ;
                OsTasksPriorityIndex_Array[TaskPriority] = ( OsTasksPriorityIndex_Array[TaskPriority] + 1 ) % TASKS_PER_PRIORITY ;

                /* put Task PCB in ready queue*/
                OsTasksPriority_Array[ TaskPriority][ ( OsTasksPriorityNext_Array[TaskPriority] ) ] = RunningTaskPCB_Index ;

                /* allocation for resource ( empty place in ready queue ) */
                OsTasksPriorityNext_Array[TaskPriority] = ( OsTasksPriorityNext_Array[TaskPriority] + 1 ) % TASKS_PER_PRIORITY ;

                /* select next running pcb */
                ReadyTaskPCB_Index = OsTasksPriority_Array [ReadyHighestPriority] [ (OsTasksPriorityIndex_Array[ReadyHighestPriority]) ] ;

                /* initialize task PCB */

                OsTasksPCB_Array[RunningTaskPCB_Index].Task_State = READY ;
                OsTasksPCB_Array[RunningTaskPCB_Index].Task_SP = ( VAR( uint32, AUTOMATIC ) ) ( &( ( (OsTasksPCB_Array[RunningTaskPCB_Index]).Task_Stack ) [TASK_STACK_SIZE] )) ;
                OsTasksPCB_Array[RunningTaskPCB_Index].Task_LR = 0xFFFFFFFD ;
                OsTasksPCB_Array[RunningTaskPCB_Index].Task_PSR = 0x01000000 ;
                OsTasksPCB_Array[RunningTaskPCB_Index].Task_PC = OsTasksNames_Array[ (OsTasksPCB_Array[RunningTaskPCB_Index].Task_ID ) ] ;
                OsTasksPCB_Array[RunningTaskPCB_Index].Task_CONTROL = 0x01u ;
                OsTasksPCB_Array[RunningTaskPCB_Index].Task_R9 = 0x00u ;

                /* release its internal resource */
                OsTaskResourceAllocation[ ( OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_Priority ) ] = FALSE ;

                RunningTaskPCB_Index = INVALID_TASK ;
                DISPATCHER_CALL ;



            }
            else
            {
                OsTasksPCB_Index_Array [ ( OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_ID ) ] = INVALID_TASK ;    /* make task invisible to other tasks */
                OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_State = SUSPENDED ;
                /* remove task's pcb index from priority queue and call dispatcher and release PCB from task */
                OsInternalScheduler ( RunningTaskPCB_Index, FALSE ) ;

            } /* else */

        } /* if */
        else
        {
            /* task still occupy resources */
            ReturnResult = E_OS_RESOURCE ;
        }
    }
    else
    {
        /* called form interrupt */
        ReturnResult = E_OS_CALLEVEL ;
    }

    CS_OFF ;

    return ReturnResult ;
}

/*****************************************************************************/

/* service causes the termination of the calling task */
/* After termination of the calling task a succeeding task <TaskID> is activated */
/* this service, ensures that the succeeding task starts to run at the earliest after the calling task has been terminated. */
/* If the succeeding task is identical with the current task, this does not result in multiple requests,
 * will immediately become ready again. */
/* internal resource assigned to the calling task is automatically released, even if the succeeding task is identical */
/* Ending a task function without call to TerminateTask or ChainTask is strictly forbidden */
/* service ChainTask is called successfully, this enforces a rescheduling and won't return to evaluate status  */
/* E_OS_LIMIT is returned the activation is ignored */
/* Too many task activations of <TaskID>, E_OS_LIMIT */
/* Task <TaskID> is invalid, E_OS_ID */
/* Calling task still occupies resources, E_OS_RESOURCE */
/* Call at interrupt level, E_OS_CALLEVEL */

FUNC (StatusType, OS_CODE) ChainTask ( TaskType TaskID )
{
    VAR( StatusType, AUTOMATIC ) ReturnResult = E_OK;

    /* critical section to avoid calling to dispatcher */
    DISPATCHER_OFF ;

    ReturnResult = TerminateTask() ;
    if ( E_OK == ReturnResult )
    {
        RunningTaskPCB_Index = INVALID_TASK ;
        ReturnResult = ActivateTask(TaskID) ;
    }
    else
    {
    }

    DISPATCHER_ON ;

    return ReturnResult ;
}

/*****************************************************************************/

/* service has no influence on tasks with no internal resource assigned (preemptable tasks). */
/* Call at interrupt level, E_OS_CALLEVEL .*/
/* if calling task has an internal resource Schedule enables a processor assignment to other tasks
 * with lower or equal priority than the ceiling priority of the internal resource and
 * higher priority than the priority of the calling task */
/* when call internal resource is released and context switching happen to highest priority task */
/* Calling task occupies resources, E_OS_RESOURCE */
/* Call at interrupt level, E_OS_CALLEVEL */

FUNC (StatusType, OS_CODE) Schedule ( void )
{
    CS_ON ;


    VAR( StatusType, AUTOMATIC ) ReturnResult = E_OK;

    if ( INVALID_ISR== IsrID)   /* check if called form ISR level */
    {
        /* no need to critical section because RunningTaskPCB_Index won't be corrupted by other task */
        if ( 0 == OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_ResourcesOccupied )
        {

            /* determine next running task's pcb and release internal resource */
            ReadyTaskPCB_Index = OsTasksPriority_Array [ReadyHighestPriority] [ (OsTasksPriorityIndex_Array[ReadyHighestPriority]) ] ;
            OsTaskResourceAllocation[ ( OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_Priority ) ] = FALSE ;
            PreemptionPriority = FALSE ;
            DISPATCHER_CALL ;

        }
        else
        {
            /* task still occupy resources */
            ReturnResult = E_OS_RESOURCE ;
        }

    }
    else
    {
        /* called form interrupt */
        ReturnResult = E_OS_CALLEVEL ;

    }

    CS_OFF ;

    return ReturnResult ;
}

/*****************************************************************************/

/* GetTaskID returns the information about the TaskID of the task which is currently running */
/* If <TaskID> can’t be evaluated (no task currently running), the service returns INVALID_TASK as TaskType */

FUNC (StatusType, OS_CODE) GetTaskID ( TaskRefType TaskID )
{
    if( INVALID_TASK == RunningTaskPCB_Index )
    {
        *TaskID = INVALID_TASK ;
    }
    else
    {
        *TaskID = OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_ID ;
    }
    return E_OK ;
}

/*****************************************************************************/

/* Returns the state of a task (running, ready, waiting, suspended) at the time of calling GetTaskState */
/* When a call is made from a task in a full preemptive system, the result may already be incorrect at the time of evaluation */
/* Task <TaskID> is invalid, E_OS_ID */

FUNC (StatusType, OS_CODE) GetTaskState ( TaskType TaskID, TaskStateRefType State )
{
    VAR( StatusType, AUTOMATIC ) ReturnResult = E_OK;

    if ( TaskID < TASKS_NUMBER ) /* valid task id */
    {
        *State = OsTasksPCB_Array[ OsTasksPCB_Index_Array[TaskID] ].Task_State ;
    }
    else /* invalid task id */
    {
        ReturnResult = E_OS_ID ;
    }

    return ReturnResult ;
}

/*****************************************************************************/





