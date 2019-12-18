#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_7__ {float f_x; float f_y; } ;
typedef  TYPE_1__ point_t ;
typedef  int int8_t ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 float abs (float) ; 
 float bezier_val (TYPE_1__*,float,int,int /*<<< orphan*/ ) ; 
 int floor (float) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  x ; 
 int /*<<< orphan*/  y ; 

point_t *puzzle_scale_curve_H(int32_t i_width, int32_t i_lines, uint8_t i_pts_nbr, point_t *ps_pt, int32_t i_shape_size)
{
    if (ps_pt == NULL)
        return NULL;

    float f_x_ratio  = ((float) i_width) / (1 - (-1));
    float f_y_ratio  = (((float)i_lines) / 2) / (1 - (0));
    float f_x_offset = ((float)i_width) / (1 - (-1));
    float f_y_offset = 0;
    float f_bez_x, f_bez_y;

    float f_current_scale = 1;

    uint8_t i_last_pt = (3 * (i_pts_nbr-1) + 1);

    point_t *ps_new_pt = malloc( sizeof( point_t ) * i_last_pt );
    if (ps_new_pt == NULL)
        return NULL;

    bool b_fit = true;

    /* check if the curve fit with available space */
    do {
        b_fit = true;

        for (uint8_t i_p = 0; i_p < i_last_pt; i_p++) {
            if ( i_p == 0 || i_p == 1 )
                ps_new_pt[i_p].f_x = ps_pt[i_p].f_x * f_x_ratio + f_x_offset;
            else if ( i_p == i_last_pt - 2 || i_p == i_last_pt - 1 )
                ps_new_pt[i_p].f_x = ps_pt[i_p].f_x * f_x_ratio + f_x_offset;
            else
                ps_new_pt[i_p].f_x = ps_pt[i_p].f_x * f_x_ratio * f_current_scale + f_x_offset;
            ps_new_pt[i_p].f_y = ps_pt[i_p].f_y * f_y_ratio * f_current_scale + f_y_offset;
        }

        for (float f_t = 0; f_t <= i_pts_nbr - 1; f_t += 0.1 ) {
            int8_t i_main_t = floor(f_t);
            if ( i_main_t == i_pts_nbr - 1 )
                i_main_t = i_pts_nbr - 2;
            float f_sub_t = f_t - i_main_t;

            f_bez_x = bezier_val(ps_new_pt,f_sub_t,i_main_t,x);
            f_bez_y = bezier_val(ps_new_pt,f_sub_t,i_main_t,y);

            if ( f_bez_x < ((float) i_width) / 2 ) {
                if ( abs ( f_bez_y ) > ( f_bez_x * ( 0.9 * ((float)i_lines) / ((float)i_width) ) ) )
                    b_fit = false;
            }
            else  {
                if ( abs ( f_bez_y ) > ( ( ((float)i_width) - f_bez_x ) * ( 0.9 * ((float)i_lines) / ((float)i_width) ) ) )
                    b_fit = false;
            }
        }

        if (!b_fit)
            f_current_scale = f_current_scale * 0.9;
    }
    while ((!b_fit) && (f_current_scale>0.1));

    if (!b_fit) {
        free(ps_new_pt);
        return NULL;
    }

    /* global scale shall be applied: */
    f_current_scale = f_current_scale * (0.5 + 0.5* (float)i_shape_size / 100);
    for (uint8_t i_p = 0; i_p < i_last_pt; i_p++) {
        if ( i_p == 0 || i_p == 1 )
            ps_new_pt[i_p].f_x = ps_pt[i_p].f_x * f_x_ratio + f_x_offset;
        else if ( i_p == i_last_pt - 2 || i_p == i_last_pt - 1 )
            ps_new_pt[i_p].f_x = ps_pt[i_p].f_x * f_x_ratio + f_x_offset;
        else
            ps_new_pt[i_p].f_x = ps_pt[i_p].f_x * f_x_ratio * f_current_scale + f_x_offset;
        ps_new_pt[i_p].f_y = ps_pt[i_p].f_y * f_y_ratio * f_current_scale + f_y_offset;
    }

    return ps_new_pt;
}