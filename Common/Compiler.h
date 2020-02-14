/*

Written by : Bebo
DATE : 7/2/2019
AUTOSAR Version : 4.3.1
DOC Name : AUTOSAR_SWS_CompilerAbstraction.pdf
Target : ARM TIVA_C TM4C123GH6PM

*/


#ifndef COMPILER_H

#define COMPILER_H


#include "Compiler_Cfg.h"


/*********************************************************************/


/* Published information */
#define MCU_MODULE_ID 30u
#define MCU_VENDOR_ID 0x002Bu   /* vendor id of NXP */

#define MCU_AR_RELEASE_MAJOR_VERSION 0x01u
#define MCU_AR_RELEASE_MINOR_VERSION 0x00u
#define MCU_AR_RELEASE_REVISION_VERSION 0x00u

#define MCU_SW_MAJOR_VERSION 0x04u
#define MCU_SW_MINOR_VERSION 0x03u
#define MCU_SW_PATCH_VERSION 0x01u


/*********************************************************************/

/* 8.2.1 */

#define	NULL_PTR	((void*) 0x0)

#define AUTOMATIC	/* used as input for memory class (memclass) and  pointer class (ptrclass) when no input from Compiler_Cfg.h is needed */
#define TYPEDEF		/* used with typedef keyword in as input for memory class (of compiler)because with typedef we cannot use them */

#define	INLINE 			inline
#define LOCAL_INLINE	static inline


/* 8.2.2 function definition use it to define functions */

#define FUNC( rettype, memclass )   rettype 									/* for the declaration and definition of functions */

#define FUNC_P2CONST(rettype, ptrclass, memclass)	const rettype *			/* declaration and definition of functions returning a pointer to a constant */

#define FUNC_P2VAR(rettype, ptrclass, memclass)		rettype *		/* for the declaration and definition of functions returning a pointer to a variable */


/* 8.2.3 Pointer definitions use it to define pointers */

#define P2VAR(ptrtype, memclass, ptrclass)	ptrtype * 		                /* for the declaration and definition of pointers in RAM, pointing to variables */

#define P2CONST(ptrtype, memclass, ptrclass) const ptrtype*				    /* for the declaration and definition of pointers in RAM pointing to constants */

#define CONSTP2VAR(ptrtype, memclass, ptrclass) ptrtype * const 		    /* for the declaration and definition of constant pointers accessing variables */

#define CONSTP2CONST(ptrtype, memclass, ptrclass)	const ptrtype * const	/* for the declaration and definition of constant pointers accessing constants */

#define P2FUNC(rettype, ptrclass, fctname)	rettype (* fctname)			    /* for the type definition of pointers to functions */ /* fctname is pointer to function name*/

#define CONSTP2FUNC(rettype, ptrclass, fctname)	rettype (* const fctname)	/* the type definition of constant pointers to functions */ /* fctname is pointer to function name*/


/* 8.2.4 Constant definitions use it to define Constants */

#define CONST(type, memclass)	const type		/* for the declaration and definition of constants */


/* 8.2.4 Variable definitions use it to define Variables */

#define VAR( type, memclass )  type		/* for the declaration and definition of constants */


#endif 	/* COMPILER_H */

