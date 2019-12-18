#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_13__ {int i_blockalign; int i_channels; int i_rate; } ;
struct TYPE_14__ {scalar_t__ i_cat; scalar_t__ i_original_fourcc; int i_codec; TYPE_3__ audio; } ;
struct TYPE_15__ {size_t i_sample; size_t i_sample_count; scalar_t__ i_sample_size; int* p_sample_size; size_t i_chunk; TYPE_4__ fmt; TYPE_6__* chunk; TYPE_2__* p_sample; } ;
typedef  TYPE_5__ mp4_track_t ;
struct TYPE_16__ {int i_sample_count; int i_sample; int i_sample_first; } ;
typedef  TYPE_6__ mp4_chunk_t ;
struct TYPE_17__ {int i_constLPCMframesperaudiopacket; int i_constbytesperaudiopacket; int i_qt_version; int i_compressionid; int i_bytes_per_sample; int i_sample_per_packet; int i_bytes_per_frame; } ;
struct TYPE_11__ {TYPE_7__* p_sample_soun; } ;
struct TYPE_12__ {TYPE_1__ data; } ;
typedef  TYPE_7__ MP4_Box_data_sample_soun_t ;

/* Variables and functions */
 scalar_t__ AUDIO_ES ; 
 scalar_t__ MP4_GetFixedSampleSize (TYPE_5__*,TYPE_7__ const*) ; 
 int UINT32_MAX ; 
#define  VLC_CODEC_A52 137 
#define  VLC_CODEC_ADPCM_IMA_QT 136 
#define  VLC_CODEC_AMR_NB 135 
#define  VLC_CODEC_AMR_WB 134 
#define  VLC_CODEC_DTS 133 
 scalar_t__ VLC_CODEC_DVD_LPCM ; 
#define  VLC_CODEC_GSM 132 
#define  VLC_CODEC_MP2 131 
#define  VLC_CODEC_MP3 130 
#define  VLC_CODEC_MP4A 129 
#define  VLC_CODEC_MPGA 128 
 scalar_t__ VLC_FOURCC (char,char,char,char) ; 

