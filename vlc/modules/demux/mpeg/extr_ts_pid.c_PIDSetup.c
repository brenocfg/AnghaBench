#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int ts_pid_type_t ;
struct TYPE_6__ {int /*<<< orphan*/  p_psip; int /*<<< orphan*/  p_si; int /*<<< orphan*/  p_stream; int /*<<< orphan*/  p_pmt; int /*<<< orphan*/  p_pat; } ;
struct TYPE_7__ {int i_pid; scalar_t__ i_refcount; int type; TYPE_1__ u; } ;
typedef  TYPE_2__ ts_pid_t ;
typedef  int /*<<< orphan*/  demux_t ;

/* Variables and functions */
 int /*<<< orphan*/  PIDReset (TYPE_2__*) ; 
#define  TYPE_CAT 134 
#define  TYPE_FREE 133 
#define  TYPE_PAT 132 
#define  TYPE_PMT 131 
#define  TYPE_PSIP 130 
#define  TYPE_SI 129 
#define  TYPE_STREAM 128 
 scalar_t__ UINT16_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ts_pat_New (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_pmt_New (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_psip_New (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_si_New (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_stream_New (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

bool PIDSetup( demux_t *p_demux, ts_pid_type_t i_type, ts_pid_t *pid, ts_pid_t *p_parent )
{
    if( pid == p_parent || pid->i_pid == 0x1FFF )
        return false;

    if( pid->i_refcount == 0 )
    {
        assert( pid->type == TYPE_FREE );
        switch( i_type )
        {
        case TYPE_FREE: /* nonsense ?*/
            PIDReset( pid );
            return true;

        case TYPE_CAT:
            return true;

        case TYPE_PAT:
            PIDReset( pid );
            pid->u.p_pat = ts_pat_New( p_demux );
            if( !pid->u.p_pat )
                return false;
            break;

        case TYPE_PMT:
            PIDReset( pid );
            pid->u.p_pmt = ts_pmt_New( p_demux );
            if( !pid->u.p_pmt )
                return false;
            break;

        case TYPE_STREAM:
            PIDReset( pid );
            pid->u.p_stream = ts_stream_New( p_demux, p_parent->u.p_pmt );
            if( !pid->u.p_stream )
                return false;
            break;

        case TYPE_SI:
            PIDReset( pid );
            pid->u.p_si = ts_si_New( p_demux );
            if( !pid->u.p_si )
                return false;
            break;

        case TYPE_PSIP:
            PIDReset( pid );
            pid->u.p_psip = ts_psip_New( p_demux );
            if( !pid->u.p_psip )
                return false;
            break;

        default:
            assert(false);
            break;
        }

        pid->i_refcount++;
        pid->type = i_type;
    }
    else if( pid->type == i_type && pid->i_refcount < UINT16_MAX )
    {
        pid->i_refcount++;
    }
    else
    {
        if( pid->type != TYPE_FREE )
            msg_Warn( p_demux, "Tried to redeclare pid %d with another type", pid->i_pid );
        return false;
    }

    return true;
}