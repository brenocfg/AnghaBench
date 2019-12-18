#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;
struct TYPE_18__ {int /*<<< orphan*/  packet; int /*<<< orphan*/  bytes; } ;
typedef  TYPE_6__ ogg_packet ;
struct TYPE_17__ {TYPE_8__* p_blocks; } ;
struct TYPE_16__ {int i_codec; int /*<<< orphan*/  i_cat; } ;
struct TYPE_14__ {int /*<<< orphan*/  p_info; } ;
struct TYPE_13__ {int i_framesize; int i_framesperpacket; } ;
struct TYPE_15__ {TYPE_2__ vorbis; TYPE_1__ speex; } ;
struct TYPE_19__ {TYPE_5__ queue; int /*<<< orphan*/  dts; TYPE_4__ fmt; TYPE_3__ special; } ;
typedef  TYPE_7__ logical_stream_t ;
typedef  int /*<<< orphan*/  demux_t ;
typedef  int /*<<< orphan*/  date_t ;
struct TYPE_20__ {scalar_t__ i_dts; int i_flags; int i_nb_samples; struct TYPE_20__* p_next; int /*<<< orphan*/  p_buffer; int /*<<< orphan*/  i_buffer; } ;
typedef  TYPE_8__ block_t ;

/* Variables and functions */
 int BLOCK_FLAG_HEADER ; 
 int Ogg_OpusPacketDuration (TYPE_6__*) ; 
 int /*<<< orphan*/  VIDEO_ES ; 
#define  VLC_CODEC_OPUS 130 
#define  VLC_CODEC_SPEEX 129 
#define  VLC_CODEC_VORBIS 128 
 scalar_t__ VLC_TICK_INVALID ; 
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VORBIS_HEADERS_VALID (TYPE_7__*) ; 
 scalar_t__ date_Decrement (int /*<<< orphan*/ *,unsigned int) ; 
 scalar_t__ date_Get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  date_Increment (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  date_Set (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*) ; 
 long vorbis_packet_blocksize (int /*<<< orphan*/ ,TYPE_6__*) ; 

__attribute__((used)) static vlc_tick_t Ogg_FixupOutputQueue( demux_t *p_demux, logical_stream_t *p_stream )
{
    vlc_tick_t i_enddts = VLC_TICK_INVALID;

#ifdef HAVE_LIBVORBIS
    long i_prev_blocksize = 0;
#else
    VLC_UNUSED(p_demux);
#endif
    // PASS 1, set number of samples
    unsigned i_total_samples = 0;
    for( block_t *p_block = p_stream->queue.p_blocks; p_block; p_block = p_block->p_next )
    {
        if( p_block->i_dts != VLC_TICK_INVALID )
        {
            i_enddts = p_block->i_dts;
            break;
        }

        if( p_block->i_flags & BLOCK_FLAG_HEADER )
            continue;

        ogg_packet dumb_packet;
        dumb_packet.bytes = p_block->i_buffer;
        dumb_packet.packet = p_block->p_buffer;

        switch( p_stream->fmt.i_codec )
        {
            case VLC_CODEC_SPEEX:
                p_block->i_nb_samples = p_stream->special.speex.i_framesize *
                                        p_stream->special.speex.i_framesperpacket;
                break;
            case VLC_CODEC_OPUS:
                p_block->i_nb_samples = Ogg_OpusPacketDuration( &dumb_packet );
                break;
#ifdef HAVE_LIBVORBIS
            case VLC_CODEC_VORBIS:
            {
                if( !VORBIS_HEADERS_VALID(p_stream) )
                {
                    msg_Err( p_demux, "missing vorbis headers, can't compute block size" );
                    break;
                }
                long i_blocksize = vorbis_packet_blocksize( p_stream->special.vorbis.p_info,
                                                            &dumb_packet );
                if ( i_prev_blocksize )
                    p_block->i_nb_samples = ( i_blocksize + i_prev_blocksize ) / 4;
                else
                    p_block->i_nb_samples = i_blocksize / 2;
                i_prev_blocksize = i_blocksize;
                break;
            }
#endif
            default:
                if( p_stream->fmt.i_cat == VIDEO_ES )
                    p_block->i_nb_samples = 1;
                break;
        }
        i_total_samples += p_block->i_nb_samples;
    }

    // PASS 2
    if( i_enddts != VLC_TICK_INVALID )
    {
        date_t d = p_stream->dts;
        date_Set( &d, i_enddts );
        i_enddts = date_Decrement( &d, i_total_samples );
        for( block_t *p_block = p_stream->queue.p_blocks; p_block; p_block = p_block->p_next )
        {
            if( p_block->i_dts != VLC_TICK_INVALID )
                break;
            if( p_block->i_flags & BLOCK_FLAG_HEADER )
                continue;
            p_block->i_dts = date_Get( &d );
            date_Increment( &d, p_block->i_nb_samples );
        }
    } /* else can't do anything, no timestamped blocks in stream */

    return i_enddts;
}