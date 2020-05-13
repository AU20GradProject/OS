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




/* call serves to enter critical sections in the code that are assigned to the resource referenced by <ResID>.
 * A critical section shall always be left using ReleaseResource  */
/*  Nested resource occupation is only allowed
 * if the inner critical sections are completely executed within the surrounding critical section
 * by order LIFO last resource to get is the first to out */
/* Nested occupation of one and the same resource is also forbidden!*/
/* recommended that corresponding calls to GetResource and ReleaseResource appear within the same function */
/* not allowed to use services which are points of rescheduling for non preemptable tasks in resources critical section
 * this points is TerminateTask, WaitTask, ChainTask, Schedule */
/* critical sections are to be left before completion of an interrupt service routine */
/* critical sections should be short */
/* service may be called from an ISR and from task level */
/* Resource <ResID> is invalid, E_OS_ID */
/* get a resource which is already occupied by any task or ISR, or the statically assigned priority of the calling task or
 interrupt routine is higher than the calculated ceiling priority, E_OS_ACCESS*/
FUNC (StatusType, OS_CODE) GetResource ( ResourceType ResID )
{
    CS_ON ;

    VAR( StatusType, AUTOMATIC ) ReturnResult = E_OK;
    VAR( uint8, AUTOMATIC ) CeilingPriority  ;
    VAR( ResourceMaskType, AUTOMATIC ) ResourceMask ;
    if ( INVALID_ISR== IsrID)   /* check if called form ISR level */
    {
        /* called from task */
        ResourceMask = ( OsTasks_Array [(OsTasksPCB_Array [ RunningTaskPCB_Index ].Task_ID)].OsTaskCeilingPriority_Internal ) & (1 << ResID) ;

        if ( ResID < OS_RESOURCES_NUMBER ) /* check for valid resource */
        {
            /* check if task try to get resource which could occupy */
            if ( OS_NO_RESOURCE_MASK != ResourceMask )
            {
                /* resource is free and running task has right to get it
                 * if running task has another resource other than ResID but has same  or higher priority then the behavior won't change
                 * case it try to get ResID instead of its resource  */

                /* first thing to do is allocate resource */

                /* modify resource setting */
                OsResourcePCB_Array[ ResID ].OsResourceOwner = OsTasksPCB_Array [ RunningTaskPCB_Index ].Task_ID ;
                OsResourcePCB_Array[ ResID ].OsPreviousResource = OsTasksPCB_Array [ RunningTaskPCB_Index ].Task_LastResourceOccupied  ;
                OsTasksPCB_Array [ RunningTaskPCB_Index ].Task_LastResourceOccupied = ResID ;

                if ( (OsResource_Array[ResID].OsResourcePriority) > (OsTasksPCB_Array [ RunningTaskPCB_Index ].Task_Priority) )
                {
                    CeilingPriority = OsTasksPCB_Array [ RunningTaskPCB_Index ].Task_Priority  ;
                    OsTasksPCB_Array [ RunningTaskPCB_Index ].Task_Priority = OsResource_Array[ResID].OsResourcePriority ;

                    if ( (OsResource_Array[ResID].OsResourcePriority) >= TASK_PRIORITIES_NUMBER )
                    {
                        Resource_IsrMask( OsResource_Array[ResID].OsResourcePriority ) ;

                    }
                    else
                    {
                        /* remove task from old priority queue */
                        OsTasksPriority_Array [CeilingPriority] [ (OsTasksPriorityIndex_Array[CeilingPriority]) ] = INVALID_TASK ;
                        OsTasksPriorityIndex_Array[CeilingPriority] = ( OsTasksPriorityIndex_Array[CeilingPriority] + 1 ) % TASKS_PER_PRIORITY ;

                        /* put task in new queue */
                        OsHeadTask( RunningTaskPCB_Index );
                    }

                }
                else
                {
                }

            }
            else
            {
                /* ceiling priority of task is higher or lower than ceiling priority of resource,
                 * if resource occupied  by another task if this task access same resource it won't get in running state
                 * if not then its priority is higher than ceiling priority
                 * if not then this resource is not occupied and lower priority task  trying to get it  */
                ReturnResult = E_OS_ACCESS ;
            } /* else */

        } /* if */
        else
        {
            /* invalid resource id */
            ReturnResult = E_OS_ID ;

        } /* else */

    } /* if */
    else
    {
        /* called form isr */

        if ( ResID < OS_RESOURCES_NUMBER ) /* check for valid resource */
        {
            ResourceMask = ( OsIsr_Array [IsrID].OsResourceRef ) & (1 << ResID) ;


            if ( OS_NO_RESOURCE_MASK != ResourceMask )
            {

                /* modify resource setting */
                OsResourcePCB_Array[ ResID ].OsResourceOwner = IsrID ;
                OsResourcePCB_Array[ ResID ].OsPreviousResource = OsIsr_Array [IsrID].Isr_LastResourceOccupied  ;
                OsIsr_Array [IsrID].Isr_LastResourceOccupied = ResID ;


                if ( (OsResource_Array[ResID].OsResourcePriority) > (OsIsr_Array [ IsrID ].Isr_Priority) )
                {
                    Resource_IsrMask( OsResource_Array[ResID].OsResourcePriority );
                }
                else
                {
                }

            }
            else
            {
            }

        } /* if */
        else
        {

            /* invalid resource id */
            ReturnResult = E_OS_ID ;

        } /* else */

    } /* else */


    if ( TRUE == OsResource_CS_Flag )
    {
        OsResource_CS_Flag = FALSE ;
    }
    else
    {
        CS_OFF ;

    }
    return ReturnResult ;
}


