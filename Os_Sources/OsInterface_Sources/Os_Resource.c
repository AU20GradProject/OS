/*

    Created by : Ahmad Hegazy
    DATE : 17/2/2019
    AUTOSAR Version : 4.3.1
    DOC Name : AUTOSAR_SWS_OS.pdf
                Osek/VDX.pdf
    Target : ARM TIVA_C TM4C123GH6PM

*/




#include "..\..\Os_Headers\OsInterface_Headers\Os.h"
#include "..\..\Os_Headers\OsInternal_Headers\Os_Internal.h"

/*This call serves to enter critical sections in the code that are assigned to the resource referenced by <ResID>. 
    A critical section shall always be left using ReleaseResource.*/
FUNC(StatusType, AUTOMATIC) GetResource (ResourceType ResID){
    /*
    StatusType is an error code:
    * E_OK: no error;
    * E_OS_ID: the resource id is invalid;
    * E_OS_ACCESS: trying to get a resource that is already in use (it is a design error).
    * A task that own the resource may not be preempted by another task that will try to get the resource. (resource prioity ceiling)
    */
   /*
    * Priotrity ceiling
    Each resource has a priority such as:
    * The priority is ≥ to max of priorities of tasks which may get the resource;
    * When a task get a resource, its priority is raised to the priority of the resource
    * When a task release the resource, its priority is lowered to the previous one.
    */

   /*
   RES_SCHEDULER is a resource that disable scheduling when in use. 
   A task which gets Res_scheduler becomes non-preemptable until it releases it;
   */
    return E_OK;
}
/* ReleaseResource is the counterpart of GetResource and serves to leave critical sections in the code that are assigned to the resource referenced by <ResID>.*/
FUNC(StatusType, AUTOMATIC) ReleaseResource (ResourceType ResID){
    /*
    StatusType is an error code:
    * E_OK: no error;
    * E_OS_ID: the resource id is invalid;
    * E_OS_ACCESS: trying to release a resource that is not in use (it is a design error).
    */
    /*    
    * When a task release the resource, its priority is lowered to the previous one.
    */
    return E_OK;
}
