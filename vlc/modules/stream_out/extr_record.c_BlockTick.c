#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;
struct TYPE_3__ {scalar_t__ i_dts; scalar_t__ i_pts; } ;
typedef  TYPE_1__ block_t ;

/* Variables and functions */
 scalar_t__ VLC_TICK_INVALID ; 
 scalar_t__ likely (int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static vlc_tick_t BlockTick( const block_t *p_block )
{
    if( unlikely(!p_block) )
        return VLC_TICK_INVALID;
    else if( likely(p_block->i_dts != VLC_TICK_INVALID) )
        return p_block->i_dts;
    else
        return p_block->i_pts;
}