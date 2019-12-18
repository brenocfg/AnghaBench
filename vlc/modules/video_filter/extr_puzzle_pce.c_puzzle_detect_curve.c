#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {float f_x; float f_y; } ;
typedef  TYPE_1__ point_t ;
typedef  int int8_t ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  filter_t ;

/* Variables and functions */
 int MAX_SECT ; 
 float bezier_val (TYPE_1__*,float,int,int /*<<< orphan*/ ) ; 
 void* floor (float) ; 
 int puzzle_SHAPE_TOP ; 
 scalar_t__ puzzle_diagonal_limit (int /*<<< orphan*/ *,scalar_t__,int,int) ; 
 int /*<<< orphan*/  x ; 
 int /*<<< orphan*/  y ; 

int puzzle_detect_curve( filter_t *p_filter, int32_t i_y, float f_x_ratio, float f_y_ratio, point_t *ps_pt, uint8_t i_pts_nbr, uint8_t i_border, uint8_t i_plane, int32_t *pi_sects)
{
    int8_t i_main_t = 0;
    float f_xd, f_yd;
    float f_xo = ps_pt[0].f_x * f_x_ratio;
    float f_yo = ps_pt[0].f_y * f_y_ratio;
    int8_t i_sect = 0;

    for (float f_t = 0; f_t <= i_pts_nbr - 1; f_t += 0.1 ) {
        i_main_t = floor(f_t);
        if ( i_main_t == i_pts_nbr - 1 )
            i_main_t = i_pts_nbr - 2;
        float f_sub_t = f_t - i_main_t;

        f_xd = bezier_val(ps_pt,f_sub_t,i_main_t,x) * f_x_ratio;
        f_yd = bezier_val(ps_pt,f_sub_t,i_main_t,y) * f_y_ratio;

        if ((f_yo < (float)i_y+0.5 && f_yd >= (float)i_y+0.5) || (f_yo > (float)i_y+0.5 && f_yd <= (float)i_y+0.5)) {
            pi_sects[i_sect] = floor(((float)i_y+0.5 - f_yo) * (f_xd - f_xo) / (f_yd - f_yo) + f_xo);
            if (i_sect < MAX_SECT - 1)
                i_sect++;
        }

        f_xo = f_xd;
        f_yo = f_yd;
    }
    f_xd = ps_pt[i_pts_nbr - 1].f_x * f_x_ratio;
    f_yd = ps_pt[i_pts_nbr - 1].f_y * f_y_ratio;

    /* ...fill from this junction to next junction */
    if ( i_y >= 0 ) {
        /* last diagonal intersection */
        pi_sects[i_sect] = (i_border==puzzle_SHAPE_TOP)?puzzle_diagonal_limit( p_filter, i_y, false, i_plane )
                                                       :puzzle_diagonal_limit( p_filter, i_y, true,  i_plane );
        if (i_sect < MAX_SECT - 1)
            i_sect++;
    }

    /* ...reorder the list of intersection */
    int32_t i_s = 0;

    while (i_s < (i_sect - 1)) {
        if (pi_sects[i_s] > pi_sects[i_s+1]) {
            uint32_t i_temp = pi_sects[i_s];
            pi_sects[i_s] = pi_sects[i_s+1];
            pi_sects[i_s+1] = i_temp;
            i_s = 0;
        }
        else {
            i_s++;
        }
    }

    return i_sect;
}