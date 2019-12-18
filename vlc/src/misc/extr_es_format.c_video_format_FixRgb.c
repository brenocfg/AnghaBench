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
struct TYPE_3__ {int i_rmask; int i_gmask; int i_bmask; int i_chroma; } ;
typedef  TYPE_1__ video_format_t ;

/* Variables and functions */
#define  VLC_CODEC_RGB15 131 
#define  VLC_CODEC_RGB16 130 
#define  VLC_CODEC_RGB24 129 
#define  VLC_CODEC_RGB32 128 

void video_format_FixRgb( video_format_t *p_fmt )
{
    /* FIXME find right default mask */
    if( !p_fmt->i_rmask || !p_fmt->i_gmask || !p_fmt->i_bmask )
    {
        switch( p_fmt->i_chroma )
        {
        case VLC_CODEC_RGB15:
            p_fmt->i_rmask = 0x7c00;
            p_fmt->i_gmask = 0x03e0;
            p_fmt->i_bmask = 0x001f;
            break;

        case VLC_CODEC_RGB16:
            p_fmt->i_rmask = 0xf800;
            p_fmt->i_gmask = 0x07e0;
            p_fmt->i_bmask = 0x001f;
            break;

        case VLC_CODEC_RGB24:
            p_fmt->i_rmask = 0xff0000;
            p_fmt->i_gmask = 0x00ff00;
            p_fmt->i_bmask = 0x0000ff;
            break;
        case VLC_CODEC_RGB32:
            p_fmt->i_rmask = 0x00ff0000;
            p_fmt->i_gmask = 0x0000ff00;
            p_fmt->i_bmask = 0x000000ff;
            break;

        default:
            return;
        }
    }
}