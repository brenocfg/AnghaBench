#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
struct TYPE_24__ {int i_height; int i_width; } ;
typedef  TYPE_3__ video_format_t ;
struct TYPE_25__ {TYPE_1__* p; } ;
typedef  TYPE_4__ picture_t ;
typedef  int /*<<< orphan*/  image_handler_t ;
struct TYPE_26__ {TYPE_6__* p_sys; } ;
typedef  TYPE_5__ filter_t ;
struct TYPE_27__ {TYPE_2__* p_style; } ;
typedef  TYPE_6__ filter_sys_t ;
struct TYPE_23__ {int i_font_size; } ;
struct TYPE_22__ {int i_visible_lines; int i_visible_pitch; } ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_CODEC_YUVA ; 
 size_t Y_PLANE ; 
 TYPE_4__* image_Convert (int /*<<< orphan*/ *,TYPE_4__*,TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/ * image_HandlerCreate (TYPE_5__*) ; 
 int /*<<< orphan*/  image_HandlerDelete (int /*<<< orphan*/ *) ; 
 TYPE_4__* image_ReadUrl (int /*<<< orphan*/ *,char const*,TYPE_3__*) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_5__*,char*,char const*) ; 
 int /*<<< orphan*/  picture_Release (TYPE_4__*) ; 
 int /*<<< orphan*/  video_format_Clean (TYPE_3__*) ; 
 int /*<<< orphan*/  video_format_Copy (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  video_format_Init (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static picture_t *LoadImage( filter_t *p_filter, const char *psz_url )
{
    filter_sys_t *p_sys = p_filter->p_sys;
    video_format_t fmt_out;
    picture_t *p_orig;
    picture_t *p_pic = NULL;
    image_handler_t *p_handler = image_HandlerCreate( p_filter );

    video_format_Init( &fmt_out, VLC_CODEC_YUVA );

    p_orig = image_ReadUrl( p_handler, psz_url, &fmt_out );

    if( !p_orig )
    {
        msg_Warn( p_filter, "Unable to read image %s", psz_url );
    }
    else if( p_sys->p_style->i_font_size > 0 )
    {
        video_format_t fmt_in;
        video_format_Copy( &fmt_in, &fmt_out );

        fmt_in.i_height = p_orig->p[Y_PLANE].i_visible_lines;
        fmt_in.i_width = p_orig->p[Y_PLANE].i_visible_pitch;
        fmt_out.i_width = p_orig->p[Y_PLANE].i_visible_pitch
            *p_sys->p_style->i_font_size/p_orig->p[Y_PLANE].i_visible_lines;
        fmt_out.i_height = p_sys->p_style->i_font_size;

        p_pic = image_Convert( p_handler, p_orig, &fmt_in, &fmt_out );
        picture_Release( p_orig );
        video_format_Clean( &fmt_in );
        if( !p_pic )
        {
            msg_Warn( p_filter, "Error while converting %s", psz_url );
        }
    }
    else
    {
        p_pic = p_orig;
    }

    video_format_Clean( &fmt_out );
    image_HandlerDelete( p_handler );

    return p_pic;
}