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
typedef  void* uint8_t ;
struct TYPE_6__ {TYPE_1__* p; } ;
typedef  TYPE_2__ picture_t ;
struct TYPE_5__ {void** p_pixels; int i_visible_lines; int i_pitch; int i_visible_pitch; } ;

/* Variables and functions */
 size_t U_PLANE ; 
 size_t V_PLANE ; 
 size_t Y_PLANE ; 
 int /*<<< orphan*/  YuvPosterization (void**,void**,void**,void**,void*,void*,void*,void*,int) ; 

__attribute__((used)) static void PlanarYUVPosterize( picture_t *p_pic, picture_t *p_outpic,
                               int i_level )
{
    uint8_t *p_in_y, *p_in_u, *p_in_v, *p_in_end_y, *p_line_end_y, *p_out_y,
            *p_out_u, *p_out_v;
    int i_current_line = 0;

    p_in_y = p_pic->p[Y_PLANE].p_pixels;
    p_in_end_y = p_in_y + p_pic->p[Y_PLANE].i_visible_lines
        * p_pic->p[Y_PLANE].i_pitch;
    p_out_y = p_outpic->p[Y_PLANE].p_pixels;

    /* iterate for every visible line in the frame */
    while( p_in_y < p_in_end_y )
    {
        p_line_end_y = p_in_y + p_pic->p[Y_PLANE].i_visible_pitch;
        /* calculate start of U plane line */
        p_in_u = p_pic->p[U_PLANE].p_pixels
            + p_pic->p[U_PLANE].i_pitch * ( i_current_line / 2 );
        p_out_u = p_outpic->p[U_PLANE].p_pixels
            + p_outpic->p[U_PLANE].i_pitch * ( i_current_line / 2 );
        /* calculate start of V plane line */
        p_in_v = p_pic->p[V_PLANE].p_pixels
            + p_pic->p[V_PLANE].i_pitch * ( i_current_line / 2 );
        p_out_v = p_outpic->p[V_PLANE].p_pixels
            + p_outpic->p[V_PLANE].i_pitch * ( i_current_line / 2 );
        /* iterate for every two pixels in line */
        while( p_in_y < p_line_end_y )
        {
            uint8_t y1, y2, u, v;
            uint8_t posterized_y1, posterized_y2, posterized_u, posterized_v;
            /* retrieve original YUV values */
            y1 = *p_in_y++;
            y2 = *p_in_y++;
            u = *p_in_u++;
            v = *p_in_v++;
            /* do posterization */
            YuvPosterization( &posterized_y1, &posterized_y2, &posterized_u,
                             &posterized_v, y1, y2, u, v, i_level );
            /* put posterized valued */
            *p_out_y++ = posterized_y1;
            *p_out_y++ = posterized_y2;
            *p_out_u++ = posterized_u;
            *p_out_v++ = posterized_v;
        }
        p_in_y += p_pic->p[Y_PLANE].i_pitch
            - p_pic->p[Y_PLANE].i_visible_pitch;
        p_out_y += p_outpic->p[Y_PLANE].i_pitch
            - p_outpic->p[Y_PLANE].i_visible_pitch;
        i_current_line++;
    }
}