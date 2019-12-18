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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_7__ {int /*<<< orphan*/  i_interval; } ;
typedef  TYPE_2__ date_time_t ;
struct TYPE_8__ {int /*<<< orphan*/  obj; TYPE_1__* p_sessions; } ;
typedef  TYPE_3__ cam_t ;
struct TYPE_6__ {scalar_t__ p_sys; } ;

/* Variables and functions */
#define  AOT_DATE_TIME_ENQ 128 
 int /*<<< orphan*/ * APDUGetLength (int /*<<< orphan*/ *,int*) ; 
 int APDUGetTag (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  DateTimeSend (TYPE_3__*,int) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void DateTimeHandle( cam_t *p_cam, int i_session_id,
                            uint8_t *p_apdu, int i_size )
{
    date_time_t *p_date =
        (date_time_t *)p_cam->p_sessions[i_session_id - 1].p_sys;

    int i_tag = APDUGetTag( p_apdu, i_size );

    switch ( i_tag )
    {
    case AOT_DATE_TIME_ENQ:
    {
        int l;
        const uint8_t *d = APDUGetLength( p_apdu, &l );

        if ( l > 0 )
        {
            p_date->i_interval = *d;
            msg_Dbg( p_cam->obj, "DateTimeHandle : interval set to %d",
                     p_date->i_interval );
        }
        else
            p_date->i_interval = 0;

        DateTimeSend( p_cam, i_session_id );
        break;
    }
    default:
        msg_Err( p_cam->obj, "unexpected tag in DateTimeHandle (0x%x)",
                 i_tag );
    }
}