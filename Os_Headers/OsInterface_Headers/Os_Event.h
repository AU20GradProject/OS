/*

    Written by : Bebo
    DATE : 7/2/2019
    AUTOSAR Version : 4.3.1
    DOC Name : AUTOSAR_SWS_OS.pdf
    Target : ARM TIVA_C TM4C123GH6PM

*/

#ifndef OS_HEADERS_OSINTERFACE_HEADERS_OS_EVENT_H_
#define OS_HEADERS_OSINTERFACE_HEADERS_OS_EVENT_H_

/* Data type of the event mask */
typedef VAR( uint64, TYPEDEF ) EventMaskType ;

/* Reference to an event mask */
typedef P2VAR ( EventMaskType, TYPEDEF, TYPEDEF ) EventMaskRefType ;

#endif /* OS_HEADERS_OSINTERFACE_HEADERS_OS_EVENT_H_ */
