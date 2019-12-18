#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_7__ {int i_width; int i_visible_width; int i_height; int i_visible_height; } ;
typedef  TYPE_1__ video_format_t ;
struct TYPE_8__ {int i_x; int i_y; int i_align; } ;
typedef  TYPE_2__ subpicture_region_t ;

/* Variables and functions */
 int SUBPICTURE_ALIGN_LEFT ; 
 int SUBPICTURE_ALIGN_TOP ; 
 int /*<<< orphan*/  VLC_CODEC_YUVA ; 
 TYPE_2__* spuregion_CreateFromPicture (int /*<<< orphan*/ *,TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  video_format_Init (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static subpicture_region_t * vout_OSDImage( vlc_object_t *p_obj,
                                            int x, int y, int w, int h,
                                            const char *psz_uri )
{
    video_format_t fmt_out;
    video_format_Init( &fmt_out, VLC_CODEC_YUVA );
    fmt_out.i_width = fmt_out.i_visible_width = w;
    fmt_out.i_height = fmt_out.i_visible_height = h;

    subpicture_region_t *image =
            spuregion_CreateFromPicture( p_obj, &fmt_out, psz_uri );
    if( image )
    {
        image->i_x = x;
        image->i_y = y;
        image->i_align = SUBPICTURE_ALIGN_LEFT|SUBPICTURE_ALIGN_TOP;
    }
    return image;
}