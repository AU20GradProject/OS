/*

    Written by : Bebo
    DATE : 7/2/2019
    AUTOSAR Version : 4.3.1
    DOC Name : AUTOSAR_SWS_OS.pdf
    Target : ARM TIVA_C TM4C123GH6PM

*/




#include "..\..\Os_Headers\OsInterface_Headers\Os.h"
#include "..\..\Os_Headers\OsInternal_Headers\Os_Internal.h"
#include "..\..\Os_Headers\OsInternal_Headers\Os_ExternalVariables.h"

/* list of resources accessed by every task */
CONST( ResourceType, OS_CONFIG_DATA ) OsIsrsResources_Array [ TOTAL_ISRS_RESOURCES_NUMBER ] = OS_ISRS_RESOURCES_OBJECT_CONGIFURATION ;

/* represent configuration data of every task */
CONST( OsIsr, OS_CONFIG_DATA ) OsIsr_Array [ ISRS_NUMBER ] = OS_ISRS_OBJECT_CONGIFURATION ;
