#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {int /*<<< orphan*/  i_height; int /*<<< orphan*/  i_width; } ;
typedef  TYPE_3__ video_format_t ;
struct TYPE_24__ {TYPE_2__* p; } ;
typedef  TYPE_4__ picture_t ;
struct TYPE_21__ {TYPE_3__ video; } ;
struct TYPE_25__ {TYPE_1__ fmt_in; TYPE_6__* p_sys; } ;
typedef  TYPE_5__ filter_t ;
struct TYPE_26__ {TYPE_4__* p_old; int /*<<< orphan*/  color_y_max; int /*<<< orphan*/  color_y_min; int /*<<< orphan*/  color_x_max; int /*<<< orphan*/  color_x_min; int /*<<< orphan*/  colors; int /*<<< orphan*/  p_buf; int /*<<< orphan*/  p_buf2; int /*<<< orphan*/  i_colors; scalar_t__ is_yuv_planar; } ;
typedef  TYPE_6__ filter_sys_t ;
struct TYPE_22__ {int /*<<< orphan*/  i_pitch; int /*<<< orphan*/ * p_pixels; } ;

/* Variables and functions */
 int /*<<< orphan*/  Draw (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FindShapes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PreparePacked (TYPE_5__*,TYPE_4__*,int*) ; 
 int /*<<< orphan*/  PreparePlanar (TYPE_5__*,TYPE_4__*) ; 
 size_t Y_PLANE ; 
 TYPE_4__* filter_NewPicture (TYPE_5__*) ; 
 int /*<<< orphan*/  picture_Copy (TYPE_4__*,TYPE_4__*) ; 
 void* picture_Hold (TYPE_4__*) ; 
 int /*<<< orphan*/  picture_Release (TYPE_4__*) ; 

__attribute__((used)) static picture_t *Filter( filter_t *p_filter, picture_t *p_inpic )
{
    filter_sys_t *p_sys = p_filter->p_sys;

    if( !p_inpic )
        return NULL;

    picture_t *p_outpic = filter_NewPicture( p_filter );
    if( !p_outpic )
    {
        picture_Release( p_inpic );
        return NULL;
    }
    picture_Copy( p_outpic, p_inpic );

    if( !p_sys->p_old )
    {
        p_sys->p_old = picture_Hold( p_inpic );
        goto exit;
    }

    int i_pix_offset;
    int i_pix_size;
    if( p_sys->is_yuv_planar )
    {
        PreparePlanar( p_filter, p_inpic );
        i_pix_offset = 0;
        i_pix_size = 1;
    }
    else
    {
        if( PreparePacked( p_filter, p_inpic, &i_pix_offset ) )
            goto exit;
        i_pix_size = 2;
    }

    /**
     * Get the areas where movement was detected
     */
    const video_format_t *p_fmt = &p_filter->fmt_in.video;
    p_sys->i_colors = FindShapes( p_sys->p_buf2, p_sys->p_buf, p_fmt->i_width, p_fmt->i_width, p_fmt->i_height,
                                  p_sys->colors, p_sys->color_x_min, p_sys->color_x_max, p_sys->color_y_min, p_sys->color_y_max );

    /**
     * Count final number of shapes
     * Draw rectangles (there can be more than 1 moving shape in 1 rectangle)
     */
    Draw( p_filter, &p_outpic->p[Y_PLANE].p_pixels[i_pix_offset], p_outpic->p[Y_PLANE].i_pitch, i_pix_size );

    /* We're done. Lets keep a copy of the picture */
    picture_Release( p_sys->p_old );
    p_sys->p_old = picture_Hold( p_inpic );

exit:
    picture_Release( p_inpic );
    return p_outpic;
}