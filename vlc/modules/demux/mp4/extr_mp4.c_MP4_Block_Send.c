#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  stream_t ;
struct TYPE_17__ {int /*<<< orphan*/  i_channels; } ;
struct TYPE_18__ {int /*<<< orphan*/  i_codec; TYPE_1__ audio; } ;
struct TYPE_19__ {int i_block_flags; int i_next_block_flags; int /*<<< orphan*/  p_es; int /*<<< orphan*/  i_pts_backup; int /*<<< orphan*/  i_dts_backup; scalar_t__ p_asf; TYPE_2__ fmt; int /*<<< orphan*/  rgi_chans_reordering; scalar_t__ b_chans_reorder; } ;
typedef  TYPE_3__ mp4_track_t ;
struct TYPE_20__ {int /*<<< orphan*/  out; int /*<<< orphan*/ * s; TYPE_5__* p_sys; } ;
typedef  TYPE_4__ demux_t ;
struct TYPE_21__ {int /*<<< orphan*/  asfpacketsys; } ;
typedef  TYPE_5__ demux_sys_t ;
struct TYPE_22__ {int i_flags; int /*<<< orphan*/  i_buffer; int /*<<< orphan*/  i_pts; int /*<<< orphan*/  i_dts; int /*<<< orphan*/  p_buffer; } ;
typedef  TYPE_6__ block_t ;

/* Variables and functions */
 int /*<<< orphan*/  DemuxASFPacket (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__* MP4_Block_Convert (TYPE_4__*,TYPE_3__*,TYPE_6__*) ; 
 int /*<<< orphan*/  aout_ChannelReorder (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  block_Release (TYPE_6__*) ; 
 int /*<<< orphan*/  es_out_Send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  vlc_stream_Delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_stream_MemoryNew (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void MP4_Block_Send( demux_t *p_demux, mp4_track_t *p_track, block_t *p_block )
{
    demux_sys_t *p_sys = p_demux->p_sys;

    p_block = MP4_Block_Convert( p_demux, p_track, p_block );
    if( p_block == NULL )
        return;

    if ( p_track->b_chans_reorder )
    {
        aout_ChannelReorder( p_block->p_buffer, p_block->i_buffer,
                             p_track->fmt.audio.i_channels,
                             p_track->rgi_chans_reordering,
                             p_track->fmt.i_codec );
    }

    p_block->i_flags |= p_track->i_block_flags;
    if( p_track->i_next_block_flags )
    {
        p_block->i_flags |= p_track->i_next_block_flags;
        p_track->i_next_block_flags = 0;
    }

    /* ASF packets in mov */
    if( p_track->p_asf )
    {
        /* Fake a new stream from MP4 block */
        stream_t *p_stream = p_demux->s;
        p_demux->s = vlc_stream_MemoryNew( p_demux, p_block->p_buffer, p_block->i_buffer, true );
        if ( p_demux->s )
        {
            p_track->i_dts_backup = p_block->i_dts;
            p_track->i_pts_backup = p_block->i_pts;
            /* And demux it as ASF packet */
            DemuxASFPacket( &p_sys->asfpacketsys, p_block->i_buffer, p_block->i_buffer );
            vlc_stream_Delete(p_demux->s);
        }
        block_Release(p_block);
        p_demux->s = p_stream;
    }
    else
        es_out_Send( p_demux->out, p_track->p_es, p_block );
}