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
FUNC (void, OS_CODE) OsDispatcher (void)
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
        __asm ( " MRS R12, CONTROL " ) ;
        __asm ( " PUSH {R12} " ) ;

        /* initialize the pointer of PSP frame casting  */
        OsPSP_StackFrame_ptr = (( ( volatile P2VAR( OsStackFrame_PSP, AUTOMATIC, REGSPACE ) ) (OsMSP_StackFrame_ptr->PSP) ) ) ;

        /* save context of preempted task */

        /* change old task state */
        OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_State = READY ;

        /* save processor states of preempted task in its pcb, this states are pushed in main stack when exception of task context switching (PendSV) is triggered */
        OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_PSR = OsPSP_StackFrame_ptr->PSR ;
        OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_PC = OsPSP_StackFrame_ptr->PC ;
        OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_LR = OsPSP_StackFrame_ptr->LR ;
        OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_R12 = OsPSP_StackFrame_ptr->R12 ;
        OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_R3 = OsPSP_StackFrame_ptr->R3 ;
        OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_R2 = OsPSP_StackFrame_ptr->R2 ;
        OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_R1 = OsPSP_StackFrame_ptr->R1 ;
        OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_R0 = OsPSP_StackFrame_ptr->R0 ;

        /* this registers are pushed manually */
        OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_SP = OsMSP_StackFrame_ptr->PSP + 0x020u  ;    /* the added value for the automatically pushed registers */
        OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_R4 = OsMSP_StackFrame_ptr->R4 ;
        OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_R5 = OsMSP_StackFrame_ptr->R5 ;
        OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_R6 = OsMSP_StackFrame_ptr->R6 ;
        OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_R7 = OsMSP_StackFrame_ptr->R7 ;
        OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_R8 = OsMSP_StackFrame_ptr->R8 ;
        OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_R9 = OsMSP_StackFrame_ptr->R9 ;
        OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_R10 = OsMSP_StackFrame_ptr->R10 ;
        OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_R11 = OsMSP_StackFrame_ptr->R11 ;
        OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_CONTROL = OsMSP_StackFrame_ptr->CONTROL ;

    }
    else    /* case running task is terminated */
    {
    }

    if ( INVALID_TASK != ReadyHighestPriority ) /* case there's tasks could enter running state */
    {
        /* initialize stack pointer to allocate space for 12 word to wirte in registers that will be pooped manually */
        __asm ( " MOV R12, #0x7FD0 " ) ;
        __asm( " MOVT R12, #0x2000 " ) ;
        __asm ( " MSR MSP, R12 " ) ;

        /* take copy for ReadyTaskPCB_Index, CS for read modify write sequence from ReadyTaskPCB_Index to ReadyHighestPriority*/
        __asm ( " CPSID i " ) ;

        /* critical section to modify priority queue */
        CeilingPriority = OsTasks_Array[ ( OsTasksPCB_Array[ ReadyTaskPCB_Index ].Task_ID ) ].OsTaskCeilingPriority_Internal ;
        DispatcherLocal_Variable = OsTasksPCB_Array[ ReadyTaskPCB_Index ].Task_Priority ;

        /* assign new priority for task if has an internal resource */
        if ( CeilingPriority >  OsTasksPCB_Array[ ReadyTaskPCB_Index ].Task_Priority )
        {

            /* remove task from old queue */
            OsTasksPriority_Array [DispatcherLocal_Variable] [ (OsTasksPriorityIndex_Array[DispatcherLocal_Variable]) ] = INVALID_TASK ;
            OsTasksPriorityIndex_Array[DispatcherLocal_Variable] = ( OsTasksPriorityIndex_Array[DispatcherLocal_Variable] + 1 ) % TASKS_PER_PRIORITY ;

            /* modify task priority */
            OsTasksPCB_Array[ DispatcherLocal_Variable ].Task_Priority =  CeilingPriority ;
            ReadyHighestPriority = CeilingPriority ;

            /* add task to the new queue */
            OsTasksPriority_Array[ CeilingPriority ][ OsTasksPriorityNext_Array[CeilingPriority] ] = ReadyTaskPCB_Index ;
            OsTasksPriorityNext_Array[CeilingPriority] = ( OsTasksPriorityNext_Array[CeilingPriority] + 1 ) % TASKS_PER_PRIORITY ;

        }
        else
        {
        }

        DispatcherLocal_Variable = ReadyTaskPCB_Index ;

        __asm ( " CPSIE i " ) ;

        SchedulingPolicy =  OsTasks_Array[ (OsTasksPCB_Array[ DispatcherLocal_Variable ].Task_ID) ].OsTaskSchedule ;

        /* write values of next running task into stack to be popped into registers */

        /* popped manually by code */
        OsMSP_StackFrame_ptr->CONTROL =  OsTasksPCB_Array[ DispatcherLocal_Variable ].Task_CONTROL ;
        OsMSP_StackFrame_ptr->R11 =  OsTasksPCB_Array[ DispatcherLocal_Variable ].Task_R11 ;
        OsMSP_StackFrame_ptr->R10 = OsTasksPCB_Array[ DispatcherLocal_Variable ].Task_R10 ;
        OsMSP_StackFrame_ptr->R9 = OsTasksPCB_Array[ DispatcherLocal_Variable ].Task_R9 ;
        OsMSP_StackFrame_ptr->R8 = OsTasksPCB_Array[ DispatcherLocal_Variable ].Task_R8 ;
        OsMSP_StackFrame_ptr->R7 = OsTasksPCB_Array[ DispatcherLocal_Variable ].Task_R7 ;
        OsMSP_StackFrame_ptr->R6 = OsTasksPCB_Array[ DispatcherLocal_Variable ].Task_R6 ;
        OsMSP_StackFrame_ptr->R5 = OsTasksPCB_Array[ DispatcherLocal_Variable ].Task_R5 ;
        OsMSP_StackFrame_ptr->R4 = OsTasksPCB_Array[ DispatcherLocal_Variable ].Task_R4 ;
        OsMSP_StackFrame_ptr->PSP = OsTasksPCB_Array[ DispatcherLocal_Variable ].Task_SP - 0x020u ;

        OsPSP_StackFrame_ptr = (( ( volatile P2VAR( OsStackFrame_PSP, AUTOMATIC, REGSPACE ) ) (OsMSP_StackFrame_ptr->PSP) ) ) ;

        /* manual pop for special register ready task */
        __asm ( " POP {R12} " ) ;
        __asm ( " MSR CONTROL, R12 " ) ;

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

        /* will be popped automatically in exception return */
        OsPSP_StackFrame_ptr->R0 = OsTasksPCB_Array[ DispatcherLocal_Variable ].Task_R0 ;
        OsPSP_StackFrame_ptr->R1 = OsTasksPCB_Array[ DispatcherLocal_Variable ].Task_R1 ;
        OsPSP_StackFrame_ptr->R2 = OsTasksPCB_Array[ DispatcherLocal_Variable ].Task_R2 ;
        OsPSP_StackFrame_ptr->R3 = OsTasksPCB_Array[ DispatcherLocal_Variable ].Task_R3 ;
        OsPSP_StackFrame_ptr->R12 = OsTasksPCB_Array[ DispatcherLocal_Variable ].Task_R12 ;
        OsPSP_StackFrame_ptr->LR = OsTasksPCB_Array[ DispatcherLocal_Variable ].Task_LR ;
        OsPSP_StackFrame_ptr->PC = OsTasksPCB_Array[ DispatcherLocal_Variable ].Task_PC ;
        OsPSP_StackFrame_ptr->PSR = OsTasksPCB_Array[ DispatcherLocal_Variable ].Task_PSR ;

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

/* used to add Task to last of proper priority queue and modify the queue */
FUNC (void, OS_CODE) OsTailTask ( uint8 PCB_Index )
{
    VAR( uint8, AUTOMATIC ) TaskPriority = OsTasksPCB_Array[PCB_Index].Task_Priority ;


    OsTasksPriority_Array[ TaskPriority ][ OsTasksPriorityNext_Array[TaskPriority] ] = PCB_Index ;
    OsTasksPriorityNext_Array[TaskPriority] = ( OsTasksPriorityNext_Array[TaskPriority] + 1 ) % TASKS_PER_PRIORITY ;

    /* check for preemption and calling dispatcher */

    /* critical section to read modify write to ReadyHighestPriority & DISPATCHER_CALL & ReadyTaskPCB_Index */

    if( TaskPriority > ReadyHighestPriority )  /* if task priority is the highest in current system */
    {
        /* modify highest priority in system and pcb index of task which will preempt running task */
        ReadyHighestPriority = TaskPriority ;
        ReadyTaskPCB_Index = PCB_Index ;

        if( TASK_FULL == SchedulingPolicy )     /* task is follow fully preemptive scheduling policy */
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

    return ;
}

/*****************************************************************************/

/* used to add to head of proper priority queue and modify the queue */
FUNC (void, OS_CODE) OsHeadTask ( uint8 PCB_Index )
{
    VAR( uint8, AUTOMATIC ) TaskPriority = OsTasksPCB_Array[PCB_Index].Task_Priority ;
    VAR( uint8, AUTOMATIC ) TempVariable =    OsTasksPriorityIndex_Array[TaskPriority] - 1 ;

    if ( 0xFF == TempVariable)
    {
        TempVariable = TASKS_PER_PRIORITY - 1 ;
    }
    else
    {
    }

    OsTasksPriorityIndex_Array[TaskPriority] = TempVariable ;
    OsTasksPriority_Array[ TaskPriority ][ TempVariable ] = PCB_Index ;


    if( TaskPriority > ReadyHighestPriority )  /* if task priority is the highest in current system */
    {
        /* modify highest priority in system and pcb index of task which will preempt running task */
        ReadyHighestPriority = TaskPriority ;

    } /* if */
    else
    {

    }

    return ;
}

/*****************************************************************************/

/* used to remove task from in the head of priority queue and modify the queue */
FUNC (void, OS_CODE) RemoveTask ( uint8 TaskPriority )
{

    OsTasksPriority_Array [TaskPriority] [ (OsTasksPriorityIndex_Array[TaskPriority]) ] = INVALID_TASK ;
    OsTasksPriorityIndex_Array[TaskPriority] = ( OsTasksPriorityIndex_Array[TaskPriority] + 1 ) % TASKS_PER_PRIORITY ;


    if ( ReadyHighestPriority > TaskPriority )  /* no need for CS, just read ReadyHighestPriority */ /* this case just happen in non preemptive tasks */
    {

    }
    else
    {

        /* check for highest priority and if no there ready tasks then TaskPriority = INVALID_TASK */
        while ( ( INVALID_TASK == OsTasksPriority_Array [TaskPriority] [ (OsTasksPriorityIndex_Array[TaskPriority]) ] ) && ( INVALID_TASK != TaskPriority ) )
        {
            /* get highest priority in system */
            TaskPriority-- ;
        } /* while */

        ReadyHighestPriority = TaskPriority ;

        if ( INVALID_TASK != TaskPriority ) /* another task could enter running state */
        {
            ReadyTaskPCB_Index = OsTasksPriority_Array [TaskPriority] [ (OsTasksPriorityIndex_Array[TaskPriority]) ] ;
        }
        else    /* no ready tasks  */
        {

        } /* else */

    }

    DISPATCHER_CALL ;


    return ;
}


/*****************************************************************************/

/* this function used to initialize content of PCB related to hardware to achieve abstraction */
FUNC (void, OS_CODE) Init_PCB ( uint8 PCB_Index, uint8 TaskID )
{

    /* initialize task PCB */
    OsTasksPCB_Array[PCB_Index].Task_SP = ( VAR( uint32, AUTOMATIC ) ) ( &( ( (OsTasksPCB_Array[PCB_Index]).Task_Stack ) [TASK_STACK_SIZE] ) ) ;
    OsTasksPCB_Array[PCB_Index].Task_LR = 0xFFFFFFFD ;
    OsTasksPCB_Array[PCB_Index].Task_PSR = 0x01000000 ;
    OsTasksPCB_Array[PCB_Index].Task_PC = OsTasksNames_Array[ TaskID ] ;
    OsTasksPCB_Array[PCB_Index].Task_CONTROL = 0x01u ;
    /* initialized because register 9 is used to hold temp of Linker register */
    OsTasksPCB_Array[PCB_Index].Task_R9 = 0x00u ;

    return ;
}


/*****************************************************************************/



