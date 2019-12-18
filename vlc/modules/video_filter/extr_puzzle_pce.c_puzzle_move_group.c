#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_10__ {size_t i_group_ID; int b_finished; TYPE_2__* ps_piece_in_plane; } ;
typedef  TYPE_3__ piece_t ;
typedef  size_t int32_t ;
struct TYPE_11__ {TYPE_5__* p_sys; } ;
typedef  TYPE_4__ filter_t ;
struct TYPE_8__ {size_t i_pieces_nbr; } ;
struct TYPE_12__ {TYPE_3__* ps_pieces; TYPE_1__ s_allocated; } ;
typedef  TYPE_5__ filter_sys_t ;
struct TYPE_9__ {int /*<<< orphan*/  i_actual_y; int /*<<< orphan*/  i_actual_x; } ;

/* Variables and functions */
 int /*<<< orphan*/  puzzle_calculate_corners (TYPE_4__*,size_t) ; 

void puzzle_move_group( filter_t *p_filter, int32_t i_piece, int32_t i_dx, int32_t i_dy)
{
    filter_sys_t *p_sys = p_filter->p_sys;
    uint32_t i_group_ID = p_sys->ps_pieces[i_piece].i_group_ID;
    for (uint32_t i = 0; i < p_sys->s_allocated.i_pieces_nbr; i++) {
        piece_t *ps_piece = &p_sys->ps_pieces[i];
        if (ps_piece->i_group_ID == i_group_ID) {
            ps_piece->b_finished = false;
            ps_piece->ps_piece_in_plane[0].i_actual_x += i_dx;
            ps_piece->ps_piece_in_plane[0].i_actual_y += i_dy;

            puzzle_calculate_corners( p_filter, i );
        }
    }
}