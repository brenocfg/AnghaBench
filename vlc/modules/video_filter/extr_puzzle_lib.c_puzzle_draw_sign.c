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
typedef  int uint8_t ;
struct TYPE_4__ {size_t i_pixel_pitch; int* p_pixels; size_t i_pitch; size_t i_visible_pitch; size_t i_visible_lines; } ;
typedef  TYPE_1__ plane_t ;
struct TYPE_5__ {TYPE_1__* p; } ;
typedef  TYPE_2__ picture_t ;
typedef  size_t int32_t ;

/* Variables and functions */
 size_t Y_PLANE ; 
 int /*<<< orphan*/  memset (int*,int,size_t) ; 

void puzzle_draw_sign(picture_t *p_pic_out, int32_t i_x, int32_t i_y, int32_t i_width, int32_t i_lines, const char **ppsz_sign, bool b_reverse)
{
    plane_t *p_out = &p_pic_out->p[Y_PLANE];
    int32_t i_pixel_pitch    = p_pic_out->p[Y_PLANE].i_pixel_pitch;

    uint8_t i_Y;

    i_Y = ( p_out->p_pixels[ i_y * p_out->i_pitch + i_x ] >= 0x7F ) ? 0x00 : 0xFF;

    for( int32_t y = 0; y < i_lines ; y++ )
        for( int32_t x = 0; x < i_width; x++ ) {
            int32_t i_dst_x = ( x + i_x ) * i_pixel_pitch;
            int32_t i_dst_y = y + i_y;
            if ( ppsz_sign[y][b_reverse?i_width-1-x:x] == 'o' ) {
                if ((i_dst_x < p_out->i_visible_pitch) && (i_dst_y < p_out->i_visible_lines) && (i_dst_x >= 0 ) && (i_dst_y >= 0))
                    memset( &p_out->p_pixels[ i_dst_y * p_out->i_pitch + i_dst_x ],   i_Y,  p_out->i_pixel_pitch );
            }
            else if ( ppsz_sign[y][b_reverse?i_width-1-x:x] == '.' ) {
                if ((i_dst_x < p_out->i_visible_pitch) && (i_dst_y < p_out->i_visible_lines) && (i_dst_x >= 0 ) && (i_dst_y >= 0))
                    p_out->p_pixels[ i_dst_y * p_out->i_pitch + i_dst_x ] = p_out->p_pixels[ i_dst_y * p_out->i_pitch + i_dst_x ] / 2 + i_Y / 2;
            }
        }
}