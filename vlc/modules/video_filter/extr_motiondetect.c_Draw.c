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
typedef  int uint8_t ;
struct TYPE_5__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ filter_t ;
struct TYPE_6__ {int i_colors; int* colors; int* color_x_min; int* color_x_max; int* color_y_min; int* color_y_max; } ;
typedef  TYPE_2__ filter_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*,int) ; 

__attribute__((used)) static void Draw( filter_t *p_filter, uint8_t *p_pix, int i_pix_pitch, int i_pix_size )
{
    filter_sys_t *p_sys = p_filter->p_sys;

    int j = 0;

    for( int i = 1; i < p_sys->i_colors; i++ )
    {
        int x, y;

        if( p_sys->colors[i] != i )
            continue;

        const int color_x_min = p_sys->color_x_min[i];
        const int color_x_max = p_sys->color_x_max[i];
        const int color_y_min = p_sys->color_y_min[i];
        const int color_y_max = p_sys->color_y_max[i];

        if( color_x_min == -1 )
            continue;
        if( ( color_y_max - color_y_min ) * ( color_x_max - color_x_min ) < 16 )
            continue;

        j++;

        y = color_y_min;
        for( x = color_x_min; x <= color_x_max; x++ )
            p_pix[y*i_pix_pitch+x*i_pix_size] = 0xff;

        y = color_y_max;
        for( x = color_x_min; x <= color_x_max; x++ )
            p_pix[y*i_pix_pitch+x*i_pix_size] = 0xff;

        x = color_x_min;
        for( y = color_y_min; y <= color_y_max; y++ )
            p_pix[y*i_pix_pitch+x*i_pix_size] = 0xff;

        x = color_x_max;
        for( y = color_y_min; y <= color_y_max; y++ )
            p_pix[y*i_pix_pitch+x*i_pix_size] = 0xff;
    }
    msg_Dbg( p_filter, "Counted %d moving shapes.", j );
}