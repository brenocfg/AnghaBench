#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_7__ {scalar_t__ i_min_x; scalar_t__ i_max_x; scalar_t__ i_min_y; scalar_t__ i_max_y; } ;
typedef  TYPE_2__ piece_t ;
typedef  scalar_t__ int32_t ;
struct TYPE_8__ {TYPE_4__* p_sys; } ;
typedef  TYPE_3__ filter_t ;
struct TYPE_6__ {size_t i_pieces_nbr; } ;
struct TYPE_9__ {TYPE_2__* ps_pieces; TYPE_1__ s_allocated; } ;
typedef  TYPE_4__ filter_sys_t ;

/* Variables and functions */

int puzzle_find_piece( filter_t *p_filter, int32_t i_x, int32_t i_y, int32_t i_except) {
    filter_sys_t *p_sys = p_filter->p_sys;

    for (uint32_t i = 0; i < p_sys->s_allocated.i_pieces_nbr; i++) {
        piece_t *ps_current_piece = &p_sys->ps_pieces[i];
        if (( ps_current_piece->i_min_x <= i_x ) &&
            ( ps_current_piece->i_max_x >= i_x ) &&
            ( ps_current_piece->i_min_y <= i_y ) &&
            ( ps_current_piece->i_max_y  >= i_y ) &&
            ( (int32_t)i != i_except ) )
        {
            return i;
        }
    }
    return -1;
}