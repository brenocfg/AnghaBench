#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned int i_visible_width; unsigned int i_visible_height; } ;
struct TYPE_6__ {TYPE_1__ video; } ;
struct TYPE_7__ {TYPE_2__ fmt_out; } ;
typedef  TYPE_3__ filter_t ;

/* Variables and functions */

__attribute__((used)) static void svg_RescaletoFit( filter_t *p_filter, int *width, int *height, float *scale )
{
    *scale = 1.0;

    if( *width > 0 && *height > 0 )
    {
        if( (unsigned)*width > p_filter->fmt_out.video.i_visible_width )
            *scale = (1.0 * p_filter->fmt_out.video.i_visible_width / *width);

        if( (unsigned)*height > p_filter->fmt_out.video.i_visible_height )
        {
            float y_scale = (1.0 * p_filter->fmt_out.video.i_visible_height / *height);
            if( y_scale < *scale )
                *scale = y_scale;
        }

        *width *= *scale;
        *height *= *scale;
    }
}