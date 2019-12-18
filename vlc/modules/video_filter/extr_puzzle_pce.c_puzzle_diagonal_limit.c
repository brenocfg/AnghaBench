#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  int int32_t ;
struct TYPE_6__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ filter_t ;
struct TYPE_7__ {TYPE_1__* ps_desk_planes; } ;
typedef  TYPE_3__ filter_sys_t ;
struct TYPE_5__ {int i_pce_max_lines; int i_pce_max_width; } ;

/* Variables and functions */

int32_t puzzle_diagonal_limit( filter_t *p_filter, int32_t i_y, bool b_left, uint8_t i_plane )
{
    filter_sys_t *p_sys = p_filter->p_sys;

    if (b_left ^ (i_y >= p_sys->ps_desk_planes[i_plane].i_pce_max_lines / 2))
        return ( i_y * p_sys->ps_desk_planes[i_plane].i_pce_max_width) / p_sys->ps_desk_planes[i_plane].i_pce_max_lines;
    else
        return p_sys->ps_desk_planes[i_plane].i_pce_max_width - ( ( i_y * p_sys->ps_desk_planes[i_plane].i_pce_max_width) / p_sys->ps_desk_planes[i_plane].i_pce_max_lines);
}