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

/**************************************************************************/

#define TASKS_NUMBER    14

#define TASK_RED_ON         0
#define TASK_GREEN_ON       1
#define TASK_BLUE_ON        2
#define TASK_YELLOW_ON      3
#define TASK_BURBULE_ON     4
#define TASK_AQUA_ON        5
#define TASK_WHITE_ON       6
#define TASK_RED_OFF        7
#define TASK_GREEN_OFF      8
#define TASK_BLUE_OFF       9
#define TASK_YELLOW_OFF     10
#define TASK_BURBULE_OFF    11
#define TASK_AQUA_OFF       12
#define TASK_WHITE_OFF      13


#define TOTAL_TASKS_RESOURCES_NUMBER    2

/**************************************************************************/



/* number of priorities allowed for tasks 0~7 */
#define TASK_PRIORITIES_NUMBER 8

/* number of tasks allowed to have same priority + 1*/
#define TASKS_PER_PRIORITY 33

/* stack size of every task in number of double words */
#define TASK_STACK_SIZE 32

/* number of tasks not in suspended state  max is 75*/
#define TASK_PCBS_NUMBER TASKS_NUMBER

/* maximum number of tasks suspended or not allowed in the system */
#define MAX_TASKS_NUMBER    255

/**************************************************************************/

/* where 0x2000.8000 is the adress of MSP which loaded form top of vector table */
#define OS_MSP_STACK_FRAME_ADDRESS  (( ( volatile P2VAR( OsStackFrame_MSP, AUTOMATIC, REGSPACE ) ) 0x20008000 ) - 1 )


/**************************************************************************/



/**************************************************************************/