/*****************************************************************************/


/*  ReleaseResource is the counterpart of GetResource and serves to
 * leave critical sections in the code that are assigned to the resource referenced by <ResID>. */
/* The service may be called from an ISR and from task level  */
/* Resource <ResID> is invalid, E_OS_ID */
/* Attempt to release a resource which is not occupied by any task or ISR, or another resource shall be released before, E_OS_NOFUNC */
/* Attempt to release a resource which has a lower ceiling priority than
 * the statically assigned priority of the calling task or interrupt routine, E_OS_ACCESS */
FUNC (StatusType, OS_CODE) ReleaseResource ( ResourceType ResID )
{
    CS_ON ;

    VAR( StatusType, AUTOMATIC ) ReturnResult = E_OK;
    VAR( uint8, AUTOMATIC ) CeilingPriority  ;
    VAR( ResourceType, AUTOMATIC ) ResID_Temp  ;
    VAR( ResourceMaskType, AUTOMATIC ) ResourceMask = ( OsTasks_Array [(OsTasksPCB_Array [ RunningTaskPCB_Index ].Task_ID)].OsTaskCeilingPriority_Internal ) & (1 << ResID) ;



    if ( INVALID_ISR== IsrID)   /* check if called form ISR level */
    {
        /* called from task */
        CeilingPriority = OsTasks_Array [ ( OsTasksPCB_Array [ RunningTaskPCB_Index ].Task_ID ) ].OsTaskCeilingPriority_Internal ;

        if ( ResID < OS_RESOURCES_NUMBER ) /* check for valid resource */
        {
            if ( OS_NO_RESOURCE_MASK != ResourceMask )
            {
                /* check for releasing sequence of nested resources */
                if ( ResID == OsTasksPCB_Array [ RunningTaskPCB_Index ].Task_LastResourceOccupied)
                {
                    /* free ResID from task's resources list */

                    OsTasksPCB_Array [ RunningTaskPCB_Index ].Task_LastResourceOccupied = OsResourcePCB_Array[ ResID ].OsPreviousResource ;
                    OsResourcePCB_Array[ ResID ].OsPreviousResource = OS_NO_RESOURCE ;
                    OsResourcePCB_Array[ ResID ].OsResourceOwner = INVALID_TASK ;


                    /* check if running task still occupy resources */
                    if( OS_NO_RESOURCE == ( OsTasksPCB_Array [ RunningTaskPCB_Index ].Task_LastResourceOccupied ) )
                    {

                    }
                    else
                    {
                        /* running task still occupy resource */

                        if( (OsTasksPCB_Array [ RunningTaskPCB_Index ].Task_Priority) > (OsResource_Array[ ResID ].OsResourcePriority) )
                        {

                        }
                        else
                        {

                            /* check for task ceiling priority */
                            CeilingPriority = OsTasks_Array [ ( OsTasksPCB_Array [ RunningTaskPCB_Index ].Task_ID ) ].OsTaskCeilingPriority_Internal ;
                            ResID_Temp = OsTasksPCB_Array [ RunningTaskPCB_Index ].Task_LastResourceOccupied ;

                            if( (OsResource_Array[ResID_Temp].OsResourcePriority) > CeilingPriority )
                            {
                                OsTasksPCB_Array [ RunningTaskPCB_Index ].Task_Priority = OsResource_Array[ResID_Temp].OsResourcePriority ;
                            }
                            else
                            {
                                OsTasksPCB_Array [ RunningTaskPCB_Index ].Task_Priority = CeilingPriority ;
                            }

                            OsHeadTask( RunningTaskPCB_Index ) ;
                            RemoveTask( OsResource_Array[ResID].OsResourcePriority ) ;

                        }

                    } /* else */

                    Resource_IsrMask( OsTasksPCB_Array [ RunningTaskPCB_Index ].Task_Priority );

                }
                else
                {
                    /* another resource must released first or task don't occupy this resource */
                    ReturnResult = E_OS_NOFUNC ;

                } /* else */

            } /* if */
            else
            {
                /* ceiling priority of task is higher or lower than ceiling priority of resource,
                 * if resource occupied  by another task if this task access same resource it won't get in running state
                 * if not then its priority is higher than ceiling priority
                 * if not then this resource is not occupied and lower priority task  trying to get it  */
                ReturnResult = E_OS_ACCESS ;
            } /* else */

        } /* if */
        else
        {
            /* invalid resource id */
            ReturnResult = E_OS_ID ;

        }  /* else */

    } /* if*/
    else
    {
        /* called from isr */

        CeilingPriority = OsIsr_Array [ IsrID ].OsResourceRef ;

        if ( ResID < OS_RESOURCES_NUMBER ) /* check for valid resource */
        {
            if ( OS_NO_RESOURCE_MASK != ResourceMask )
            {

                /* check for releasing sequence of nested resources */
                if ( ResID == OsIsr_Array [ IsrID ].Isr_LastResourceOccupied)
                {
                    /* free ResID from task's resources list */
                    OsIsr_Array [ IsrID ].Isr_LastResourceOccupied = OsResourcePCB_Array[ ResID ].OsPreviousResource ;
                    OsResourcePCB_Array[ ResID ].OsPreviousResource = OS_NO_RESOURCE ;
                    OsResourcePCB_Array[ ResID ].OsResourceOwner = INVALID_TASK ;

                    /* check if running task still occupy resources */
                    if( OS_NO_RESOURCE == ( OsTasksPCB_Array [ RunningTaskPCB_Index ].Task_LastResourceOccupied ) )
                    {

                    }
                    else
                    {
                        /* running task still occupy resource */

                        if( (OsIsr_Array [ IsrID ].Isr_Priority) > (OsResource_Array[ ResID ].OsResourcePriority) )
                        {

                        }
                        else
                        {

                            ResID_Temp = OsIsr_Array [ IsrID ].Isr_LastResourceOccupied ;
                            Resource_IsrMask( OsResource_Array[ResID_Temp].OsResourcePriority );

                        }

                    } /* else */

                }
                else
                {
                    /* another resource must released first or task don't occupy this resource */
                    ReturnResult = E_OS_NOFUNC ;

                } /* else */

            }
            else
            {
                /* ceiling priority of task is higher or lower than ceiling priority of resource,
                 * if resource occupied  by another task if this task access same resource it won't get in running state
                 * if not then its priority is higher than ceiling priority
                 * if not then this resource is not occupied and lower priority task  trying to get it  */
                ReturnResult = E_OS_ACCESS ;
            }
        }
        else
        {
            /* invalid resource id */
            ReturnResult = E_OS_ID ;
        }
    }

    if ( TRUE == OsResource_CS_Flag )
    {
        OsResource_CS_Flag = FALSE ;
    }
    else
    {
        CS_OFF ;

    }

    return ReturnResult ;


}



/*****************************************************************************/