__attribute__((used)) static uint32_t MP4_TrackGetReadSize( mp4_track_t *p_track, uint32_t *pi_nb_samples )
{
    uint32_t i_size = 0;
    *pi_nb_samples = 0;

    if ( p_track->i_sample == p_track->i_sample_count )
        return 0;

    if ( p_track->fmt.i_cat != AUDIO_ES )
    {
        *pi_nb_samples = 1;

        if( p_track->i_sample_size == 0 ) /* all sizes are different */
            return p_track->p_sample_size[p_track->i_sample];
        else
            return p_track->i_sample_size;
    }
    else
    {
        const MP4_Box_data_sample_soun_t *p_soun = p_track->p_sample->data.p_sample_soun;
        const mp4_chunk_t *p_chunk = &p_track->chunk[p_track->i_chunk];
        uint32_t i_max_samples = p_chunk->i_sample_count - p_chunk->i_sample;

        /* Group audio packets so we don't call demux for single sample unit */
        if( p_track->fmt.i_original_fourcc == VLC_CODEC_DVD_LPCM &&
            p_soun->i_constLPCMframesperaudiopacket &&
            p_soun->i_constbytesperaudiopacket )
        {
            /* uncompressed case */
            uint32_t i_packets = i_max_samples / p_soun->i_constLPCMframesperaudiopacket;
            if ( UINT32_MAX / p_soun->i_constbytesperaudiopacket < i_packets )
                i_packets = UINT32_MAX / p_soun->i_constbytesperaudiopacket;
            *pi_nb_samples = i_packets * p_soun->i_constLPCMframesperaudiopacket;
            return i_packets * p_soun->i_constbytesperaudiopacket;
        }

        if( p_track->fmt.i_original_fourcc == VLC_FOURCC('r','r','t','p') )
        {
            *pi_nb_samples = 1;
            return p_track->i_sample_size;
        }

        /* all samples have a different size */
        if( p_track->i_sample_size == 0 )
        {
            *pi_nb_samples = 1;
            return p_track->p_sample_size[p_track->i_sample];
        }

        if( p_soun->i_qt_version == 1 )
        {
            if ( p_soun->i_compressionid == 0xFFFE )
            {
                *pi_nb_samples = 1; /* != number of audio samples */
                if ( p_track->i_sample_size )
                    return p_track->i_sample_size;
                else
                    return p_track->p_sample_size[p_track->i_sample];
            }
            else if ( p_soun->i_compressionid != 0 || p_soun->i_bytes_per_sample > 1 ) /* compressed */
            {
                /* in this case we are dealing with compressed data
                   -2 in V1: additional fields are meaningless (VBR and such) */
                *pi_nb_samples = i_max_samples;//p_track->chunk[p_track->i_chunk].i_sample_count;
                if( p_track->fmt.audio.i_blockalign > 1 )
                    *pi_nb_samples = p_soun->i_sample_per_packet;
                i_size = *pi_nb_samples / p_soun->i_sample_per_packet * p_soun->i_bytes_per_frame;
                return i_size;
            }
            else /* uncompressed case */
            {
                uint32_t i_packets;
                if( p_track->fmt.audio.i_blockalign > 1 )
                    i_packets = 1;
                else
                    i_packets = i_max_samples / p_soun->i_sample_per_packet;

                if ( UINT32_MAX / p_soun->i_bytes_per_frame < i_packets )
                    i_packets = UINT32_MAX / p_soun->i_bytes_per_frame;

                *pi_nb_samples = i_packets * p_soun->i_sample_per_packet;
                i_size = i_packets * p_soun->i_bytes_per_frame;
                return i_size;
            }
        }

        /* uncompressed v0 (qt) or... not (ISO) */

        /* Quicktime built-in support handling */
        if( p_soun->i_compressionid == 0 && p_track->i_sample_size == 1 )
        {
            switch( p_track->fmt.i_codec )
            {
                /* sample size is not integer */
                case VLC_CODEC_GSM:
                    *pi_nb_samples = 160 * p_track->fmt.audio.i_channels;
                    return 33 * p_track->fmt.audio.i_channels;
                case VLC_CODEC_ADPCM_IMA_QT:
                    *pi_nb_samples = 64 * p_track->fmt.audio.i_channels;
                    return 34 * p_track->fmt.audio.i_channels;
                default:
                    break;
            }
        }

        /* More regular V0 cases */
        uint32_t i_max_v0_samples;
        switch( p_track->fmt.i_codec )
        {
            /* Compressed samples in V0 */
            case VLC_CODEC_AMR_NB:
            case VLC_CODEC_AMR_WB:
                i_max_v0_samples = 16;
                break;
            case VLC_CODEC_MPGA:
            case VLC_CODEC_MP2:
            case VLC_CODEC_MP3:
            case VLC_CODEC_DTS:
            case VLC_CODEC_MP4A:
            case VLC_CODEC_A52:
                i_max_v0_samples = 1;
                break;
                /* fixme, reverse using a list of uncompressed codecs */
            default:
                /* Read 25ms of samples (uncompressed) */
                i_max_v0_samples = p_track->fmt.audio.i_rate / 40 *
                                   p_track->fmt.audio.i_channels;
                if( i_max_v0_samples < 1 )
                    i_max_v0_samples = 1;
                break;
        }

        *pi_nb_samples = 0;
        for( uint32_t i=p_track->i_sample;
             i<p_chunk->i_sample_first+p_chunk->i_sample_count &&
             i<p_track->i_sample_count;
             i++ )
        {
            (*pi_nb_samples)++;
            if ( p_track->i_sample_size == 0 )
                i_size += p_track->p_sample_size[i];
            else
                i_size += MP4_GetFixedSampleSize( p_track, p_soun );

            /* Try to detect compression in ISO */
            if(p_soun->i_compressionid != 0)
            {
                /* Return only 1 sample */
                break;
            }

            if ( *pi_nb_samples == i_max_v0_samples )
                break;
        }
    }

    //fprintf( stderr, "size=%d\n", i_size );
    return i_size;
}