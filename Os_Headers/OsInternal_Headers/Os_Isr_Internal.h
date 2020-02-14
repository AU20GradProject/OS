/*

    Written by : Bebo
    DATE : 7/2/2019
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

/*******************************************************************/



#endif /* OS_HEADERS_OSINTERNAL_HEADERS_OS_ISR_INTERNAL_H_ */
