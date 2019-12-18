#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ i_chroma; } ;
typedef  TYPE_1__ video_format_t ;
struct TYPE_10__ {int /*<<< orphan*/  i_chan_mode; int /*<<< orphan*/  i_physical_channels; int /*<<< orphan*/  i_channels; int /*<<< orphan*/  i_rate; int /*<<< orphan*/  channel_type; int /*<<< orphan*/  i_format; } ;
struct TYPE_9__ {int i_cat; int /*<<< orphan*/  i_codec; TYPE_1__ video; int /*<<< orphan*/  i_profile; TYPE_3__ audio; } ;
typedef  TYPE_2__ es_format_t ;
typedef  TYPE_3__ audio_format_t ;

/* Variables and functions */
#define  AUDIO_ES 130 
#define  SPU_ES 129 
#define  VIDEO_ES 128 
 int video_format_IsSimilar (TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ vlc_fourcc_GetCodec (int,int /*<<< orphan*/ ) ; 

bool es_format_IsSimilar( const es_format_t *p_fmt1, const es_format_t *p_fmt2 )
{
    if( p_fmt1->i_cat != p_fmt2->i_cat ||
        vlc_fourcc_GetCodec( p_fmt1->i_cat, p_fmt1->i_codec ) !=
        vlc_fourcc_GetCodec( p_fmt2->i_cat, p_fmt2->i_codec ) )
        return false;

    switch( p_fmt1->i_cat )
    {
    case AUDIO_ES:
    {
        audio_format_t a1 = p_fmt1->audio;
        audio_format_t a2 = p_fmt2->audio;

        if( a1.i_format && a2.i_format && a1.i_format != a2.i_format )
            return false;
        if( a1.channel_type != a2.channel_type ||
            a1.i_rate != a2.i_rate ||
            a1.i_channels != a2.i_channels ||
            a1.i_physical_channels != a2.i_physical_channels ||
            a1.i_chan_mode != a2.i_chan_mode )
            return false;
        if( p_fmt1->i_profile != p_fmt2->i_profile )
            return false;
        return true;
    }

    case VIDEO_ES:
    {
        video_format_t v1 = p_fmt1->video;
        video_format_t v2 = p_fmt2->video;
        if( !v1.i_chroma )
            v1.i_chroma = vlc_fourcc_GetCodec( p_fmt1->i_cat, p_fmt1->i_codec );
        if( !v2.i_chroma )
            v2.i_chroma = vlc_fourcc_GetCodec( p_fmt2->i_cat, p_fmt2->i_codec );
        return video_format_IsSimilar( &v1, &v2 );
    }

    case SPU_ES:
    default:
        return true;
    }
}