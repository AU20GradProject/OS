/*

    Written by : Bebo
    DATE : 7/2/2019
    AUTOSAR Version : 4.3.1
    DOC Name : AUTOSAR_SWS_OS.pdf
    Target : ARM TIVA_C TM4C123GH6PM

*/

#ifndef OS_HEADERS_OSINTERNAL_HEADERS_OS_TASK_INTERNAL_H_
#define OS_HEADERS_OSINTERNAL_HEADERS_OS_TASK_INTERNAL_H_


/*****************************************************************************/


/* used for initialize all elements of array with value x */
#define VAL_1(x)        x
#define VAL_2(x)        VAL_1(x), VAL_1(x)
#define VAL_4(x)        VAL_2(x), VAL_2(x)
#define VAL_8(x)        VAL_4(x), VAL_4(x)
#define VAL_16(x)       VAL_8(x), VAL_8(x)
#define VAL_32(x)       VAL_16(x), VAL_16(x)
#define VAL_64(x)       VAL_32(x), VAL_32(x)
#define VAL_128(x)      VAL_64(x), VAL_64(x)
#define VAL_256(x)      VAL_128(x), VAL_128(x)


/*****************************************************************************/
/* set pending bit of PendSv exception and set stack pointer to MSP */

#define DISPATCHER_CALL *( ( volatile P2VAR( uint32, AUTOMATIC, REGSPACE ) ) 0xE000ED04 ) |= ( 0x01u << 28 )



/* set BASEPRI priority to be 7 to disable dispatcher*/
#define DISPATCHER_OFF  __asm ( " SVC #0x00 " ) ; \
                        __asm ( " MOV R11, #0x0E0u " ) ;\
                        __asm ( " MSR BASEPRI, R11 " )


/* befor convert to dipatcher make stack pointer for MSP*/
#define DISPATCHER_ON    __asm ( " SVC #0x00 " ) ; \
                         __asm ( " MOV R11, #0x00 " );\
                         __asm ( " MSR BASEPRI, R11  " ) ;\
                         __asm ( " MRS R10, CONTROL " ) ;\
                         __asm ( " ORR R10, R10, #0x01 " ) ;\
                         __asm ( " MSR CONTROL, R10 " )


/* set and clear PRIMASK register*/
#define CS_ON           __asm ( " SVC #0x00 " ) ; \
                        __asm ( " CPSID i " ) ;


#define CS_OFF      __asm ( " CPSIE i " ) ; \
                    __asm ( " MRS R10, CONTROL " ) ;\
                    __asm ( " ORR R10, R10, #0x01 " ) ;\
                    __asm ( " MSR CONTROL, R10 " )

/*****************************************************************************/


typedef struct
{
    /* OsTaskSchedule attribute defines the preemptability of the task.
     * If this attribute is set to NON, no internal resources may be assigned to this task */
    VAR( uint8, AUTOMATIC ) OsTaskSchedule ;

    /* defines the maximum number of queued activation requests for the task
     * 1" means that at any time only a single activation is permitted for this task
     * for basic tasks in BCC2,ECC2 */
    VAR( uint8, AUTOMATIC ) OsTaskActivation ;

    /* priority of a task is defined by the value of this,
     * larger values correspond to higher priorities 0 is lowest */
    VAR( uint8, AUTOMATIC ) OsTaskPriority ;

    /*  internal resource ceiling priority if no resources accessed by the task value will be = OsTaskPriority */
    VAR( uint8, AUTOMATIC ) OsTaskCeilingPriority_Internal ;

    /* defines the list of resource that task may occupy */
    VAR( ResourceMaskType, AUTOMATIC ) OsResourceRef ;

    /* defines the list of events the extended task may react on, as a mask for events of this task  */
    VAR( EventMaskType, AUTOMATIC ) OsTaskEventRef ;


} OsTask ;



/*****************************************************************************/


