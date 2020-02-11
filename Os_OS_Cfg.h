/*

    Written by : Bebo
    DATE : 7/2/2019
    AUTOSAR Version : 4.3.1
    DOC Name : AUTOSAR_SWS_OS.pdf
    Target : ARM TIVA_C TM4C123GH6PM

*/

#ifndef OS_OS_CFG_H_
#define OS_OS_CFG_H_



/************************************************************************************************/

/************************************************************************************************/

/* Os */
/* 10.2.20 */

/* OsHooks */
/* 10.2.16 */

#define SC1     0x00u
#define SC2     0x01u
#define SC3     0x02u
#define SC4     0x03u


#define OS_STANDARD    0x55u
#define OS_EXTENDED    0xAAu


#define OS_OS_OBJECT_CONGIFURATION \
{ \
\
 .OsStackMonitoring = TRUE\
 ,\
 .OsUseGetServiceId = FALSE\
 ,\
 .OsUseParameterAccess = FALSE\
 ,\
 .OsUseResScheduler = TRUE\
 ,\
 .OsErrorHook = FALSE\
 ,\
 .OsPostTaskHook = FALSE\
 ,\
 .OsPreTaskHook = FALSE\
 ,\
 .OsProtectionHook = FALSE\
 ,\
 .OsShutdownHook = FALSE\
 ,\
 .OsStartupHook = FALSE\
 ,\
 .OsNumberOfCores = 0x01u\
 ,\
 .OsScalabilityClass = SC1\
 ,\
 .OsStatus = OS_EXTENDED\
\
}




/************************************************************************************************/


/************************************************************************************************/

#endif /* OS_OS_CFG_H_ */
