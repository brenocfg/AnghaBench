#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_8__ {unsigned int symbol_rate; int /*<<< orphan*/  modulation; int /*<<< orphan*/  fec_inner; } ;
struct TYPE_9__ {TYPE_2__ qam; } ;
struct dvb_frontend_parameters {TYPE_3__ u; int /*<<< orphan*/  inversion; void* frequency; } ;
struct dvb_frontend_event {TYPE_3__ u; int /*<<< orphan*/  inversion; void* frequency; } ;
struct TYPE_7__ {unsigned int symbol_rate_max; unsigned int symbol_rate_min; } ;
struct TYPE_10__ {TYPE_1__ info; } ;
typedef  TYPE_4__ frontend_t ;
struct TYPE_11__ {int /*<<< orphan*/  i_frontend_handle; TYPE_4__* p_frontend; } ;
typedef  TYPE_5__ dvb_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  DecodeInversion (int /*<<< orphan*/ *) ; 
 scalar_t__ EWOULDBLOCK ; 
 int /*<<< orphan*/  FEC_NONE ; 
 int /*<<< orphan*/  FE_GET_EVENT ; 
 int /*<<< orphan*/  FE_SET_FRONTEND ; 
 int /*<<< orphan*/  QAM_AUTO ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 scalar_t__ errno ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dvb_frontend_parameters*) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 void* var_GetInteger (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vlc_strerror_c (scalar_t__) ; 

__attribute__((used)) static int FrontendSetQAM( vlc_object_t *p_access, dvb_sys_t *p_sys )
{
    frontend_t *p_frontend = p_sys->p_frontend;
    struct dvb_frontend_parameters fep;
    unsigned int i_val;

    /* Prepare the fep structure */

    fep.frequency = var_GetInteger( p_access, "dvb-frequency" );

    fep.inversion = DecodeInversion( p_access );

    /* Default symbol-rate is for dvb-s, and doesn't fit
     * for dvb-c, so if it's over the limit of frontend, default to
     * somewhat common value
     */
    i_val = var_GetInteger( p_access, "dvb-srate" );
    if( i_val < p_frontend->info.symbol_rate_max &&
        i_val > p_frontend->info.symbol_rate_min )
        fep.u.qam.symbol_rate = i_val;

    fep.u.qam.fec_inner = FEC_NONE;

    fep.u.qam.modulation = QAM_AUTO;

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