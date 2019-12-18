#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {TYPE_1__* p; } ;
typedef  TYPE_2__ picture_t ;
struct TYPE_5__ {int i_visible_lines; int i_pitch; int i_visible_pitch; int /*<<< orphan*/ * p_pixels; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADJUST_8_TIMES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLANAR_WRITE_UV (int) ; 
 size_t U_PLANE ; 
 int VLC_SUCCESS ; 
 size_t V_PLANE ; 

int planar_sat_hue_C( picture_t * p_pic, picture_t * p_outpic, int i_sin, int i_cos,
                         int i_sat, int i_x, int i_y )
{
    uint8_t *p_in, *p_in_v, *p_in_end, *p_line_end;
    uint8_t *p_out, *p_out_v;

    p_in = p_pic->p[U_PLANE].p_pixels;
    p_in_v = p_pic->p[V_PLANE].p_pixels;
    p_in_end = p_in + p_pic->p[U_PLANE].i_visible_lines
                      * p_pic->p[U_PLANE].i_pitch - 8;

    p_out = p_outpic->p[U_PLANE].p_pixels;
    p_out_v = p_outpic->p[V_PLANE].p_pixels;

    uint8_t i_u, i_v;

    for( ; p_in < p_in_end ; )
    {
        p_line_end = p_in + p_pic->p[U_PLANE].i_visible_pitch - 8;

        for( ; p_in < p_line_end ; )
        {
            /* Do 8 pixels at a time */
            ADJUST_8_TIMES( PLANAR_WRITE_UV( 8 ) );
        }

        p_line_end += 8;

        for( ; p_in < p_line_end ; )
        {
            PLANAR_WRITE_UV( 8 );
        }

        p_in += p_pic->p[U_PLANE].i_pitch
                - p_pic->p[U_PLANE].i_visible_pitch;
        p_in_v += p_pic->p[V_PLANE].i_pitch
                - p_pic->p[V_PLANE].i_visible_pitch;
        p_out += p_outpic->p[U_PLANE].i_pitch
                - p_outpic->p[U_PLANE].i_visible_pitch;
        p_out_v += p_outpic->p[V_PLANE].i_pitch
                    - p_outpic->p[V_PLANE].i_visible_pitch;
    }

    return VLC_SUCCESS;
}