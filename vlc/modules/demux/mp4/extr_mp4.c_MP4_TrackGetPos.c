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
typedef  int uint64_t ;
struct TYPE_13__ {int i_blockalign; } ;
struct TYPE_14__ {scalar_t__ i_cat; int i_codec; TYPE_3__ audio; } ;
struct TYPE_16__ {size_t i_chunk; int i_sample_size; int i_sample; scalar_t__* p_sample_size; TYPE_5__* chunk; TYPE_4__ fmt; TYPE_2__* p_sample; } ;
typedef  TYPE_6__ mp4_track_t ;
struct TYPE_17__ {scalar_t__ i_compressionid; scalar_t__ i_qt_version; int i_sample_per_packet; int i_bytes_per_frame; } ;
struct TYPE_15__ {int i_offset; int i_sample_first; } ;
struct TYPE_11__ {TYPE_7__* p_sample_soun; } ;
struct TYPE_12__ {TYPE_1__ data; } ;
typedef  TYPE_7__ MP4_Box_data_sample_soun_t ;

/* Variables and functions */
 scalar_t__ AUDIO_ES ; 
 int MP4_GetFixedSampleSize (TYPE_6__*,TYPE_7__*) ; 
#define  VLC_CODEC_ADPCM_IMA_QT 129 
#define  VLC_CODEC_GSM 128 

__attribute__((used)) static uint64_t MP4_TrackGetPos( mp4_track_t *p_track )
{
    unsigned int i_sample;
    uint64_t i_pos;

    i_pos = p_track->chunk[p_track->i_chunk].i_offset;

    if( p_track->i_sample_size )
    {
        MP4_Box_data_sample_soun_t *p_soun =
            p_track->p_sample->data.p_sample_soun;

        /* Quicktime builtin support, _must_ ignore sample tables */
        if( p_track->fmt.i_cat == AUDIO_ES && p_soun->i_compressionid == 0 &&
            p_track->i_sample_size == 1 )
        {
            switch( p_track->fmt.i_codec )
            {
            case VLC_CODEC_GSM: /* # Samples > data size */
                i_pos += ( p_track->i_sample -
                           p_track->chunk[p_track->i_chunk].i_sample_first ) / 160 * 33;
                return i_pos;
            case VLC_CODEC_ADPCM_IMA_QT: /* # Samples > data size */
                i_pos += ( p_track->i_sample -
                           p_track->chunk[p_track->i_chunk].i_sample_first ) / 64 * 34;
                return i_pos;
            default:
                break;
            }
        }

        if( p_track->fmt.i_cat != AUDIO_ES || p_soun->i_qt_version == 0 ||
            p_track->fmt.audio.i_blockalign <= 1 ||
            p_soun->i_sample_per_packet * p_soun->i_bytes_per_frame == 0 )
        {
            i_pos += ( p_track->i_sample -
                       p_track->chunk[p_track->i_chunk].i_sample_first ) *
                     MP4_GetFixedSampleSize( p_track, p_soun );
        }
        else
        {
            /* we read chunk by chunk unless a blockalign is requested */
            i_pos += ( p_track->i_sample - p_track->chunk[p_track->i_chunk].i_sample_first ) /
                        p_soun->i_sample_per_packet * p_soun->i_bytes_per_frame;
        }
    }
    else
    {
        for( i_sample = p_track->chunk[p_track->i_chunk].i_sample_first;
             i_sample < p_track->i_sample; i_sample++ )
        {
            i_pos += p_track->p_sample_size[i_sample];
        }
    }

    return i_pos;
}