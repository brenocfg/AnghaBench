#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_19__ {scalar_t__ i_cols; scalar_t__ i_rows; scalar_t__ i_rotate; TYPE_2__* ps_pieces; } ;
typedef  TYPE_7__ save_game_t ;
typedef  int int32_t ;
struct TYPE_20__ {TYPE_9__* p_sys; } ;
typedef  TYPE_8__ filter_t ;
struct TYPE_17__ {scalar_t__ i_rows; scalar_t__ i_rotate; size_t i_pieces_nbr; int i_cols; } ;
struct TYPE_16__ {scalar_t__ i_cols; } ;
struct TYPE_21__ {TYPE_3__* ps_pieces; TYPE_5__ s_allocated; TYPE_6__* ps_desk_planes; TYPE_4__ s_current_param; } ;
typedef  TYPE_9__ filter_sys_t ;
struct TYPE_18__ {int i_border_width; int i_border_lines; scalar_t__ i_lines; scalar_t__ i_width; } ;
struct TYPE_15__ {scalar_t__ i_original_row; scalar_t__ i_original_col; int i_top_shape; int i_btm_shape; int i_right_shape; int i_left_shape; size_t i_group_ID; int b_finished; TYPE_1__* ps_piece_in_plane; int /*<<< orphan*/  i_actual_mirror; int /*<<< orphan*/  i_actual_angle; } ;
struct TYPE_14__ {scalar_t__ i_original_row; scalar_t__ i_original_col; float f_pos_x; float f_pos_y; int i_top_shape; int i_btm_shape; int i_right_shape; int i_left_shape; int /*<<< orphan*/  i_actual_mirror; int /*<<< orphan*/  i_actual_angle; } ;
struct TYPE_13__ {int i_actual_x; int i_actual_y; } ;

/* Variables and functions */
 unsigned int SHAPES_QTY ; 
 int /*<<< orphan*/  puzzle_calculate_corners (TYPE_8__*,size_t) ; 
 int vlc_mrand48 () ; 

