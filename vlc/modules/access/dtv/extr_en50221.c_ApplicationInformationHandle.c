#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  obj; } ;
typedef  TYPE_1__ cam_t ;

/* Variables and functions */
#define  AOT_APPLICATION_INFO 128 
 int* APDUGetLength (int*,int*) ; 
 int APDUGetTag (int*,int) ; 
 int* GetLength (int*,int*) ; 
 int /*<<< orphan*/  VLC_UNUSED (int) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  msg_Info (int /*<<< orphan*/ ,char*,int*,int,int,int) ; 

__attribute__((used)) static void ApplicationInformationHandle( cam_t * p_cam, int i_session_id,
                                          uint8_t *p_apdu, int i_size )
{
    VLC_UNUSED(i_session_id);
    int i_tag = APDUGetTag( p_apdu, i_size );

    switch ( i_tag )
    {
    case AOT_APPLICATION_INFO:
    {
        int i_type, i_manufacturer, i_code;
        int l = 0;
        uint8_t *d = APDUGetLength( p_apdu, &l );

        if ( l < 4 ) break;
        p_apdu[l + 4] = '\0';

        i_type = *d++;
        i_manufacturer = ((int)d[0] << 8) | d[1];
        d += 2;
        i_code = ((int)d[0] << 8) | d[1];
        d += 2;
        d = GetLength( d, &l );
        d[l] = '\0';
        msg_Info( p_cam->obj, "CAM: %s, %02X, %04X, %04X",
                  d, i_type, i_manufacturer, i_code );
        break;
    }
    default:
        msg_Err( p_cam->obj,
                 "unexpected tag in ApplicationInformationHandle (0x%x)",
                 i_tag );
    }
}