typedef struct
{


    /* variable to carry number of multiple activation requested for basic tasks
     * at every activate will be decremented if not equeal to zero
     * initialized from configuration task array */
    VAR( uint8, AUTOMATIC ) OsTaskMultipleActivation ;

    /* priority of the task */
    VAR( uint8, AUTOMATIC ) Task_Priority ;

    /* number of resource number occupied by task */
    VAR( uint8, AUTOMATIC ) Task_ResourcesOccupied ;

    /* hold resource id of last occupied resource by the task */
    VAR( ResourceType, AUTOMATIC ) Task_LastResourceOccupied ;

    /* id of task own this PCB */
    VAR( TaskType, AUTOMATIC ) Task_ID ;

    /* state of task own this PCB */
    VAR( TaskStateType, AUTOMATIC ) Task_State ;

    /* general purpose register */
    VAR( uint32, AUTOMATIC ) Task_R0 ;
    VAR( uint32, AUTOMATIC ) Task_R1 ;
    VAR( uint32, AUTOMATIC ) Task_R2 ;
    VAR( uint32, AUTOMATIC ) Task_R3 ;
    VAR( uint32, AUTOMATIC ) Task_R4 ;
    VAR( uint32, AUTOMATIC ) Task_R5 ;
    VAR( uint32, AUTOMATIC ) Task_R6 ;
    VAR( uint32, AUTOMATIC ) Task_R7 ;
    VAR( uint32, AUTOMATIC ) Task_R8 ;
    VAR( uint32, AUTOMATIC ) Task_R9 ;
    VAR( uint32, AUTOMATIC ) Task_R10 ;
    VAR( uint32, AUTOMATIC ) Task_R11 ;
    VAR( uint32, AUTOMATIC ) Task_R12 ;

    /* PSP for task */
    VAR( uint32, AUTOMATIC ) Task_SP ;

    /* linker register of task used for return  from function calls */
    VAR( uint32, AUTOMATIC ) Task_LR ;

    /* program counter for task */
    P2FUNC( void, AUTOMATIC, Task_PC ) (void)  ;

    /* status register for task */
    VAR( uint32, AUTOMATIC ) Task_PSR ;

    /* control register for task to save privilege level */
    VAR( uint32, AUTOMATIC ) Task_CONTROL ;

    /* flags determine states of the task set or cleared */
    VAR( EventMaskType, AUTOMATIC ) Task_EvnetsFlag ;

    /* flags determine which events task is waiting */
    VAR( EventMaskType, AUTOMATIC ) Task_EvnetsWaiting ;

    VAR( uint32, AUTOMATIC ) Task_Stack [TASK_STACK_SIZE] ;

} OsTask_PCB ;


/*****************************************************************************/


/* used to reference stack frame in case of interrupt
 * to easily access the element that pushed to main stack for context switching  */
typedef struct
{

    /* this registers are pushed manually */
    VAR (uint32, AUTOMATIC) CONTROL ;
    VAR (uint32, AUTOMATIC) R11 ;
    VAR (uint32, AUTOMATIC) R10 ;
    VAR (uint32, AUTOMATIC) R9 ;
    VAR (uint32, AUTOMATIC) R8 ;
    VAR (uint32, AUTOMATIC) R7 ;
    VAR (uint32, AUTOMATIC) R6 ;
    VAR (uint32, AUTOMATIC) R5 ;
    VAR (uint32, AUTOMATIC) R4 ;
    VAR (uint32, AUTOMATIC) PSP ;

    VAR (uint32, AUTOMATIC) emp_1 ;
    VAR (uint32, AUTOMATIC) emp_2 ;


} OsStackFrame_MSP;


/*****************************************************************************/


typedef struct
{

    /* this register are pushed by exception entry automatically */
    VAR (uint32, AUTOMATIC) R0 ;
    VAR (uint32, AUTOMATIC) R1 ;
    VAR (uint32, AUTOMATIC) R2 ;
    VAR (uint32, AUTOMATIC) R3 ;
    VAR (uint32, AUTOMATIC) R12 ;
    VAR (uint32, AUTOMATIC) LR ;
    P2FUNC( void, AUTOMATIC, PC ) (void)  ;
    VAR (uint32, AUTOMATIC) PSR ;

} OsStackFrame_PSP ;


/*****************************************************************************/


/* make context switching */
FUNC (void, OS_CODE) OsDispatcher (void) ;

/* used to add Task to last of proper priority queue and modify the queue */
FUNC (void, OS_CODE) OsTailTask (  uint8 PCB_Index ) ;

/* used to add to head of proper priority queue and modify the queue */
FUNC (void, OS_CODE) OsHeadTask ( uint8 PCB_Index ) ;

/* used to remove task from in the head of priority queue and modify the queue */
FUNC (void, OS_CODE) RemoveTask ( uint8 TaskPriority ) ;

FUNC (void, OS_CODE) Init_PCB ( uint8 PCB_Index, uint8 TaskID ) ;


/*****************************************************************************/

#endif /* OS_HEADERS_OSINTERNAL_HEADERS_OS_TASK_INTERNAL_H_ */





