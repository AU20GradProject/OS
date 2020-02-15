/*

    Created by : Ahmad HEGAZY
    DATE : 15/2/2019
    AUTOSAR Version : 4.3.1
    DOC Name : AUTOSAR_SWS_OS.pdf
                OSEK/VDX.pdf
    Target : ARM TIVA_C TM4C123GH6PM

*/

#ifndef OS_HEADERS_OSINTERFACE_HEADERS_OS_ISR_H_
#define OS_HEADERS_OSINTERFACE_HEADERS_OS_ISR_H_


/*********************************************************************************************************/


#define INVALID_ISR 0xFFu  /**/
#define TIMER_ISR     0x00u

/* enum data type identifies an interrupt service routine (ISR). */
typedef VAR( uint8, TYPEDEF ) ISRType ;

/* Variable contains active ISR ID, set at the beginning of the ISR
    if no ISR is active, INVALID_ISR is the default value. */
VAR(ISRType, AUTOMATIC) ActiveISR = INVALID_ISR;

/*
    Within the application, an interrupt service routine of category 2 is defined according to the following pattern:
    ISR (FuncName)
    {
    }
    The keyword ISR is evaluated by the system generation to clearly distinguish between func-tions and interrupt service routines in the source code.
*/
#define ISR( FuncName )   FUNC(void, OS_CODE) FuncName (void)

/* This service returns the identifier of the currently executing ISR.*/
FUNC(ISRType, AUTOMATIC) GetISRID( void );
/*This service restores the state saved by DisableAllInterrupts.*/
FUNC(void, AUTOMATIC) EnableAllInterrupts(void);
/*This service disables all interrupts for which the hardware supports disabling. The state before is saved for the EnableAllInterrupts call.*/
FUNC(void, AUTOMATIC) DisableAllInterrupts(void);
/* This service restores the recognition status of all interrupts saved by the SuspendAllInterrupts service. */
FUNC(void, AUTOMATIC) ResumeAllInterrupts(void);
/*This service saves the recognition status of all interrupts and disables all interrupts for which the hardware supports disabling.*/
FUNC(void, AUTOMATIC) SuspendAllInterrupts(void);
/*This service restores the recognition status of interrupts saved by the SuspendOSInterrupts service.*/
FUNC(void, AUTOMATIC) ResumeOSInterrupts(void);
/* This service saves the recognition status of interrupts of category 2 and disables the recognition of these interrupts.*/
FUNC(void, AUTOMATIC) SuspendOSInterrupts(void);



/*********************************************************************************************************/

#endif /* OS_HEADERS_OSINTERFACE_HEADERS_OS_ISR_H_ */
