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
struct TYPE_5__ {int /*<<< orphan*/  hierarchy_information; int /*<<< orphan*/  guard_interval; int /*<<< orphan*/  transmission_mode; int /*<<< orphan*/  constellation; void* code_rate_LP; void* code_rate_HP; int /*<<< orphan*/  bandwidth; } ;
struct TYPE_6__ {TYPE_1__ ofdm; } ;
struct dvb_frontend_parameters {TYPE_2__ u; int /*<<< orphan*/  inversion; int /*<<< orphan*/  frequency; } ;
struct dvb_frontend_event {TYPE_2__ u; int /*<<< orphan*/  inversion; int /*<<< orphan*/  frequency; } ;
struct TYPE_7__ {int /*<<< orphan*/  i_frontend_handle; } ;
typedef  TYPE_3__ dvb_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  DecodeBandwidth (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DecodeHierarchy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DecodeInversion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DecodeTransmission (int /*<<< orphan*/ *) ; 
 scalar_t__ EWOULDBLOCK ; 
 void* FEC_NONE ; 
 int /*<<< orphan*/  FE_GET_EVENT ; 
 int /*<<< orphan*/  FE_SET_FRONTEND ; 
 int /*<<< orphan*/  GUARD_INTERVAL_AUTO ; 
 int /*<<< orphan*/  QAM_AUTO ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 scalar_t__ errno ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dvb_frontend_parameters*) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_GetInteger (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vlc_strerror_c (scalar_t__) ; 

__attribute__((used)) static int FrontendSetOFDM( vlc_object_t *p_access, dvb_sys_t *p_sys )
{
    struct dvb_frontend_parameters fep;

    /* Prepare the fep structure */

    fep.frequency = var_GetInteger( p_access, "dvb-frequency" );

    fep.inversion = DecodeInversion( p_access );

    fep.u.ofdm.bandwidth = DecodeBandwidth( p_access );
    fep.u.ofdm.code_rate_HP = FEC_NONE;
    fep.u.ofdm.code_rate_LP = FEC_NONE;
    fep.u.ofdm.constellation = QAM_AUTO;
    fep.u.ofdm.transmission_mode = DecodeTransmission( p_access );
    fep.u.ofdm.guard_interval = GUARD_INTERVAL_AUTO;
    fep.u.ofdm.hierarchy_information = DecodeHierarchy( p_access );

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