#define OS_TASKS_OBJECT_CONGIFURATION \
{\
    {\
        .OsTaskSchedule = TASK_FULL \
        ,\
        .OsTaskActivation = 1 \
        ,\
        .OsTaskPriority = 0 \
        ,\
        .OsTaskCeilingPriority_Internal = 0x04u \
        ,\
        .OsResourceRef = \
        (\
                OS_RESORCE_0_MASK | \
                OS_RESORCE_1_MASK | \
                OS_RESORCE_2_MASK | \
                OS_RESORCE_3_MASK | \
                OS_RESORCE_4_MASK \
        )\
        ,\
        .OsTaskEventRef = \
        (\
                OS_EVENT_BASIC_TASK \
        )\
    }\
    ,\
    {\
        .OsTaskSchedule = TASK_FULL \
        ,\
        .OsTaskActivation = 2 \
        ,\
        .OsTaskPriority = 1 \
        ,\
        .OsTaskCeilingPriority_Internal = 0x01u \
        ,\
        .OsResourceRef = OS_NO_RESOURCE_MASK \
        ,\
        .OsTaskEventRef = OS_EVENT_BASIC_TASK \
    }\
    ,\
    {\
        .OsTaskSchedule = TASK_FULL \
        ,\
        .OsTaskActivation = 1 \
        ,\
        .OsTaskPriority = 2 \
        ,\
        .OsTaskCeilingPriority_Internal = 0x02u \
        ,\
        .OsResourceRef = OS_NO_RESOURCE_MASK \
        ,\
        .OsTaskEventRef = OS_EVENT_BASIC_TASK \
    }\
    ,\
    {\
        .OsTaskSchedule = TASK_FULL \
        ,\
        .OsTaskActivation = 1 \
        ,\
        .OsTaskPriority = 3 \
        ,\
        .OsTaskCeilingPriority_Internal = 0x03u \
        ,\
        .OsResourceRef = OS_NO_RESOURCE_MASK \
        ,\
        .OsTaskEventRef = OS_EVENT_BASIC_TASK \
    }\
    ,\
    {\
        .OsTaskSchedule = TASK_FULL \
        ,\
        .OsTaskActivation = 1 \
        ,\
        .OsTaskPriority = 4 \
        ,\
        .OsTaskCeilingPriority_Internal = 0x04u \
        ,\
        .OsResourceRef = OS_NO_RESOURCE_MASK \
        ,\
        .OsTaskEventRef = OS_EVENT_BASIC_TASK \
    }\
    ,\
    {\
        .OsTaskSchedule = TASK_FULL \
        ,\
        .OsTaskActivation = 1 \
        ,\
        .OsTaskPriority = 5 \
        ,\
        .OsTaskCeilingPriority_Internal = 0x05u \
        ,\
        .OsResourceRef = OS_NO_RESOURCE_MASK \
        ,\
        .OsTaskEventRef = OS_EVENT_BASIC_TASK \
    }\
    ,\
    {\
        .OsTaskSchedule = TASK_FULL \
        ,\
        .OsTaskActivation = 1 \
        ,\
        .OsTaskPriority = 6 \
        ,\
        .OsTaskCeilingPriority_Internal = 0x06u \
        ,\
        .OsResourceRef = OS_NO_RESOURCE_MASK \
        ,\
        .OsTaskEventRef = OS_EVENT_BASIC_TASK \
    }\
    ,\
    {\
        .OsTaskSchedule = TASK_FULL \
        ,\
        .OsTaskActivation = 1 \
        ,\
        .OsTaskPriority = 7 \
        ,\
        .OsTaskCeilingPriority_Internal = 0x07u \
        ,\
        .OsResourceRef = OS_NO_RESOURCE_MASK \
        ,\
        .OsTaskEventRef = \
        (\
                OS_EVENT_MASK_1 | \
                OS_EVENT_MASK_2 | \
                OS_EVENT_MASK_3 | \
                OS_EVENT_MASK_4 \
        )\
    }\
    ,\
    {\
        .OsTaskSchedule = TASK_FULL \
        ,\
        .OsTaskActivation = 1 \
        ,\
        .OsTaskPriority = 7 \
        ,\
        .OsTaskCeilingPriority_Internal = 0x07u \
        ,\
        .OsResourceRef = OS_NO_RESOURCE_MASK \
        ,\
        .OsTaskEventRef = OS_EVENT_BASIC_TASK \
    }\
    ,\
    {\
        .OsTaskSchedule = TASK_FULL \
        ,\
        .OsTaskActivation = 1 \
        ,\
        .OsTaskPriority = 6 \
        ,\
        .OsTaskCeilingPriority_Internal = 0x06u \
        ,\
        .OsResourceRef = OS_NO_RESOURCE_MASK \
        ,\
        .OsTaskEventRef = OS_EVENT_BASIC_TASK \
    }\
    ,\
    {\
        .OsTaskSchedule = TASK_FULL \
        ,\
        .OsTaskActivation = 1 \
        ,\
        .OsTaskPriority = 5 \
        ,\
        .OsTaskCeilingPriority_Internal = 0x05u \
        ,\
        .OsResourceRef = OS_NO_RESOURCE_MASK \
        ,\
        .OsTaskEventRef = OS_EVENT_BASIC_TASK \
    }\
    ,\
    {\
        .OsTaskSchedule = TASK_FULL \
        ,\
        .OsTaskActivation = 1 \
        ,\
        .OsTaskPriority = 4 \
        ,\
        .OsTaskCeilingPriority_Internal = 0x04u \
        ,\
        .OsResourceRef = OS_NO_RESOURCE_MASK \
        ,\
        .OsTaskEventRef = OS_EVENT_BASIC_TASK \
    }\
    ,\
    {\
        .OsTaskSchedule = TASK_FULL \
        ,\
        .OsTaskActivation = 1 \
        ,\
        .OsTaskPriority = 3 \
        ,\
        .OsTaskCeilingPriority_Internal = 0x03u \
        ,\
        .OsResourceRef = OS_NO_RESOURCE_MASK \
        ,\
        .OsTaskEventRef = OS_EVENT_BASIC_TASK \
    }\
    ,\
    {\
        .OsTaskSchedule = TASK_FULL \
        ,\
        .OsTaskActivation = 1 \
        ,\
        .OsTaskPriority = 2 \
        ,\
        .OsTaskCeilingPriority_Internal = 0x02u \
        ,\
        .OsResourceRef = OS_NO_RESOURCE_MASK \
        ,\
        .OsTaskEventRef = OS_EVENT_BASIC_TASK \
    }\
}


#define TASKS_PCB_INDEX_ARRAY_CONFIGURATION \
{\
    VAL_8(0xFFu),VAL_4(0xFFu),VAL_2(0xFFu)\
}

#endif /* OS_CFG_OS_TASK_CFG_H_ */
