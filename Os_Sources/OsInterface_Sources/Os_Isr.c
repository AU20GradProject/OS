/*

    Created by : Ahmad HEGAZY
    DATE : 15/2/2019
    AUTOSAR Version : 4.3.1
    DOC Name : AUTOSAR_SWS_OS.pdf
                OSEK/VDX.pdf
    Target : ARM TIVA_C TM4C123GH6PM

*/




#include "..\..\Os_Headers\OsInterface_Headers\Os.h"
#include "..\..\Os_Headers\OsInternal_Headers\Os_Internal.h"
#include "..\..\Os_Headers\OsInternal_Headers\Os_ExternalVariables.h"

/* This service returns the identifier of the currently executing ISR.*/
FUNC(ISRType, OS_CODE) GetISRID( void )
{
    /*
    [SWS_Os_00263] If called from category 2 ISR (or Hook routines called inside a category 2 ISR), GetISRID() shall return the identifier of the currently executing ISR.
    [SWS_Os_00264] If its caller is not a category 2 ISR (or Hook routines called inside a category 2 ISR), GetISRID() shall return INVALID_ISR.
   */
    return IsrID;
}

/*This service restores the state saved by DisableAllInterrupts.*/
FUNC(StatusType, OS_CODE) EnableAllInterrupts(void)
{
    CS_ON;
    StatusType status = E_OK;

    /* The service may be called from an ISR category 1 and category 2 and from the task level, but not from hook routines. */


    if( HookID != INVALID_HOOK)
    {
        status = E_NOT_OK;
    }else
    {

    /* This service is a counterpart of DisableAllInterrupts service, which has to be called before, and its aim is the completion of the critical section of code. */
        if (ActiveIsrDisable != DisAllIntActive)
        {
            /* Error interrupts wasnot disabled using DisableAllInterrupts before enabling it*/
            status = E_NOT_OK;
        }
        else
        {
        /*
        * The implementation should adapt this service to the target hardware providing a minimum overhead. Usually, this service enables recognition of interrupts by the central processing unit.
        */
            ActiveIsrDisable = NoDisableActive; /* cannot be interrupted after because interrupt is disabled.*/
            __asm volatile (" CPSIE i");
        }
    }

    CS_OFF; /* disable critical section */

    return status;
}

/*This service disables all interrupts for which the hardware supports disabling. The state before is saved for the EnableAllInterrupts call.*/
FUNC(StatusType, OS_CODE) DisableAllInterrupts(void)
{
    CS_ON;
    StatusType status = E_OK;
    
    /*
    The service may be called from an ISR category 1 and category 2 and from the task level, but not from hook routines.
    */
    if( HookID != INVALID_HOOK)
    {
        status = E_NOT_OK;
        CS_OFF;
    /*
    This service is intended to start a critical section of the code. This section shall be finished by calling the EnableAllInterrupts service. No API service calls are allowed within this critical section.
    */
    }
    else
    {
        if (ActiveIsrDisable != NoDisableActive)
        {
            /* Error nesting is not supported*/
            status = E_NOT_OK;
            CS_OFF;
        }
        else
        {
            /*
            The implementation should adapt this service to the target hardware providing a minimum overhead. Usually, this service disables recognition of interrupts by the central processing unit.
            Note that this service does not support nesting. If nesting is needed for critical sections e.g. for libraries SuspendOSInterrupts/ResumeOSInterrupts or SuspendAllInterrupt/ResumeAllInterrupts should be used.
            */
        	__asm volatile (" CPSID i");
            ActiveIsrDisable = DisAllIntActive; /* cannot be interrupted before because interrupt is disabled. */
        }
    }

    END_PRIVILEGE;
    return status;
}
/* The rest of the functions werenot implemented because we donot need them */

