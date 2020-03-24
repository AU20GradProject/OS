/*

    Written by : Bebo
    DATE : 7/2/2019
    AUTOSAR Version : 4.3.1
    DOC Name : AUTOSAR_SWS_OS.pdf
    Target : ARM TIVA_C TM4C123GH6PM

*/

#ifndef OS_HEADERS_OSINTERFACE_HEADERS_OS_TASK_H_
#define OS_HEADERS_OSINTERFACE_HEADERS_OS_TASK_H_

/* This data type identifies a task */

#define INVALID_TASK    0xFFu /* Constant of data type TaskType for a not defined task. */
typedef VAR( uint8, TYPEDEF ) TaskType ;

/* This data type points to a variable of TaskType */
typedef P2VAR( TaskType, TYPEDEF, TYPEDEF ) TaskRefType ;

/* This data type identifies the state of a task enum for following values  */


#define RUNNING     0x44
#define WAITING     0x88
#define READY       0xCC
#define SUSPENDED   0xFF

typedef VAR( uint8, TYPEDEF ) TaskStateType ;

/* This data type points to a variable of the data type TaskStateType */
typedef P2VAR( TaskStateType, TYPEDEF, TYPEDEF ) TaskStateRefType ;




/*****************************************************************************/

/* task <TaskID> is transferred from the suspended state into the ready state
 * Rescheduling after the call to ActivateTask depends on the place it is called from (ISR, non preemptable task, preemptable task)
 * When an extended task is transferred from suspended state into ready state all its events are cleared
 * No error, E_OK
 * Too many task activations of <TaskID>, E_OS_LIMIT
 * Task <TaskID> is invalid, E_OS_ID */

FUNC (StatusType, OS_CODE) ActivateTask ( TaskType TaskID ) ;

/*****************************************************************************/

/* service causes the termination of the calling task. The calling task is transferred from the running state into the suspended state
 * internal resource assigned to the calling task is automatically released
 * Other resources occupied by the task shall have been released before the call to TerminateTask
 * TerminateTask is called successfully, it enforces a rescheduling.
 * Task still occupies resources, E_OS_RESOURCE
 * Call at interrupt level, E_OS_CALLEVEL */

FUNC (StatusType, OS_CODE) TerminateTask ( void ) ;

/*****************************************************************************/


FUNC (StatusType, OS_CODE) ChainTask ( TaskType TaskID ) ;

/*****************************************************************************/


/* service has no influence on tasks with no internal resource assigned (preemptable tasks). */
/* Call at interrupt level, E_OS_CALLEVEL .*/
/* if calling task has an internal resource Schedule enables a processor assignment to other tasks
 * with lower or equal priority than the ceiling priority of the internal resource and
 * higher priority than the priority of the calling task */
/* when call internal resource is released and context switching happen to highest priority task */

FUNC (StatusType, OS_CODE) Schedule ( void ) ;

/*****************************************************************************/


/* GetTaskID returns the information about the TaskID of the task which is currently running */
/* If <TaskID> can’t be evaluated (no task currently running), the service returns INVALID_TASK as TaskType */

FUNC (StatusType, OS_CODE) GetTaskID ( TaskRefType TaskID ) ;

/*****************************************************************************/

/* Returns the state of a task (running, ready, waiting, suspended) at the time of calling GetTaskState */
/* When a call is made from a task in a full preemptive system, the result may already be incorrect at the time of evaluation */
/* Task <TaskID> is invalid, E_OS_ID */

FUNC (StatusType, OS_CODE) GetTaskState ( TaskType TaskID, TaskStateRefType State ) ;

/*****************************************************************************/











#endif /* OS_HEADERS_OSINTERFACE_HEADERS_OS_TASK_H_ */
