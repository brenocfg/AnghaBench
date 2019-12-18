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
typedef  size_t uint32_t ;
typedef  size_t int32_t ;
struct TYPE_13__ {TYPE_6__* p_sys; } ;
typedef  TYPE_5__ filter_t ;
struct TYPE_10__ {unsigned int i_pieces_nbr; } ;
struct TYPE_9__ {int i_auto_solve_speed; } ;
struct TYPE_14__ {scalar_t__ i_auto_solve_countdown_val; TYPE_4__* ps_pieces; TYPE_2__ s_allocated; TYPE_1__ s_current_param; } ;
typedef  TYPE_6__ filter_sys_t ;
struct TYPE_12__ {scalar_t__ i_group_ID; int i_actual_mirror; TYPE_3__* ps_piece_in_plane; scalar_t__ i_actual_angle; int /*<<< orphan*/  b_finished; } ;
struct TYPE_11__ {int /*<<< orphan*/  i_original_y; int /*<<< orphan*/  i_actual_y; int /*<<< orphan*/  i_original_x; int /*<<< orphan*/  i_actual_x; } ;

/* Variables and functions */
 scalar_t__ init_countdown (int) ; 
 int /*<<< orphan*/  puzzle_calculate_corners (TYPE_5__*,size_t) ; 
 scalar_t__ vlc_mrand48 () ; 

void puzzle_auto_solve( filter_t *p_filter)
{
    filter_sys_t *p_sys = p_filter->p_sys;

    if ( p_sys->s_current_param.i_auto_solve_speed < 500 )
        return;

    if ( --p_sys->i_auto_solve_countdown_val > 0 )
        return;

    /* delay reached, preset next delay and proceed with puzzle_auto_solve */
    p_sys->i_auto_solve_countdown_val = init_countdown(p_sys->s_current_param.i_auto_solve_speed);

    /* random piece to be moved */
    int32_t i_start = ((unsigned)vlc_mrand48()) % p_sys->s_allocated.i_pieces_nbr;

    /* here the computer will help player by placing the piece at the final location */
    for (uint32_t i_l = 0; i_l < p_sys->s_allocated.i_pieces_nbr; i_l++) {
        int32_t i = ( i_l + i_start ) % p_sys->s_allocated.i_pieces_nbr;
        if ( !p_sys->ps_pieces[i].b_finished ) {
            for (uint32_t j = 0; j < p_sys->s_allocated.i_pieces_nbr; j++) {
                if ( p_sys->ps_pieces[j].i_group_ID == p_sys->ps_pieces[i].i_group_ID ) {
                    p_sys->ps_pieces[j].i_actual_angle   = 0;
                    p_sys->ps_pieces[j].i_actual_mirror  = +1;
                    p_sys->ps_pieces[j].ps_piece_in_plane[0].i_actual_x = p_sys->ps_pieces[j].ps_piece_in_plane[0].i_original_x;
                    p_sys->ps_pieces[j].ps_piece_in_plane[0].i_actual_y = p_sys->ps_pieces[j].ps_piece_in_plane[0].i_original_y;
                    puzzle_calculate_corners( p_filter, j );
                }
            }
            break;
        }
    }
}