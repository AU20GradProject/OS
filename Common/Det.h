#ifndef DET_H

#define DET_H

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

#include "Std_Types.h"


FUNC(Std_ReturnType, MCU_CODE ) Det_ReportError( uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId ) ;


#endif // DET_H
