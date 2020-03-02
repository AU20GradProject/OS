/*

    Written by : Bakr
    DATE : 18/2/2020
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

#define SCHEDULE_TABLE_1 0
#define SCHEDULE_TABLE_2 1

#define TABLES_NUMBER               2
#define TABLES_POINTS_NUMBER        4
#define TABLES_TASKS_NUMBER         4
#define TABLES_EVENTS_SET_NUMBER    0


#define EMPTY_NEXT_TABLE            -1

#define OS_TABLESS_OBJECT_CONGIFURATION \
{\
    {\
        .OsScheduleTableRepeating = FALSE,\
        .OsScheduleTableCounterRef = COUNTER_1,\
        .ExpiryPointsNumber = 2,\
        .FirstExpiryPoint = 0,\
        .OsScheduleTableDuration = 2000u,\
        .OsScheduleTblSyncStrategy = EXPLICIT,\
    }\
    ,\
    {\
        .OsScheduleTableRepeating = TRUE,\
        .OsScheduleTableCounterRef = COUNTER_1,\
        .ExpiryPointsNumber = 2,\
        .FirstExpiryPoint = 2,\
        .OsScheduleTableDuration = 2000u,\
        .OsScheduleTblSyncStrategy = EXPLICIT,\
    }\
}

#define OS_TABLESS_POINTS_OBJECT_CONGIFURATION \
{\
        {\
            .OsScheduleTblExpPointOffset = 1000,\
            .PointTasks = {1,0},\
            .OsScheduleTblAdjustableExpPoint = 0,\
        },\
        {\
            .OsScheduleTblExpPointOffset = 1000,\
            .PointTasks = {1,1},\
            .OsScheduleTblAdjustableExpPoint = 0,\
        },\
        {\
            .OsScheduleTblExpPointOffset = 1000,\
            .PointTasks = {1,2},\
            .OsScheduleTblAdjustableExpPoint = 0,\
        },\
        {\
            .OsScheduleTblExpPointOffset = 1000,\
            .PointTasks = {1,3},\
            .OsScheduleTblAdjustableExpPoint = 0,\
        },\
}
/* contains id for tasks to be activated by the schedule table's points */
#define OS_TABLESS_TASKS_OBJECT_CONGIFURATION \
{\
    0,7,2,9\
}


#define OS_TABLESS_TASKS_SET_OBJECT_CONGIFURATION \
{\
}

#define OS_TABLESS_EVENTS_SET_OBJECT_CONGIFURATION \
{\
}


#endif /* OS_CFG_OS_SCHEDULETABLE_CFG_H_ */
