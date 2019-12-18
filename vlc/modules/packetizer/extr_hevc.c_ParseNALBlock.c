#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;
typedef  scalar_t__ uint8_t ;
struct TYPE_22__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ decoder_t ;
struct TYPE_23__ {int b_need_ts; scalar_t__ pts; scalar_t__ sets; int /*<<< orphan*/  dts; scalar_t__ b_recovery_point; } ;
typedef  TYPE_2__ decoder_sys_t ;
struct TYPE_24__ {int i_flags; scalar_t__ i_dts; scalar_t__ i_pts; int i_buffer; int* p_buffer; } ;
typedef  TYPE_3__ block_t ;

/* Variables and functions */
 int BLOCK_FLAG_AU_END ; 
 int BLOCK_FLAG_DROP ; 
 scalar_t__ COMPLETE ; 
 TYPE_3__* GatherAndValidateChain (TYPE_3__*) ; 
 scalar_t__ HEVC_NAL_VPS ; 
 scalar_t__ MISSING ; 
 TYPE_3__* OutputQueues (TYPE_2__*,int) ; 
 TYPE_3__* ParseNonVCL (TYPE_1__*,scalar_t__,TYPE_3__*) ; 
 TYPE_3__* ParseVCL (TYPE_1__*,scalar_t__,TYPE_3__*) ; 
 scalar_t__ SENT ; 
 int /*<<< orphan*/  SetOutputBlockProperties (TYPE_1__*,TYPE_3__*) ; 
 scalar_t__ VLC_TICK_INVALID ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  block_Release (TYPE_3__*) ; 
 scalar_t__ date_Get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  date_Set (int /*<<< orphan*/ *,scalar_t__ const) ; 
 scalar_t__ hevc_getNALType (int*) ; 
 int /*<<< orphan*/  msg_Info (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_1__*,char*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static block_t *ParseNALBlock(decoder_t *p_dec, bool *pb_ts_used, block_t *p_frag)
{
    decoder_sys_t *p_sys = p_dec->p_sys;
    *pb_ts_used = false;
    bool b_au_end = p_frag->i_flags & BLOCK_FLAG_AU_END;

    if(p_sys->b_need_ts)
    {
        if(p_frag->i_dts != VLC_TICK_INVALID)
            date_Set(&p_sys->dts, p_frag->i_dts);
        p_sys->pts = p_frag->i_pts;
        if(date_Get( &p_sys->dts ) != VLC_TICK_INVALID)
            p_sys->b_need_ts = false;
        *pb_ts_used = true;
    }

    if(unlikely(p_frag->i_buffer < 5))
    {
        msg_Warn(p_dec,"NAL too small");
        block_Release(p_frag);
        return NULL;
    }

    if(p_frag->p_buffer[4] & 0x80)
    {
        msg_Warn(p_dec,"Forbidden zero bit not null, corrupted NAL");
        block_Release(p_frag);
        return GatherAndValidateChain(OutputQueues(p_sys, false)); /* will drop */
    }

    /* Get NALU type */
    const vlc_tick_t dts = p_frag->i_dts, pts = p_frag->i_pts;
    block_t * p_output = NULL;
    uint8_t i_nal_type = hevc_getNALType(&p_frag->p_buffer[4]);

    if (i_nal_type < HEVC_NAL_VPS)
    {
        /* NAL is a VCL NAL */
        p_output = ParseVCL(p_dec, i_nal_type, p_frag);
        if (p_output && (p_output->i_flags & BLOCK_FLAG_DROP))
            msg_Info(p_dec, "Waiting for VPS/SPS/PPS");
    }
    else
    {
        p_output = ParseNonVCL(p_dec, i_nal_type, p_frag);
    }

    if( !p_output && b_au_end )
        p_output = OutputQueues(p_sys, p_sys->sets != MISSING &&
                                       p_sys->b_recovery_point);

    p_output = GatherAndValidateChain(p_output);
    if(p_output)
    {
        if(p_sys->sets != SENT)
        {
            assert(p_sys->sets == COMPLETE);
            p_sys->sets = SENT;
        }

        SetOutputBlockProperties( p_dec, p_output );
        if (dts != VLC_TICK_INVALID)
            date_Set(&p_sys->dts, dts);
        p_sys->pts = pts;
        *pb_ts_used = true;
    }

    return p_output;
}