/*

    Created by : Ahmad Hegazy
    DATE : 17/2/2019
    AUTOSAR Version : 4.3.1
    DOC Name : AUTOSAR_SWS_OS.pdf
                Osek/VDX.pdf
    Target : ARM TIVA_C TM4C123GH6PM

*/

#ifndef OS_HEADERS_OSINTERFACE_HEADERS_OS_RESOURCE_H_
#define OS_HEADERS_OSINTERFACE_HEADERS_OS_RESOURCE_H_


/* Data type for a resource */
typedef VAR( uint8, TYPEDEF ) ResourceType ;


/*  
    * DeclareResource serves as an external declaration of a re-source. 
    * The function and use of this service are similar to that of the external declaration of variables.
    * Since Autosar OS is a static OS, this function has no use, All resources are declared precompilation
*/
FUNC(void, AUTOMATIC) DeclareResource (ResourceType ResID);
/*This call serves to enter critical sections in the code that are assigned to the resource referenced by <ResID>. 
    A critical section shall always be left using ReleaseResource.*/
FUNC(StatusType, AUTOMATIC) GetResource (ResourceType ResID);
/* ReleaseResource is the counterpart of GetResource and serves to leave critical sections in the code that are assigned to the resource referenced by <ResID>.*/
FUNC(StatusType, AUTOMATIC) ReleaseResource (ResourceType ResID);

#endif /* OS_HEADERS_OSINTERFACE_HEADERS_OS_RESOURCE_H_ */
