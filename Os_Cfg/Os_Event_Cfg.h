/*

    Written by : Bebo
    DATE : 7/2/2019
    AUTOSAR Version : 4.3.1
    DOC Name : AUTOSAR_SWS_OS.pdf
    Target : ARM TIVA_C TM4C123GH6PM

*/

#ifndef OS_CFG_OS_EVENT_CFG_H_
#define OS_CFG_OS_EVENT_CFG_H_


#define OS_EVENTS_NUMBER   4u

#define OS_EVENT_BASIC_TASK 0x00000000u

#define OS_EVENT_MASK_1     0x00000001u

#define OS_EVENT_MASK_2     0x00000002u

#define OS_EVENT_MASK_3     0x00000004u

#define OS_EVENT_MASK_4     0x00000008u



#define OS_EVENTS_OBJECT_CONGIFURATION \
{\
    OS_EVENT_MASK_1\
    ,\
    OS_EVENT_MASK_2\
    ,\
    OS_EVENT_MASK_3\
    ,\
    OS_EVENT_MASK_4\
}

#endif /* OS_CFG_OS_EVENT_CFG_H_ */
