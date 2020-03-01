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

/* choose next task to run and make context switching */
void OsDispatcher (void)
{


    if ( INVALID_TASK != RunningTaskPCB_Index )/* case there's preemption to running task */
    {


        /* push value of preempted task's special registers which not pushed automatically into main stack while preemption */
        __asm ( " MRS R12, PSP " ) ;
        __asm ( " PUSH {R12} " ) ;
        __asm ( " PUSH {R4} " ) ;
        __asm ( " PUSH {R5} " ) ;
        __asm ( " PUSH {R6} " ) ;
        __asm ( " PUSH {R7} " ) ;
        __asm ( " PUSH {R8} " ) ;
        __asm ( " PUSH {R9} " ) ;
        __asm ( " PUSH {R10} " ) ;
        __asm ( " PUSH {R11} " ) ;



        /* save context of preempted task */

        /* change old task state */
        OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_State = READY ;

        /* save processor states of preempted task in its pcb, this states are pushed in main stack when exception of task context switching (PendSV) is triggered */
        OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_PSR = OsMSP_StackFrame_ptr->PSR ;
        OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_PC = OsMSP_StackFrame_ptr->PC ;
        OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_LR = OsMSP_StackFrame_ptr->LR ;
        OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_R12 = OsMSP_StackFrame_ptr->R12 ;
        OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_R3 = OsMSP_StackFrame_ptr->R3 ;
        OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_R2 = OsMSP_StackFrame_ptr->R2 ;
        OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_R1 = OsMSP_StackFrame_ptr->R1 ;
        OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_R0 = OsMSP_StackFrame_ptr->R0 ;

        /* this registers are pushed manually */
        OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_SP = OsMSP_StackFrame_ptr->PSP ;
        OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_R4 = OsMSP_StackFrame_ptr->R4 ;
        OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_R5 = OsMSP_StackFrame_ptr->R5 ;
        OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_R6 = OsMSP_StackFrame_ptr->R6 ;
        OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_R7 = OsMSP_StackFrame_ptr->R7 ;
        OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_R8 = OsMSP_StackFrame_ptr->R8 ;
        OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_R9 = OsMSP_StackFrame_ptr->R9 ;
        OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_R10 = OsMSP_StackFrame_ptr->R10 ;
        OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_R11 = OsMSP_StackFrame_ptr->R11 ;


        OsTaskResourceAllocation[ ( OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_Priority ) ] = PreemptionPriority ;

    }
    else    /* case running task is terminated */
    {

    }

    if ( INVALID_TASK != ReadyHighestPriority ) /* case there's tasks could enter running state */
    {
        __asm ( " MOV R12, #0x7FB4 " ) ;
        __asm( " MOVT R12, #0x2000 " ) ;
        __asm ( " MSR MSP, R12 " ) ;

        /* take copy for ReadyTaskPCB_Index, CS for read modify write sequence from ReadyTaskPCB_Index to ReadyHighestPriority*/
        __asm ( " CPSID i " ) ;

        DispatcherLocal_Variable = ReadyTaskPCB_Index ;
        PreemptionPriority = OsTasks_Array[ ( OsTasksPCB_Array[ DispatcherLocal_Variable ].Task_ID ) ].OsTaskCeillingPriority_Internal ;

        __asm ( " CPSIE i " ) ;

        /* write values of next running task into stack to be popped into registers */

        /* popped manually by code */
        OsMSP_StackFrame_ptr->R11 = OsTasksPCB_Array[ DispatcherLocal_Variable ].Task_R11 ;
        OsMSP_StackFrame_ptr->R10 = OsTasksPCB_Array[ DispatcherLocal_Variable ].Task_R10 ;
        OsMSP_StackFrame_ptr->R9 = OsTasksPCB_Array[ DispatcherLocal_Variable ].Task_R9 ;
        OsMSP_StackFrame_ptr->R8 = OsTasksPCB_Array[ DispatcherLocal_Variable ].Task_R8 ;
        OsMSP_StackFrame_ptr->R7 = OsTasksPCB_Array[ DispatcherLocal_Variable ].Task_R7 ;
        OsMSP_StackFrame_ptr->R6 = OsTasksPCB_Array[ DispatcherLocal_Variable ].Task_R6 ;
        OsMSP_StackFrame_ptr->R5 = OsTasksPCB_Array[ DispatcherLocal_Variable ].Task_R5 ;
        OsMSP_StackFrame_ptr->R4 = OsTasksPCB_Array[ DispatcherLocal_Variable ].Task_R4 ;
        OsMSP_StackFrame_ptr->PSP = OsTasksPCB_Array[ DispatcherLocal_Variable ].Task_SP ;

        /* will be popped automatically in exception return */
        OsMSP_StackFrame_ptr->R0 = OsTasksPCB_Array[ DispatcherLocal_Variable ].Task_R0 ;
        OsMSP_StackFrame_ptr->R1 = OsTasksPCB_Array[ DispatcherLocal_Variable ].Task_R1 ;
        OsMSP_StackFrame_ptr->R2 = OsTasksPCB_Array[ DispatcherLocal_Variable ].Task_R2 ;
        OsMSP_StackFrame_ptr->R3 = OsTasksPCB_Array[ DispatcherLocal_Variable ].Task_R3 ;
        OsMSP_StackFrame_ptr->R12 = OsTasksPCB_Array[ DispatcherLocal_Variable ].Task_R12 ;
        OsMSP_StackFrame_ptr->LR = OsTasksPCB_Array[ DispatcherLocal_Variable ].Task_LR ;
        OsMSP_StackFrame_ptr->PC = OsTasksPCB_Array[ DispatcherLocal_Variable ].Task_PC ;
        OsMSP_StackFrame_ptr->PSR = OsTasksPCB_Array[ DispatcherLocal_Variable ].Task_PSR ;



        /* manual pop for special register ready task */
        __asm ( " POP {R11} " ) ;
        __asm ( " POP {R10} " ) ;
        __asm ( " POP {R9} " ) ;
        __asm ( " POP {R8} " ) ;
        __asm ( " POP {R7} " ) ;
        __asm ( " POP {R6} " ) ;
        __asm ( " POP {R5} " ) ;
        __asm ( " POP {R4} " ) ;

        __asm ( " POP {R12} " ) ;
        __asm ( " MSR PSP, R12 " ) ;





        /* change index of running task pcb and change state for running task */
        RunningTaskPCB_Index = DispatcherLocal_Variable ;
        OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_State = RUNNING ;
    }
    else /* no ready tasks, go to idle mechanism */
    {
        while ( INVALID_TASK == ReadyHighestPriority) ;
    }

    return ;

}


