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

/* called from an interrupt service routine and from the task level, but not from hook routines */
/* events of task <TaskID> are set according to the event mask <Mask> */
/* Calling SetEvent causes <TaskID> to be transferred to the ready state,
 * if it was waiting for at least one of the events specified in <Mask */
/* events not set in the event mask remain unchanged */
/* Task <TaskID> is invalid, E_OS_ID */
/*  Referenced task is no extended task, E_OS_ACCESS */
/* Events can not be set as the referenced task is in the suspended state, E_OS_STATE */

StatusType SetEvent ( TaskType TaskID, EventMaskType Mask )
{
    VAR ( StatusType, AUTOMATIC ) ReturnResult = E_OK ;
    VAR ( uint8, AUTOMATIC ) PCB_Index ;


    if (TaskID < TASKS_NUMBER ) /* valid task id */
    {

        if( OS_EVENT_BASIC_TASK != OsTasks_Array[ TaskID ].OsTaskEventRef ) /* task is extended task */
        {
            Mask &= OsTasks_Array[ TaskID ].OsTaskEventRef ;

            /* critical section to protect read modify write sequence, read from PCB_Index write to events flags  */
            CS_ON ;

            PCB_Index = OsTasksPCB_Index_Array[ TaskID ] ;

            if( INVALID_TASK != PCB_Index ) /* task is not suspended */
            {
                OsTasksPCB_Array[ PCB_Index ].Task_EvnetsFlag |= Mask ;

                if ( OS_EVENT_BASIC_TASK != ( ( OsTasksPCB_Array[ PCB_Index ].Task_EvnetsWaiting ) & Mask ) ) /* set event task is waiting for */
                {
                    OsTasksPCB_Array[ PCB_Index ].Task_EvnetsWaiting = OS_EVENT_BASIC_TASK ;

                    CS_OFF ;

                    /* add new task's pcb index to proper priority queue */
                    OsInternalScheduler ( PCB_Index, TRUE ) ;

                }
                else /* set event task isn't waiting for it */
                {
                    CS_OFF ;
                }
            }
            else
            {
                CS_OFF ;
                /* task is suspended */
                ReturnResult = E_OS_STATE ;

            } /* else */

        } /* if */
        else
        {
            /* task is basic task or has no reference to this event */
            ReturnResult = E_OS_ACCESS ;

        } /* else */

    } /* if */
    else
    {
        /* invalid task ID*/
        ReturnResult = E_OS_ID ;
    }

    return ReturnResult ;
}


/*****************************************************************************/

/* The events of the extended task calling ClearEvent are cleared according to the event mask <Mask>. */
/* The system service ClearEvent is restricted to extended tasks which own the event */
/* The system service ClearEvent is restricted to extended tasks which own the event */
/* Call at interrupt level, E_OS_CALLEVEL */

StatusType ClearEvent ( EventMaskType Mask )
{

    StatusType ReturnResult = E_OK ;


    if ( INVALID_ISR== IsrID)   /* check if called form ISR level */
    {
        if ( OS_EVENT_BASIC_TASK != OsTasks_Array [ ( OsTasksPCB_Array[RunningTaskPCB_Index].Task_ID ) ].OsTaskEventRef )
        {
            /* critical section to read modify write of Task_EvnetsFlag */
            CS_ON ;

            OsTasksPCB_Array[RunningTaskPCB_Index].Task_EvnetsFlag &= ~Mask ;

            CS_OFF ;
        }
        else
        {
            /* task is basic task or has no reference to this event */
            ReturnResult = E_OS_ACCESS ;

        } /* else */

    } /* if */
    else
    {
        /* called form interrupt */
        ReturnResult = E_OS_CALLEVEL ;
    }

    return ReturnResult ;
}

/*****************************************************************************/

