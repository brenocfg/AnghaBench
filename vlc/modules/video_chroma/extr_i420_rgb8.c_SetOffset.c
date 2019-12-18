#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */

__attribute__((used)) static void SetOffset( int i_width, int i_height, int i_pic_width,
                       int i_pic_height, bool *pb_hscale,
                       int *pi_vscale, int *p_offset )
{
    int i_x;                                    /* x position in destination */
    int i_scale_count;                                     /* modulo counter */

    /*
     * Prepare horizontal offset array
     */
    if( i_pic_width - i_width == 0 )
    {
        /* No horizontal scaling: YUV conversion is done directly to picture */
        *pb_hscale = 0;
    }
    else if( i_pic_width - i_width > 0 )
    {
        int i_dummy = 0;

        /* Prepare scaling array for horizontal extension */
        *pb_hscale = 1;
        i_scale_count = i_pic_width;
        for( i_x = i_width; i_x--; )
        {
            while( (i_scale_count -= i_width) > 0 )
            {
                *p_offset++ = 0;
                *p_offset++ = 0;
            }
            *p_offset++ = 1;
            *p_offset++ = i_dummy;
            i_dummy = 1 - i_dummy;
            i_scale_count += i_pic_width;
        }
    }
    else /* if( i_pic_width - i_width < 0 ) */
    {
        int i_remainder = 0;
        int i_jump;

        /* Prepare scaling array for horizontal reduction */
        *pb_hscale = 1;
        i_scale_count = i_width;
        for( i_x = i_pic_width; i_x--; )
        {
            i_jump = 1;
            while( (i_scale_count -= i_pic_width) > 0 )
            {
                i_jump += 1;
            }
            *p_offset++ = i_jump;
            *p_offset++ = ( i_jump += i_remainder ) >> 1;
            i_remainder = i_jump & 1;
            i_scale_count += i_width;
        }
    }

    /*
     * Set vertical scaling indicator
     */
    if( i_pic_height - i_height == 0 )
    {
        *pi_vscale = 0;
    }
    else if( i_pic_height - i_height > 0 )
    {
        *pi_vscale = 1;
    }
    else /* if( i_pic_height - i_height < 0 ) */
    {
        *pi_vscale = -1;
    }
}