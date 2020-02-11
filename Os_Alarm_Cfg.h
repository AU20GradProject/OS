/*

    Written by : Bebo
    DATE : 7/2/2019
    AUTOSAR Version : 4.3.1
    DOC Name : AUTOSAR_SWS_OS.pdf
    Target : ARM TIVA_C TM4C123GH6PM

*/



#ifndef OS_ALARM_CFG_H_
#define OS_ALARM_CFG_H_


#define ALARM_ABSOLUTE  0x55u
#define ALARM_RELATIVE  0xAAu


#define ALARMS_NUMBER   3u

#define ALARM_ACTIVATE_TASK             0x01u
#define ALARM_CALL_BACK                 0x02u
#define ALARM_INCREMENT_COUNTER         0x04u
#define ALARM_SET_EVENT                 0x08u

#define OS_ALARMS_OBJECT_CONGIFURATION \
{\
}


#endif /* OS_ALARM_CFG_H_ */