/* service returns the current state of all event bits of the task <TaskID>, not the events that the task is waiting for */
/* service may be called from interrupt service routines, task level and some hook routines */
/* current status of the event mask of task <TaskID> is copied to <Event>. */
/* Task <TaskID> is invalid, E_OS_ID */
/* Referenced task <TaskID> is not an extended task, E_OS_ACCESS */
/* Referenced task <TaskID> is in the suspended state, E_OS_STATE */

StatusType GetEvent ( TaskType TaskID, EventMaskRefType Event )
{

    StatusType ReturnResult = E_OK ;
    VAR ( uint8, AUTOMATIC ) PCB_Index ;


    if ( TaskID < TASKS_NUMBER ) /* valid task id */
    {

        if( OS_EVENT_BASIC_TASK != OsTasks_Array[ TaskID ].OsTaskEventRef ) /* task is extended task */
        {

            /* critical section to protect read modify write sequence, read from PCB_Index write to  index of OsTasksPCB_Array */
            CS_ON ;

            PCB_Index = OsTasksPCB_Index_Array[ TaskID ] ;

            if( INVALID_TASK != PCB_Index ) /* task is not suspended */
            {
                *Event = OsTasksPCB_Array[ PCB_Index ].Task_EvnetsFlag ;
            }
            else
            {
                /* task is suspended */
                ReturnResult = E_OS_STATE ;

            } /* else */

            CS_OFF ;
        }
        else
        {
            /* task is basic task or has no reference to this event */
            ReturnResult = E_OS_ACCESS ;

        } /* else */

    } /* if */
    else
    {
        /* invalid task ID*/
        ReturnResult = E_OS_ID ;
    }

    return ReturnResult ;
}

/*****************************************************************************/

/* The state of the calling task is set to waiting, unless at least one of the events specified in <Mask> has already been set. */
/* call enforces rescheduling, if the wait condition occurs.
 * If rescheduling takes place, the internal resource of the task is released while the task is in the waiting state. */
/* service shall only be called from the extended task owning the event */
/* Calling task is not an extended task, E_OS_ACCESS */
/* Calling task occupies resources, E_OS_RESOURCE */
/* Call at interrupt level, E_OS_CALLEVEL */

StatusType WaitEvent ( EventMaskType Mask )
{


    StatusType ReturnResult = E_OK ;

    if ( INVALID_ISR== IsrID)   /* check if called form ISR level */
    {

        Mask &= OsTasks_Array [ ( OsTasksPCB_Array[RunningTaskPCB_Index].Task_ID ) ].OsTaskEventRef ;
        if ( OS_EVENT_BASIC_TASK != Mask )
        {
            /* no need to critical section because RunningTaskPCB_Index won't be corrupted by other task */
            if ( 0 == OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_ResourcesOccupied )
            {
                /* critical section to read modify write sequence, read for Task_EvnetsFlag,  write for Task_EvnetsWaiting, Task_State, and Dispatcher */
                CS_ON ;

                /* check if at least on event task is waiting is set or not*/
                if ( OS_EVENT_BASIC_TASK == ( Mask & OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_EvnetsFlag ) )
                {
                    /* no waiting events are set write waiting mask, change task state, call scheduler, and release its internal resource  */
                    OsTaskResourceAllocation[ ( OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_Priority ) ] = FALSE ;
                    OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_EvnetsWaiting =  Mask ;
                    OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_State = WAITING ;
                    OsInternalScheduler ( RunningTaskPCB_Index, FALSE ) ;

                }
                else
                {
                    /* at least on event which task is waiting for is set */
                }
                CS_OFF ;
            }
            else
            {

                /* task still occupy resources */
                ReturnResult = E_OS_RESOURCE ;

            } /* else */

        } /* event */
        else
        {
            /* task is basic task or has no reference to this event */
            ReturnResult = E_OS_ACCESS ;

        } /* else */

    } /* if */
    else
    {
        /* called form interrupt */
        ReturnResult = E_OS_CALLEVEL ;
    }


    return ReturnResult ;
}

/*****************************************************************************/
