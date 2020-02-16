/*

    Created by : Ahmad Hegazy
    DATE : 16/2/2019
    AUTOSAR Version : 4.3.1
    DOC Name : AUTOSAR_SWS_OS.pdf
                OSEK/VDX.pdf
    Target : ARM TIVA_C TM4C123GH6PM

*/

#ifndef OS_HEADERS_OSINTERFACE_HEADERS_OS_EVENT_H_
#define OS_HEADERS_OSINTERFACE_HEADERS_OS_EVENT_H_

/* Data type of the event mask */
typedef VAR( uint64, TYPEDEF ) EventMaskType ;

/* Reference to an event mask */
typedef P2VAR ( EventMaskType, TYPEDEF, TYPEDEF ) EventMaskRefType ;

/*The service may be called from an interrupt service routine and from the task level, but not from hook routines.
The events of task <TaskID> are set according to the event mask <Mask>. Calling SetEvent causes the task <TaskID> to be transferred to the ready state, if it was waiting for at least one of the events specified in <Mask>.*/
FUNC(StatusType, AUTOMATIC) SetEvent ( TaskType TaskID, EventMaskType Mask);
/*The events of the extended task calling ClearEvent are cleared according to the event mask <Mask>.*/
FUNC(StatusType, AUTOMATIC) ClearEvent ( EventMaskType Mask);
/*This service returns the current state of all event bits of the task <TaskID>, not the events that the task is waiting for.
The service may be called from interrupt service routines, task level and some hook routines (see Figure 12-1).
The current status of the event mask of task <TaskID> is copied to <Event>.*/
FUNC(StatusType, AUTOMATIC) GetEvent ( TaskType TaskID, EventMaskRefType Mask);
/*The state of the calling task is set to waiting, unless at least one of the events specified in <Mask> has already been set.*/
FUNC(StatusType, AUTOMATIC) WaitEvent ( EventMaskType Mask);

#endif /* OS_HEADERS_OSINTERFACE_HEADERS_OS_EVENT_H_ */
