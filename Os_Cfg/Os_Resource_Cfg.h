/*

    Written by : Bebo
    DATE : 7/2/2019
    AUTOSAR Version : 4.3.1
    DOC Name : AUTOSAR_SWS_OS.pdf
    Target : ARM TIVA_C TM4C123GH6PM

*/

#ifndef OS_CFG_OS_RESOURCE_CFG_H_
#define OS_CFG_OS_RESOURCE_CFG_H_

#define RESOURCE_INTERNAL    0x11u

#define RESOURCE_LINKED      0x22u

#define RESOURCE_STANDARD    0x44u


#define RESORCE_0   0

#define RESORCE_1   1

#define RESORCE_2   2

#define RESORCE_3   3

#define RESORCE_4   4

#define RESORCE_5   5





#define NO_RESOURCE         0xFFu

#define RESOURCES_NUMBER    6



#define OS_RESOURCES_OBJECT_CONGIFURATION   \
{ \
    {\
        .OsResourceProperty = RESOURCE_INTERNAL \
        ,\
        .OsResourceLinkedResourceRef = NO_RESOURCE\
        ,\
        .OsResourcePriority = 0x04u \
    }\
    ,\
    {\
        .OsResourceProperty =  RESOURCE_STANDARD  \
        ,\
        .OsResourceLinkedResourceRef = NO_RESOURCE \
        ,\
        .OsResourcePriority = 0x08u \
    }\
    ,\
    {\
        .OsResourceProperty =  RESOURCE_STANDARD  \
        ,\
        .OsResourceLinkedResourceRef = NO_RESOURCE \
        ,\
        .OsResourcePriority = 0x07u \
    }\
    ,\
    {\
        .OsResourceProperty =  RESOURCE_STANDARD  \
        ,\
        .OsResourceLinkedResourceRef = NO_RESOURCE \
        ,\
        .OsResourcePriority = 0x06u \
    }\
    ,\
    {\
        .OsResourceProperty =  RESOURCE_STANDARD  \
        ,\
        .OsResourceLinkedResourceRef = NO_RESOURCE \
        ,\
        .OsResourcePriority = 0x05u \
    }\
    ,\
    {\
        .OsResourceProperty = RESOURCE_LINKED \
        ,\
        .OsResourceLinkedResourceRef = RESORCE_5 \
        ,\
        .OsResourcePriority = 0x05u \
    }\
}


#define OS_RESOURCES_PCB_OBJECT_CONGIFURATION \
{\
}

#endif /* OS_CFG_OS_RESOURCE_CFG_H_ */
