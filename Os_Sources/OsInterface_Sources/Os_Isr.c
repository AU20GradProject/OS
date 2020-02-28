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
FUNC(ISRType, AUTOMATIC) GetISRID( void ){
    /*
    [SWS_Os_00263] ⌈If called from category 2 ISR (or Hook routines called inside a category 2 ISR), GetISRID() shall return the identifier of the currently executing ISR.
    [SWS_Os_00264] ⌈If its caller is not a category 2 ISR (or Hook routines called inside a category 2 ISR), GetISRID() shall return INVALID_ISR. ⌋ ( )
   */
    return ActiveISR;
}

/*This service restores the state saved by DisableAllInterrupts.*/
FUNC(void, AUTOMATIC) EnableAllInterrupts(void){
/*
* The service may be called from an ISR category 1 and category 2 and from the task level, but not from hook routines.
*/
        // -----> @TODO CHECK IF CALLER IS NOT A HOOK ROUTINE 
/*
* This service is a counterpart of DisableAllInterrupts service, which has to be called before, and its aim is the completion of the critical section of code.
*/
    if (ActiveIsrDisable != DisAllIntActive){
        /* Error interrupts wasnot disabled using DisableAllInterrupts before enabling it*/
        return;
    }
/*
* The implementation should adapt this service to the target hardware providing a minimum overhead. Usually, this service enables recognition of interrupts by the central processing unit.
*/
    ActiveIsrDisable = NoDisableActive; /* cannot be interrupted after because interrupt is disabled.*/
    __asm volatile ("CPSIE i");
    return;
}

/*This service disables all interrupts for which the hardware supports disabling. The state before is saved for the EnableAllInterrupts call.*/
FUNC(void, AUTOMATIC) DisableAllInterrupts(void){
    /*
    The service may be called from an ISR category 1 and category 2 and from the task level, but not from hook routines.
    */
        // -----> @TODO CHECK IF CALLER IS NOT A HOOK ROUTINE 
    /*
    This service is intended to start a critical section of the code. This section shall be finished by calling the EnableAllInterrupts service. No API service calls are allowed within this critical section.
    */
   
   /*
    The implementation should adapt this service to the target hardware providing a minimum overhead. Usually, this service disables recognition of interrupts by the central processing unit.
    Note that this service does not support nesting. If nesting is needed for critical sections e.g. for libraries SuspendOSInterrupts/ResumeOSInterrupts or SuspendAllInterrupt/ResumeAllInterrupts should be used.
    */   
    if (ActiveIsrDisable != NoDisableActive){
        /* Error nesting is not supported*/
        return;
    }
    __asm volatile ("CPSID i");
    ActiveIsrDisable = DisAllIntActive; /* cannot be interrupted before because interrupt is disabled. */
    return;
}
/* The rest of the functions werenot implemented because we donot need them */

/* This service restores the recognition status of all interrupts saved by the SuspendAllInterrupts service. */
FUNC(void, AUTOMATIC) ResumeAllInterrupts(void){
    /*
    The service may be called from an ISR category 1 and category 2, from alarm-callbacks and from the task level, but not from all hook routines.
    */
    /*
    This service is the counterpart of SuspendAllInterrupts service, which has to have been called before, and its aim is the completion of the critical section of code. No API service calls beside SuspendAllInterrupts/ResumeAllInterrupts pairs and SuspendOSInterrupts/ResumeOSInterrupts pairs are allowed within this critical section.
    */

    if (ActiveIsrDisable != SuspendAllIntActive){
        /* Error interrupts wasnot suspended before resuming them*/
        return;
    }
    /*
    The implementation should adapt this service to the target hardware providing a minimum overhead.
    SuspendAllInterrupts/ResumeAllInterrupts can be nested. In case of nesting pairs of the calls SuspendAllInterrupts and ResumeAllInterrupts the interrupt recognition status saved by the first call of SuspendAllInterrupts is restored by the last call of the ResumeAllInterrupts service.
    */
    ActiveIsrDisable = NoDisableActive;
}

/*This service saves the recognition status of all interrupts and disables all interrupts for which the hardware supports disabling.*/
FUNC(void, AUTOMATIC) SuspendAllInterrupts(void){ 
    ActiveIsrDisable = SuspendAllIntActive;  
    /*
    The service may be called from an ISR category 1 and category 2, from alarm-callbacks and from the task level, but not from all hook routines.
    */
    /*
   This service is intended to protect a critical section of code from interruptions of any kind. This section shall be finished by calling the ResumeAllInterrupts service. No API service calls beside SuspendAllInterrupts/ResumeAllInterrupts pairs and SuspendOSInterrupts/ResumeOSInterrupts pairs are allowed within this critical section.
    */
    /*
    The implementation should adapt this service to the target hardware providing a minimum overhead.
    */
}
/*This service restores the recognition status of interrupts saved by the SuspendOSInterrupts service.*/
FUNC(void, AUTOMATIC) ResumeOSInterrupts(void){
    /*
    The service may be called from an ISR category 1 and category 2 and from the task level, but not from hook routines.
    */
   /*
   This service is the counterpart of SuspendOSInterrupts service, which has to have been called before, and its aim is the completion of the critical section of code. No API service calls beside SuspendAllInterrupts/ResumeAllInterrupts pairs and SuspendOSInterrupts/ResumeOSInterrupts pairs are allowed within this critical section.
    */
    if (ActiveIsrDisable != SuspendOSIntActive){
        /* Error OS interrupts wasnot suspended before resuming them*/
        return;
    }

    /*
    The implementation should adapt this service to the target hardware providing a minimum overhead.
    SuspendOSInterrupts/ResumeOSInterrupts can be nested. In case of nesting pairs of the calls SuspendOSInterrupts and ResumeOSInterrupts the interrupt recognition status saved by the first call of SuspendOSInterrupts is restored by the last call of the ResumeOSInterrupts service.
    */
    ActiveIsrDisable = NoDisableActive; //can be nested, so how to know if nested or not and how many nests 
}

/* This service saves the recognition status of interrupts of category 2 and disables the recognition of these interrupts.*/
FUNC(void, AUTOMATIC) SuspendOSInterrupts(void){
    ActiveIsrDisable = SuspendOSIntActive;
    /*
    The service may be called from an ISR and from the task level, but not from hook routines.
    */
   /* 
   This service is intended to protect a critical section of code. This section shall be finished by calling the ResumeOSInterrupts service. No API service calls beside SuspendAllInterrupts/ResumeAllInterrupts pairs and SuspendOSInterrupts/ResumeOSInterrupts pairs are allowed within this critical section.
    */
   /*
   The implementation should adapt this service to the target hardware providing a minimum overhead.
    It is intended only to disable interrupts of category 2. However, if this is not possible in an efficient way more interrupts may be disabled.
    */
}

