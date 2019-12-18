#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;

/* Type definitions */
struct TYPE_17__ {int i_pcroffset; int b_disable; int b_fix_done; scalar_t__ i_first_dts; scalar_t__ i_current; } ;
struct TYPE_18__ {int i_pid_pcr; TYPE_2__ pcr; int /*<<< orphan*/  i_number; } ;
typedef  TYPE_3__ ts_pmt_t ;
struct TYPE_19__ {TYPE_5__* p_sys; } ;
typedef  TYPE_4__ demux_t ;
struct TYPE_20__ {scalar_t__ seltype; int /*<<< orphan*/  b_check_pcr_offset; } ;
typedef  TYPE_5__ demux_sys_t ;
struct TYPE_21__ {scalar_t__ i_dts; } ;
typedef  TYPE_6__ block_t ;
struct TYPE_16__ {scalar_t__ i_pcr_count; } ;
struct TYPE_15__ {TYPE_1__ probed; } ;

/* Variables and functions */
 scalar_t__ FROM_SCALE (scalar_t__) ; 
 int FindPCRCandidate (TYPE_3__*) ; 
 TYPE_12__* GetPID (TYPE_5__*,int) ; 
 scalar_t__ PROGRAM_ALL ; 
 scalar_t__ TO_SCALE (scalar_t__) ; 
 scalar_t__ TS_TICK_UNKNOWN ; 
 int /*<<< orphan*/  UpdatePESFilters (TYPE_4__*,int) ; 
 scalar_t__ VLC_TICK_FROM_MS (int) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_4__*,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void PCRFixHandle( demux_t *p_demux, ts_pmt_t *p_pmt, block_t *p_block )
{
    demux_sys_t *p_sys = p_demux->p_sys;

    /* disable PCR offset check */
    if( !p_sys->b_check_pcr_offset && p_pmt->pcr.i_pcroffset == -1 )
        p_pmt->pcr.i_pcroffset = 0;

    if ( p_pmt->pcr.b_disable || p_pmt->pcr.b_fix_done )
    {
        return;
    }
    /* Record the first data packet timestamp in case there wont be any PCR */
    else if( p_pmt->pcr.i_first_dts == TS_TICK_UNKNOWN )
    {
        p_pmt->pcr.i_first_dts = TO_SCALE(p_block->i_dts);
    }
    else if( p_block->i_dts - FROM_SCALE(p_pmt->pcr.i_first_dts) > VLC_TICK_FROM_MS(500) ) /* "PCR repeat rate shall not exceed 100ms" */
    {
        if( p_pmt->pcr.i_current < 0 &&
            GetPID( p_sys, p_pmt->i_pid_pcr )->probed.i_pcr_count == 0 )
        {
            int i_cand = FindPCRCandidate( p_pmt );
            p_pmt->i_pid_pcr = i_cand;
            if ( GetPID( p_sys, p_pmt->i_pid_pcr )->probed.i_pcr_count == 0 )
                p_pmt->pcr.b_disable = true;
            msg_Warn( p_demux, "No PCR received for program %d, set up workaround using pid %d",
                      p_pmt->i_number, i_cand );
            UpdatePESFilters( p_demux, p_sys->seltype == PROGRAM_ALL );
        }
        p_pmt->pcr.b_fix_done = true;
    }
}