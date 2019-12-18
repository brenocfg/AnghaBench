#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;
struct TYPE_9__ {int /*<<< orphan*/  out; int /*<<< orphan*/  s; TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_10__ {int /*<<< orphan*/  p_es; int /*<<< orphan*/  pts; } ;
typedef  TYPE_2__ demux_sys_t ;
struct TYPE_11__ {scalar_t__ i_pts; scalar_t__ i_dts; } ;
typedef  TYPE_3__ block_t ;

/* Variables and functions */
 scalar_t__ CDG_FRAME_DELTA ; 
 int /*<<< orphan*/  CDG_FRAME_SIZE ; 
 scalar_t__ PosToDate (TYPE_1__*) ; 
 int VLC_DEMUXER_EOF ; 
 int VLC_DEMUXER_SUCCESS ; 
 scalar_t__ VLC_TICK_0 ; 
 scalar_t__ date_Get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  date_Set (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  es_out_Send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  es_out_SetPCR (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*) ; 
 TYPE_3__* vlc_stream_Block (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int Demux( demux_t *p_demux )
{
    demux_sys_t *p_sys = p_demux->p_sys;
    block_t     *p_block;
    vlc_tick_t  i_date;

    p_block = vlc_stream_Block( p_demux->s, CDG_FRAME_SIZE );
    if( p_block == NULL )
    {
        msg_Dbg( p_demux, "cannot read data, eof" );
        return VLC_DEMUXER_EOF;
    }

    i_date = PosToDate( p_demux );
    if( i_date >= date_Get( &p_sys->pts ) + CDG_FRAME_DELTA )
    {
        p_block->i_dts = p_block->i_pts = VLC_TICK_0 + i_date;
        date_Set( &p_sys->pts, VLC_TICK_0 + i_date );
    }
    else
    {
        p_block->i_dts = VLC_TICK_0 + i_date;
        p_block->i_pts = date_Get( &p_sys->pts );
    }

    es_out_SetPCR( p_demux->out, p_block->i_pts );
    es_out_Send( p_demux->out, p_sys->p_es, p_block );
    return VLC_DEMUXER_SUCCESS;
}