#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;
typedef  int /*<<< orphan*/  decoder_t ;
struct TYPE_6__ {scalar_t__ i_dts; scalar_t__ i_pts; } ;
typedef  TYPE_1__ block_t ;

/* Variables and functions */
 TYPE_1__* ParseMPEGBlock (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static block_t *PacketizeParse( void *p_private, bool *pb_ts_used, block_t *p_block )
{
    decoder_t *p_dec = p_private;
    const vlc_tick_t i_dts = p_block->i_dts;
    const vlc_tick_t i_pts = p_block->i_pts;

    block_t *p_au = ParseMPEGBlock( p_dec, p_block );

    *pb_ts_used = p_au &&  p_au->i_dts == i_dts && p_au->i_pts == i_pts;

    return p_au;
}