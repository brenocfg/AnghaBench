#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_17__ {TYPE_1__* p; int /*<<< orphan*/ * V_PIXELS; int /*<<< orphan*/ * U_PIXELS; int /*<<< orphan*/ * Y_PIXELS; } ;
typedef  TYPE_6__ picture_t ;
struct TYPE_15__ {int i_x_offset; int i_visible_width; int i_y_offset; int i_visible_height; } ;
struct TYPE_16__ {TYPE_4__ video; } ;
struct TYPE_13__ {int i_y_offset; int i_visible_height; scalar_t__ i_visible_width; scalar_t__ i_x_offset; } ;
struct TYPE_14__ {TYPE_2__ video; } ;
struct TYPE_18__ {TYPE_5__ fmt_in; TYPE_3__ fmt_out; TYPE_8__* p_sys; } ;
typedef  TYPE_7__ filter_t ;
struct TYPE_19__ {int* p_offset; scalar_t__ p_buffer; int /*<<< orphan*/  i_bytespp; int /*<<< orphan*/  i_buffer_size; int /*<<< orphan*/ * p_rgb32; } ;
typedef  TYPE_8__ filter_sys_t ;
struct TYPE_12__ {int i_pitch; int i_visible_pitch; scalar_t__ p_pixels; } ;

/* Variables and functions */
 scalar_t__ AllocateOrGrow (scalar_t__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONVERT_YUV_PIXEL (int) ; 
 int /*<<< orphan*/  CONVERT_Y_PIXEL (int) ; 
 int /*<<< orphan*/  SCALE_HEIGHT (int,int) ; 
 int /*<<< orphan*/  SCALE_WIDTH ; 
 int /*<<< orphan*/  SetOffset (int,int,scalar_t__,int,int*,unsigned int*,int*) ; 

void I420_RGB32( filter_t *p_filter, picture_t *p_src, picture_t *p_dest )
{
    filter_sys_t *p_sys = p_filter->p_sys;

    /* We got this one from the old arguments */
    uint32_t *p_pic = (uint32_t*)p_dest->p->p_pixels;
    uint8_t  *p_y   = p_src->Y_PIXELS;
    uint8_t  *p_u   = p_src->U_PIXELS;
    uint8_t  *p_v   = p_src->V_PIXELS;

    bool  b_hscale;                         /* horizontal scaling type */
    unsigned int i_vscale;                          /* vertical scaling type */
    unsigned int i_x, i_y;                /* horizontal and vertical indexes */

    int         i_right_margin;
    int         i_rewind;
    int         i_scale_count;                       /* scale modulo counter */
    int         i_chroma_width = (p_filter->fmt_in.video.i_x_offset + p_filter->fmt_in.video.i_visible_width) / 2; /* chroma width */
    uint32_t *  p_pic_start;       /* beginning of the current line for copy */
    int         i_uval, i_vval;                           /* U and V samples */
    int         i_red, i_green, i_blue;          /* U and V modified samples */
    uint32_t *  p_yuv = p_sys->p_rgb32;
    uint32_t *  p_ybase;                     /* Y dependant conversion table */

    /* Conversion buffer pointer */
    uint32_t *  p_buffer_start;
    uint32_t *  p_buffer;

    /* Offset array pointer */
    int *       p_offset_start = p_sys->p_offset;
    int *       p_offset;

    const int i_source_margin = p_src->p[0].i_pitch
                                 - p_src->p[0].i_visible_pitch
                                 - p_filter->fmt_in.video.i_x_offset;
    const int i_source_margin_c = p_src->p[1].i_pitch
                                 - p_src->p[1].i_visible_pitch
                                 - ( p_filter->fmt_in.video.i_x_offset / 2 );

    i_right_margin = p_dest->p->i_pitch - p_dest->p->i_visible_pitch;
    i_rewind = (-(p_filter->fmt_in.video.i_x_offset + p_filter->fmt_in.video.i_visible_width)) & 7;

    /* Rule: when a picture of size (x1,y1) with aspect ratio r1 is rendered
     * on a picture of size (x2,y2) with aspect ratio r2, if x1 grows to x1'
     * then y1 grows to y1' = x1' * y2/x2 * r2/r1 */
    SetOffset( (p_filter->fmt_in.video.i_x_offset + p_filter->fmt_in.video.i_visible_width),
               (p_filter->fmt_in.video.i_y_offset + p_filter->fmt_in.video.i_visible_height),
               (p_filter->fmt_out.video.i_x_offset + p_filter->fmt_out.video.i_visible_width),
               (p_filter->fmt_out.video.i_y_offset + p_filter->fmt_out.video.i_visible_height),
               &b_hscale, &i_vscale, p_offset_start );

    if(b_hscale &&
       AllocateOrGrow(&p_sys->p_buffer, &p_sys->i_buffer_size,
                      p_filter->fmt_in.video.i_x_offset +
                      p_filter->fmt_in.video.i_visible_width,
                      p_sys->i_bytespp))
        return;
    else p_buffer_start = (uint32_t*)p_sys->p_buffer;

    /*
     * Perform conversion
     */
    i_scale_count = ( i_vscale == 1 ) ?
                    (p_filter->fmt_out.video.i_y_offset + p_filter->fmt_out.video.i_visible_height) :
                    (p_filter->fmt_in.video.i_y_offset + p_filter->fmt_in.video.i_visible_height);
    for( i_y = 0; i_y < (p_filter->fmt_in.video.i_y_offset + p_filter->fmt_in.video.i_visible_height); i_y++ )
    {
        p_pic_start = p_pic;
        p_buffer = b_hscale ? p_buffer_start : p_pic;

        for ( i_x = (p_filter->fmt_in.video.i_x_offset + p_filter->fmt_in.video.i_visible_width) / 8; i_x--; )
        {
            CONVERT_YUV_PIXEL(4);  CONVERT_Y_PIXEL(4);
            CONVERT_YUV_PIXEL(4);  CONVERT_Y_PIXEL(4);
            CONVERT_YUV_PIXEL(4);  CONVERT_Y_PIXEL(4);
            CONVERT_YUV_PIXEL(4);  CONVERT_Y_PIXEL(4);
        }

        /* Here we do some unaligned reads and duplicate conversions, but
         * at least we have all the pixels */
        if( i_rewind )
        {
            p_y -= i_rewind;
            p_u -= i_rewind >> 1;
            p_v -= i_rewind >> 1;
            p_buffer -= i_rewind;
            CONVERT_YUV_PIXEL(4);  CONVERT_Y_PIXEL(4);
            CONVERT_YUV_PIXEL(4);  CONVERT_Y_PIXEL(4);
            CONVERT_YUV_PIXEL(4);  CONVERT_Y_PIXEL(4);
            CONVERT_YUV_PIXEL(4);  CONVERT_Y_PIXEL(4);
        }
        SCALE_WIDTH;
        SCALE_HEIGHT( 420, 4 );

        p_y += i_source_margin;
        if( i_y % 2 )
        {
            p_u += i_source_margin_c;
            p_v += i_source_margin_c;
        }
    }
}