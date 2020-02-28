/*

    Written by : Bebo
    DATE : 7/2/2019
    AUTOSAR Version : 4.3.1
    DOC Name : AUTOSAR_SWS_OS.pdf
    Target : ARM TIVA_C TM4C123GH6PM

*/




#include "..\..\Os_Headers\OsInterface_Headers\Os.h"
#include "..\..\Os_Headers\OsInternal_Headers\Os_Internal.h"



CONST( OsCounter, OS_CONFIG_DATA ) OsCounter_Array [ COUNTERS_NUMBER ] = OS_COUNTERS_OBJECT_CONGIFURATION ;

VAR( OsCounterInternal, OS_DATA)   OsCounterInternal_Array [COUNTERS_NUMBER ] = OS_COUNTERS_INTERNAL_OBJECT;

