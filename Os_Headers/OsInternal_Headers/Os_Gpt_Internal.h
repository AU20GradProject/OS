/*
        Os_Gpt.h
        Written by : Bakr
        DATE : 18/2/2020
 */

#ifndef OS_HEADERS_OSINTERNAL_HEADERS_OS_GPT_INTERNAL_H_
#define OS_HEADERS_OSINTERNAL_HEADERS_OS_GPT_INTERNAL_H_

/* Configurations */
#define SYSTICK_TICK_DURATION_MS        1u
#define SYSTICK_ENABLE                  STD_ON
#define SYSTICK_INT_ENABLE              STD_ON
#define SYSTICK_CLK_SRC                 CLK_SRC_PIOSC_DIV4


/* Register addresses */
#define Systick_STCTRL          (*(( volatile P2VAR( uint32, AUTOMATIC, REGSPACE ) ) 0xE000E010 ))
#define Systick_STRELOAD        (*(( volatile P2VAR( uint32, AUTOMATIC, REGSPACE ) ) 0xE000E014 ))
#define Systick_STCURRENT       (*(( volatile P2VAR( uint32, AUTOMATIC, REGSPACE ) ) 0xE000E018 ))

/* Registers pin numbers */
#define ENABLE  0u
#define INTEN   1u
#define CLK_SRC 2u
#define COUNT   16u

/* Configuration Constants */
#define CLK_SRC_PIOSC_DIV4  0 /* sets the clock source to be PIOSC*/
#define CLK_SRC_SYSTEM  1

/* Function Declarations */
FUNC(StatusType, OSCODE_Internal) Init_Systick(void);



#endif /* OS_HEADERS_OSINTERNAL_HEADERS_OS_GPT_INTERNAL_H_ */
