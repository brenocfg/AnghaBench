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
 void* POSTERIZE_PIXEL (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void RVPosterize( picture_t *p_pic, picture_t *p_outpic,
                                 bool rv32, int level )
{
    uint8_t *p_in, *p_in_end, *p_line_end, *p_out, pixel;

    p_in = p_pic->p[0].p_pixels;
    p_in_end = p_in + p_pic->p[0].i_visible_lines
        * p_pic->p[0].i_pitch;
    p_out = p_outpic->p[0].p_pixels;

    while( p_in < p_in_end )
    {
        p_line_end = p_in + p_pic->p[0].i_visible_pitch;
        while( p_in < p_line_end )
        {
            pixel = *p_in++;
            *p_out++ = POSTERIZE_PIXEL( pixel, level );
            pixel = *p_in++;
            *p_out++ = POSTERIZE_PIXEL( pixel, level );
            pixel = *p_in++;
            *p_out++ = POSTERIZE_PIXEL( pixel, level );
            /* for rv32 we take 4 chunks at the time */
            if ( rv32 )
            {
                pixel = *p_in++;
                *p_out++ = POSTERIZE_PIXEL( pixel, level );
            }
        }
        p_in += p_pic->p[0].i_pitch - p_pic->p[0].i_visible_pitch;
        p_out += p_outpic->p[0].i_pitch
            - p_outpic->p[0].i_visible_pitch;
    }
}