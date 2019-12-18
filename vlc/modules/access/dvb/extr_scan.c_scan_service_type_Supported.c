#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int scan_service_type_t ;

/* Variables and functions */
#define  SERVICE_TYPE_DIGITAL_MPEG2_HD 133 
#define  SERVICE_TYPE_DIGITAL_RADIO 132 
#define  SERVICE_TYPE_DIGITAL_RADIO_AC 131 
#define  SERVICE_TYPE_DIGITAL_TELEVISION 130 
#define  SERVICE_TYPE_DIGITAL_TELEVISION_AC_HD 129 
#define  SERVICE_TYPE_DIGITAL_TELEVISION_AC_SD 128 

__attribute__((used)) static int scan_service_type_Supported( scan_service_type_t service_type )
{
    switch( service_type )
    {
        case SERVICE_TYPE_DIGITAL_TELEVISION:
        case SERVICE_TYPE_DIGITAL_RADIO:
        case SERVICE_TYPE_DIGITAL_MPEG2_HD:
        case SERVICE_TYPE_DIGITAL_TELEVISION_AC_SD:
        case SERVICE_TYPE_DIGITAL_TELEVISION_AC_HD:
        case SERVICE_TYPE_DIGITAL_RADIO_AC:
            return true;
        default:
            break;
    }
    return false;
}