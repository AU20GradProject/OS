/*
 * Os_General_Cfg.h
 *
 *  Created on: Feb 13, 2020
 *      Author: ME
 */

#ifndef OS_CFG_OS_GENERAL_CFG_H_
#define OS_CFG_OS_GENERAL_CFG_H_


/************************************************************************************************/


/* Os */
/* 10.2.20 */

/* OsHooks */
/* 10.2.16 */

#define OS_SC1     0x00u
#define OS_SC2     0x01u
#define OS_SC3     0x02u
#define OS_SC4     0x03u


#define OS_STANDARD    0x55u
#define OS_EXTENDED    0xAAu

#define OS_MODE         OS_EXTENDED

#define APPMODE_INVALID     0xFFFFu

/* list appmodes defined by user in configuration tool */
#define OSAPPMPDE_1         0X02u

#define OS_APPMODES_NUMBER          2

#define AUTOSTART_TASKS_NUMBER      2

#define AUTOSTART_ALARMS_NUMBER     2

#define AUTOSTART_TABLESS_NUMBER    2



/* used to define OS object */
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
 .OsScalabilityClass = OS_SC1\
 ,\
 .OsStatus = OS_EXTENDED\
\
}


#define OS_APPMODES_OBJECT_CONGIFURATION \
{\
}

#define OS_AUTOSTART_TASKS_OBJECT_CONGIFURATION \
{\
}


#define OS_AUTOSTART_ALARMS_OBJECT_CONGIFURATION \
{\
}


#define OS_AUTOSTART_TABLES_OBJECT_CONGIFURATION \
{\
}

#define OS_AUTOSTART_SETTING_ALARMS_OBJECT_CONGIFURATION \
{\
}

#define OS_AUTOSTART_SETTING_TABLES_OBJECT_CONGIFURATION \
{\
}

/************************************************************************************************/


#endif /* OS_CFG_OS_GENERAL_CFG_H_ */
