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
typedef  size_t uint8_t ;
struct TYPE_12__ {int i_actual_angle; size_t i_step_x_x; size_t i_actual_mirror; size_t i_step_x_y; int i_step_y_y; int i_step_y_x; size_t i_TLx; size_t i_TLy; size_t i_TRx; size_t i_TRy; size_t i_BRx; size_t i_BRy; size_t i_BLx; size_t i_BLy; int i_max_x; int i_min_x; int i_max_y; int i_min_y; int i_center_x; int i_center_y; size_t i_group_ID; int b_overlap; TYPE_3__* ps_piece_in_plane; } ;
typedef  TYPE_4__ piece_t ;
typedef  size_t int32_t ;
struct TYPE_13__ {TYPE_6__* p_sys; } ;
typedef  TYPE_5__ filter_t ;
struct TYPE_9__ {size_t i_planes; } ;
struct TYPE_14__ {int* pi_group_qty; TYPE_2__* ps_desk_planes; TYPE_1__ s_allocated; TYPE_4__* ps_pieces; } ;
typedef  TYPE_6__ filter_sys_t ;
struct TYPE_11__ {int i_actual_x; int i_actual_y; size_t i_width; size_t i_lines; } ;
struct TYPE_10__ {int i_width; int i_lines; } ;

/* Variables and functions */
 size_t NO_PCE ; 
 void* __MAX (void*,void*) ; 
 void* __MIN (void*,void*) ; 
 size_t puzzle_find_piece (TYPE_5__*,int,int,size_t) ; 

void puzzle_calculate_corners( filter_t *p_filter,  int32_t i_piece )
{
    filter_sys_t *p_sys = p_filter->p_sys;
    piece_t *ps_piece = &p_sys->ps_pieces[i_piece];

    switch ( ps_piece->i_actual_angle)
    {
      case 0:
        ps_piece->i_step_x_x = ps_piece->i_actual_mirror;
        ps_piece->i_step_x_y = 0;
        ps_piece->i_step_y_y = 1;
        ps_piece->i_step_y_x = 0;
        break;
      case 1:
        ps_piece->i_step_x_x = 0;
        ps_piece->i_step_x_y = -ps_piece->i_actual_mirror; /* x offset on original pict creates negative y offset on desk */
        ps_piece->i_step_y_y = 0;
        ps_piece->i_step_y_x = 1;
        break;
      case 2:
        ps_piece->i_step_x_x = -ps_piece->i_actual_mirror;
        ps_piece->i_step_x_y = 0;
        ps_piece->i_step_y_y = -1;
        ps_piece->i_step_y_x = 0;
        break;
      case 3:
        ps_piece->i_step_x_x = 0;
        ps_piece->i_step_x_y = ps_piece->i_actual_mirror;
        ps_piece->i_step_y_y = 0;
        ps_piece->i_step_y_x = -1;
        break;
    }

    /* regen geometry */
    for (uint8_t i_plane = 1; i_plane < p_sys->s_allocated.i_planes; i_plane++) {
        ps_piece->ps_piece_in_plane[i_plane].i_actual_x =
            ps_piece->ps_piece_in_plane[0].i_actual_x * p_sys->ps_desk_planes[i_plane].i_width / p_sys->ps_desk_planes[0].i_width;
        ps_piece->ps_piece_in_plane[i_plane].i_actual_y =
            ps_piece->ps_piece_in_plane[0].i_actual_y * p_sys->ps_desk_planes[i_plane].i_lines / p_sys->ps_desk_planes[0].i_lines;
    }

    /* regen location of grabed piece's corners */
    int32_t i_width = ps_piece->ps_piece_in_plane[0].i_width;
    int32_t i_lines = ps_piece->ps_piece_in_plane[0].i_lines;

    ps_piece->i_TLx = ps_piece->ps_piece_in_plane[0].i_actual_x;
    ps_piece->i_TLy = ps_piece->ps_piece_in_plane[0].i_actual_y;
    ps_piece->i_TRx = ps_piece->i_TLx + ( i_width - 1 ) * ps_piece->i_step_x_x;
    ps_piece->i_TRy = ps_piece->i_TLy + ( i_width - 1 ) * ps_piece->i_step_x_y;
    ps_piece->i_BRx = ps_piece->i_TLx + ( i_width - 1 ) * ps_piece->i_step_x_x + ( i_lines - 1 ) * ps_piece->i_step_y_x;
    ps_piece->i_BRy = ps_piece->i_TLy + ( i_width - 1 ) * ps_piece->i_step_x_y + ( i_lines - 1 ) * ps_piece->i_step_y_y;
    ps_piece->i_BLx = ps_piece->i_TLx + ( i_lines - 1 ) * ps_piece->i_step_y_x;
    ps_piece->i_BLy = ps_piece->i_TLy + ( i_lines - 1 ) * ps_piece->i_step_y_y;

    ps_piece->i_max_x = __MAX( __MAX( ps_piece->i_TLx, ps_piece->i_TRx ), __MAX( ps_piece->i_BLx, ps_piece->i_BRx ) );
    ps_piece->i_min_x = __MIN( __MIN( ps_piece->i_TLx, ps_piece->i_TRx ), __MIN( ps_piece->i_BLx, ps_piece->i_BRx ) );
    ps_piece->i_max_y = __MAX( __MAX( ps_piece->i_TLy, ps_piece->i_TRy ), __MAX( ps_piece->i_BLy, ps_piece->i_BRy ) );
    ps_piece->i_min_y = __MIN( __MIN( ps_piece->i_TLy, ps_piece->i_TRy ), __MIN( ps_piece->i_BLy, ps_piece->i_BRy ) );

    ps_piece->i_center_x = ( ps_piece->i_max_x + ps_piece->i_min_x ) / 2;
    ps_piece->i_center_y = ( ps_piece->i_max_y + ps_piece->i_min_y ) / 2;

    int32_t pce_overlap = puzzle_find_piece( p_filter, ps_piece->i_center_x, ps_piece->i_center_y, i_piece);

    if ( ( pce_overlap != NO_PCE ) && ( p_sys->pi_group_qty[ps_piece->i_group_ID] == 1 ) )
        ps_piece->b_overlap = true;
}