/*

    Written by : Bebo
    DATE : 7/2/2019
    AUTOSAR Version : 4.3.1
    DOC Name : AUTOSAR_SWS_OS.pdf
    Target : ARM TIVA_C TM4C123GH6PM

*/

#ifndef OS_HEADERS_OSINTERFACE_HEADERS_OS_H_
#define OS_HEADERS_OSINTERFACE_HEADERS_OS_H_

#include "..\..\Common\Std_Types.h"
#include "..\..\Common\Os_MemMap.h"

#include "..\..\Os_Cfg\Os_Cfg.h"

#include "Os_General.h"
#include "Os_Task.h"
#include "Os_Isr.h"
#include "Os_Resource.h"
#include "Os_Event.h"
#include "Os_Counter.h"
#include "Os_Alarm.h"
#include "Os_ScheduleTable.h"
#include "../OsInternal_Headers/Os_Gpt_Internal.h" /* used in testing the OS in main function */ 

#define INVALID_HOOK 0xFFU
/* enum data type identifies an Hook routine. */
typedef VAR( uint8, TYPEDEF ) HOOKType ;



#endif /* OS_HEADERS_OSINTERFACE_HEADERS_OS_H_ */
