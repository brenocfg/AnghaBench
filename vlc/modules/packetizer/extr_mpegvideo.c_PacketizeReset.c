#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ decoder_t ;
struct TYPE_4__ {int b_frame_slice; int i_prev_temporal_ref; int /*<<< orphan*/  b_sync_on_intra_frame; int /*<<< orphan*/  b_waiting_iframe; int /*<<< orphan*/  i_last_ref_pts; int /*<<< orphan*/  i_pts; int /*<<< orphan*/  i_dts; int /*<<< orphan*/  prev_iframe_dts; int /*<<< orphan*/  dts; int /*<<< orphan*/ * p_frame; int /*<<< orphan*/ ** pp_last; int /*<<< orphan*/  i_next_block_flags; } ;
typedef  TYPE_2__ decoder_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_FLAG_DISCONTINUITY ; 
 int /*<<< orphan*/  VLC_TICK_INVALID ; 
 int /*<<< orphan*/  VLC_UNUSED (int) ; 
 int /*<<< orphan*/  block_ChainRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  date_Set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void PacketizeReset( void *p_private, bool b_flush )
{
    VLC_UNUSED(b_flush);
    decoder_t *p_dec = p_private;
    decoder_sys_t *p_sys = p_dec->p_sys;

    p_sys->i_next_block_flags = BLOCK_FLAG_DISCONTINUITY;
    if( p_sys->p_frame )
    {
        block_ChainRelease( p_sys->p_frame );
        p_sys->p_frame = NULL;
        p_sys->pp_last = &p_sys->p_frame;
        p_sys->b_frame_slice = false;
    }
    date_Set( &p_sys->dts, VLC_TICK_INVALID );
    date_Set( &p_sys->prev_iframe_dts, VLC_TICK_INVALID );
    p_sys->i_dts =
    p_sys->i_pts =
    p_sys->i_last_ref_pts = VLC_TICK_INVALID;
    p_sys->b_waiting_iframe = p_sys->b_sync_on_intra_frame;
    p_sys->i_prev_temporal_ref = 2048;
}