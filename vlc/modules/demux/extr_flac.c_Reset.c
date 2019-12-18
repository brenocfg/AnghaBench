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
struct TYPE_3__ {int /*<<< orphan*/ * p_current_block; int /*<<< orphan*/  p_packetizer; int /*<<< orphan*/  i_pts; } ;
typedef  TYPE_1__ demux_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  FlushPacketizer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VLC_TICK_INVALID ; 
 int /*<<< orphan*/  block_Release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Reset( demux_sys_t *p_sys )
{
    p_sys->i_pts = VLC_TICK_INVALID;

    FlushPacketizer( p_sys->p_packetizer );
    if( p_sys->p_current_block )
    {
        block_Release( p_sys->p_current_block );
        p_sys->p_current_block = NULL;
    }
}