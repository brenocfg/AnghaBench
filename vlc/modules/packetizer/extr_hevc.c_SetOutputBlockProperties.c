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
typedef  scalar_t__ vlc_tick_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ decoder_t ;
struct TYPE_7__ {scalar_t__ pts; int /*<<< orphan*/ * p_timing; int /*<<< orphan*/  dts; scalar_t__ p_active_sps; } ;
typedef  TYPE_2__ decoder_sys_t ;
struct TYPE_8__ {scalar_t__ i_length; int /*<<< orphan*/  i_flags; } ;
typedef  TYPE_3__ block_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_FLAG_AU_END ; 
 scalar_t__ const VLC_TICK_INVALID ; 
 scalar_t__ const date_Get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  date_Increment (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hevc_get_num_clock_ts (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hevc_release_sei_pic_timing (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void SetOutputBlockProperties(decoder_t *p_dec, block_t *p_output)
{
    decoder_sys_t *p_sys = p_dec->p_sys;
    /* Set frame duration */
    if(p_sys->p_active_sps)
    {
        uint8_t i_num_clock_ts = hevc_get_num_clock_ts(p_sys->p_active_sps,
                                                       p_sys->p_timing);
        const vlc_tick_t i_start = date_Get(&p_sys->dts);
        if( i_start != VLC_TICK_INVALID )
        {
            date_Increment(&p_sys->dts, i_num_clock_ts);
            p_output->i_length = date_Get(&p_sys->dts) - i_start;
        }
        p_sys->pts = VLC_TICK_INVALID;
    }
    p_output->i_flags &= ~BLOCK_FLAG_AU_END;
    hevc_release_sei_pic_timing(p_sys->p_timing);
    p_sys->p_timing = NULL;
}