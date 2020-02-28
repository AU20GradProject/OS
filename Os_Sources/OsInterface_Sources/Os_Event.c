/*

    Created by : Ahmad Hegazy
    DATE : 16/2/2019
    AUTOSAR Version : 4.3.1
    DOC Name : AUTOSAR_SWS_OS.pdf
                OSEK/VDX.pdf
    Target : ARM TIVA_C TM4C123GH6PM

*/



#include "..\..\Os_Headers\OsInterface_Headers\Os.h"
#include "..\..\Os_Headers\OsInternal_Headers\Os_Internal.h"

/*Operation:
• Event X signaling : ev_set |= mask_X;
• Is event X arrived ? : ev_set & mask_X;
• Wait for event X : ev_wait | mask_X;
• Clear event X : ev_set &= ~mask_X;*/

/*The service may be called from an interrupt service routine and from the task level, but not from hook routines.
The events of task <TaskID> are set according to the event mask <Mask>. Calling SetEvent causes the task <TaskID> to be transferred to the ready state, if it was waiting for at least one of the events specified in <Mask>.*/
FUNC(StatusType, AUTOMATIC) SetEvent ( TaskType TaskID, EventMaskType Mask ){
    /*
    Events of task <TaskID> are set according to the <Mask> passed as 2nd argument.
    * StatusType is an error code:
    * E_OK: no error;
    * E_OS_ID: invalid TaskId;
    * E_OS_ACCESS: TaskID is not an extended task (not able to manage events);
    * E_OS_STATE: Events cannot be set because the target task is in the SUSPENDED state.
    * This service is not blocking and may be called from a task or an ISR2
    * */
    return E_OK; /*to the schedular, may do context switching*/
}

/*The events of the extended task calling ClearEvent are cleared according to the event mask <Mask>.*/
FUNC(StatusType, AUTOMATIC) ClearEvent ( EventMaskType Mask ){
    /*
    * The events selected by <Mask> are cleared.
    * May be called by the owning task (only);
    * StatusType is an error code:
    * E_OK: no error;
    * E_OS_ACCESS: The calling task is not an extended one (so it does not manage events);
    * E_OS_CALLEVEL: The caller is not a task.
    * non-blocking service.
    * */
    return E_OK;
}

/*This service returns the current state of all event bits of the task <TaskID>, not the events that the task is waiting for.
The service may be called from interrupt service routines, task level and some hook routines (see Figure 12-1).
The current status of the event mask of task <TaskID> is copied to <Event>.*/
FUNC(StatusType, AUTOMATIC) GetEvent ( TaskType TaskID, EventMaskRefType Event ){
    /*
    The event mask of the task <TaskId> is copied to the variable event (A pointer to an EventMaskType is passed to the service);
    * StatusType is an error code:
    * E_OK: no error;
    * E_OS_ID: invalid TaskID;
    * E_OS_ACCESS: TaskID is nor an extended task;
    * E_OS_STATE: Events may not be copied because the target task is in the SUSPENDED state.
    * Non-blocking service, my be called from a task or an ISR2.*/
    
    return E_OK;
}

/*The state of the calling task is set to waiting, unless at least one of the events specified in <Mask> has already been set.*/
FUNC(StatusType, AUTOMATIC) WaitEvent ( EventMaskType Mask){
    /*
    Put the calling task in the WAITING state until one of the events is set. 
    * May be called by the event owning (extended) task only;
    * StatusType is an error code:
    * E_OK: no error;
    * E_OS_ACCESS: The calling task is not an extended one;
    * E_OS_RESOURCE: The task has not released all the resources;
    * E_OS_CALLEVEL: The caller is not a task
    * Blocking service.
    * */
    return E_OK; /*to the schedular, should do context switching*/
}

