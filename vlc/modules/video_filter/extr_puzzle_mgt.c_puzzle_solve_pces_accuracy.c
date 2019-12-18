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
struct TYPE_10__ {int b_finished; int i_actual_mirror; size_t i_group_ID; scalar_t__ i_OTy; TYPE_2__* ps_piece_in_plane; scalar_t__ i_OLx; scalar_t__ i_TLy; scalar_t__ i_TLx; scalar_t__ i_TRy; scalar_t__ i_ORx; scalar_t__ i_TRx; } ;
typedef  TYPE_3__ piece_t ;
struct TYPE_11__ {TYPE_5__* p_sys; } ;
typedef  TYPE_4__ filter_t ;
struct TYPE_8__ {size_t i_pieces_nbr; } ;
struct TYPE_12__ {size_t i_solve_acc_loop; scalar_t__ i_done_count; scalar_t__ i_tmp_done_count; int b_finished; scalar_t__ i_magnet_accuracy; TYPE_3__* ps_pieces; TYPE_1__ s_allocated; } ;
typedef  TYPE_5__ filter_sys_t ;
struct TYPE_9__ {scalar_t__ i_actual_y; scalar_t__ i_actual_x; } ;

/* Variables and functions */
 scalar_t__ abs (scalar_t__) ; 
 int /*<<< orphan*/  puzzle_calculate_corners (TYPE_4__*,size_t) ; 

void puzzle_solve_pces_accuracy( filter_t *p_filter) {
    filter_sys_t *p_sys = p_filter->p_sys;

    p_sys->i_solve_acc_loop++;
    if (p_sys->i_solve_acc_loop >= p_sys->s_allocated.i_pieces_nbr) {
        p_sys->i_done_count = p_sys->i_tmp_done_count;
        p_sys->i_tmp_done_count = 0;
        p_sys->i_solve_acc_loop = 0;
        p_sys->b_finished = (p_sys->i_done_count == p_sys->s_allocated.i_pieces_nbr);
    }

    piece_t *ps_piece = &p_sys->ps_pieces[p_sys->i_solve_acc_loop];

    ps_piece->b_finished = false;
    if (    ps_piece->i_actual_mirror == 1
         && abs( ps_piece->i_TRx - ps_piece->i_ORx )  < p_sys->i_magnet_accuracy
         && abs( ps_piece->i_TRy - ps_piece->i_OTy )  < p_sys->i_magnet_accuracy
         && abs( ps_piece->i_TLx - ps_piece->i_OLx )  < p_sys->i_magnet_accuracy
         && abs( ps_piece->i_TLy - ps_piece->i_OTy )  < p_sys->i_magnet_accuracy )
    {
        uint32_t i_group_ID = ps_piece->i_group_ID;
        p_sys->i_tmp_done_count++;

        for ( uint32_t i = 0; i < p_sys->s_allocated.i_pieces_nbr; i++) {
            ps_piece = &p_sys->ps_pieces[i];
            if ( ( ps_piece->i_group_ID == i_group_ID ) && ( !ps_piece->b_finished ) ) {
                ps_piece->ps_piece_in_plane[0].i_actual_x = ps_piece->i_OLx;
                ps_piece->ps_piece_in_plane[0].i_actual_y = ps_piece->i_OTy;
                ps_piece->i_actual_mirror = +1;
                puzzle_calculate_corners( p_filter, i );
                ps_piece->b_finished = true;
            }
        }
    }
}