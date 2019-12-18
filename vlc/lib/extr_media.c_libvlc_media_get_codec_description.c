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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int libvlc_track_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_ES ; 
 int /*<<< orphan*/  SPU_ES ; 
 int /*<<< orphan*/  UNKNOWN_ES ; 
 int /*<<< orphan*/  VIDEO_ES ; 
#define  libvlc_track_audio 131 
#define  libvlc_track_text 130 
#define  libvlc_track_unknown 129 
#define  libvlc_track_video 128 
 char const* vlc_fourcc_GetDescription (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

const char *
libvlc_media_get_codec_description( libvlc_track_type_t i_type,
                                    uint32_t i_codec )
{
    switch( i_type )
    {
        case libvlc_track_audio:
            return vlc_fourcc_GetDescription( AUDIO_ES, i_codec );
        case libvlc_track_video:
            return vlc_fourcc_GetDescription( VIDEO_ES, i_codec );
        case libvlc_track_text:
            return vlc_fourcc_GetDescription( SPU_ES, i_codec );
        case libvlc_track_unknown:
        default:
            return vlc_fourcc_GetDescription( UNKNOWN_ES, i_codec );
    }
}