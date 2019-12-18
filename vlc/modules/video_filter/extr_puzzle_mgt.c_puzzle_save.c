#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int i_cols; int i_rows; TYPE_4__* ps_pieces; int /*<<< orphan*/  i_rotate; } ;
typedef  TYPE_6__ save_game_t ;
typedef  size_t int32_t ;
struct TYPE_18__ {TYPE_8__* p_sys; } ;
typedef  TYPE_7__ filter_t ;
struct TYPE_12__ {int i_cols; int i_rows; int /*<<< orphan*/  i_rotate; } ;
struct TYPE_19__ {TYPE_5__* ps_pieces; TYPE_3__* ps_desk_planes; TYPE_1__ s_allocated; } ;
typedef  TYPE_8__ filter_sys_t ;
struct TYPE_16__ {int /*<<< orphan*/  i_actual_mirror; int /*<<< orphan*/  i_actual_angle; TYPE_2__* ps_piece_in_plane; int /*<<< orphan*/  i_left_shape; int /*<<< orphan*/  i_right_shape; int /*<<< orphan*/  i_btm_shape; int /*<<< orphan*/  i_top_shape; int /*<<< orphan*/  i_original_col; int /*<<< orphan*/  i_original_row; } ;
struct TYPE_15__ {float f_pos_x; float f_pos_y; int /*<<< orphan*/  i_actual_mirror; int /*<<< orphan*/  i_actual_angle; int /*<<< orphan*/  i_left_shape; int /*<<< orphan*/  i_right_shape; int /*<<< orphan*/  i_btm_shape; int /*<<< orphan*/  i_top_shape; int /*<<< orphan*/  i_original_col; int /*<<< orphan*/  i_original_row; } ;
struct TYPE_14__ {size_t i_border_width; size_t i_border_lines; scalar_t__ i_lines; scalar_t__ i_width; } ;
struct TYPE_13__ {float i_actual_x; float i_actual_y; } ;

/* Variables and functions */
 void* calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_6__*) ; 

save_game_t* puzzle_save(filter_t *p_filter)
{
    filter_sys_t *p_sys = p_filter->p_sys;

    save_game_t *ps_save_game = calloc(1, sizeof(*ps_save_game));
    if (!ps_save_game)
        return NULL;

    ps_save_game->i_cols   = p_sys->s_allocated.i_cols;
    ps_save_game->i_rows   = p_sys->s_allocated.i_rows;
    ps_save_game->i_rotate = p_sys->s_allocated.i_rotate;

    ps_save_game->ps_pieces = calloc( ps_save_game->i_cols * ps_save_game->i_rows , sizeof(*ps_save_game->ps_pieces));
    if (!ps_save_game->ps_pieces) {
        free(ps_save_game);
        return NULL;
    }

    int32_t i_border_width = p_sys->ps_desk_planes[0].i_border_width;
    int32_t i_border_lines = p_sys->ps_desk_planes[0].i_border_lines;

    for (int32_t i_pce = 0; i_pce < ps_save_game->i_cols * ps_save_game->i_rows; i_pce++) {
        ps_save_game->ps_pieces[i_pce].i_original_row  = p_sys->ps_pieces[i_pce].i_original_row;
        ps_save_game->ps_pieces[i_pce].i_original_col  = p_sys->ps_pieces[i_pce].i_original_col;
        ps_save_game->ps_pieces[i_pce].i_top_shape     = p_sys->ps_pieces[i_pce].i_top_shape;
        ps_save_game->ps_pieces[i_pce].i_btm_shape     = p_sys->ps_pieces[i_pce].i_btm_shape;
        ps_save_game->ps_pieces[i_pce].i_right_shape   = p_sys->ps_pieces[i_pce].i_right_shape;
        ps_save_game->ps_pieces[i_pce].i_left_shape    = p_sys->ps_pieces[i_pce].i_left_shape;
        ps_save_game->ps_pieces[i_pce].f_pos_x         =(p_sys->ps_pieces[i_pce].ps_piece_in_plane[0].i_actual_x - i_border_width ) / ((float)p_sys->ps_desk_planes[0].i_width - 2*i_border_width);
        ps_save_game->ps_pieces[i_pce].f_pos_y         =(p_sys->ps_pieces[i_pce].ps_piece_in_plane[0].i_actual_y - i_border_lines ) / ((float)p_sys->ps_desk_planes[0].i_lines - 2*i_border_lines);
        ps_save_game->ps_pieces[i_pce].i_actual_angle  = p_sys->ps_pieces[i_pce].i_actual_angle;
        ps_save_game->ps_pieces[i_pce].i_actual_mirror = p_sys->ps_pieces[i_pce].i_actual_mirror;
    }

    return ps_save_game;
}