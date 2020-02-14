/*

    Written by : Bebo
    DATE : 7/2/2019
    AUTOSAR Version : 4.3.1
    DOC Name : AUTOSAR_SWS_OS.pdf
    Target : ARM TIVA_C TM4C123GH6PM

*/

#ifndef OS_HEADERS_OSINTERFACE_HEADERS_OS_TASK_H_
#define OS_HEADERS_OSINTERFACE_HEADERS_OS_TASK_H_

/* This data type identifies a task */

#define INVALID_TASK    0xFFu /* Constant of data type TaskType for a not defined task. */
typedef VAR( uint8, TYPEDEF ) TaskType ;

/* This data type points to a variable of TaskType */
typedef P2VAR( TaskType, TYPEDEF, TYPEDEF ) TaskRefType ;

/* This data type identifies the state of a task enum for following values  */


#define RUNNING     0x44
#define WAITING     0x88
#define READY       0xCC
#define SUSPENDED   0xFF

typedef VAR( uint8, TYPEDEF ) TaskStateType ;

/* This data type points to a variable of the data type TaskStateType */
typedef P2VAR( TaskStateType, TYPEDEF, TYPEDEF ) TaskStateRefType ;


#endif /* OS_HEADERS_OSINTERFACE_HEADERS_OS_TASK_H_ */
