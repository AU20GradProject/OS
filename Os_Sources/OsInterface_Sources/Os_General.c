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

/********************************************************************************************/

/* service returns the current application mode. It may be used to write mode dependent code. */
AppModeType GetActiveApplicationMode ( void )
{
    return AppMode ;
}


/********************************************************************************************/


/* The user can call this system service to start the operating system in a specific mode */
void StartOS ( AppModeType Mode )
{
    VAR ( uint16, AUTOMATIC ) LocalTemp = 0 ;
    VAR ( uint16, AUTOMATIC ) LocalCounter = 0 ;

    /* all interrupt must be disabled before calling StartOS */

    /* tasks  auto starting */

    LocalCounter = OsAppModes_Array [Mode].AutoStartTasks_Index  ;
    if ( APPMODE_INVALID != LocalCounter )
    {

        /* determine stop index of tasks which will be activated by for loop */
        LocalTemp = OsAppModes_Array [Mode].AutoStartTasks_Index + OsAppModes_Array [Mode].AutoStartTasks_Number ;

        for( ; LocalCounter <= LocalTemp ; LocalCounter++ )
        {
            ActivateTask( OsAutoStartTasks_Array[LocalCounter] ) ;

        } /* for */
    }
    else
    {
        /* this app mode hasn't auto start tasks */
    }


    /************************************************************************/


    /* alarms auto starting */
    LocalCounter = OsAppModes_Array [Mode].AutoStartAlarms_Index  ;

    if ( APPMODE_INVALID != LocalCounter )
    {
        /* determine stop index of alarms which will be activated by for loop */
        LocalTemp = OsAppModes_Array [Mode].AutoStartAlarms_Index + OsAppModes_Array [Mode].AutoStartAlarms_Number ;

        for( ; LocalCounter <= LocalTemp ; LocalCounter++ )
        {
            if( ALARM_ABSOLUTE == OsAutoStartAlarms_SettingArray[LocalCounter].OsAlarmAutostartType )
            {
                /*
                SetAbsAlarm( OsAutoStartAlarms_Array[LocalCounter], OsAutoStartAlarms_SettingArray[LocalCounter].OsAlarmAlarmTime , OsAutoStartAlarms_SettingArray[LocalCounter].OsAlarmCycleTime );
                */

            }
            else
            {
                /*
                SetRelAlarm( OsAutoStartAlarms_Array[LocalCounter], OsAutoStartAlarms_SettingArray[LocalCounter].OsAlarmAlarmTime , OsAutoStartAlarms_SettingArray[LocalCounter].OsAlarmCycleTime );
                */

            } /* else */

        }  /* for*/

    } /* if */
    else
    {
        /* this app mode hasn't auto start tasks */
    }


    /************************************************************************/


    /* schedule tables auto starting */
    LocalCounter = OsAppModes_Array [Mode].AutoStartScheduleTables_Index  ;

    if ( APPMODE_INVALID != LocalCounter )
    {
        /* determine stop index of schedule tables which will be activated by for loop */
        LocalTemp = OsAppModes_Array [Mode].AutoStartScheduleTables_Index + OsAppModes_Array [Mode].AutoStartScheduleTables_Number ;

        for( ; LocalCounter <= LocalTemp ; LocalCounter++ )
        {

            if( TABLE_ABSOLUTE == OsAutoStartTables_SettingArray[LocalCounter].OsScheduleTableAutostartType )
            {
                /*
                StartScheduleTableAbs( OsAutoStartTabless_Array[LocalCounter] , OsAutoStartTables_SettingArray[LocalCounter].OsScheduleTableStartValue ) ;
                */

            }
            else
            {
                /*
                StartScheduleTableRel( OsAutoStartTabless_Array[LocalCounter] , OsAutoStartTables_SettingArray[LocalCounter].OsScheduleTableStartValue ) ;
                */

            } /* else */

        } /* for */

    } /* if */
    else
    {
        /* this app mode hasn't auto start tasks */
    }

    /************************************************************************/


    CS_OFF ;

    return ;
}

/********************************************************************************************/

/* user can call this system service to abort the overall system (e.g. emergency off).
 * The operating system also calls this function internally,
 *  if it has reached an undefined internal state and is no longer ready to run.    */
void ShutdownOS ( StatusType Error )
{

    CS_ON ;
    while (1) ;

    return ;
}
