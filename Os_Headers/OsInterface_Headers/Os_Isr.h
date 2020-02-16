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

/* All possible interrupt service routines IDs */

#define INVALID_ISR 0xFFu  
#define GPIOPortA_ISRID 0x01u
#define GPIOPortB_ISRID 0x02u
#define GPIOPortC_ISRID 0x03u
#define GPIOPortD_ISRID 0x04u
#define GPIOPortE_ISRID 0x05u
#define UART0_ISRID     0x06u
#define UART1_ISRID     0x07u
#define SSI0_ISRID      0x08u
#define I2C0_ISRID      0x09u
#define PWMFault_ISRID  0x0au
#define PWMGen0_ISRID   0x0bu
#define PWMGen1_ISRID   0x0cu
#define PWMGen2_ISRID   0x0du
#define QEI0_ISRID      0x0eu
#define ADCSeq0_ISRID   0x0fu
#define ADCSeq1_ISRID   0x10u
#define ADCSeq2_ISRID   0x12u
#define ADCSeq3_ISRID   0x13u
#define Watchdog_ISRID  0x14u
#define Timer0A_ISRID   0x15u
#define Timer0B_ISRID   0x16u
#define Timer1A_ISRID   0x17u
#define Timer1B_ISRID   0x18u
#define Timer2A_ISRID   0x19u
#define Timer2B_ISRID   0x1au
#define Comp0_ISRID     0x1bu
#define Comp1_ISRID     0x1cu
#define Comp2_ISRID     0x1du
#define SysCtrl_ISRID   0x1eu
#define FlashCtrl_ISRID 0x1fu
#define GPIOPortF_ISRID 0x20u
#define GPIOPortG_ISRID 0x21u
#define GPIOPortH_ISRID 0x22u
#define UART2_ISRID     0x23u
#define SSI1_ISRID      0x24u
#define Timer3A_ISRID   0x25u
#define Timer3B_ISRID   0x26u
#define I2C1_ISRID      0x27u
#define QEI1_ISRID      0x28u
#define CAN0_ISRID      0x29u
#define CAN1_ISRID      0x2au
#define CAN2_ISRID      0x2bu
#define Hibernate_ISRID 0x2cu
#define USB0_ISRID      0x2du
#define PWMGen3_ISRID   0x2eu
#define uDMAST_ISRID    0x2fu
#define uDMAError_ISRID 0x30u
#define ADC1Seq0_ISRID  0x31u
#define ADC1Seq1_ISRID  0x32u
#define ADC1Seq2_ISRID  0x33u
#define ADC1Seq3_ISRID  0x34u
#define GPIOPortJ_ISRID 0x35u
#define GPIOPortK_ISRID 0x36u
#define GPIOPortL_ISRID 0x37u
#define SSI2_ISRID      0x38u
#define SSI3_ISRID      0x39u
#define UART3_ISRID     0x3au
#define UART4_ISRID     0x3bu
#define UART5_ISRID     0x3cu
#define UART6_ISRID     0x3du
#define UART7_ISRID     0x3eu
#define I2C2_ISRID      0x3fu
#define I2C3_ISRID      0x40u
#define Timer4A_ISRID   0x41u
#define Timer4B_ISRID   0x42u
#define Timer5A_ISRID   0x43u
#define Timer5B_ISRID   0x44u
#define WideTimer0A_ISRID 0x45u
#define WideTimer0B_ISRID 0x46u
#define WideTimer1A_ISRID 0x47u
#define WideTimer1B_ISRID 0x48u
#define WideTimer2A_ISRID 0x49u
#define WideTimer2B_ISRID 0x4au
#define WideTimer3A_ISRID 0x4bu
#define WideTimer3B_ISRID 0x4cu
#define WideTimer4A_ISRID 0x4du
#define WideTimer4B_ISRID 0x4eu
#define WideTimer5A_ISRID 0x4fu
#define WideTimer5B_ISRID 0x50u
#define FPU_ISRID       0x51u
#define I2C4_ISRID      0x52u
#define I2C5_ISRID      0x53u
#define GPIOPortM_ISRID 0x54u
#define GPIOPortN_ISRID 0x55u
#define QEI2_ISRID      0x56u
#define GPIOPortP0_ISRID 0x57u
#define GPIOPortP1_ISRID 0x58u
#define GPIOPortP2_ISRID 0x59u
#define GPIOPortP3_ISRID 0x5au
#define GPIOPortP4_ISRID 0x5bu
#define GPIOPortP5_ISRID 0x5cu
#define GPIOPortP6_ISRID 0x5du
#define GPIOPortP7_ISRID 0x5eu
#define GPIOPortQ0_ISRID 0x5fu
#define GPIOPortQ1_ISRID 0x60u
#define GPIOPortQ2_ISRID 0x61u
#define GPIOPortQ3_ISRID 0x62u
#define GPIOPortQ4_ISRID 0x63u
#define GPIOPortQ5_ISRID 0x64u
#define GPIOPortQ6_ISRID 0x65u
#define GPIOPortQ7_ISRID 0x66u
#define GPIOPortR_ISRID 0x67u
#define GPIOPortS_ISRID 0x68u
#define PWM1Gen0_ISRID  0x69u
#define PWM1Gen1_ISRID  0x6au
#define PWM1Gen2_ISRID  0x6bu
#define PWM1Gen3_ISRID  0x6cu
#define PWM1Fault_ISRID 0x6du

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
