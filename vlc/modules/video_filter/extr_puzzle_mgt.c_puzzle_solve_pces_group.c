#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_8__ {scalar_t__ i_actual_angle; scalar_t__ i_actual_mirror; scalar_t__ i_group_ID; int i_OTy; int i_ORx; int i_OLx; int i_TRx; int i_TLx; int i_TRy; int i_TLy; int i_BRx; int i_BLx; int i_BRy; int i_BLy; size_t i_step_x_x; int i_OBy; size_t i_step_y_y; int i_right_shape; int i_top_shape; int i_btm_shape; scalar_t__ i_left_shape; int /*<<< orphan*/  b_finished; } ;
typedef  TYPE_2__ piece_t ;
typedef  size_t int32_t ;
struct TYPE_9__ {TYPE_4__* p_sys; } ;
typedef  TYPE_3__ filter_t ;
struct TYPE_7__ {size_t i_pieces_nbr; } ;
struct TYPE_10__ {size_t i_solve_grp_loop; int i_magnet_accuracy; TYPE_2__* ps_pieces; TYPE_1__ s_allocated; } ;
typedef  TYPE_4__ filter_sys_t ;

/* Variables and functions */
 int abs (int) ; 
 int /*<<< orphan*/  puzzle_move_group (TYPE_3__*,size_t,size_t,size_t) ; 

void puzzle_solve_pces_group( filter_t *p_filter) {
    filter_sys_t *p_sys = p_filter->p_sys;
    int32_t i_dx, i_dy;

    p_sys->i_solve_grp_loop++;
    p_sys->i_solve_grp_loop %= p_sys->s_allocated.i_pieces_nbr;

    int32_t i_piece_A = p_sys->i_solve_grp_loop;
    piece_t *ps_piece_A = &p_sys->ps_pieces[i_piece_A];

    for (uint32_t i_piece_B = 0; i_piece_B < p_sys->s_allocated.i_pieces_nbr; i_piece_B++)
    {
        piece_t *ps_piece_B = &p_sys->ps_pieces[i_piece_B];

        if ( ps_piece_A->i_actual_angle != ps_piece_B->i_actual_angle || ps_piece_A->i_actual_mirror != ps_piece_B->i_actual_mirror )
            continue;

        if ( (ps_piece_B->i_group_ID != p_sys->ps_pieces[i_piece_A].i_group_ID ) )
        {
            if ( abs(ps_piece_A->i_OTy - ps_piece_B->i_OTy )<3)
            {
                if (    abs( ps_piece_A->i_ORx - ps_piece_B->i_OLx + 1 ) < 3
                     && abs( ps_piece_A->i_TRx - ps_piece_B->i_TLx + 1 ) < p_sys->i_magnet_accuracy
                     && abs( ps_piece_A->i_TRy - ps_piece_B->i_TLy ) < p_sys->i_magnet_accuracy
                     && abs( ps_piece_A->i_BRx - ps_piece_B->i_BLx + 1 ) < p_sys->i_magnet_accuracy
                     && abs( ps_piece_A->i_BRy - ps_piece_B->i_BLy ) < p_sys->i_magnet_accuracy )
                {
                    i_dx = ps_piece_A->i_TRx - ps_piece_B->i_TLx + ps_piece_A->i_step_x_x;
                    i_dy = ps_piece_A->i_TRy - ps_piece_B->i_TLy;

                    if (!ps_piece_B->b_finished)
                        puzzle_move_group( p_filter, i_piece_B, i_dx, i_dy);
                    else
                        puzzle_move_group( p_filter, i_piece_A, -i_dx, -i_dy);

                    uint32_t i_group_ID = ps_piece_B->i_group_ID;
                    for (uint32_t i_for = 0; i_for < p_sys->s_allocated.i_pieces_nbr; i_for++)
                        if ( p_sys->ps_pieces[i_for].i_group_ID == i_group_ID)
                            p_sys->ps_pieces[i_for].i_group_ID = p_sys->ps_pieces[i_piece_A].i_group_ID;
                }
            }
            else if ( abs(ps_piece_A->i_OLx - ps_piece_B->i_OLx ) < 3 )
            {
                if (    abs(ps_piece_A->i_OBy - ps_piece_B->i_OTy + 1 ) < 3
                     && abs( ps_piece_B->i_TLx - ps_piece_A->i_BLx ) < p_sys->i_magnet_accuracy
                     && abs( ps_piece_B->i_TLy - 1 - ps_piece_A->i_BLy ) < p_sys->i_magnet_accuracy
                     && abs( ps_piece_B->i_TRx - ps_piece_A->i_BRx ) < p_sys->i_magnet_accuracy
                     && abs( ps_piece_B->i_TRy - 1 - ps_piece_A->i_BRy ) < p_sys->i_magnet_accuracy )
                {

                    i_dx = ps_piece_A->i_BLx - ps_piece_B->i_TLx;
                    i_dy = ps_piece_A->i_BLy - ps_piece_B->i_TLy + ps_piece_A->i_step_y_y;

                    if (!ps_piece_B->b_finished)
                        puzzle_move_group( p_filter, i_piece_B, i_dx, i_dy);
                    else
                        puzzle_move_group( p_filter, i_piece_A, -i_dx, -i_dy);

                    uint32_t i_group_ID = ps_piece_B->i_group_ID;
                    for (uint32_t i_for = 0; i_for < p_sys->s_allocated.i_pieces_nbr; i_for++)
                        if ( p_sys->ps_pieces[i_for].i_group_ID == i_group_ID)
                            p_sys->ps_pieces[i_for].i_group_ID = p_sys->ps_pieces[i_piece_A].i_group_ID;
                }
            }
        }

        if ( abs( ps_piece_A->i_OTy - ps_piece_B->i_OTy ) < 3 )
        {
            if (    abs( ps_piece_A->i_ORx - ps_piece_B->i_OLx + 1 ) < 3
                 && abs( ps_piece_A->i_TRx - ps_piece_B->i_TLx + 1 ) < p_sys->i_magnet_accuracy
                 && abs( ps_piece_A->i_TRy - ps_piece_B->i_TLy ) < p_sys->i_magnet_accuracy
                 && abs( ps_piece_A->i_BRx - ps_piece_B->i_BLx + 1 ) < p_sys->i_magnet_accuracy
                 && abs( ps_piece_A->i_BRy - ps_piece_B->i_BLy ) < p_sys->i_magnet_accuracy )
            {
                ps_piece_B->i_left_shape = 0;
                ps_piece_A->i_right_shape = 6;
            }
        }
        else if ( abs( ps_piece_A->i_OLx - ps_piece_B->i_OLx )<3 )
        {
            if (    abs( ps_piece_A->i_OBy - ps_piece_B->i_OTy + 1 )<3
                 && abs( ps_piece_B->i_TLx - ps_piece_A->i_BLx ) < p_sys->i_magnet_accuracy
                 && abs( ps_piece_B->i_TLy - 1 - ps_piece_A->i_BLy ) < p_sys->i_magnet_accuracy
                 && abs( ps_piece_B->i_TRx - ps_piece_A->i_BRx ) < p_sys->i_magnet_accuracy
                 && abs( ps_piece_B->i_TRy - 1 - ps_piece_A->i_BRy ) < p_sys->i_magnet_accuracy )
            {
                ps_piece_B->i_top_shape = 2;
                ps_piece_A->i_btm_shape = 4;
            }
        }
   }
}