/* This service restores the recognition status of all interrupts saved by the SuspendAllInterrupts service. */
FUNC(StatusType, OS_CODE) ResumeAllInterrupts(void)
{
    CS_ON;
    StatusType status = E_OK;

    /*
    The service may be called from an ISR category 1 and category 2, from alarm-callbacks and from the task level, but not from all hook routines.
    */
    if( HookID != INVALID_HOOK)
    {
        status = E_NOT_OK;
        CS_OFF;
    }
    else
    {
        /*
        This service is the counterpart of SuspendAllInterrupts service, which has to have been called before, and its aim is the completion of the critical section of code. No API service calls beside SuspendAllInterrupts/ResumeAllInterrupts pairs and SuspendOSInterrupts/ResumeOSInterrupts pairs are allowed within this critical section.
        */
        /*
        The implementation should adapt this service to the target hardware providing a minimum overhead.
        SuspendAllInterrupts/ResumeAllInterrupts can be nested. In case of nesting pairs of the calls SuspendAllInterrupts and ResumeAllInterrupts the interrupt recognition status saved by the first call of SuspendAllInterrupts is restored by the last call of the ResumeAllInterrupts service.
        */
        if (ActiveIsrDisable != SuspendAllIntActive && ActiveIsrDisable != SuspendOSIntActive)
        {
            /* Error interrupts wasnot suspended before resuming them*/
            status = E_NOT_OK;
        }
        else
        {
            PEND0_REG_ADDR = PEND0;
            PEND1_REG_ADDR = PEND1;
            PEND2_REG_ADDR = PEND2;
            PEND3_REG_ADDR = PEND3;
            PEND4_REG_ADDR = PEND4;
            UNPEND0_REG_ADDR = ~PEND0;
            UNPEND1_REG_ADDR = ~PEND1;
            UNPEND2_REG_ADDR = ~PEND2;
            UNPEND3_REG_ADDR = ~PEND3;
            UNPEND4_REG_ADDR = ~PEND4;
            if ( 0 == --suspendCount)
            {
                ActiveIsrDisable = NoDisableActive;  
                CS_OFF;
            }else
            {
                ActiveIsrDisable = SuspendAllIntActive;  
            }
        }
    }
    END_PRIVILEGE;
	return status;
}

/*This service saves the recognition status of all interrupts and disables all interrupts for which the hardware supports disabling.*/
FUNC(StatusType, OS_CODE) SuspendAllInterrupts(void)
        {
    CS_ON;
    StatusType status = E_OK;
    /*
    The service may be called from an ISR category 1 and category 2, from alarm-callbacks and from the task level, but not from all hook routines.
    */
    if( HookID != INVALID_HOOK){
        status = E_NOT_OK;
        CS_OFF;
    }else{
        /*
    This service is intended to protect a critical section of code from interruptions of any kind. This section shall be finished by calling the ResumeAllInterrupts service. No API service calls beside SuspendAllInterrupts/ResumeAllInterrupts pairs and SuspendOSInterrupts/ResumeOSInterrupts pairs are allowed within this critical section.
        */
        /*
        The implementation should adapt this service to the target hardware providing a minimum overhead.
        */
        if (ActiveIsrDisable == NoDisableActive){
            PEND0 = PEND0_REG_ADDR;
            PEND1 = PEND1_REG_ADDR;
            PEND2 = PEND2_REG_ADDR;
            PEND3 = PEND3_REG_ADDR;
            PEND4 = PEND4_REG_ADDR;
            ActiveIsrDisable = SuspendAllIntActive;  
            suspendCount = 1;
        }else if (ActiveIsrDisable == DisAllIntActive){
            /* nesting is not supported in DisableAllInterrupts*/
            status = E_NOT_OK;
            CS_OFF;
        }else {
            /* Nesting, data is stored in the 1st time */
            suspendCount++;
        }
    }
    END_PRIVILEGE;
    return status;
}


