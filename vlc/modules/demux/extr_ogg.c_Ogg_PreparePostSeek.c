#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int i_streams; int /*<<< orphan*/  i_pcr; int /*<<< orphan*/  oy; TYPE_2__** pp_stream; } ;
typedef  TYPE_1__ demux_sys_t ;
struct TYPE_5__ {int /*<<< orphan*/  i_next_block_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_FLAG_DISCONTINUITY ; 
 int /*<<< orphan*/  Ogg_ResetStream (TYPE_2__*) ; 
 int /*<<< orphan*/  VLC_TICK_INVALID ; 
 int /*<<< orphan*/  ogg_sync_reset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Ogg_PreparePostSeek( demux_sys_t *p_sys )
{
    for( int i = 0; i < p_sys->i_streams; i++ )
    {
        Ogg_ResetStream( p_sys->pp_stream[i] );
        p_sys->pp_stream[i]->i_next_block_flags = BLOCK_FLAG_DISCONTINUITY;
    }

    ogg_sync_reset( &p_sys->oy );
    p_sys->i_pcr = VLC_TICK_INVALID;
}