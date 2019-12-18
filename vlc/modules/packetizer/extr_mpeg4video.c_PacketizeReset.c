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
struct TYPE_4__ {scalar_t__ i_last_timeincr; scalar_t__ i_last_time; scalar_t__ i_time_ref; scalar_t__ i_last_time_ref; int /*<<< orphan*/  i_last_ref_pts; int /*<<< orphan*/  i_interpolated_dts; int /*<<< orphan*/  i_interpolated_pts; int /*<<< orphan*/ * p_frame; int /*<<< orphan*/ ** pp_last; } ;
typedef  TYPE_2__ decoder_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_TICK_INVALID ; 
 int /*<<< orphan*/  block_ChainRelease (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void PacketizeReset( void *p_private, bool b_flush )
{
    decoder_t *p_dec = p_private;
    decoder_sys_t *p_sys = p_dec->p_sys;

    if( b_flush )
    {
        if( p_sys->p_frame )
            block_ChainRelease( p_sys->p_frame );
        p_sys->p_frame = NULL;
        p_sys->pp_last = &p_sys->p_frame;
    }

    p_sys->i_interpolated_pts =
    p_sys->i_interpolated_dts =
    p_sys->i_last_ref_pts = VLC_TICK_INVALID;

    p_sys->i_last_time_ref =
    p_sys->i_time_ref =
    p_sys->i_last_time =
    p_sys->i_last_timeincr = 0;
}