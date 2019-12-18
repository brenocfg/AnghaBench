#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_24__ {int i_actual_mirror; scalar_t__ i_actual_angle; } ;
typedef  TYPE_3__ piece_t ;
struct TYPE_25__ {scalar_t__ i_planes; } ;
typedef  TYPE_4__ picture_t ;
typedef  size_t int32_t ;
struct TYPE_26__ {TYPE_6__* p_sys; } ;
typedef  TYPE_5__ filter_t ;
struct TYPE_23__ {scalar_t__ i_shape_size; int /*<<< orphan*/  b_advanced; } ;
struct TYPE_22__ {size_t i_pieces_nbr; } ;
struct TYPE_27__ {int /*<<< orphan*/  b_shape_init; int /*<<< orphan*/ * ps_pieces_shapes; TYPE_2__ s_current_param; TYPE_3__* ps_pieces; TYPE_1__ s_allocated; int /*<<< orphan*/ * ps_puzzle_array; } ;
typedef  TYPE_6__ filter_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  puzzle_drw_adv_pce_in_plane (TYPE_5__*,TYPE_4__*,TYPE_4__*,scalar_t__,TYPE_3__*) ; 
 int /*<<< orphan*/  puzzle_drw_basic_pce_in_plane (TYPE_5__*,TYPE_4__*,TYPE_4__*,scalar_t__,TYPE_3__*) ; 
 int /*<<< orphan*/  puzzle_drw_complex_pce_in_plane (TYPE_5__*,TYPE_4__*,TYPE_4__*,scalar_t__,TYPE_3__*,size_t) ; 

void puzzle_draw_pieces( filter_t *p_filter, picture_t *p_pic_in, picture_t *p_pic_out)
{
    filter_sys_t *p_sys = p_filter->p_sys;

    if ((p_sys->ps_puzzle_array == NULL) || (p_sys->ps_pieces == NULL))
        return;

    for( uint8_t i_plane = 0; i_plane < p_pic_out->i_planes; i_plane++ ) {
        for ( int32_t i = p_sys->s_allocated.i_pieces_nbr-1; i >= 0 ; i-- ) {
            piece_t *ps_piece = &p_sys->ps_pieces[i];

            if (!p_sys->s_current_param.b_advanced
                    || (ps_piece->i_actual_mirror == 1 && ps_piece->i_actual_angle == 0
                    && p_sys->s_current_param.i_shape_size == 0))
            {
                puzzle_drw_basic_pce_in_plane(p_filter, p_pic_in, p_pic_out, i_plane, ps_piece);
            }
            else if ( ( p_sys->s_current_param.i_shape_size == 0) ||
                      (p_sys->ps_pieces_shapes == NULL) || (!p_sys->b_shape_init) )
            {
                puzzle_drw_adv_pce_in_plane(p_filter, p_pic_in, p_pic_out, i_plane, ps_piece);
            }
            else {
                puzzle_drw_complex_pce_in_plane(p_filter, p_pic_in, p_pic_out, i_plane, ps_piece, i);
            }
        }
    }

    return;
}