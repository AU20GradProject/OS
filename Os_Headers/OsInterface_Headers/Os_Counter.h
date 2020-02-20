/*

    Written by : Bebo
    DATE : 7/2/2019
    AUTOSAR Version : 4.3.1
    DOC Name : AUTOSAR_SWS_OS.pdf
    Target : ARM TIVA_C TM4C123GH6PM

*/

#ifndef OS_HEADERS_OSINTERFACE_HEADERS_OS_COUNTER_H_
#define OS_HEADERS_OSINTERFACE_HEADERS_OS_COUNTER_H_

typedef VAR( uint8, TYPEDEF ) CounterType ;


typedef VAR( uint32, TYPEDEF ) TickType ;

typedef P2VAR(TickType, TYPEDEF, VAR) TickRefType;



FUNC( StatusType, OS_CODE) IncrementCounter( CounterType CounterID );

FUNC( StatusType, OS_CODE) GetCounterValue( CounterType CounterID, TickRefType Value );

FUNC( StatusType, OS_CODE) GetElapsedValue( CounterType CounterID, TickRefType Value, TickRefType ElapsedValue );


#endif /* OS_HEADERS_OSINTERFACE_HEADERS_OS_COUNTER_H_ */
