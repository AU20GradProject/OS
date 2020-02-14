/*

    Written by : Bebo
    DATE : 7/2/2019
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



#endif /* OS_COUNTER_INTERNAL_H_ */
