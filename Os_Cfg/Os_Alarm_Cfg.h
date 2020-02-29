/*

    Written by : Bakr
    DATE : 18/2/2020
    AUTOSAR Version : 4.3.1
    DOC Name : AUTOSAR_SWS_OS.pdf
    Target : ARM TIVA_C TM4C123GH6PM

*/



#ifndef OS_CFG_OS_ALARM_CFG_H_
#define OS_CFG_OS_ALARM_CFG_H_


#define ALARM_ABSOLUTE  0x55u
#define ALARM_RELATIVE  0xAAu


#define ALARMS_NUMBER   2u

#define ALARM_1         0u

#define ALARM_ACTIVATE_TASK             0x01u
#define ALARM_CALL_BACK                 0x02u
#define ALARM_INCREMENT_COUNTER         0x04u
#define ALARM_SET_EVENT                 0x08u
#define ALARM_NOFUNC                    0x09u

#define AUTOSTART                       0x55u

#define ALARM_FINISHED                  0x0u
#define ALARM_ONESHOT                   0x1u
#define ALARM_CYCLIC                    0x2u

#define ALARM_ACTION_INC_COUNTER        0x13u
#define ALARM_ACTION_ACT_TASK           0x10u
#define ALARM_ACTION_CALLBACK           0x11u
#define ALARM_ACTION_SET_EVENT          0x12u

#define OS_ALARMS_OBJECT_CONGIFURATION \
{\
    {\
    .OsAlarmCounterRef = COUNTER_1\
    ,\
    .AlarmAction = \
        {\
            .ActionType = ALARM_ACTION_CALLBACK \
        }\
    }\
}

#define OS_ALARMS_INTERNAL_OBJECT_CONFIGURATION \
{\
    {\
        .AlarmExpiryTickValue = 0u \
        ,\
        .Cycle = 0 \
        ,\
        .InUse = FALSE\
    }\
}

#endif /* OS_CFG_OS_ALARM_CFG_H_ */
