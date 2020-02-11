/*

    Written by : Bebo
    DATE : 7/2/2019
    AUTOSAR Version : 4.3.1
    DOC Name : AUTOSAR_SWS_OS.pdf
    Target : ARM TIVA_C TM4C123GH6PM

*/


#ifndef OS_COUNTER_CFG_H_
#define OS_COUNTER_CFG_H_


#define COUNTERS_NUMBER 2


#define COUNTER_1       0
#define COUNTER_2       1


#define COUNTER_HARDWARE    0x55u
#define COUNTER_SOFTWARE    0xAAu


#define OS_COUNTERS_OBJECT_CONGIFURATION \
{\
    {\
    .OsCounterType = COUNTER_HARDWARE \
    ,\
    .OsCounterTicksPerBase = 100u \
    ,\
    .OsCounterMaxAllowedValue = 1000u \
    ,\
    .OsCounterMinCycle = 20u \
    }\
    ,\
    {\
    .OsCounterType = COUNTER_SOFTWARE \
    ,\
    .OsCounterTicksPerBase = 200u \
    ,\
    .OsCounterMaxAllowedValue = 4000u \
    ,\
    .OsCounterMinCycle = 50u \
    }\
}



#endif /* OS_COUNTER_CFG_H_ */
