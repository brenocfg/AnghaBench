#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_7__ {int i_rate; } ;
struct TYPE_8__ {int i_extra; int i_codec; int i_original_fourcc; int i_cat; scalar_t__ p_extra; TYPE_2__ audio; } ;
struct TYPE_9__ {unsigned int i_samples_count; int i_read_duration; TYPE_3__ fmt; int /*<<< orphan*/  i_track_id; TYPE_1__* samples; } ;
typedef  TYPE_4__ mp4mux_trackinfo_t ;
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  bo_t ;
struct TYPE_6__ {scalar_t__ i_size; int i_length; } ;

/* Variables and functions */
#define  AUDIO_ES 138 
 int CLOCK_FREQ ; 
#define  SPU_ES 137 
#define  VIDEO_ES 136 
#define  VLC_CODEC_DTS 135 
#define  VLC_CODEC_MP1V 134 
#define  VLC_CODEC_MP2V 133 
#define  VLC_CODEC_MP3 132 
#define  VLC_CODEC_MP4A 131 
#define  VLC_CODEC_MP4V 130 
#define  VLC_CODEC_MPGA 129 
#define  VLC_CODEC_MPGV 128 
 int /*<<< orphan*/  bo_add_16be (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bo_add_24be (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bo_add_32be (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  bo_add_8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bo_add_mp4_tag_descr (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * box_full_new (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bo_t *GetESDS(mp4mux_trackinfo_t *p_track)
{
    bo_t *esds;

    /* */
    int i_decoder_specific_info_size = (p_track->fmt.i_extra > 0) ? 5 + p_track->fmt.i_extra : 0;

    esds = box_full_new("esds", 0, 0);
    if(!esds)
        return NULL;

    /* Compute Max bitrate */
    int64_t i_bitrate_avg = 0;
    int64_t i_bitrate_max = 0;
    /* Compute avg/max bitrate */
    for (unsigned i = 0; i < p_track->i_samples_count; i++) {
        i_bitrate_avg += p_track->samples[i].i_size;
        if (p_track->samples[i].i_length > 0) {
            int64_t i_bitrate = CLOCK_FREQ * 8 * p_track->samples[i].i_size / p_track->samples[i].i_length;
            if (i_bitrate > i_bitrate_max)
                i_bitrate_max = i_bitrate;
        }
    }

    if (p_track->i_read_duration > 0)
        i_bitrate_avg = CLOCK_FREQ * 8 * i_bitrate_avg / p_track->i_read_duration;
    else
        i_bitrate_avg = 0;
    if (i_bitrate_max <= 1)
        i_bitrate_max = 0x7fffffff;

    /* ES_Descriptor ISO/IEC 14496-1 */
    bo_add_mp4_tag_descr(esds, 0x03, 3 + 5 + 13 + i_decoder_specific_info_size + 5 + 1);
    bo_add_16be(esds, p_track->i_track_id);
    bo_add_8   (esds, 0x1f);      // flags=0|streamPriority=0x1f

    /* DecoderConfigDescr ISO/IEC 14496-1
        http://mp4ra.org/#/object_types */
    bo_add_mp4_tag_descr(esds, 0x04, 13 + i_decoder_specific_info_size);

    uint8_t i_object_profile_indication;
    switch(p_track->fmt.i_codec)
    {
    case VLC_CODEC_MP4V:
        i_object_profile_indication = 0x20; /* Visual 14496-2 */
        break;
    case VLC_CODEC_MPGV:
        if(p_track->fmt.i_original_fourcc == VLC_CODEC_MP1V)
        {
            i_object_profile_indication = 0x6a; /* Visual ISO/IEC 11172-2  */
            break;
        }
        /* fallthrough */
    case VLC_CODEC_MP2V:
        /* MPEG-I=0x6b, MPEG-II = 0x60 -> 0x65 */
        i_object_profile_indication = 0x61; /* Visual 13818-2 Main Profile */
        break;
    case VLC_CODEC_MP1V:
        i_object_profile_indication = 0x6a; /* Visual ISO/IEC 11172-2  */
        break;
    case VLC_CODEC_MP4A:
        /* FIXME for mpeg2-aac == 0x66->0x68 */
        i_object_profile_indication = 0x40; /* Audio 14496-3 */
        break;
    case VLC_CODEC_MP3:
    case VLC_CODEC_MPGA:
        i_object_profile_indication =
            p_track->fmt.audio.i_rate < 32000 ? 0x69 /* Audio 13818-3 */
                                              : 0x6b;/* Audio 11172-3 */
        break;
    case VLC_CODEC_DTS:
        i_object_profile_indication = 0xa9; /* Core Substream */
        break;
    default:
        i_object_profile_indication = 0xFE; /* No profile specified */
        break;
    }

    uint8_t i_stream_type;
    switch(p_track->fmt.i_cat)
    {
        case VIDEO_ES:
            i_stream_type = 0x04;
            break;
        case AUDIO_ES:
            i_stream_type = 0x05;
            break;
        case SPU_ES:
            i_stream_type = 0x0D;
            break;
        default:
            i_stream_type = 0x20; /* Private */
            break;
    }

    bo_add_8   (esds, i_object_profile_indication);
    bo_add_8   (esds, (i_stream_type << 2) | 1);
    bo_add_24be(esds, 1024 * 1024);       // bufferSizeDB
    bo_add_32be(esds, i_bitrate_max);     // maxBitrate
    bo_add_32be(esds, i_bitrate_avg);     // avgBitrate

    if (p_track->fmt.i_extra > 0) {
        /* DecoderSpecificInfo */
        bo_add_mp4_tag_descr(esds, 0x05, p_track->fmt.i_extra);

        for (int i = 0; i < p_track->fmt.i_extra; i++)
            bo_add_8(esds, ((uint8_t*)p_track->fmt.p_extra)[i]);
    }

    /* SL_Descr mandatory */
    bo_add_mp4_tag_descr(esds, 0x06, 1);
    bo_add_8    (esds, 0x02);  // sl_predefined

    return esds;
}