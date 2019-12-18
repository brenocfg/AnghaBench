#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/ * p_psip; int /*<<< orphan*/ * p_si; int /*<<< orphan*/ * p_stream; int /*<<< orphan*/ * p_pmt; int /*<<< orphan*/ * p_pat; } ;
struct TYPE_14__ {int i_refcount; scalar_t__ type; TYPE_1__ u; } ;
typedef  TYPE_2__ ts_pid_t ;
struct TYPE_15__ {int /*<<< orphan*/  p_sys; } ;
typedef  TYPE_3__ demux_t ;

/* Variables and functions */
 int /*<<< orphan*/  PIDReset (TYPE_2__*) ; 
 int /*<<< orphan*/  SetPIDFilter (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
#define  TYPE_CAT 134 
#define  TYPE_FREE 133 
#define  TYPE_PAT 132 
#define  TYPE_PMT 131 
#define  TYPE_PSIP 130 
#define  TYPE_SI 129 
#define  TYPE_STREAM 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ts_pat_Del (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_pmt_Del (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_psip_Del (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_si_Del (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_stream_Del (TYPE_3__*,int /*<<< orphan*/ *) ; 

void PIDRelease( demux_t *p_demux, ts_pid_t *pid )
{
    if( pid->i_refcount == 0 )
    {
        assert( pid->type == TYPE_FREE );
        return;
    }
    else if( pid->i_refcount == 1 )
    {
        pid->i_refcount--;
    }
    else if( pid->i_refcount > 1 )
    {
        assert( pid->type != TYPE_FREE && pid->type != TYPE_PAT );
        pid->i_refcount--;
    }

    if( pid->i_refcount == 0 )
    {
        switch( pid->type )
        {
        default:
        case TYPE_FREE: /* nonsense ?*/
            assert( pid->type != TYPE_FREE );
            break;

        case TYPE_CAT:
            break;

        case TYPE_PAT:
            ts_pat_Del( p_demux, pid->u.p_pat );
            pid->u.p_pat = NULL;
            break;

        case TYPE_PMT:
            ts_pmt_Del( p_demux, pid->u.p_pmt );
            pid->u.p_pmt = NULL;
            break;

        case TYPE_STREAM:
            ts_stream_Del( p_demux, pid->u.p_stream );
            pid->u.p_stream = NULL;
            break;

        case TYPE_SI:
            ts_si_Del( p_demux, pid->u.p_si );
            pid->u.p_si = NULL;
            break;

        case TYPE_PSIP:
            ts_psip_Del( p_demux, pid->u.p_psip );
            pid->u.p_psip = NULL;
            break;
        }

        SetPIDFilter( p_demux->p_sys, pid, false );
        PIDReset( pid );
    }
}