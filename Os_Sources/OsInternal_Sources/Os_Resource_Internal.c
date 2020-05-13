/*

    Written by : Bebo
    DATE : 7/2/2019
    AUTOSAR Version : 4.3.1
    DOC Name : AUTOSAR_SWS_OS.pdf
    Target : ARM TIVA_C TM4C123GH6PM

*/




#include "..\..\Os_Headers\OsInterface_Headers\Os.h"
#include "..\..\Os_Headers\OsInternal_Headers\Os_Internal.h"
#include "..\..\Os_Headers\OsInternal_Headers\Os_ExternalVariables.h"


void Resource_IsrMask ( uint8 ResourcePriority )
{

    switch (ResourcePriority)
    {
        case ( TASK_PRIORITIES_NUMBER ):
        {
            __asm ( " MOV R10, #0x0E0u " ) ;
            __asm ( " MSR BASEPRI_MAX, R10 " ) ;

            break ;
        }
        case ( TASK_PRIORITIES_NUMBER + 1 ):
        {
            __asm ( " MOV R10, #0x0C0u " ) ;
            __asm ( " MSR BASEPRI_MAX, R10 " ) ;

            break ;
        }
        case ( TASK_PRIORITIES_NUMBER + 2 ):
        {
            __asm ( " MOV R10, #0x0A0u " ) ;
            __asm ( " MSR BASEPRI_MAX, R10 " ) ;
            break ;
        }
        case ( TASK_PRIORITIES_NUMBER + 3 ):
        {
            __asm ( " MOV R10, #0x080u " ) ;
            __asm ( " MSR BASEPRI_MAX, R10 " ) ;

            break ;
        }
        case ( TASK_PRIORITIES_NUMBER + 4 ):
        {

            __asm ( " MOV R10, #0x060u " ) ;
            __asm ( " MSR BASEPRI_MAX, R10 " ) ;

            break ;
        }
        case ( TASK_PRIORITIES_NUMBER + 5 ):
        {

            __asm ( " MOV R10, #0x040u " ) ;
            __asm ( " MSR BASEPRI_MAX, R10 " ) ;

            break ;
        }
        case ( TASK_PRIORITIES_NUMBER + 6 ):
        {

            __asm ( " MOV R10, #0x020u " ) ;
            __asm ( " MSR BASEPRI_MAX, R10 " ) ;

            break ;
        }
        case ( TASK_PRIORITIES_NUMBER + 7 ):
        {
            OsResource_CS_Flag = TRUE ;
            __asm ( " CPSID i " ) ;

            break ;
        }
        default :
        {
            __asm ( " MOV R10, #0x000u " ) ;
            __asm ( " MSR BASEPRI_MAX, R10 " ) ;

            break ;
        }
    }
    return ;
}
