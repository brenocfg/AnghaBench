#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_9__ ;
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_19__ ;
typedef  struct TYPE_22__   TYPE_11__ ;
typedef  struct TYPE_21__   TYPE_10__ ;

/* Type definitions */
struct TYPE_29__ {int /*<<< orphan*/  i_first; scalar_t__ b_disable; } ;
struct TYPE_30__ {int i_pid_pcr; TYPE_6__ pcr; } ;
typedef  TYPE_7__ ts_pmt_t ;
struct TYPE_24__ {int /*<<< orphan*/  i_pcr_count; } ;
struct TYPE_31__ {int i_pid; TYPE_1__ probed; } ;
typedef  TYPE_8__ ts_pid_t ;
struct TYPE_28__ {int i_size; TYPE_4__** p_elems; } ;
struct TYPE_32__ {TYPE_5__ programs; } ;
typedef  TYPE_9__ ts_pat_t ;
typedef  int /*<<< orphan*/  stime_t ;
struct TYPE_21__ {TYPE_11__* p_sys; } ;
typedef  TYPE_10__ demux_t ;
struct TYPE_22__ {scalar_t__ i_pmt_es; } ;
typedef  TYPE_11__ demux_sys_t ;
struct TYPE_26__ {TYPE_7__* p_pmt; } ;
struct TYPE_27__ {TYPE_3__ u; } ;
struct TYPE_25__ {TYPE_9__* p_pat; } ;
struct TYPE_23__ {scalar_t__ type; TYPE_2__ u; } ;

/* Variables and functions */
 TYPE_19__* GetPID (TYPE_11__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCRCheckDTS (TYPE_10__*,TYPE_7__*,int /*<<< orphan*/ ) ; 
 scalar_t__ PIDReferencedByProgram (TYPE_7__*,int) ; 
 int /*<<< orphan*/  ProgramSetPCR (TYPE_10__*,TYPE_7__*,int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_PAT ; 
 int /*<<< orphan*/  TimeStampWrapAround (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void PCRHandle( demux_t *p_demux, ts_pid_t *pid, stime_t i_pcr )
{
    demux_sys_t   *p_sys = p_demux->p_sys;

    pid->probed.i_pcr_count++;

    if( p_sys->i_pmt_es <= 0 )
        return;

    if(unlikely(GetPID(p_sys, 0)->type != TYPE_PAT))
        return;

    /* Search program and set the PCR */
    ts_pat_t *p_pat = GetPID(p_sys, 0)->u.p_pat;
    for( int i = 0; i < p_pat->programs.i_size; i++ )
    {
        ts_pmt_t *p_pmt = p_pat->programs.p_elems[i]->u.p_pmt;
        if( p_pmt->pcr.b_disable )
            continue;
        stime_t i_program_pcr = TimeStampWrapAround( p_pmt->pcr.i_first, i_pcr );

        if( p_pmt->i_pid_pcr == 0x1FFF ) /* That program has no dedicated PCR pid ISO/IEC 13818-1 2.4.4.9 */
        {
            if( PIDReferencedByProgram( p_pmt, pid->i_pid ) ) /* PCR shall be on pid itself */
            {
                /* ? update PCR for the whole group program ? */
                ProgramSetPCR( p_demux, p_pmt, i_program_pcr );
            }
        }
        else /* set PCR provided by current pid to program(s) referencing it */
        {
            /* Can be dedicated PCR pid (no owned then) or another pid (owner == pmt) */
            if( p_pmt->i_pid_pcr == pid->i_pid ) /* If that program references current pid as PCR */
            {
                /* We've found a target group for update */
                PCRCheckDTS( p_demux, p_pmt, i_pcr );
                ProgramSetPCR( p_demux, p_pmt, i_program_pcr );
            }
        }

    }
}