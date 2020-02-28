/*

Written by : Bebo
DATE : 1/9/2019
AUTOSAR Version : 4.3.1
DOC Name : AUTOSAR_SWS_PlatformTypes.pdf
Target : ARM TIVA_C TM4C123GH6PM

*/


#ifndef PLATFORM_TYPES_H

#define PLATFORM_TYPES_H


/* 8.3 */
#ifndef TRUE 					
#define TRUE 	0x01u
#endif 

#ifndef FALSE 
#define FALSE 	0x0u
#endif

#define CPU_TYPE_8 		8		
#define CPU_TYPE_16 	16
#define CPU_TYPE_32 	32
#define CPU_TYPE_64 	64

#define MSB_FIRST 		0		
#define LSB_FIRST 		1

#define HIGH_BYTE_FIRST 0		
#define LOW_BYTE_FIRST 	1


/* 8.2 */
typedef unsigned char 		boolean;			

typedef signed char 		sint8;
typedef unsigned char 		uint8;

typedef signed short 		sint16;
typedef unsigned short 		uint16;

typedef signed long 		sint32;
typedef unsigned long 		uint32;

typedef signed long long 	sint64;
typedef unsigned long long 	uint64;

/* its 32 bit due to tiva is faster with dealing with 32 bit
 * but least mean it won't overflow at uint8 range but it logically used for
 * range < 256 */
typedef unsigned long 		uint8_least;
typedef unsigned long 		uint16_least;
typedef unsigned long 		uint32_least;

typedef signed long 		sint8_least;
typedef signed long 		sint16_least;
typedef signed long 		sint32_least;

typedef float 				float32;
typedef double 				float64;


/* 7.2 & 7.3*/ 
#define CPU_TYPE			CPU_TYPE_32			/* 2 ARM */
#define CPU_BIT_ORDER		LSB_FIRST			/* 2.3.6 ARM */
#define CPU_BYTE_ORDER 		LOW_BYTE_FIRST		/* 2.4.6 ARM */

#endif 	/* PLATFORM_TYPES_H */

