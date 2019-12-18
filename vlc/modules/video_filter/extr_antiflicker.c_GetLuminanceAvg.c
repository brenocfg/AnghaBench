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
typedef  scalar_t__ uint8_t ;
struct TYPE_5__ {TYPE_1__* p; } ;
typedef  TYPE_2__ picture_t ;
struct TYPE_4__ {int i_visible_lines; int i_visible_pitch; int i_pitch; scalar_t__* p_pixels; } ;

/* Variables and functions */
 size_t Y_PLANE ; 

__attribute__((used)) static int GetLuminanceAvg( picture_t *p_pic )
{
    uint8_t *p_yplane_out = p_pic->p[Y_PLANE].p_pixels;

    int i_num_lines = p_pic->p[Y_PLANE].i_visible_lines;
    int i_num_cols = p_pic->p[Y_PLANE].i_visible_pitch;
    int i_in_pitch = p_pic->p[Y_PLANE].i_pitch;

    if( i_num_lines == 0 || i_num_cols == 0 )
        return 0;

    unsigned lum_sum = 0;
    for( int i_line = 0 ; i_line < i_num_lines ; ++i_line )
    {
        for( int i_col = 0 ; i_col < i_num_cols; ++i_col )
        {
            lum_sum += p_yplane_out[i_line*i_in_pitch+i_col];
        }
    }
    unsigned div = i_num_lines * i_num_cols;
    return (lum_sum + (div>>1)) / div;
}