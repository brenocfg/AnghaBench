#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;
typedef  int /*<<< orphan*/  tt_basenode_t ;
struct vlc_memstream {int /*<<< orphan*/  length; int /*<<< orphan*/  ptr; } ;
struct TYPE_9__ {int /*<<< orphan*/  out; TYPE_3__* p_sys; } ;
typedef  TYPE_2__ demux_t ;
struct TYPE_8__ {int i_current; int i_count; int /*<<< orphan*/ * p_array; } ;
struct TYPE_10__ {scalar_t__ i_next_demux_time; int b_first_time; TYPE_1__ times; int /*<<< orphan*/  b_slave; int /*<<< orphan*/  p_es; scalar_t__ p_rootnode; } ;
typedef  TYPE_3__ demux_sys_t ;
struct TYPE_11__ {scalar_t__ i_dts; scalar_t__ i_pts; scalar_t__ i_length; } ;
typedef  TYPE_4__ block_t ;

/* Variables and functions */
 int VLC_DEMUXER_EGENERIC ; 
 int VLC_DEMUXER_EOF ; 
 int VLC_DEMUXER_SUCCESS ; 
 scalar_t__ VLC_SUCCESS ; 
 scalar_t__ const VLC_TICK_0 ; 
 scalar_t__ const VLC_TICK_FROM_MS (int) ; 
 TYPE_4__* block_heap_Alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  es_out_Send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  es_out_SetPCR (int /*<<< orphan*/ ,scalar_t__ const) ; 
 int /*<<< orphan*/  tt_node_ToText (struct vlc_memstream*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ tt_time_Convert (int /*<<< orphan*/ *) ; 
 scalar_t__ vlc_memstream_close (struct vlc_memstream*) ; 
 scalar_t__ vlc_memstream_open (struct vlc_memstream*) ; 

__attribute__((used)) static int Demux( demux_t* p_demux )
{
    demux_sys_t* p_sys = p_demux->p_sys;

    /* Last one must be an end time */
    while( p_sys->times.i_current + 1 < p_sys->times.i_count &&
           tt_time_Convert( &p_sys->times.p_array[p_sys->times.i_current] ) <= p_sys->i_next_demux_time )
    {
        const vlc_tick_t i_playbacktime =
                tt_time_Convert( &p_sys->times.p_array[p_sys->times.i_current] );
        const vlc_tick_t i_playbackendtime =
                tt_time_Convert( &p_sys->times.p_array[p_sys->times.i_current + 1] ) - 1;

        if ( !p_sys->b_slave && p_sys->b_first_time )
        {
            es_out_SetPCR( p_demux->out, VLC_TICK_0 + i_playbacktime );
            p_sys->b_first_time = false;
        }

        struct vlc_memstream stream;

        if( vlc_memstream_open( &stream ) )
            return VLC_DEMUXER_EGENERIC;

        tt_node_ToText( &stream, (tt_basenode_t *) p_sys->p_rootnode,
                        &p_sys->times.p_array[p_sys->times.i_current] );

        if( vlc_memstream_close( &stream ) == VLC_SUCCESS )
        {
            block_t* p_block = block_heap_Alloc( stream.ptr, stream.length );
            if( p_block )
            {
                p_block->i_dts =
                    p_block->i_pts = VLC_TICK_0 + i_playbacktime;
                p_block->i_length = i_playbackendtime - i_playbacktime;

                es_out_Send( p_demux->out, p_sys->p_es, p_block );
            }
        }

        p_sys->times.i_current++;
    }

    if ( !p_sys->b_slave )
    {
        es_out_SetPCR( p_demux->out, VLC_TICK_0 + p_sys->i_next_demux_time );
        p_sys->i_next_demux_time += VLC_TICK_FROM_MS(125);
    }

    if( p_sys->times.i_current + 1 >= p_sys->times.i_count )
        return VLC_DEMUXER_EOF;

    return VLC_DEMUXER_SUCCESS;
}