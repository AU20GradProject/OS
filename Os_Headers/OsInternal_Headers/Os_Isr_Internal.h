/*

    Created by : Ahmad HEGAZY
    DATE : 15/2/2019
    AUTOSAR Version : 4.3.1
    DOC Name : AUTOSAR_SWS_OS.pdf
    Target : ARM TIVA_C TM4C123GH6PM

*/

#ifndef OS_HEADERS_OSINTERNAL_HEADERS_OS_ISR_INTERNAL_H_
#define OS_HEADERS_OSINTERNAL_HEADERS_OS_ISR_INTERNAL_H_


/*******************************************************************/

typedef struct
{
    /*  specifies the category of this ISR. */
    VAR( uint8, AUTOMATIC ) OsIsrCategory ;

    /*  ceiling priority of Isr in case it access resources if not then it = 0  */
    VAR( uint8, AUTOMATIC ) OsIsrCeillingPriority ;

    /* defines number of resources accessed by Isr */
    VAR( uint8, AUTOMATIC ) OsIsrResourcesNumber ;

    /* defines index of first resource accessed by Isr in IsrReources list*/
    VAR( uint16, AUTOMATIC ) OsIsrResourceRef ;


} OsIsr;


#define NoDisableActive 0x00u
#define DisAllIntActive 0x01u
#define SuspendAllIntActive 0x02u
#define SuspendOSIntActive 0x03u

/* enum contains the called interrupt disable function */
typedef VAR( uint8, TYPEDEF ) ActiveIsrDisableType;

/* Variable contains the called interrupt disable function, if no function is called default value is NoDisableActive*/
VAR(ActiveIsrDisableType, AUTOMATIC) ActiveIsrDisable;

/* PEND registers addresses */
#define PEND0_REG_ADDR (*(( volatile P2VAR( uint32, AUTOMATIC, REGSPACE ) ) 0xE000E200 ))
#define PEND1_REG_ADDR (*(( volatile P2VAR( uint32, AUTOMATIC, REGSPACE ) ) 0xE000E204 ))
#define PEND2_REG_ADDR (*(( volatile P2VAR( uint32, AUTOMATIC, REGSPACE ) ) 0xE000E208 ))
#define PEND3_REG_ADDR (*(( volatile P2VAR( uint32, AUTOMATIC, REGSPACE ) ) 0xE000E20C ))
#define PEND4_REG_ADDR (*(( volatile P2VAR( uint32, AUTOMATIC, REGSPACE ) ) 0xE000E210 ))

/* Clear PEND registers addresses */
#define UNPEND0_REG_ADDR (*(( volatile P2VAR( uint32, AUTOMATIC, REGSPACE ) ) 0xE000E280 ))
#define UNPEND1_REG_ADDR (*(( volatile P2VAR( uint32, AUTOMATIC, REGSPACE ) ) 0xE000E284 ))
#define UNPEND2_REG_ADDR (*(( volatile P2VAR( uint32, AUTOMATIC, REGSPACE ) ) 0xE000E288 ))
#define UNPEND3_REG_ADDR (*(( volatile P2VAR( uint32, AUTOMATIC, REGSPACE ) ) 0xE000E28C ))
#define UNPEND4_REG_ADDR (*(( volatile P2VAR( uint32, AUTOMATIC, REGSPACE ) ) 0xE000E290 ))

/* PEND status store variables */
VAR(uint32, AUTOMATIC) PEND0;
VAR(uint32, AUTOMATIC) PEND1;
VAR(uint32, AUTOMATIC) PEND2;
VAR(uint32, AUTOMATIC) PEND3;
VAR(uint32, AUTOMATIC) PEND4;

VAR(uint8, AUTOMATIC) suspendCount;

/*******************************************************************/

#define END_PRIVILEGE  __asm ( " MRS R10, CONTROL " ) ;\
                       __asm ( " ORR R10, R10, #0x01 " ) ;\
                       __asm ( " MSR CONTROL, R10 " )

#endif /* OS_HEADERS_OSINTERNAL_HEADERS_OS_ISR_INTERNAL_H_ */
