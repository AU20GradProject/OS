/*

    Written by : Bebo
    DATE : 7/2/2019
    AUTOSAR Version : 4.3.1
    DOC Name : AUTOSAR_SWS_OS.pdf
    Target : ARM TIVA_C TM4C123GH6PM

*/


#ifndef OS_TASK_CFG_H_
#define OS_TASK_CFG_H_

#define NON     0x55u
#define FULL    0xAAu

#define TASKS_NUMBER 2

#define OSDEFAULTAPPMODE 0x01u

#define OS_TASKS_OBJECT_CONGIFURATION \
{\
    {\
        .OsTaskAutostart = TRUE \
        ,\
        .OsTaskSchedule = NON \
        ,\
        .OsTaskActivation = 2 \
        ,\
        .OsTaskPriority = 3 \
        ,\
        .OsTaskAppModeRef =  OSDEFAULTAPPMODE \
        ,\
        .OsTaskResourceRef = 5 \
        ,\
        .OsTaskEventRef = OS_EVENT_MASK_4 \
    }\
    ,\
    {\
        .OsTaskAutostart = TRUE \
        ,\
        .OsTaskSchedule = FULL \
        ,\
        .OsTaskActivation = 1 \
        ,\
        .OsTaskPriority = 4 \
        ,\
        .OsTaskAppModeRef =  OSDEFAULTAPPMODE \
        ,\
        .OsTaskResourceRef = 7 \
        ,\
        .OsTaskEventRef = OS_EVENT_BASIC_TASK \
       }\
}

#endif /* OS_TASK_CFG_H_ */
