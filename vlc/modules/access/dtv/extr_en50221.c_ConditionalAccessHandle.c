#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint16_t ;
struct TYPE_7__ {int* pi_system_ids; } ;
typedef  TYPE_2__ system_ids_t ;
struct TYPE_8__ {int /*<<< orphan*/  obj; int /*<<< orphan*/ ** pp_selected_programs; TYPE_1__* p_sessions; } ;
typedef  TYPE_3__ cam_t ;
struct TYPE_6__ {scalar_t__ p_sys; } ;

/* Variables and functions */
#define  AOT_CA_INFO 128 
 int* APDUGetLength (int*,int*) ; 
 int APDUGetTag (int*,int) ; 
 int /*<<< orphan*/  CAPMTAdd (TYPE_3__*,int,int /*<<< orphan*/ *) ; 
 int MAX_PROGRAMS ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void ConditionalAccessHandle( cam_t * p_cam, int i_session_id,
                                     uint8_t *p_apdu, int i_size )
{
    system_ids_t *p_ids =
        (system_ids_t *)p_cam->p_sessions[i_session_id - 1].p_sys;
    int i_tag = APDUGetTag( p_apdu, i_size );

    switch ( i_tag )
    {
    case AOT_CA_INFO:
    {
        int i;
        int l = 0;
        uint8_t *d = APDUGetLength( p_apdu, &l );
        msg_Dbg( p_cam->obj, "CA system IDs supported by the application :" );

        for ( i = 0; i < l / 2; i++ )
        {
            p_ids->pi_system_ids[i] = ((uint16_t)d[0] << 8) | d[1];
            d += 2;
            msg_Dbg( p_cam->obj, "- 0x%x", p_ids->pi_system_ids[i] );
        }
        p_ids->pi_system_ids[i] = 0;

        for ( i = 0; i < MAX_PROGRAMS; i++ )
        {
            if ( p_cam->pp_selected_programs[i] != NULL )
            {
                CAPMTAdd( p_cam, i_session_id,
                          p_cam->pp_selected_programs[i] );
            }
        }
        break;
    }

    default:
        msg_Err( p_cam->obj,
                 "unexpected tag in ConditionalAccessHandle (0x%x)",
                 i_tag );
    }
}