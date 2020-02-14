/*

Written by : Bebo
DATE : 7/2/2019
AUTOSAR Version : 4.3.1
DOC Name : AUTOSAR_SWS_StandardTypes.pdf
Target : ARM TIVA_C TM4C123GH6PM

*/

#ifndef STD_TYPES_H

#define STD_TYPES_H

#include "Platform_Types.h"
#include "Compiler.h"

/* 8.2 */
#ifndef STATUSTYPEDEFINED
#define STATUSTYPEDEFINED
#define E_OK 0x00u
typedef VAR( uint8, TYPEDEF) StatusType ; 	/* OSEK compliance */
#endif
#define E_NOT_OK 0x01u

#define STD_HIGH 0x01u /* Physical state 5V or 3.3V */
#define STD_LOW 0x00u /* Physical state 0V */

#define STD_ACTIVE 0x01u /* Logical state active */
#define STD_IDLE 0x00u /* Logical state idle */

#define STD_ON 0x01u
#define STD_OFF 0x00u

/* 8.1 */
typedef VAR( uint8, TYPEDEF) Std_ReturnType ;

typedef struct
{
	VAR( uint16, AUTOMATIC ) vendorID ;
	VAR( uint16, AUTOMATIC ) moduleID ;
	VAR( uint8, AUTOMATIC )	sw_major_version ;
	VAR( uint8, AUTOMATIC )	sw_minor_version ;
	VAR( uint8, AUTOMATIC )	sw_patch_version ;
} Std_VersionInfoType ;


#endif /* STD_TYPES_H */

