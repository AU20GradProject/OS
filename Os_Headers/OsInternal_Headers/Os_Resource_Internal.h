/*

    Written by : Bebo
    DATE : 7/2/2019
    AUTOSAR Version : 4.3.1
    DOC Name : AUTOSAR_SWS_OS.pdf
    Target : ARM TIVA_C TM4C123GH6PM

*/

#ifndef OS_HEADERS_OSINTERNAL_HEADERS_OS_RESOURCE_INTERNAL_H_
#define OS_HEADERS_OSINTERNAL_HEADERS_OS_RESOURCE_INTERNAL_H_

/*******************************************************************/


typedef struct
{
    /*This specifies the type of the resource*/
    VAR( boolean, AUTOMATIC ) OsResourceProperty ;

    /* link to the resource. Must be valid if OsResourceProperty is LINKED.
     * If OsResourceProperty is not LINKED the value is ignored */
    VAR( ResourceType, AUTOMATIC ) OsResourceLinkedResourceRef ;


} OsResource ;

/*******************************************************************/


#endif /* OS_HEADERS_OSINTERNAL_HEADERS_OS_RESOURCE_INTERNAL_H_ */
