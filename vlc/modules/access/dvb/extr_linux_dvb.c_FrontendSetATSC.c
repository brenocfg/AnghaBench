#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_5__ {int /*<<< orphan*/  modulation; } ;
struct TYPE_6__ {TYPE_1__ vsb; } ;
struct dvb_frontend_parameters {TYPE_2__ u; int /*<<< orphan*/  frequency; } ;
struct dvb_frontend_event {TYPE_2__ u; int /*<<< orphan*/  frequency; } ;
struct TYPE_7__ {int /*<<< orphan*/  i_frontend_handle; } ;
typedef  TYPE_3__ dvb_sys_t ;

/* Variables and functions */
 scalar_t__ EWOULDBLOCK ; 
 int /*<<< orphan*/  FE_GET_EVENT ; 
 int /*<<< orphan*/  FE_SET_FRONTEND ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VSB_8 ; 
 scalar_t__ errno ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dvb_frontend_parameters*) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_GetInteger (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vlc_strerror_c (scalar_t__) ; 

__attribute__((used)) static int FrontendSetATSC( vlc_object_t *p_access, dvb_sys_t *p_sys )
{
    struct dvb_frontend_parameters fep;

    /* Prepare the fep structure */

    fep.frequency = var_GetInteger( p_access, "dvb-frequency" );
    fep.u.vsb.modulation = VSB_8;

    /* Empty the event queue */
    for( ; ; )
    {
        struct dvb_frontend_event event;
        if ( ioctl( p_sys->i_frontend_handle, FE_GET_EVENT, &event ) < 0
              && errno == EWOULDBLOCK )
            break;
    }

    /* Now send it all to the frontend device */
    if( ioctl( p_sys->i_frontend_handle, FE_SET_FRONTEND, &fep ) < 0 )
    {
        msg_Err( p_access, "frontend error: %s", vlc_strerror_c(errno) );
        return VLC_EGENERIC;
    }

    return VLC_SUCCESS;
}