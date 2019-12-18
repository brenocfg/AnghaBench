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
typedef  scalar_t__ const int64_t ;
struct TYPE_12__ {int /*<<< orphan*/  out; int /*<<< orphan*/  s; TYPE_4__* p_sys; } ;
typedef  TYPE_3__ demux_t ;
struct TYPE_10__ {int /*<<< orphan*/  i_channels; } ;
struct TYPE_11__ {int /*<<< orphan*/  i_codec; TYPE_1__ audio; } ;
struct TYPE_13__ {unsigned int i_frame_size; scalar_t__ i_data_size; scalar_t__ i_data_pos; int /*<<< orphan*/  i_frame_samples; int /*<<< orphan*/  pts; int /*<<< orphan*/  p_es; TYPE_2__ fmt; int /*<<< orphan*/  pi_chan_table; scalar_t__ i_chans_to_reorder; } ;
typedef  TYPE_4__ demux_sys_t ;
struct TYPE_14__ {int /*<<< orphan*/  i_buffer; int /*<<< orphan*/  p_buffer; int /*<<< orphan*/  i_pts; int /*<<< orphan*/  i_dts; } ;
typedef  TYPE_5__ block_t ;

/* Variables and functions */
 int VLC_DEMUXER_EOF ; 
 int VLC_DEMUXER_SUCCESS ; 
 int /*<<< orphan*/  aout_ChannelReorder (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  date_Get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  date_Increment (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  es_out_Send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  es_out_SetPCR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_3__*,char*) ; 
 TYPE_5__* vlc_stream_Block (int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ vlc_stream_Tell (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int Demux( demux_t *p_demux )
{
    demux_sys_t *p_sys = p_demux->p_sys;
    block_t     *p_block;
    const int64_t i_pos = vlc_stream_Tell( p_demux->s );
    unsigned int i_read_size = p_sys->i_frame_size;

    if( p_sys->i_data_size > 0 )
    {
        int64_t i_end = p_sys->i_data_pos + p_sys->i_data_size;
        if ( i_pos >= i_end )
            return VLC_DEMUXER_EOF;  /* EOF */

        /* Don't read past data chunk boundary */
        if ( i_end < i_pos + i_read_size )
            i_read_size = i_end - i_pos;
    }

    if( ( p_block = vlc_stream_Block( p_demux->s, i_read_size ) ) == NULL )
    {
        msg_Warn( p_demux, "cannot read data" );
        return VLC_DEMUXER_EOF;
    }

    p_block->i_dts =
    p_block->i_pts = date_Get( &p_sys->pts );

    /* set PCR */
    es_out_SetPCR( p_demux->out, p_block->i_pts );

    /* Do the channel reordering */
    if( p_sys->i_chans_to_reorder )
        aout_ChannelReorder( p_block->p_buffer, p_block->i_buffer,
                             p_sys->fmt.audio.i_channels,
                             p_sys->pi_chan_table, p_sys->fmt.i_codec );

    es_out_Send( p_demux->out, p_sys->p_es, p_block );

    date_Increment( &p_sys->pts, p_sys->i_frame_samples );

    return VLC_DEMUXER_SUCCESS;
}