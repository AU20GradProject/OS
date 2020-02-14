/*

    Written by : Bebo
    DATE : 7/2/2019
    AUTOSAR Version : 4.3.1
    DOC Name : AUTOSAR_SWS_OS.pdf
    Target : ARM TIVA_C TM4C123GH6PM

*/

#ifndef OS_HEADERS_OSINTERFACE_HEADERS_OS_GENERAL_H_
#define OS_HEADERS_OSINTERFACE_HEADERS_OS_GENERAL_H_


/*********************************************************************************************************/


/* enum type used for all status information the API services offer. Naming convention:
 * all errors for API services start with E_.
 * Those reserved for the operating system will begin with E_OS_ */

#define E_OS_ACCESS     1u
#define E_OS_CALLEVEL   2u
#define E_OS_ID         3u
#define E_OS_LIMIT      4u
#define E_OS_NOFUNC     5u
#define E_OS_RESOURCE   6u
#define E_OS_STATE      7u
#define E_OS_VALUE      8u


/* enum data type represents the application mode, max allowed modes is 8 , elements name defined by user and exist in Os_General_Cfg.h */

#define NOT_AUTOSTART       0x00u
#define OSDEFAULTAPPMODE    0x01u  /* Default application mode, always a valid parameter to StartOS */
typedef VAR( uint8, TYPEDEF ) AppModeType ;

/*********************************************************************************************************/




#endif /* OS_HEADERS_OSINTERFACE_HEADERS_OS_GENERAL_H_ */
