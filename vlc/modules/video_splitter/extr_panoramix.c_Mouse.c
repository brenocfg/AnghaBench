#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int x; int y; } ;
typedef  TYPE_3__ vout_window_mouse_event_t ;
struct TYPE_12__ {TYPE_5__* p_sys; } ;
typedef  TYPE_4__ video_splitter_t ;
struct TYPE_13__ {int i_row; int i_col; TYPE_6__** pp_output; } ;
typedef  TYPE_5__ video_splitter_sys_t ;
struct TYPE_9__ {int i_left; int i_top; int const i_right; int const i_bottom; } ;
struct TYPE_10__ {TYPE_1__ black; } ;
struct TYPE_14__ {int i_output; int const i_width; int const i_height; int i_src_x; int i_src_y; TYPE_2__ filter; scalar_t__ b_active; } ;
typedef  TYPE_6__ panoramix_output_t ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 

__attribute__((used)) static int Mouse( video_splitter_t *p_splitter, int i_index,
                  vout_window_mouse_event_t *restrict ev )
{
    video_splitter_sys_t *p_sys = p_splitter->p_sys;

    for( int y = 0; y < p_sys->i_row; y++ )
    {
        for( int x = 0; x < p_sys->i_col; x++ )
        {
            const panoramix_output_t *p_output = &p_sys->pp_output[x][y];
            if( p_output->b_active && p_output->i_output == i_index )
            {
                const int i_x = ev->x - p_output->filter.black.i_left;
                const int i_y = ev->y - p_output->filter.black.i_top;

                if( i_x >= 0 && i_x < p_output->i_width  - p_output->filter.black.i_right &&
                    i_y >= 0 && i_y < p_output->i_height - p_output->filter.black.i_bottom )
                {
                    ev->x = p_output->i_src_x + i_x;
                    ev->y = p_output->i_src_y + i_y;
                    return VLC_SUCCESS;
                }
            }
        }
    }
    return VLC_EGENERIC;
}