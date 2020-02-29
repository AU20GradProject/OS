/*

    Written by : Bakr
    DATE : 18/2/2020
    AUTOSAR Version : 4.3.1
    DOC Name : AUTOSAR_SWS_OS.pdf
    Target : ARM TIVA_C TM4C123GH6PM

*/

#ifndef OS_HEADERS_OSINTERNAL_HEADERS_OS_COUNTER_INTERNAL_H_
#define OS_HEADERS_OSINTERNAL_HEADERS_OS_COUNTER_INTERNAL_H_



/*******************************************************************/

typedef struct
{
    /* enum contains the natural type or unit of the counter. */
    VAR( CounterType, AUTOMATIC ) OsCounterType ;

    /* specifies the number of ticks required to reach a counterspecific unit.
     * The interpretation is implementation-specific */
    VAR( TickType, AUTOMATIC ) OsCounterTicksPerBase ;

    /* Maximum possible allowed value of the system counter in ticks */
    VAR( TickType, AUTOMATIC ) OsCounterMaxAllowedValue ;

    /* specifies the minimum allowed number of counter ticks for a cyclic alarm linked to the counter */
    VAR( TickType, AUTOMATIC ) OsCounterMinCycle ;

} OsCounter ;

/*******************************************************************/
typedef struct
{
    /* Contains the current value of the counter  */
    VAR( TickType , AUTOMATIC ) OsCounterVal;

    /* Incremented at each system tick until it reaches OsCounterTicksPerBase value this OsCounter Value is Incremented */
    VAR( TickType , AUTOMATIC ) OsCounterTicksValue;

} OsCounterInternal;

typedef P2VAR(OsCounterInternal, TYPDEF,TYPDEF)   OsCounterRefInternal;

typedef P2CONST(OsCounter, TYPEDEF,TYPEDEF)   OsCounterRef;


#endif /* OS_COUNTER_INTERNAL_H_ */
