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
struct TYPE_5__ {scalar_t__ i_chroma; scalar_t__ i_width; scalar_t__ i_height; scalar_t__ i_visible_width; scalar_t__ i_visible_height; scalar_t__ i_x_offset; scalar_t__ i_y_offset; int i_sar_den; scalar_t__ orientation; scalar_t__ multiview_mode; scalar_t__ i_rmask; scalar_t__ i_gmask; scalar_t__ i_bmask; scalar_t__ i_sar_num; } ;
typedef  TYPE_1__ video_format_t ;
typedef  int int64_t ;

/* Variables and functions */
 scalar_t__ VLC_CODEC_RGB15 ; 
 scalar_t__ VLC_CODEC_RGB16 ; 
 scalar_t__ VLC_CODEC_RGB24 ; 
 scalar_t__ VLC_CODEC_RGB32 ; 
 int /*<<< orphan*/  video_format_FixRgb (TYPE_1__*) ; 

bool video_format_IsSimilar( const video_format_t *f1,
                             const video_format_t *f2 )
{
    if( f1->i_chroma != f2->i_chroma )
        return false;

    if( f1->i_width != f2->i_width || f1->i_height != f2->i_height ||
        f1->i_visible_width != f2->i_visible_width ||
        f1->i_visible_height != f2->i_visible_height ||
        f1->i_x_offset != f2->i_x_offset || f1->i_y_offset != f2->i_y_offset )
        return false;
    if( (int64_t)f1->i_sar_num * f2->i_sar_den !=
        (int64_t)f2->i_sar_num * f1->i_sar_den )
        return false;

    if( f1->orientation != f2->orientation)
        return false;

    if( f1->multiview_mode!= f2->multiview_mode )
       return false;

    if( f1->i_chroma == VLC_CODEC_RGB15 ||
        f1->i_chroma == VLC_CODEC_RGB16 ||
        f1->i_chroma == VLC_CODEC_RGB24 ||
        f1->i_chroma == VLC_CODEC_RGB32 )
    {
        video_format_t v1 = *f1;
        video_format_t v2 = *f2;

        video_format_FixRgb( &v1 );
        video_format_FixRgb( &v2 );

        if( v1.i_rmask != v2.i_rmask ||
            v1.i_gmask != v2.i_gmask ||
            v1.i_bmask != v2.i_bmask )
            return false;
    }
    return true;
}