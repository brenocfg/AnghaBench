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
typedef  int uint8_t ;

/* Variables and functions */
 int WHITE ; 
 int abs (int) ; 
 int const** pi_kernel_x ; 
 int const** pi_kernel_y ; 

__attribute__((used)) static uint8_t sobel( const uint8_t *p_pixels, const int i_pitch,
                      const int i_lines, int i_col, int i_line )
{
    int i_x_val = 0;
    int i_y_val = 0;
    int i_col_offset;
    int i_line_offset;
    for ( int i_x = 0; i_x < 3; i_x++ )
    {
        /* Check if we are at the first pixel on the scanline */
        if (i_x == 0 && i_col == 0)
        {
            /* Duplicate the first pixel on the scanline */
            i_col_offset = 0;
        }
        /* Check if we are on the last pixel on the scanline */
        else if (i_x == 2 && i_col == i_pitch - 1)
        {
            /* Duplicate the last pixel on the scanline */
            i_col_offset = i_pitch - 1;
        }
        else
        {
            i_col_offset = i_col + i_x - 1;
        }
        for ( int i_y = 0; i_y < 3; i_y++ )
        {
            /* Check if we are at the top scanline */
            if (i_y == 0 && i_line == 0)
            {
                /* Duplicate the top pixel */
                i_line_offset = 0;
            }
            /* Check if we are the bottom scanline */
            else if (i_y == 2 && i_line == i_lines - 1 )
            {
                /* Duplicate the bottom pixel */
                i_line_offset = i_pitch * (i_lines - 1);
            }
            else {
                i_line_offset = i_pitch * (i_line + i_y - 1);
            }
            /* Apply the kernel to the pixel */
            i_x_val += pi_kernel_x[i_x][i_y] * p_pixels[i_line_offset + i_col_offset];
            i_y_val += pi_kernel_y[i_x][i_y] * p_pixels[i_line_offset + i_col_offset];
        }
    }
    int i_ret = abs(i_x_val) + abs(i_y_val);
    return (i_ret > WHITE) ? WHITE : i_ret;
}