/*****************************************************************************/

/* add/remove PCB which have index PCB_Index to/from proper priority queue and call disaptacher if preemption needed
 * add or removing depend on AddToQueue parameter if TRUE then add if false then remove */
void OsInternalScheduler ( uint8 PCB_Index, boolean AddToQueue )
{

    VAR( uint8, AUTOMATIC ) TaskPriority = OsTasksPCB_Array[ PCB_Index ].Task_Priority ;
    VAR( uint8, AUTOMATIC ) TempVariable = 0 ;


    if( TRUE == AddToQueue )    /* add pcb to ready queue */
    {
        /* critical section to read modify write to OsTasksPriorityNext_Array */

        /* take a copy */
        TempVariable = OsTasksPriorityNext_Array[TaskPriority] ;

        /* allocation for resource ( empty place in ready queue ) */
        OsTasksPriorityNext_Array[TaskPriority] = ( OsTasksPriorityNext_Array[TaskPriority] + 1 ) % TASKS_PER_PRIORITY ;


        /* put Task PCB in ready queue*/
        OsTasksPriority_Array[ TaskPriority][ TempVariable ] = PCB_Index ;

        /* check case no running tasks in system */
        if ( INVALID_TASK != RunningTaskPCB_Index )
        {
            TempVariable = OsTasks_Array[ (OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_ID) ].OsTaskSchedule ;
        }
        else
        {

        }
        /* check for preemption and calling dispatcher */

        /* critical section to read modify write to ReadyHighestPriority & DISPATCHER_CALL & ReadyTaskPCB_Index */

        if( TaskPriority > ReadyHighestPriority )  /* if task priority is the highest in current system */
        {
            /* modify highest priority in system and pcb index of task which will preempt running task */
            ReadyHighestPriority = TaskPriority ;

            ReadyTaskPCB_Index = PCB_Index ;

            if( ( TASK_FULL == TempVariable ) && ( TaskPriority > PreemptionPriority ) )     /* task is follow fully preemptive scheduling policy */
            {
                DISPATCHER_CALL ;
            }
            else    /* task is follow non preemptive scheduling policy */
            {
            }

        } /* if */
        else if ( INVALID_TASK == ReadyHighestPriority )   /* if no ready tasks in system */
        {
            /* modify highest priority in system and pcb index of task which will preempt running task */
            ReadyHighestPriority = TaskPriority ;
            ReadyTaskPCB_Index = PCB_Index ;

            DISPATCHER_CALL ;
        }
        else
        {
        }


    } /* if */
    else    /* remover pcb from ready queue */
    {
        TaskPriority = OsTasksPCB_Array[ PCB_Index ].Task_Priority ;

        /* here no need for critical section because just running task can reach for this point of code
           and if preempted that will be with higher priority task which won't access same element  */


        if ( ReadyHighestPriority > TaskPriority )  /* no need for CS, just read ReadyHighestPriority */ /* this case just happen in non preemptive tasks */
        {

        }
        else    /* in preemptive task ReadyHighestPriority will be equal to RunningTaskPCB_Index while task is running */
        {

            /* critical section to read modify write to OsTasksPriority_Array & ReadyHighestPriority & ReadyTaskPCB_Index */

            /* remove PCB index from ready queue and shift first element in queue
             * done in critical section just before calling dispatcher, because if preempted
             * how will it return after pcb index in ready priority queue is removed */
            OsTasksPriority_Array [TaskPriority] [ (OsTasksPriorityIndex_Array[TaskPriority]) ] = INVALID_TASK ;
            OsTasksPriorityIndex_Array[TaskPriority] = ( OsTasksPriorityIndex_Array[TaskPriority] + 1 ) % TASKS_PER_PRIORITY ;


            /* check for highest priority and if no there ready tasks then TaskPriority = INVALID_TASK */
            while ( ( INVALID_TASK == OsTasksPriority_Array [TaskPriority] [ (OsTasksPriorityIndex_Array[TaskPriority]) ] ) && ( INVALID_TASK != TaskPriority ) )
            {
                /* get highest priority in system */
                TaskPriority-- ;
            } /* while */

            ReadyHighestPriority = TaskPriority ;

            if ( INVALID_TASK != TaskPriority ) /* another task could enter running state */
            {

                /* check for task allocate resources and preempted by higher priority task wasn't allocate related resource */
                TempVariable = TaskPriority ;
                while( ( OsTaskResourceAllocation[TempVariable] == FALSE ) && ( TempVariable != INVALID_TASK ) )
                {
                    TempVariable -- ;
                }

                if ( TempVariable == INVALID_TASK ) /* no task allocate resources */
                {
                    ReadyTaskPCB_Index = OsTasksPriority_Array [TaskPriority] [ (OsTasksPriorityIndex_Array[TaskPriority]) ] ;
                }
                else if ( OsTaskResourceAllocation[TempVariable] > ReadyHighestPriority )  /* there's task was allocating resources and preempted */
                {
                    ReadyTaskPCB_Index = OsTasksPriority_Array [TempVariable] [ (OsTasksPriorityIndex_Array[TempVariable]) ] ;
                }
                else
                {
                    ReadyTaskPCB_Index = OsTasksPriority_Array [TaskPriority] [ (OsTasksPriorityIndex_Array[TaskPriority]) ] ;
                }

            } /* if */
            else    /* no ready tasks  */
            {

            } /* else */


            if ( SUSPENDED == OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_State ) /* task is terminated, done in CS because this lines need to done in atomic way */
            {
                /* release PCB of task in case of termination , this must done here right before calling dispatcher to terminate task
                 * because if in TerminateTask i won't have access to PCB any more and task couldn't be preempted correctly along this function */
                OsTasksPCB_Array[RunningTaskPCB_Index].Task_ID = INVALID_TASK ; /* make its PCB available */
                NotSuspendedTasks_Number-- ;
                RunningTaskPCB_Index = INVALID_TASK ;
            }
            else    /* task is waiting */
            {

            } /* else */

        }  /* else */


        DISPATCHER_CALL ;


    } /* else */


    return ;
}



/*****************************************************************************/


void OsTaskFrame (void)
{

    __asm ( " SVC #0x32 " ) ;
    __asm ( " MRS R10, CONTROL " ) ;
    __asm ( " ORR R10, R10, #0x03 " ) ;
    __asm ( " MSR CONTROL, R10 " ) ;

    __asm ( " MOV PC, R11 " ) ;

    return ;
}

