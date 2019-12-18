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
 int /*<<< orphan*/  memset (int*,int,int) ; 

__attribute__((used)) static void DrawRectangle( uint8_t *pb_dst, int i_pitch, int i_width, int i_height,
                           int x, int y, int i_w, int i_h )
{
    if( x + i_w > i_width || y + i_h > i_height )
        return;

    /* top line */
    memset( &pb_dst[y * i_pitch + x], 0xff, i_w );

    /* left and right */
    for( int dy = 1; dy < i_h-1; dy++ )
    {
        pb_dst[(y+dy) * i_pitch + x +     0] = 0xff;
        pb_dst[(y+dy) * i_pitch + x + i_w-1] = 0xff;
    }

    /* bottom line */
    memset( &pb_dst[(y+i_h-1) * i_pitch + x], 0xff, i_w );
}