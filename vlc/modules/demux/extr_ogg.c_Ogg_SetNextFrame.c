#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;
struct TYPE_21__ {int bytes; int /*<<< orphan*/  granulepos; } ;
typedef  TYPE_5__ ogg_packet ;
typedef  int /*<<< orphan*/  ogg_int64_t ;
struct TYPE_23__ {int i_divider_num; int i_divider_den; } ;
struct TYPE_20__ {scalar_t__ i_cat; int i_codec; int i_bitrate; } ;
struct TYPE_18__ {long i_prev_blocksize; int /*<<< orphan*/  p_info; } ;
struct TYPE_17__ {int i_framesize; int i_framesperpacket; } ;
struct TYPE_19__ {TYPE_2__ vorbis; TYPE_1__ speex; } ;
struct TYPE_22__ {int b_interpolation_failed; TYPE_8__ dts; TYPE_4__ fmt; TYPE_3__ special; int /*<<< orphan*/  b_contiguous; } ;
typedef  TYPE_6__ logical_stream_t ;
typedef  int int64_t ;
typedef  int /*<<< orphan*/  demux_t ;

/* Variables and functions */
 scalar_t__ AUDIO_ES ; 
 scalar_t__ Ogg_GranuleIsValid (TYPE_6__*,int /*<<< orphan*/ ) ; 
 scalar_t__ Ogg_GranuleToTime (TYPE_6__*,int /*<<< orphan*/ ,int,int) ; 
 int Ogg_OpusPacketDuration (TYPE_5__*) ; 
 scalar_t__ VIDEO_ES ; 
#define  VLC_CODEC_OPUS 130 
#define  VLC_CODEC_SPEEX 129 
#define  VLC_CODEC_VORBIS 128 
 scalar_t__ VLC_TICK_INVALID ; 
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VORBIS_HEADERS_VALID (TYPE_6__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ date_Get (TYPE_8__*) ; 
 int /*<<< orphan*/  date_Increment (TYPE_8__*,int) ; 
 int /*<<< orphan*/  date_Set (TYPE_8__*,scalar_t__) ; 
 long vorbis_packet_blocksize (int /*<<< orphan*/ ,TYPE_5__*) ; 

__attribute__((used)) static void Ogg_SetNextFrame( demux_t *p_demux, logical_stream_t *p_stream,
                              ogg_packet *p_oggpacket )
{
    VLC_UNUSED(p_demux);
    ogg_int64_t i_granule = p_oggpacket->granulepos;

    if( Ogg_GranuleIsValid( p_stream, i_granule ) )
    {
        vlc_tick_t i_endtime = Ogg_GranuleToTime( p_stream, i_granule, false, false );
        assert( !p_stream->b_contiguous || i_endtime != VLC_TICK_INVALID );
        if( i_endtime != VLC_TICK_INVALID )
        {
            date_Set( &p_stream->dts, i_endtime );
            return;
        }
    }

    /* Do Interpolation if can't compute directly from granule */
    if( date_Get( &p_stream->dts ) != VLC_TICK_INVALID )
    {
        if( p_stream->fmt.i_cat == VIDEO_ES )
        {
            date_Increment( &p_stream->dts, 1 );
        }
        else if( p_stream->fmt.i_cat == AUDIO_ES )
        {
            int64_t i_samples = 0;
            switch( p_stream->fmt.i_codec )
            {
                case VLC_CODEC_OPUS:
                    i_samples = Ogg_OpusPacketDuration( p_oggpacket );
                    break;
                case VLC_CODEC_SPEEX:
                    i_samples = p_stream->special.speex.i_framesize *
                                p_stream->special.speex.i_framesperpacket;
                    break;
#ifdef HAVE_LIBVORBIS
                case VLC_CODEC_VORBIS:
                    if( p_stream->special.vorbis.p_info &&
                        VORBIS_HEADERS_VALID(p_stream) )
                    {
                        long i_blocksize = vorbis_packet_blocksize(
                                    p_stream->special.vorbis.p_info, p_oggpacket );
                        /* duration in samples per channel */
                        if ( p_stream->special.vorbis.i_prev_blocksize )
                            i_samples = ( i_blocksize + p_stream->special.vorbis.i_prev_blocksize ) / 4;
                        else
                            i_samples = i_blocksize / 2;
                        p_stream->special.vorbis.i_prev_blocksize = i_blocksize;
                    }
                    break;
#endif
                default:
                    if( p_stream->fmt.i_bitrate )
                    {
                        i_samples = 8 * p_oggpacket->bytes * p_stream->dts.i_divider_num;
                        i_samples /= p_stream->fmt.i_bitrate / p_stream->dts.i_divider_den;
                    }
                    break;
            }
            if( i_samples == 0 )
                p_stream->b_interpolation_failed = true;
            else
                date_Increment( &p_stream->dts, i_samples );
        }
    }
}