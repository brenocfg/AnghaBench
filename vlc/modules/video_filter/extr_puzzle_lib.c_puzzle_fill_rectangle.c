#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct TYPE_4__ {size_t i_pixel_pitch; size_t i_visible_pitch; size_t i_visible_lines; size_t i_pitch; int /*<<< orphan*/ * p_pixels; } ;
typedef  TYPE_1__ plane_t ;
struct TYPE_5__ {size_t i_planes; TYPE_1__* p; } ;
typedef  TYPE_2__ picture_t ;
typedef  size_t int32_t ;

/* Variables and functions */
 size_t U_PLANE ; 
 size_t V_PLANE ; 
 size_t Y_PLANE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,size_t,size_t) ; 

void puzzle_fill_rectangle(picture_t *p_pic_out, int32_t i_x, int32_t i_y, int32_t i_w, int32_t i_h, uint8_t i_Y, uint8_t i_U, uint8_t i_V )
{
    uint8_t i_c;

    for( uint8_t i_plane = 0; i_plane < p_pic_out->i_planes; i_plane++ ) {
        plane_t *p_oyp = &p_pic_out->p[i_plane];
        int32_t i_pixel_pitch    = p_pic_out->p[i_plane].i_pixel_pitch;

        if (i_plane == Y_PLANE)
            i_c = i_Y;
        else if (i_plane == U_PLANE)
            i_c = i_U;
        else if (i_plane == V_PLANE)
            i_c = i_V;

        int32_t i_x_min = (     i_x     * p_oyp->i_visible_pitch / p_pic_out->p[0].i_visible_pitch ) * i_pixel_pitch;
        int32_t i_x_max = ( (i_x + i_w) * p_oyp->i_visible_pitch / p_pic_out->p[0].i_visible_pitch ) * i_pixel_pitch;
        int32_t i_y_min =       i_y     * p_oyp->i_visible_lines / p_pic_out->p[0].i_visible_lines;
        int32_t i_y_max =   (i_y + i_h) * p_oyp->i_visible_lines / p_pic_out->p[0].i_visible_lines;

        for( int32_t i_dy = 0; i_dy < i_y_max - i_y_min; i_dy++ )
            memset( &p_oyp->p_pixels[(i_y_min + i_dy) * p_oyp->i_pitch + i_x_min], i_c,  i_x_max - i_x_min);
    }
}