/*

    Written by : Bebo
    DATE : 7/2/2019
    AUTOSAR Version : 4.3.1
    DOC Name : AUTOSAR_SWS_OS.pdf
    Target : ARM TIVA_C TM4C123GH6PM

*/

#ifndef OS_HEADERS_OSINTERNAL_HEADERS_OS_GENERAL_INTERNAL_H_
#define OS_HEADERS_OSINTERNAL_HEADERS_OS_GENERAL_INTERNAL_H_

/*******************************************************************/

typedef struct
{
    VAR( boolean, AUTOMATIC )   OsStackMonitoring ;         /* Select stack monitoring of Tasks/Category 2 ISRs (true: Stacks are monitored) */
    VAR( boolean, AUTOMATIC )   OsUseGetServiceId ;         /* determine whether access macros to get service id which caused last error is defined or not */
    VAR( boolean, AUTOMATIC )   OsUseParameterAccess ;      /* determine whether access macros to get values of parameter of service which caused last error is defined or not */
    VAR( boolean, AUTOMATIC )   OsUseResScheduler ;         /* defines whether the resource RES_SCHEDULER is used within the application. */
    VAR( boolean, AUTOMATIC )   OsErrorHook ;               /* whether Error hook as defined by OSEK called in case of error ( true: Hook is called ) */
    VAR( boolean, AUTOMATIC )   OsPostTaskHook ;            /* as post hook but here before old task is leave running state */
    VAR( boolean, AUTOMATIC )   OsPreTaskHook ;             /* as pre hook but here after new task is enter running state */
    VAR( boolean, AUTOMATIC )   OsProtectionHook ;          /* enable/disable the call to the (user supplied) protection hook ( true: hook is called )*/
    VAR( boolean, AUTOMATIC )   OsShutdownHook ;            /* as previous hooks but for hook called when shutdown is requested */
    VAR( boolean, AUTOMATIC )   OsStartupHook ;             /* as previous hooks but for hook called after os startup and before scheduler */
    VAR( uint8, AUTOMATIC )     OsNumberOfCores ;           /* Maximum number of cores that are controlled by the OS */
    VAR( uint8, AUTOMATIC )     OsScalabilityClass ;        /* determine supported scalability class by OS */
    VAR( uint8, AUTOMATIC )     OsStatus ;                  /* The Status attribute specifies whether a system with standard or extended status has to be used */

} OsOS ;

/*******************************************************************/


#endif /* OS_HEADERS_OSINTERNAL_HEADERS_OS_GENERAL_INTERNAL_H_ */
