#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_14__ {char i_type; scalar_t__ i_length; char i_compression; int /*<<< orphan*/  i_keyframe; scalar_t__ i_timecode; } ;
typedef  TYPE_1__ frame_header_t ;
struct TYPE_15__ {int /*<<< orphan*/  out; int /*<<< orphan*/  s; TYPE_3__* p_sys; } ;
typedef  TYPE_2__ demux_t ;
struct TYPE_16__ {scalar_t__ i_pcr; scalar_t__ p_es_video; int /*<<< orphan*/  fh_buffer; scalar_t__ p_es_audio; int /*<<< orphan*/  idx; int /*<<< orphan*/  b_index; } ;
typedef  TYPE_3__ demux_sys_t ;
struct TYPE_17__ {scalar_t__ i_dts; scalar_t__ i_pts; int /*<<< orphan*/  p_buffer; } ;
typedef  TYPE_4__ block_t ;

/* Variables and functions */
 scalar_t__ FrameHeaderLoad (TYPE_2__*,TYPE_1__*) ; 
 scalar_t__ NUV_FH_SIZE ; 
 int VLC_DEMUXER_EGENERIC ; 
 int VLC_DEMUXER_EOF ; 
 int VLC_DEMUXER_SUCCESS ; 
 scalar_t__ VLC_TICK_0 ; 
 scalar_t__ VLC_TICK_INVALID ; 
 TYPE_4__* block_Realloc (TYPE_4__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  block_Release (TYPE_4__*) ; 
 int /*<<< orphan*/  demux_IndexAppend (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  es_out_Send (int /*<<< orphan*/ ,scalar_t__,TYPE_4__*) ; 
 int /*<<< orphan*/  es_out_SetPCR (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_2__*,char*,char) ; 
 scalar_t__ unlikely (int) ; 
 TYPE_4__* vlc_stream_Block (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ vlc_stream_Read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ vlc_stream_Tell (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int Demux( demux_t *p_demux )
{
    demux_sys_t *p_sys = p_demux->p_sys;
    frame_header_t fh;
    block_t *p_data;

    for( ;; )
    {
        if( FrameHeaderLoad( p_demux, &fh ) )
            return VLC_DEMUXER_EOF;

        if( fh.i_type == 'A' || fh.i_type == 'V' )
            break;

        /* TODO add support for some block type */

        if( fh.i_type != 'R' && fh.i_length > 0 )
        {
            if( vlc_stream_Read( p_demux->s, NULL,
                                 fh.i_length ) != fh.i_length )
                return VLC_DEMUXER_EGENERIC;
        }
    }

    /* */
    if( ( p_data = vlc_stream_Block( p_demux->s, fh.i_length ) ) == NULL )
        return VLC_DEMUXER_EOF;

    p_data->i_dts = VLC_TICK_0 + (int64_t)fh.i_timecode * 1000;
    p_data->i_pts = (fh.i_type == 'V') ? VLC_TICK_INVALID : p_data->i_dts;

    /* only add keyframes to index */
    if( !fh.i_keyframe && !p_sys->b_index )
        demux_IndexAppend( &p_sys->idx,
                           p_data->i_dts - VLC_TICK_0,
                           vlc_stream_Tell(p_demux->s) - NUV_FH_SIZE );

    /* */
    if( p_sys->i_pcr < 0 || p_sys->i_pcr < p_data->i_dts - VLC_TICK_0 )
    {
        p_sys->i_pcr = p_data->i_dts - VLC_TICK_0;
        es_out_SetPCR( p_demux->out, VLC_TICK_0 + p_sys->i_pcr );
    }

    if( fh.i_type == 'A' && p_sys->p_es_audio )
    {
        if( fh.i_compression == '3' )
            es_out_Send( p_demux->out, p_sys->p_es_audio, p_data );
        else
        {
            msg_Dbg( p_demux, "unsupported compression %c for audio (upload samples)", fh.i_compression );
            block_Release( p_data );
        }
    }
    else if( fh.i_type == 'V' && p_sys->p_es_video )
    {
        if( fh.i_compression >='0' && fh.i_compression <='3' )
        {
            /* for rtjpeg data, the header is also needed */
            p_data = block_Realloc( p_data, NUV_FH_SIZE, fh.i_length );
            if( unlikely(!p_data) )
                return VLC_DEMUXER_EGENERIC;
            memcpy( p_data->p_buffer, p_sys->fh_buffer, NUV_FH_SIZE );
        }
        /* 0,1,2,3 -> rtjpeg, >=4 mpeg4 */
        if( fh.i_compression >= '0' )
            es_out_Send( p_demux->out, p_sys->p_es_video, p_data );
        else
        {
            msg_Dbg( p_demux, "unsupported compression %c for video (upload samples)", fh.i_compression );
            block_Release( p_data );
        }
    }
    else
    {
        block_Release( p_data );
    }

    return VLC_DEMUXER_SUCCESS;
}