/*This service restores the recognition status of interrupts saved by the SuspendOSInterrupts service.*/
FUNC(StatusType, OS_CODE) ResumeOSInterrupts(void)
{
    CS_ON;
    StatusType status = E_OK;
    /*
    The service may be called from an ISR category 1 and category 2, from alarm-callbacks and from the task level, but not from all hook routines.
    */
    if( HookID != INVALID_HOOK)
    {
        status = E_NOT_OK;
        CS_OFF;
    }else
    {
        /*
        This service is the counterpart of SuspendAllInterrupts service, which has to have been called before, and its aim is the completion of the critical section of code. No API service calls beside SuspendAllInterrupts/ResumeAllInterrupts pairs and SuspendOSInterrupts/ResumeOSInterrupts pairs are allowed within this critical section.
        */
        /*
        The implementation should adapt this service to the target hardware providing a minimum overhead.
        SuspendAllInterrupts/ResumeAllInterrupts can be nested. In case of nesting pairs of the calls SuspendAllInterrupts and ResumeAllInterrupts the interrupt recognition status saved by the first call of SuspendAllInterrupts is restored by the last call of the ResumeAllInterrupts service.
        */
        if (ActiveIsrDisable != SuspendOSIntActive && ActiveIsrDisable != SuspendAllIntActive){
            /* Error interrupts wasnot suspended before resuming them*/
            status = E_NOT_OK;
        }else {
            PEND0_REG_ADDR = PEND0;
            PEND1_REG_ADDR = PEND1;
            PEND2_REG_ADDR = PEND2;
            PEND3_REG_ADDR = PEND3;
            PEND4_REG_ADDR = PEND4;
            UNPEND0_REG_ADDR = ~PEND0;
            UNPEND1_REG_ADDR = ~PEND1;
            UNPEND2_REG_ADDR = ~PEND2;
            UNPEND3_REG_ADDR = ~PEND3;
            UNPEND4_REG_ADDR = ~PEND4;

            if ( 0 == --suspendCount)
            {
                ActiveIsrDisable = NoDisableActive;  
                CS_OFF;
            }
            else
            {
                ActiveIsrDisable = SuspendOSIntActive;  
            }
        }
    }
    END_PRIVILEGE;
	return status;
}

/* This service saves the recognition status of interrupts of category 2 and disables the recognition of these interrupts.*/
FUNC(StatusType, OS_CODE) SuspendOSInterrupts(void){
    CS_ON;
    StatusType status = E_OK;
    ActiveIsrDisable = SuspendOSIntActive;
    /*
    The service may be called from an ISR and from the task level, but not from hook routines.
    */
    if( HookID != INVALID_HOOK){
        status = E_NOT_OK;
        CS_OFF;
    }else{
    /* 
    This service is intended to protect a critical section of code. This section shall be finished by calling the ResumeOSInterrupts service. No API service calls beside SuspendAllInterrupts/ResumeAllInterrupts pairs and SuspendOSInterrupts/ResumeOSInterrupts pairs are allowed within this critical section.
        */
    /*
    The implementation should adapt this service to the target hardware providing a minimum overhead.
        It is intended only to disable interrupts of category 2. However, if this is not possible in an efficient way more interrupts may be disabled.
        */
        if (ActiveIsrDisable == NoDisableActive){
            PEND0 = PEND0_REG_ADDR;
            PEND1 = PEND1_REG_ADDR;
            PEND2 = PEND2_REG_ADDR;
            PEND3 = PEND3_REG_ADDR;
            PEND4 = PEND4_REG_ADDR;
            ActiveIsrDisable = SuspendOSIntActive;  
            suspendCount = 1;
        }else if (ActiveIsrDisable == DisAllIntActive){
            /* nesting is not supported in DisableAllInterrupts*/
            status = E_NOT_OK;
            CS_OFF;
        }else {
            /* Nesting, data is stored in the 1st time */
            suspendCount++;
        }
    }
    END_PRIVILEGE;
    return status;
}
