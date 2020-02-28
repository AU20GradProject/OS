/*
 * Os_Gpt_internal.c
 *
 *  Created on: Feb 15, 2020
 *      Author: midobakr
 */

#ifndef OS_SOURCES_OSINTERNAL_SOURCES_OS_GPT_INTERNAL_C_
#define OS_SOURCES_OSINTERNAL_SOURCES_OS_GPT_INTERNAL_C_


#include "..\..\Os_Headers\OsInterface_Headers\Os.h"
#include "..\..\Os_Headers\OsInternal_Headers\Os_Internal.h"



FUNC(StatusType, OSCODE_Internal) Init_Systick(void){

    StatusType retVal = E_OK;
    /* Set clock source */
    if(SYSTICK_CLK_SRC == CLK_SRC_PIOSC_DIV4){

        Systick_STCTRL &= ~(1<<CLK_SRC);

        /* Reload Value */
        Systick_STRELOAD = (uint32)4000 * SYSTICK_TICK_DURATION_MS - 1;

        //Systick_STRELOAD = ReloadValue;
    }else if(SYSTICK_CLK_SRC == CLK_SRC_SYSTEM){


        Systick_STCTRL = (1<< CLK_SRC);

        Systick_STRELOAD = /*need mcu ref pointer here*/16000 * SYSTICK_TICK_DURATION_MS - 1;
    }

    /* Set interrupt    */
    if(SYSTICK_INT_ENABLE == STD_ON){

        Systick_STCTRL |= (1<<INTEN);

    }else if(SYSTICK_INT_ENABLE == STD_OFF){

        Systick_STCTRL &= ~(1<<INTEN);

    }

    /* Enable Systick */
    if(SYSTICK_ENABLE == STD_ON){

        Systick_STCTRL |= (1<<ENABLE);

    }else if(SYSTICK_ENABLE == STD_OFF){

        Systick_STCTRL &= ~(1<<ENABLE);

    }
    return retVal;
}



#endif /* OS_SOURCES_OSINTERNAL_SOURCES_OS_GPT_INTERNAL_C_ */
