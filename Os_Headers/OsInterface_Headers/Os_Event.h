/*

    Written by : Bebo
    DATE : 7/2/2019
    AUTOSAR Version : 4.3.1
    DOC Name : AUTOSAR_SWS_OS.pdf
    Target : ARM TIVA_C TM4C123GH6PM

*/

#ifndef OS_HEADERS_OSINTERFACE_HEADERS_OS_EVENT_H_
#define OS_HEADERS_OSINTERFACE_HEADERS_OS_EVENT_H_

/* Data type of the event mask */
typedef VAR( uint64, TYPEDEF ) EventMaskType ;

/* Reference to an event mask */
typedef P2VAR ( EventMaskType, TYPEDEF, TYPEDEF ) EventMaskRefType ;


/*****************************************************************************/

/* called from an interrupt service routine and from the task level, but not from hook routines */
/* events of task <TaskID> are set according to the event mask <Mask> */
/* Calling SetEvent causes <TaskID> to be transferred to the ready state,
 * if it was waiting for at least one of the events specified in <Mask */
/* events not set in the event mask remain unchanged */
/* Task <TaskID> is invalid, E_OS_ID */
/*  Referenced task is no extended task, E_OS_ACCESS */
/* Events can not be set as the referenced task is in the suspended state, E_OS_STATE */

StatusType SetEvent ( TaskType TaskID, EventMaskType Mask ) ;

/*****************************************************************************/

/* The events of the extended task calling ClearEvent are cleared according to the event mask <Mask>. */
/* The system service ClearEvent is restricted to extended tasks which own the event */
/* The system service ClearEvent is restricted to extended tasks which own the event */
/* Call at interrupt level, E_OS_CALLEVEL */

StatusType ClearEvent ( EventMaskType Mask ) ;

/*****************************************************************************/

/* service returns the current state of all event bits of the task <TaskID>, not the events that the task is waiting for */
/* service may be called from interrupt service routines, task level and some hook routines */
/* current status of the event mask of task <TaskID> is copied to <Event>. */
/* Task <TaskID> is invalid, E_OS_ID */
/* Referenced task <TaskID> is not an extended task, E_OS_ACCESS */
/* Referenced task <TaskID> is in the suspended state, E_OS_STATE */

StatusType GetEvent ( TaskType TaskID, EventMaskRefType Event ) ;

/*****************************************************************************/

/* The state of the calling task is set to waiting, unless at least one of the events specified in <Mask> has already been set. */
/* call enforces rescheduling, if the wait condition occurs.
 * If rescheduling takes place, the internal resource of the task is released while the task is in the waiting state. */
/* service shall only be called from the extended task owning the event */
/* Calling task is not an extended task, E_OS_ACCESS */
/* Calling task occupies resources, E_OS_RESOURCE */
/* Call at interrupt level, E_OS_CALLEVEL */

StatusType WaitEvent ( EventMaskType Mask ) ;

/*****************************************************************************/



#endif /* OS_HEADERS_OSINTERFACE_HEADERS_OS_EVENT_H_ */
