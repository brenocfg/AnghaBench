#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_fourcc_t ;
struct TYPE_5__ {unsigned int i_codec; int /*<<< orphan*/  i_fourcc; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 unsigned int AV_CODEC_ID_RAWVIDEO ; 
 int /*<<< orphan*/  VLC_CODEC_UNKNOWN ; 
 TYPE_1__* audio_codecs ; 
 TYPE_1__* spu_codecs ; 
 TYPE_1__* video_codecs ; 

vlc_fourcc_t GetVlcFourcc( unsigned i_ffmpeg_codec )
{
    for( size_t i = 0; i < ARRAY_SIZE(video_codecs); i++ )
    {
        if( i_ffmpeg_codec == AV_CODEC_ID_RAWVIDEO )
            return VLC_CODEC_UNKNOWN;
        if( video_codecs[i].i_codec == i_ffmpeg_codec )
            return video_codecs[i].i_fourcc;
    }
    for( size_t i = 0; i < ARRAY_SIZE(audio_codecs); i++ )
    {
        if( audio_codecs[i].i_codec == i_ffmpeg_codec )
            return audio_codecs[i].i_fourcc;
    }
    for( size_t i = 0; i < ARRAY_SIZE(spu_codecs); i++ )
    {
        if( spu_codecs[i].i_codec == i_ffmpeg_codec )
            return spu_codecs[i].i_fourcc;
    }
    return VLC_CODEC_UNKNOWN;
}