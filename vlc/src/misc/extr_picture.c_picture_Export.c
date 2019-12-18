#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  vlc_fourcc_t ;
struct TYPE_12__ {int i_sar_num; int i_sar_den; unsigned int i_visible_width; unsigned int i_visible_height; unsigned int i_width; unsigned int i_height; unsigned int i_x_offset; unsigned int i_y_offset; int /*<<< orphan*/  i_chroma; } ;
typedef  TYPE_1__ video_format_t ;
struct TYPE_13__ {int /*<<< orphan*/  date; TYPE_1__ format; } ;
typedef  TYPE_2__ picture_t ;
typedef  unsigned int int64_t ;
typedef  int /*<<< orphan*/  image_handler_t ;
typedef  int /*<<< orphan*/  fmt_out ;
struct TYPE_14__ {int /*<<< orphan*/  i_dts; int /*<<< orphan*/  i_pts; } ;
typedef  TYPE_3__ block_t ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/ * image_HandlerCreate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  image_HandlerDelete (int /*<<< orphan*/ *) ; 
 TYPE_3__* image_Write (int /*<<< orphan*/ *,TYPE_2__*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

int picture_Export( vlc_object_t *p_obj,
                    block_t **pp_image,
                    video_format_t *p_fmt,
                    picture_t *p_picture,
                    vlc_fourcc_t i_format,
                    int i_override_width, int i_override_height,
                    bool b_crop )
{
    /* */
    video_format_t fmt_in = p_picture->format;
    if( fmt_in.i_sar_num <= 0 || fmt_in.i_sar_den <= 0 )
    {
        fmt_in.i_sar_num =
        fmt_in.i_sar_den = 1;
    }

    /* */
    video_format_t fmt_out;
    memset( &fmt_out, 0, sizeof(fmt_out) );
    fmt_out.i_sar_num =
    fmt_out.i_sar_den = 1;
    fmt_out.i_chroma  = i_format;

    /* compute original width/height */
    unsigned int i_width, i_height, i_original_width, i_original_height;
    if( fmt_in.i_visible_width > 0 && fmt_in.i_visible_height > 0 )
    {
        i_width = fmt_in.i_visible_width;
        i_height = fmt_in.i_visible_height;
    }
    else
    {
        i_width = fmt_in.i_width;
        i_height = fmt_in.i_height;
    }
    if( fmt_in.i_sar_num >= fmt_in.i_sar_den )
    {
        i_original_width = (int64_t)i_width * fmt_in.i_sar_num / fmt_in.i_sar_den;
        i_original_height = i_height;
    }
    else
    {
        i_original_width =  i_width;
        i_original_height = i_height * fmt_in.i_sar_den / fmt_in.i_sar_num;
    }

    /* */
    if( b_crop && i_override_width > 0 && i_override_height > 0 )
    {
        float f_ar_dest = (float)i_override_width / i_override_height;
        float f_ar_src = (float)i_width / i_height;
        unsigned int i_crop_width, i_crop_height;
        if ( f_ar_dest > f_ar_src )
        {
            i_crop_width = i_width;
            i_crop_height = (float)i_crop_width / f_ar_dest;
        }
        else
        {
            i_crop_height = i_height;
            i_crop_width = (float)i_crop_height * f_ar_dest;
        }
        fmt_out.i_width = i_override_width;
        fmt_out.i_height = i_override_height;
        fmt_in.i_visible_width = i_crop_width;
        fmt_in.i_visible_height = i_crop_height;
        fmt_in.i_x_offset += (i_width - i_crop_width) / 2;
        fmt_in.i_y_offset += (i_height - i_crop_height) / 2;
    }
    else
    {
        fmt_out.i_width  = ( i_override_width < 0 ) ?
                           i_original_width : (unsigned)i_override_width;
        fmt_out.i_height = ( i_override_height < 0 ) ?
                           i_original_height : (unsigned)i_override_height;
    }

    /* scale if only one direction is provided */
    if( fmt_out.i_height == 0 && fmt_out.i_width > 0 )
    {
        fmt_out.i_height = i_height * fmt_out.i_width
                         * fmt_in.i_sar_den / fmt_in.i_width / fmt_in.i_sar_num;
    }
    else if( fmt_out.i_width == 0 && fmt_out.i_height > 0 )
    {
        fmt_out.i_width  = i_width * fmt_out.i_height
                         * fmt_in.i_sar_num / fmt_in.i_height / fmt_in.i_sar_den;
    }

    image_handler_t *p_image = image_HandlerCreate( p_obj );
    if( !p_image )
        return VLC_ENOMEM;

    block_t *p_block = image_Write( p_image, p_picture, &fmt_in, &fmt_out );

    image_HandlerDelete( p_image );

    if( !p_block )
        return VLC_EGENERIC;

    p_block->i_pts =
    p_block->i_dts = p_picture->date;

    if( p_fmt )
        *p_fmt = fmt_out;
    *pp_image = p_block;

    return VLC_SUCCESS;
}