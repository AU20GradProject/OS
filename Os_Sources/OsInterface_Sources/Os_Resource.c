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
StatusType GetResource ( ResourceType ResID )
{
    CS_ON ;

    VAR( StatusType, AUTOMATIC ) ReturnResult = E_OK;
    VAR( uint8, AUTOMATIC ) CeilingPriority  ;

    if ( INVALID_ISR== IsrID)   /* check if called form ISR level */
    {
        /* called from task */
        CeilingPriority = OsTasks_Array [ ( OsTasksPCB_Array [ RunningTaskPCB_Index ].Task_ID ) ].OsTaskCeillingPriority ;


        if ( ResID < RESOURCES_NUMBER ) /* check for valid resource */
        {
            if ( OsResource_Array[ ResID ].OsResourcePriority <= CeilingPriority )
            {
                /* resource is free and running task has right to get it
                 * if running task has another resource other than ResID but has same  or higher priority then the behavior won't change
                 * case it try to get ResID instead of its resource  */

                /* first thing to do is allocate resource */


                /* save old preemption priority */
                OsResourcePCB_Array[ ResID ].OsPreviousPreemptionPriority =  PreemptionPriority ;

                /* check if task has a higher internal ceiling priority or previous resource in case of nesting has higher priority  */
                if ( ( OsResource_Array[ ResID ].OsResourcePriority ) > PreemptionPriority )
                {
                    PreemptionPriority = OsResource_Array[ ResID ].OsResourcePriority ;

                    /* case there's interrupt allocate resource must mask all lower priority interrupt than ceiling priority */
                    switch ( PreemptionPriority )
                    {
                        case 0x08u :
                        {

                            __asm ( " MOV R10, #0x0E0u " ) ;
                            __asm ( " MSR BASEPRI_MAX, R10 " ) ;

                            break ;
                        }
                        case 0x09u :
                        {
                            __asm ( " MOV R10, #0x0C0u " ) ;
                            __asm ( " MSR BASEPRI_MAX, R10 " ) ;

                            break ;
                        }

                        case 0x0Au :
                        {
                            __asm ( " MOV R10, #0x0A0u " ) ;
                            __asm ( " MSR BASEPRI_MAX, R10 " ) ;

                            break ;
                        }
                        case 0x0Bu :
                        {
                            __asm ( " MOV R10, #0x080u " ) ;
                            __asm ( " MSR BASEPRI_MAX, R10 " ) ;

                            break ;
                        }
                        case 0x0Cu :
                        {
                            __asm ( " MOV R10, #0x060u " ) ;
                            __asm ( " MSR BASEPRI_MAX, R10 " ) ;

                            break ;
                        }
                        case 0x0Du :
                        {
                            __asm ( " MOV R10, #0x040u " ) ;
                            __asm ( " MSR BASEPRI_MAX, R10 " ) ;

                            break ;
                        }
                        case 0x0Eu :
                        {
                            __asm ( " MOV R10, #0x020u " ) ;
                            __asm ( " MSR BASEPRI_MAX, R10 " ) ;

                            break ;
                        }
                        case 0x0Fu :
                        {


                            break ;

                        } /* case */

                    } /* switch */

                } /* if */
                else
                {

                }

                OsTaskResourceAllocation[ ( OsTasksPCB_Array [ RunningTaskPCB_Index ].Task_Priority ) ] = PreemptionPriority ;


                /* modify resource setting */
                OsResourcePCB_Array[ ResID ].OsResourceOwner = OsTasksPCB_Array [ RunningTaskPCB_Index ].Task_Priority ;
                OsResourcePCB_Array[ ResID ].OsPreviousResource = OsTasksPCB_Array [ RunningTaskPCB_Index ].Task_LastResourceOccupied  ;
                OsTasksPCB_Array [ RunningTaskPCB_Index ].Task_LastResourceOccupied = ResID ;

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
        /* discard for now */
        if ( ResID < RESOURCES_NUMBER ) /* check for valid resource */
        {

            /* called from isr */
            CeilingPriority = OsIsr_Array [ IsrID ].OsIsrCeillingPriority ;

            if ( OsResource_Array[ ResID ].OsResourcePriority <= CeilingPriority )
            {

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

    CS_OFF ;

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
StatusType ReleaseResource ( ResourceType ResID )
{
    CS_ON ;

    VAR( StatusType, AUTOMATIC ) ReturnResult = E_OK;
    VAR( uint8, AUTOMATIC ) CeilingPriority  ;

    if ( INVALID_ISR== IsrID)   /* check if called form ISR level */
    {
        /* called from task */
        CeilingPriority = OsTasks_Array [ ( OsTasksPCB_Array [ RunningTaskPCB_Index ].Task_ID ) ].OsTaskCeillingPriority ;

        if ( ResID < RESOURCES_NUMBER ) /* check for valid resource */
        {
            if ( OsResource_Array[ ResID ].OsResourcePriority <= CeilingPriority )
            {
                /* check for releasing sequence of nested resources */
                if ( ResID == OsTasksPCB_Array [ RunningTaskPCB_Index ].Task_LastResourceOccupied)
                {
                    /* free ResID from task's resources list */
                    OsTasksPCB_Array [ RunningTaskPCB_Index ].Task_LastResourceOccupied = OsResourcePCB_Array[ ResID ].OsPreviousResource ;
                    OsResourcePCB_Array[ ResID ].OsPreviousResource = NO_RESOURCE ;
                    OsResourcePCB_Array[ ResID ].OsResourceOwner = INVALID_TASK ;


                    /* critical section to modify preemption priority */



                    /* check if preemption priority of task was masking all interrupts */
                    if ( PreemptionPriority == 0x0F )
                    {
                        /* related to CS_ON in GetResource : case 0x0F */
                    }
                    else
                    {
                    }

                    PreemptionPriority = OsResourcePCB_Array[ ResID ].OsPreviousPreemptionPriority ;

                    /* check if running task still occupy resources */
                    if( NO_RESOURCE == ( OsTasksPCB_Array [ RunningTaskPCB_Index ].Task_LastResourceOccupied ) )
                    {

                    }
                    else
                    {
                        /* running task still occupy resource */

                        /* case there's interrupt allocate resource must mask all lower priority interrupt than ceiling priority */
                        switch ( PreemptionPriority )
                        {

                            case 0x08u :
                            {

                                __asm ( " MOV R10, #0x0E0u " ) ;
                                __asm ( " MSR BASEPRI_MAX, R10 " ) ;

                                break ;
                            }
                            case 0x09u :
                            {
                                __asm ( " MOV R10, #0x0C0u " ) ;
                                __asm ( " MSR BASEPRI_MAX, R10 " ) ;

                                break ;
                            }

                            case 0x0Au :
                            {
                                __asm ( " MOV R10, #0x0A0u " ) ;
                                __asm ( " MSR BASEPRI_MAX, R10 " ) ;

                                break ;
                            }
                            case 0x0Bu :
                            {
                                __asm ( " MOV R10, #0x080u " ) ;
                                __asm ( " MSR BASEPRI_MAX, R10 " ) ;

                                break ;
                            }
                            case 0x0Cu :
                            {
                                __asm ( " MOV R10, #0x060u " ) ;
                                __asm ( " MSR BASEPRI_MAX, R10 " ) ;

                                break ;
                            }
                            case 0x0Du :
                            {
                                __asm ( " MOV R10, #0x040u " ) ;
                                __asm ( " MSR BASEPRI_MAX, R10 " ) ;

                                break ;
                            }
                            case 0x0Eu :
                            {
                                __asm ( " MOV R10, #0x020u " ) ;
                                __asm ( " MSR BASEPRI_MAX, R10 " ) ;

                                break ;
                            }
                            case 0x0Fu :
                            {

                                break ;

                            }
                            default :
                            {
                                __asm ( " MOV R10, #0x01Fu " ) ;
                                __asm ( " MSR BASEPRI_MAX, R10 " ) ;

                            } /* case */

                        } /* switch */

                    } /* else */

                    OsTaskResourceAllocation[ ( OsTasksPCB_Array [ RunningTaskPCB_Index ].Task_Priority ) ] = PreemptionPriority ;
                    ReadyTaskPCB_Index = OsTasksPriority_Array [ReadyHighestPriority] [ (OsTasksPriorityIndex_Array[ReadyHighestPriority]) ] ;

                    /* check for tasks could preempt running task after release resource */
                    if ( ReadyHighestPriority > PreemptionPriority )
                    {
                        DISPATCHER_CALL ;
                    }
                    else
                    {

                    }



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
        /* discard for now */

        CeilingPriority = OsIsr_Array [ IsrID ].OsIsrCeillingPriority ;

        if ( ResID < RESOURCES_NUMBER ) /* check for valid resource */
        {
            if ( OsResource_Array[ ResID ].OsResourcePriority <= CeilingPriority )
            {

                /* check for releasing sequence of nested resources */
                if ( ResID == OsIsr_LastResource [ IsrID ] )
                {

                    /* free ResID from task's resources list */
                    OsIsr_LastResource [ IsrID ] = OsResourcePCB_Array[ ResID ].OsPreviousResource ;
                    OsResourcePCB_Array[ ResID ].OsPreviousResource = NO_RESOURCE ;
                    OsResourcePCB_Array[ ResID ].OsResourceOwner = INVALID_TASK ;

                    /* check if running task still occupy resources */
                    if( NO_RESOURCE == ( OsTasksPCB_Array [ RunningTaskPCB_Index ].Task_LastResourceOccupied ) )
                    {

                    }
                    else
                    {
                        /* running isr still occupy resource */


                        /* check if preemption priority of isr was masking all interrupts */
                        if ( OsResource_Array[ ResID ].OsResourcePriority == 0x0F )
                        {
                            /* related to CS_ON in GetResource : case 0x0F */
                        }
                        else
                        {

                        }

                        /* case there's interrupt allocate resource must mask all lower priority interrupt than ceiling priority */
                        switch ( OsResourcePCB_Array[ ResID ].OsPreviousPreemptionPriority )
                        {

                            case 0x08u :
                            {

                                __asm ( " MOV R10, #0x0E0u " ) ;
                                __asm ( " MSR BASEPRI_MAX, R10 " ) ;

                                break ;
                            }
                            case 0x09u :
                            {
                                __asm ( " MOV R10, #0x0C0u " ) ;
                                __asm ( " MSR BASEPRI_MAX, R10 " ) ;

                                break ;
                            }

                            case 0x0Au :
                            {
                                __asm ( " MOV R10, #0x0A0u " ) ;
                                __asm ( " MSR BASEPRI_MAX, R10 " ) ;

                                break ;
                            }
                            case 0x0Bu :
                            {
                                __asm ( " MOV R10, #0x080u " ) ;
                                __asm ( " MSR BASEPRI_MAX, R10 " ) ;

                                break ;
                            }
                            case 0x0Cu :
                            {
                                __asm ( " MOV R10, #0x060u " ) ;
                                __asm ( " MSR BASEPRI_MAX, R10 " ) ;

                                break ;
                            }
                            case 0x0Du :
                            {
                                __asm ( " MOV R10, #0x040u " ) ;
                                __asm ( " MSR BASEPRI_MAX, R10 " ) ;

                                break ;
                            }
                            case 0x0Eu :
                            {
                                __asm ( " MOV R10, #0x020u " ) ;
                                __asm ( " MSR BASEPRI_MAX, R10 " ) ;

                                break ;
                            }
                            case 0x0Fu :
                            {

                                CS_ON ;

                                break ;

                            }
                            default :
                            {
                                __asm ( " MOV R10, #0x01Fu " ) ;
                                __asm ( " MSR BASEPRI_MAX, R10 " ) ;

                            } /* case */

                        } /* switch */

                    } /* else */
                }
                else
                {
                    /* another resource must released first or task don't occupy this resource */
                    ReturnResult = E_OS_NOFUNC ;
                }

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

    CS_OFF ;

    return ReturnResult ;


}



/*****************************************************************************/