void puzzle_load( filter_t *p_filter, save_game_t *ps_save_game)
{
    filter_sys_t *p_sys = p_filter->p_sys;

    if (p_sys->s_current_param.i_cols  != ps_save_game->i_cols
        || p_sys->s_allocated.i_rows   != ps_save_game->i_rows
        || p_sys->s_allocated.i_rotate != ps_save_game->i_rotate)
        return;

    int32_t i_border_width = p_sys->ps_desk_planes[0].i_border_width;
    int32_t i_border_lines = p_sys->ps_desk_planes[0].i_border_lines;

    for (uint32_t i_pce=0; i_pce < p_sys->s_allocated.i_pieces_nbr; i_pce++) {
       for (uint32_t i=0; i < p_sys->s_allocated.i_pieces_nbr; i++)
            if   ( p_sys->ps_pieces[i].i_original_row == ps_save_game->ps_pieces[i_pce].i_original_row
                && p_sys->ps_pieces[i].i_original_col == ps_save_game->ps_pieces[i_pce].i_original_col  )
            {
                p_sys->ps_pieces[i].ps_piece_in_plane[0].i_actual_x = i_border_width
                        + ((float)p_sys->ps_desk_planes[0].i_width - 2 * i_border_width)
                        * ps_save_game->ps_pieces[i_pce].f_pos_x;
                p_sys->ps_pieces[i].ps_piece_in_plane[0].i_actual_y = i_border_lines
                        + ((float)p_sys->ps_desk_planes[0].i_lines - 2 * i_border_lines)
                        * ps_save_game->ps_pieces[i_pce].f_pos_y;

                p_sys->ps_pieces[i].i_top_shape     =  ps_save_game->ps_pieces[i_pce].i_top_shape;
                p_sys->ps_pieces[i].i_btm_shape     =  ps_save_game->ps_pieces[i_pce].i_btm_shape;
                p_sys->ps_pieces[i].i_right_shape   =  ps_save_game->ps_pieces[i_pce].i_right_shape;
                p_sys->ps_pieces[i].i_left_shape    =  ps_save_game->ps_pieces[i_pce].i_left_shape;
                p_sys->ps_pieces[i].i_actual_angle  =  ps_save_game->ps_pieces[i_pce].i_actual_angle;
                p_sys->ps_pieces[i].i_actual_mirror =  ps_save_game->ps_pieces[i_pce].i_actual_mirror;
                p_sys->ps_pieces[i].i_group_ID     = i_pce;
                p_sys->ps_pieces[i].b_finished     = false;

                p_sys->ps_pieces[i].ps_piece_in_plane[0].i_actual_x = i_border_width + ((float)p_sys->ps_desk_planes[0].i_width
                                                                        - 2*i_border_width) * ps_save_game->ps_pieces[i_pce].f_pos_x;
                p_sys->ps_pieces[i].ps_piece_in_plane[0].i_actual_y = i_border_lines + ((float)p_sys->ps_desk_planes[0].i_lines
                                                                        - 2*i_border_lines) * ps_save_game->ps_pieces[i_pce].f_pos_y;
                puzzle_calculate_corners( p_filter, i );

                break;
            }
    }

    for (uint32_t i_pce=0; i_pce < p_sys->s_allocated.i_pieces_nbr; i_pce++) {
        /* redefine shapes */
        uint32_t i_left_pce  = 0;
        uint32_t i_right_pce = 6;
        uint32_t i_top_pce   = 2;
        uint32_t i_btm_pce   = 4;

        uint32_t i_pce_pair = 0;
        for (int32_t i_row = 0; i_row < p_sys->s_allocated.i_rows; i_row++)
            for (int32_t i_col = 0; i_col < p_sys->s_allocated.i_cols; i_col++) {
                if (p_sys->ps_pieces[i_pce].i_original_row == p_sys->ps_pieces[i_pce_pair].i_original_row) {
                    if (p_sys->ps_pieces[i_pce].i_original_col == p_sys->ps_pieces[i_pce_pair].i_original_col - 1)
                        i_right_pce = i_pce_pair;
                    else if (p_sys->ps_pieces[i_pce].i_original_col == p_sys->ps_pieces[i_pce_pair].i_original_col + 1)
                        i_left_pce = i_pce_pair;
                }
                else if (p_sys->ps_pieces[i_pce].i_original_col == p_sys->ps_pieces[i_pce_pair].i_original_col) {
                    if (p_sys->ps_pieces[i_pce].i_original_row == p_sys->ps_pieces[i_pce_pair].i_original_row - 1)
                        i_btm_pce = i_pce_pair;
                    else if (p_sys->ps_pieces[i_pce].i_original_row == p_sys->ps_pieces[i_pce_pair].i_original_row + 1)
                        i_top_pce = i_pce_pair;
                }
                i_pce_pair++;
            }

        if ((p_sys->ps_pieces[i_pce].i_left_shape == 0) && (p_sys->ps_pieces[i_pce].i_original_col != 0)) {
            p_sys->ps_pieces[i_left_pce].i_right_shape = 6 + 8 + 8*(( (unsigned) vlc_mrand48()) % ( SHAPES_QTY ) ) + (vlc_mrand48() & 0x01);
            p_sys->ps_pieces[i_pce].i_left_shape = (p_sys->ps_pieces[i_left_pce].i_right_shape - 6 ) ^ 0x01;
        }

        if ((p_sys->ps_pieces[i_pce].i_right_shape == 6) && (p_sys->ps_pieces[i_pce].i_original_col != p_sys->s_allocated.i_cols-1)) {
            p_sys->ps_pieces[i_pce].i_right_shape = 6 + 8 + 8*(( (unsigned) vlc_mrand48()) % ( SHAPES_QTY ) ) + (vlc_mrand48() & 0x01);
            p_sys->ps_pieces[i_right_pce].i_left_shape = (p_sys->ps_pieces[i_pce].i_right_shape - 6 ) ^ 0x01;
        }

        if ((p_sys->ps_pieces[i_pce].i_top_shape == 2) && (p_sys->ps_pieces[i_pce].i_original_row != 0)) {
            p_sys->ps_pieces[i_top_pce].i_btm_shape = 4 + 8 + 8*(( (unsigned) vlc_mrand48()) % ( SHAPES_QTY ) ) + (vlc_mrand48() & 0x01);
            p_sys->ps_pieces[i_pce].i_top_shape = (p_sys->ps_pieces[i_top_pce].i_btm_shape - 2 ) ^ 0x01;
        }

        if ((p_sys->ps_pieces[i_pce].i_btm_shape == 4) && (p_sys->ps_pieces[i_pce].i_original_row != p_sys->s_allocated.i_rows-1)) {
            p_sys->ps_pieces[i_pce].i_btm_shape = 4 + 8 + 8*(( (unsigned) vlc_mrand48()) % ( SHAPES_QTY ) ) + (vlc_mrand48() & 0x01);
            p_sys->ps_pieces[i_btm_pce].i_top_shape = (p_sys->ps_pieces[i_pce].i_btm_shape - 2 ) ^ 0x01;
        }

    }
}