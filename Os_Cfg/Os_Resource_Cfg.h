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




#define OS_RESOURCES_NUMBER   5u

#define OS_NO_RESOURCE_MASK     0x00000000u
#define OS_RESORCE_0_MASK       0x00000001u
#define OS_RESORCE_1_MASK       0x00000002u
#define OS_RESORCE_2_MASK       0x00000004u
#define OS_RESORCE_3_MASK       0x00000008u
#define OS_RESORCE_4_MASK       0x00000010u



#define OS_RESOURCE_0       0u
#define OS_RESOURCE_1       1u
#define OS_RESOURCE_2       2u
#define OS_RESOURCE_3       3u
#define OS_RESOURCE_4       4u
#define OS_NO_RESOURCE      0xFFu




#define OS_RESOURCES_OBJECT_CONGIFURATION   \
{ \
    {\
        .OsResourceProperty = RESOURCE_INTERNAL \
        ,\
        .OsResourceLinkedResourceRef = OS_NO_RESOURCE\
        ,\
        .OsResourcePriority = 0x04u \
    }\
    ,\
    {\
        .OsResourceProperty =  RESOURCE_STANDARD  \
        ,\
        .OsResourceLinkedResourceRef = OS_NO_RESOURCE \
        ,\
        .OsResourcePriority = 0x08u \
    }\
    ,\
    {\
        .OsResourceProperty =  RESOURCE_STANDARD  \
        ,\
        .OsResourceLinkedResourceRef = OS_NO_RESOURCE \
        ,\
        .OsResourcePriority = 0x07u \
    }\
    ,\
    {\
        .OsResourceProperty =  RESOURCE_STANDARD  \
        ,\
        .OsResourceLinkedResourceRef = OS_NO_RESOURCE \
        ,\
        .OsResourcePriority = 0x06u \
    }\
    ,\
    {\
        .OsResourceProperty =  RESOURCE_STANDARD  \
        ,\
        .OsResourceLinkedResourceRef = OS_NO_RESOURCE \
        ,\
        .OsResourcePriority = 0x05u \
    }\
}


#define OS_RESOURCES_PCB_OBJECT_CONGIFURATION \
{\
}

#endif /* OS_CFG_OS_RESOURCE_CFG_H_ */
