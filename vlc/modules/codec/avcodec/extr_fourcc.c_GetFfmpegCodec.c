#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ vlc_fourcc_t ;
struct vlc_avcodec_fourcc {scalar_t__ i_fourcc; unsigned int i_codec; } ;
typedef  enum es_format_category_e { ____Placeholder_es_format_category_e } es_format_category_e ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct vlc_avcodec_fourcc*) ; 
#define  AUDIO_ES 130 
#define  SPU_ES 129 
#define  VIDEO_ES 128 
 struct vlc_avcodec_fourcc* audio_codecs ; 
 struct vlc_avcodec_fourcc* spu_codecs ; 
 struct vlc_avcodec_fourcc* video_codecs ; 
 scalar_t__ vlc_fourcc_GetCodec (int,scalar_t__) ; 
 char* vlc_fourcc_GetDescription (int,scalar_t__) ; 

bool GetFfmpegCodec( enum es_format_category_e cat, vlc_fourcc_t i_fourcc,
                     unsigned *pi_ffmpeg_codec, const char **ppsz_name )
{
    const struct vlc_avcodec_fourcc *base;
    size_t count;

    switch( cat )
    {
        case VIDEO_ES:
            base = video_codecs;
            count = ARRAY_SIZE(video_codecs);
            break;
        case AUDIO_ES:
            base = audio_codecs;
            count = ARRAY_SIZE(audio_codecs);
            break;
        case SPU_ES:
            base = spu_codecs;
            count = ARRAY_SIZE(spu_codecs);
            break;
        default:
            base = NULL;
            count = 0;
    }

    i_fourcc = vlc_fourcc_GetCodec( cat, i_fourcc );

    for( size_t i = 0; i < count; i++ )
    {
        if( base[i].i_fourcc == i_fourcc )
        {
            if( pi_ffmpeg_codec != NULL )
                *pi_ffmpeg_codec = base[i].i_codec;
            if( ppsz_name )
                *ppsz_name = vlc_fourcc_GetDescription( cat, i_fourcc );
            return true;
        }
    }
    return false;
}