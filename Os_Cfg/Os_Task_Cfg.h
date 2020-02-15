/*

    Written by : Bebo
    DATE : 7/2/2019
    AUTOSAR Version : 4.3.1
    DOC Name : AUTOSAR_SWS_OS.pdf
    Target : ARM TIVA_C TM4C123GH6PM

*/


#ifndef OS_CFG_OS_TASK_CFG_H_
#define OS_CFG_OS_TASK_CFG_H_

/**************************************************************************/

#define TASK_NON        0x55u
#define TASK_FULL       0xAAu

#define TASKS_NUMBER    2

#define TOTAL_TASKS_RESOURCES_NUMBER    2


/* number of priorities allowed for tasks 0~7 */
#define TASK_PRIORITIES_NUMBER 8

/* number of tasks allowed to have same priority + 1*/
#define TASKS_PER_PRIORITY 33

/* stack size of every task in number of words */
#define TASK_STACK_SIZE 32

/* number of tasks not in suspended state */
#define TASK_PCBS_NUMBER 75

/* maximum number of tasks suspended or not allowed in the system */
#define MAX_TASKS_NUMBER    255


/**************************************************************************/

#define OS_TASKS_RESOURCES_OBJECT_CONGIFURATION \
{\
    RESORCE_1 \
    ,\
    RESORCE_3 \
}


/**************************************************************************/

#define OS_TASKS_OBJECT_CONGIFURATION \
{\
    {\
        .OsTaskSchedule = TASK_NON \
        ,\
        .OsTaskActivation = 2 \
        ,\
        .OsTaskPriority = 3 \
        ,\
        .OsTaskCeillingPriority = 3 \
        ,\
        .OsTaskResourcesNumber = 0 \
        ,\
        .OsTaskResourceRef = 0 \
        ,\
        .OsTaskAppModeRef = \
        (\
                OSDEFAULTAPPMODE \
        )\
        ,\
        .OsTaskEventRef = \
        (\
                OS_EVENT_MASK_1 | \
                OS_EVENT_MASK_2 | \
                OS_EVENT_MASK_4 \
        )\
    }\
    ,\
    {\
        .OsTaskSchedule = TASK_FULL \
        ,\
        .OsTaskActivation = 1 \
        ,\
        .OsTaskPriority = 4 \
        ,\
        .OsTaskCeillingPriority = 6 \
        ,\
        .OsTaskResourcesNumber = 2 \
        ,\
        .OsTaskResourceRef = 0 \
        ,\
        .OsTaskAppModeRef = \
        (\
                OSDEFAULTAPPMODE \
        )\
        ,\
        .OsTaskEventRef = OS_EVENT_BASIC_TASK \
       }\
}


#define TASKS_PCB_INDEX_ARRAY_CONFIGURATION \
{\
    VAL_2(0xFFu)\
}

#endif /* OS_CFG_OS_TASK_CFG_H_ */
