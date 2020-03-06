/*

    Written by : Bebo
    DATE : 7/2/2019
    AUTOSAR Version : 4.3.1
    DOC Name : AUTOSAR_SWS_OS.pdf
    Target : ARM TIVA_C TM4C123GH6PM

*/

#ifndef OS_HEADERS_OSINTERFACE_HEADERS_OS_RESOURCE_H_
#define OS_HEADERS_OSINTERFACE_HEADERS_OS_RESOURCE_H_


/* Data type for a resource */
typedef VAR( uint8, TYPEDEF ) ResourceType ;


/* call serves to enter critical sections in the code that are assigned to the resource referenced by <ResID>.
 * A critical section shall always be left using ReleaseResource  */
/*  Nested resource occupation is only allowed
 * if the inner critical sections are completely executed within the surrounding critical section
 * by order LIFO last resource to get is the first to out */
/* Nested occupation of one and the same resource is also forbidden!*/
/* recommended that corresponding calls to GetResource and ReleaseResource appear within the same function */
/* not allowed to use services which are points of rescheduling for non preemptable tasks in resources critical section
 * this points is TerminateTask, WaitTask, ChainTask, Schedule */
/* critical sections are to be left before completion of an interrupt service routine */
/* critical sections should be short */
/* service may be called from an ISR and from task leve */
/* Resource <ResID> is invalid, E_OS_ID */
/* get a resource which is already occupied by any task or ISR, or the statically assigned priority of the calling task or
 interrupt routine is higher than the calculated ceiling priority, E_OS_ACCESS*/

FUNC (StatusType, OS_CODE) GetResource ( ResourceType ResID ) ;


/*  ReleaseResource is the counterpart of GetResource and serves to
 * leave critical sections in the code that are assigned to the resource referenced by <ResID>. */
/* The service may be called from an ISR and from task level  */
/* Resource <ResID> is invalid, E_OS_ID */
/* Attempt to release a resource which is not occupied by any task or ISR, or another resource shall be released before, E_OS_NOFUNC*/
/* Attempt to release a resource which has a lower ceiling priority than
 * the statically assigned priority of the calling task or interrupt routine, E_OS_ACCESS */

FUNC (StatusType, OS_CODE) ReleaseResource ( ResourceType ResID ) ;



#endif /* OS_HEADERS_OSINTERFACE_HEADERS_OS_RESOURCE_H_ */
