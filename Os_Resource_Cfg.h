/*

    Written by : Bebo
    DATE : 7/2/2019
    AUTOSAR Version : 4.3.1
    DOC Name : AUTOSAR_SWS_OS.pdf
    Target : ARM TIVA_C TM4C123GH6PM

*/

#ifndef OS_RESOURCE_CFG_H_
#define OS_RESOURCE_CFG_H_

#define RESOURCE_INTERNAL    0x11u

#define RESOURCE_LINKED      0x22u

#define RESOURCE_STANDARD    0x44u


#define RESORCE_1   0

#define RESORCE_2   1

#define RESORCE_3   2



#define NO_RESOURCE 0x00

#define RESOURCES_NUMBER 3



#define OS_RESOURCES_OBJECT_CONGIFURATION   \
{ \
    {\
        .OsResourceProperty = RESOURCE_INTERNAL \
        ,\
        .OsResourceLinkedResourceRef = NO_RESOURCE\
    }\
    ,\
    {\
        .OsResourceProperty =  RESOURCE_STANDARD  \
        ,\
        .OsResourceLinkedResourceRef = NO_RESOURCE \
    }\
    ,\
    {\
        .OsResourceProperty = RESOURCE_LINKED \
        ,\
        .OsResourceLinkedResourceRef = RESORCE_1 \
    }\
}


#endif /* OS_RESOURCE_CFG_H_ */
