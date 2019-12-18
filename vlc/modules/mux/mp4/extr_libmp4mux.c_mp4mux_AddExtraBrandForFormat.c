#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  tracks; } ;
typedef  TYPE_1__ mp4mux_handle_t ;
struct TYPE_7__ {int i_codec; } ;
typedef  TYPE_2__ es_format_t ;

/* Variables and functions */
 int /*<<< orphan*/  BRAND_M4A ; 
 int /*<<< orphan*/  BRAND_av01 ; 
 int /*<<< orphan*/  BRAND_avc1 ; 
 int /*<<< orphan*/  BRAND_hevc ; 
 int /*<<< orphan*/  BRAND_iso6 ; 
 int /*<<< orphan*/  BRAND_mp41 ; 
#define  VLC_CODEC_AV1 138 
#define  VLC_CODEC_DIV1 137 
#define  VLC_CODEC_DIV2 136 
#define  VLC_CODEC_DIV3 135 
#define  VLC_CODEC_H263 134 
#define  VLC_CODEC_H264 133 
#define  VLC_CODEC_HEVC 132 
#define  VLC_CODEC_MP3 131 
#define  VLC_CODEC_MP4A 130 
#define  VLC_CODEC_MP4V 129 
#define  VLC_CODEC_MPGA 128 
 int /*<<< orphan*/  mp4mux_AddExtraBrand (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int vlc_array_count (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mp4mux_AddExtraBrandForFormat(mp4mux_handle_t *h, const es_format_t *fmt)
{
    switch(fmt->i_codec)
    {
        case VLC_CODEC_H264:
            mp4mux_AddExtraBrand(h, BRAND_avc1);
            break;
        case VLC_CODEC_HEVC:
            mp4mux_AddExtraBrand(h, BRAND_hevc);
            break;
        case VLC_CODEC_AV1:
            mp4mux_AddExtraBrand(h, BRAND_av01);
            mp4mux_AddExtraBrand(h, BRAND_iso6);
            break;
        case VLC_CODEC_MP3:
        case VLC_CODEC_MPGA:
        case VLC_CODEC_MP4V:
        case VLC_CODEC_DIV1:
        case VLC_CODEC_DIV2:
        case VLC_CODEC_DIV3:
        case VLC_CODEC_H263:
            mp4mux_AddExtraBrand(h, BRAND_mp41);
            break;
        case VLC_CODEC_MP4A:
            mp4mux_AddExtraBrand(h, BRAND_mp41);
            if(vlc_array_count(&h->tracks) == 1)
                mp4mux_AddExtraBrand(h, BRAND_M4A);
            break;
        default:
            break;
    }
}