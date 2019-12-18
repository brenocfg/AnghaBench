#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;
struct TYPE_12__ {int /*<<< orphan*/  out; TYPE_4__* p_sys; } ;
typedef  TYPE_3__ demux_t ;
struct TYPE_11__ {size_t i_current; size_t i_count; TYPE_1__* p_array; } ;
struct TYPE_13__ {scalar_t__ i_next_demux_time; int i_next_block_flags; int b_first_time; TYPE_2__ index; int /*<<< orphan*/  b_slave; int /*<<< orphan*/  es; } ;
typedef  TYPE_4__ demux_sys_t ;
struct TYPE_14__ {scalar_t__ i_dts; scalar_t__ i_pts; int i_flags; scalar_t__ i_length; } ;
typedef  TYPE_5__ block_t ;
struct TYPE_10__ {scalar_t__ time; int active; } ;

/* Variables and functions */
 int BLOCK_FLAG_DISCONTINUITY ; 
 int VLC_DEMUXER_EOF ; 
 int VLC_DEMUXER_SUCCESS ; 
 scalar_t__ VLC_TICK_0 ; 
 scalar_t__ VLC_TICK_FROM_SEC (int) ; 
 TYPE_5__* demux_From (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  es_out_Send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  es_out_SetPCR (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int Demux( demux_t *p_demux )
{
    demux_sys_t *p_sys = p_demux->p_sys;

    vlc_tick_t i_barrier = p_sys->i_next_demux_time;

    while( p_sys->index.i_current < p_sys->index.i_count &&
           p_sys->index.p_array[p_sys->index.i_current].time <= i_barrier )
    {
        /* Find start and end of our interval */
        vlc_tick_t i_start_time = p_sys->index.p_array[p_sys->index.i_current].time;
        vlc_tick_t i_end_time = i_start_time;
        /* use next interval time as end time */
        while( ++p_sys->index.i_current < p_sys->index.i_count )
        {
            if( i_start_time != p_sys->index.p_array[p_sys->index.i_current].time )
            {
                i_end_time = p_sys->index.p_array[p_sys->index.i_current].time;
                break;
            }
        }

        block_t *p_block = demux_From( p_demux, i_start_time );
        if( p_block )
        {
            p_block->i_length = i_end_time - i_start_time;
            p_block->i_dts = p_block->i_pts = VLC_TICK_0 + i_start_time;

            if( p_sys->i_next_block_flags )
            {
                p_block->i_flags = p_sys->i_next_block_flags;
                p_sys->i_next_block_flags = 0;
            }

            if ( !p_sys->b_slave && p_sys->b_first_time )
            {
                es_out_SetPCR( p_demux->out, p_block->i_dts );
                p_sys->b_first_time = false;
            }

            es_out_Send( p_demux->out, p_sys->es, p_block );
        }

        if( p_sys->index.i_current < p_sys->index.i_count &&
            p_sys->index.p_array[p_sys->index.i_current].active > 1 )
        {
            /* we'll need to clear up overlaps */
            p_sys->i_next_block_flags |= BLOCK_FLAG_DISCONTINUITY;
        }
    }

    if ( !p_sys->b_slave )
    {
        es_out_SetPCR( p_demux->out, VLC_TICK_0 + i_barrier );
        p_sys->i_next_demux_time += VLC_TICK_FROM_SEC(1);
    }

    if( p_sys->index.i_current >= p_sys->index.i_count )
        return VLC_DEMUXER_EOF;

    return VLC_DEMUXER_SUCCESS;
}