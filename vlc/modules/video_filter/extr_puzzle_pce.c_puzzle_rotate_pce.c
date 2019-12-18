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
typedef  scalar_t__ uint8_t ;
struct TYPE_10__ {int i_actual_angle; int i_actual_mirror; TYPE_2__* ps_piece_in_plane; } ;
typedef  TYPE_3__ piece_t ;
typedef  int int8_t ;
typedef  size_t int32_t ;
struct TYPE_11__ {TYPE_5__* p_sys; } ;
typedef  TYPE_4__ filter_t ;
struct TYPE_8__ {int i_rotate; } ;
struct TYPE_12__ {TYPE_1__ s_current_param; TYPE_3__* ps_pieces; } ;
typedef  TYPE_5__ filter_sys_t ;
struct TYPE_9__ {size_t i_actual_y; size_t i_actual_x; } ;

/* Variables and functions */
 scalar_t__ abs (int) ; 
 int /*<<< orphan*/  puzzle_calculate_corners (TYPE_4__*,size_t) ; 

void puzzle_rotate_pce( filter_t *p_filter, int32_t i_piece, int8_t i_rotate_mirror, int32_t i_center_x, int32_t i_center_y, bool b_avoid_mirror )
{
    filter_sys_t *p_sys = p_filter->p_sys;
    piece_t *ps_piece = &p_sys->ps_pieces[i_piece];

    if ( p_sys->s_current_param.i_rotate == 0 )
        return;

    if ( p_sys->s_current_param.i_rotate == 1 && (i_rotate_mirror != 2) )
        return;

    for ( uint8_t i=0; i < abs( i_rotate_mirror ); i++) {
        int32_t i_tempx, i_tempy;

        /* piece has to be rotated by 90° */
        if ( i_rotate_mirror > 0 ) {
            ps_piece->i_actual_angle++;
            ps_piece->i_actual_angle &= 0x03;

            i_tempx = -( i_center_y - ps_piece->ps_piece_in_plane[0].i_actual_y ) + i_center_x;
            i_tempy = +( i_center_x - ps_piece->ps_piece_in_plane[0].i_actual_x ) + i_center_y;
        }
        else {
            ps_piece->i_actual_angle--;
            ps_piece->i_actual_angle &= 0x03;

            i_tempx = +( i_center_y - ps_piece->ps_piece_in_plane[0].i_actual_y ) + i_center_x;
            i_tempy = -( i_center_x - ps_piece->ps_piece_in_plane[0].i_actual_x ) + i_center_y;
        }

        ps_piece->ps_piece_in_plane[0].i_actual_x = i_tempx;
        ps_piece->ps_piece_in_plane[0].i_actual_y = i_tempy;

        if ( ps_piece->i_actual_angle == 0 && p_sys->s_current_param.i_rotate == 3 && !b_avoid_mirror ) {
            ps_piece->ps_piece_in_plane[0].i_actual_x = 2 * i_center_x - ps_piece->ps_piece_in_plane[0].i_actual_x;
            ps_piece->i_actual_mirror *= -1;
        }
        puzzle_calculate_corners( p_filter, i_piece );
    }
}