#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_fourcc_t ;
struct TYPE_3__ {int i_chroma; int i_width; int i_visible_width; int i_height; int i_visible_height; int i_bits_per_pixel; int /*<<< orphan*/  i_sar_den; int /*<<< orphan*/  i_sar_num; scalar_t__ i_y_offset; scalar_t__ i_x_offset; } ;
typedef  TYPE_1__ video_format_t ;

/* Variables and functions */
 int /*<<< orphan*/  VIDEO_ES ; 
#define  VLC_CODEC_ARGB 166 
#define  VLC_CODEC_BGRA 165 
#define  VLC_CODEC_GREY 164 
#define  VLC_CODEC_GREY_10B 163 
#define  VLC_CODEC_GREY_10L 162 
#define  VLC_CODEC_GREY_12B 161 
#define  VLC_CODEC_GREY_12L 160 
#define  VLC_CODEC_I410 159 
#define  VLC_CODEC_I411 158 
#define  VLC_CODEC_I420 157 
#define  VLC_CODEC_I422 156 
#define  VLC_CODEC_I440 155 
#define  VLC_CODEC_I444 154 
#define  VLC_CODEC_J420 153 
#define  VLC_CODEC_J422 152 
#define  VLC_CODEC_J440 151 
#define  VLC_CODEC_J444 150 
#define  VLC_CODEC_NV12 149 
#define  VLC_CODEC_P010 148 
#define  VLC_CODEC_P016 147 
#define  VLC_CODEC_RGB15 146 
#define  VLC_CODEC_RGB16 145 
#define  VLC_CODEC_RGB24 144 
#define  VLC_CODEC_RGB32 143 
#define  VLC_CODEC_RGB8 142 
#define  VLC_CODEC_RGBA 141 
#define  VLC_CODEC_RGBP 140 
#define  VLC_CODEC_UYVY 139 
#define  VLC_CODEC_VYUY 138 
#define  VLC_CODEC_XYZ12 137 
#define  VLC_CODEC_Y211 136 
#define  VLC_CODEC_YUV420A 135 
#define  VLC_CODEC_YUV422A 134 
#define  VLC_CODEC_YUVA 133 
#define  VLC_CODEC_YUVP 132 
#define  VLC_CODEC_YUYV 131 
#define  VLC_CODEC_YV12 130 
#define  VLC_CODEC_YV9 129 
#define  VLC_CODEC_YVYU 128 
 int vlc_fourcc_GetCodec (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_ureduce (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 

void video_format_Setup( video_format_t *p_fmt, vlc_fourcc_t i_chroma,
                         int i_width, int i_height,
                         int i_visible_width, int i_visible_height,
                         int i_sar_num, int i_sar_den )
{
    p_fmt->i_chroma         = vlc_fourcc_GetCodec( VIDEO_ES, i_chroma );
    p_fmt->i_width          = i_width;
    p_fmt->i_visible_width  = i_visible_width;
    p_fmt->i_height         = i_height;
    p_fmt->i_visible_height = i_visible_height;
    p_fmt->i_x_offset       =
    p_fmt->i_y_offset       = 0;
    vlc_ureduce( &p_fmt->i_sar_num, &p_fmt->i_sar_den,
                 i_sar_num, i_sar_den, 0 );

    switch( p_fmt->i_chroma )
    {
    case VLC_CODEC_YUVA:
        p_fmt->i_bits_per_pixel = 32;
        break;
    case VLC_CODEC_YUV420A:
        p_fmt->i_bits_per_pixel = 20;
        break;
    case VLC_CODEC_YUV422A:
        p_fmt->i_bits_per_pixel = 24;
        break;
    case VLC_CODEC_I444:
    case VLC_CODEC_J444:
        p_fmt->i_bits_per_pixel = 24;
        break;
    case VLC_CODEC_I422:
    case VLC_CODEC_YUYV:
    case VLC_CODEC_YVYU:
    case VLC_CODEC_UYVY:
    case VLC_CODEC_VYUY:
    case VLC_CODEC_J422:
        p_fmt->i_bits_per_pixel = 16;
        break;
    case VLC_CODEC_I440:
    case VLC_CODEC_J440:
        p_fmt->i_bits_per_pixel = 16;
        break;
    case VLC_CODEC_P010:
        p_fmt->i_bits_per_pixel = 15;
        break;
    case VLC_CODEC_P016:
        p_fmt->i_bits_per_pixel = 20;
        break;
    case VLC_CODEC_I411:
    case VLC_CODEC_YV12:
    case VLC_CODEC_I420:
    case VLC_CODEC_J420:
    case VLC_CODEC_NV12:
        p_fmt->i_bits_per_pixel = 12;
        break;
    case VLC_CODEC_YV9:
    case VLC_CODEC_I410:
        p_fmt->i_bits_per_pixel = 9;
        break;
    case VLC_CODEC_Y211:
        p_fmt->i_bits_per_pixel = 8;
        break;
    case VLC_CODEC_YUVP:
        p_fmt->i_bits_per_pixel = 8;
        break;

    case VLC_CODEC_RGB32:
    case VLC_CODEC_RGBA:
    case VLC_CODEC_ARGB:
    case VLC_CODEC_BGRA:
        p_fmt->i_bits_per_pixel = 32;
        break;
    case VLC_CODEC_RGB24:
        p_fmt->i_bits_per_pixel = 24;
        break;
    case VLC_CODEC_RGB15:
    case VLC_CODEC_RGB16:
        p_fmt->i_bits_per_pixel = 16;
        break;
    case VLC_CODEC_RGB8:
        p_fmt->i_bits_per_pixel = 8;
        break;

    case VLC_CODEC_GREY:
    case VLC_CODEC_RGBP:
        p_fmt->i_bits_per_pixel = 8;
        break;

    case VLC_CODEC_GREY_10B:
    case VLC_CODEC_GREY_10L:
        p_fmt->i_bits_per_pixel = 10;
        break;

    case VLC_CODEC_GREY_12B:
    case VLC_CODEC_GREY_12L:
        p_fmt->i_bits_per_pixel = 12;
        break;

    case VLC_CODEC_XYZ12:
        p_fmt->i_bits_per_pixel = 48;
        break;

    default:
        p_fmt->i_bits_per_pixel = 0;
        break;
    }
}