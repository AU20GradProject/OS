/*

    Written by : Bebo
    DATE : 7/2/2019
    AUTOSAR Version : 4.3.1
    DOC Name : AUTOSAR_SWS_OS.pdf
    Target : ARM TIVA_C TM4C123GH6PM

*/
#ifndef OS_CFG_OS_SCHEDULETABLE_CFG_H_
#define OS_CFG_OS_SCHEDULETABLE_CFG_H_


#define TABLE_ABSOLUTE      0x55u
#define TABLE_SYNCHRON      0xAAu

#define IMPLICIT        0u
#define EXPLICIT        1u


#define TABLES_NUMBER               1
#define TABLES_POINTS_NUMBER        2
#define TABLES_TASKS_NUMBER         2
#define TABLES_EVENTS_SET_NUMBER    2


#define EMPTY_NEXT_TABLE            -1

#define OS_TABLESS_OBJECT_CONGIFURATION \
{\
    {\
        .OsScheduleTableRepeating = TRUE,\
        .OsScheduleTableCounterRef = COUNTER_1,\
        .ExpiryPointsNumber = 2,\
        .FirstExpiryPoint = 0,\
        .OsScheduleTableDuration = 2000u,\
        .OsScheduleTblSyncStrategy = EXPLICIT,\
    }\
}

#define OS_TABLESS_POINTS_OBJECT_CONGIFURATION \
{\
        {\
            .OsScheduleTblExpPointOffset = 1000,\
            .PointTasks = 1,\
            .PointEvents = 1,\
            .OsScheduleTblAdjustableExpPoint = 0,\
        },\
        {\
            .OsScheduleTblExpPointOffset = 1500,\
            .PointTasks = 1,\
            .PointEvents = 1,\
            .OsScheduleTblAdjustableExpPoint = 0,\
        }\
}
/* contains id for tasks to be activated by the schedule table's points */
#define OS_TABLESS_TASKS_OBJECT_CONGIFURATION \
{\
    0,1\
}


#define OS_TABLESS_TASKS_SET_OBJECT_CONGIFURATION \
{\
    0,\
    1\
}

#define OS_TABLESS_EVENTS_SET_OBJECT_CONGIFURATION \
{\
    0xFFFFFFF,\
    0x00000000\
}


#endif /* OS_CFG_OS_SCHEDULETABLE_CFG_H_ */
