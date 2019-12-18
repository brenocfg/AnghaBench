#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  point_t ;
struct TYPE_10__ {int i_row_nbr; int i_first_row_offset; int /*<<< orphan*/  ps_piece_shape_row; } ;
typedef  TYPE_2__ piece_shape_t ;
typedef  int /*<<< orphan*/  piece_shape_row_t ;
typedef  int int32_t ;
struct TYPE_11__ {TYPE_4__* p_sys; } ;
typedef  TYPE_3__ filter_t ;
struct TYPE_12__ {TYPE_1__* ps_desk_planes; } ;
typedef  TYPE_4__ filter_sys_t ;
struct TYPE_9__ {int i_pce_max_width; int i_pce_max_lines; } ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 float __MIN (int /*<<< orphan*/ ,int) ; 
 int floor (float) ; 
 int /*<<< orphan*/  malloc (int) ; 
 size_t puzzle_SHAPE_TOP ; 
 int puzzle_generate_shape_lines (TYPE_3__*,TYPE_2__*,int,int,float,float,int /*<<< orphan*/ *,size_t,size_t,size_t) ; 
 int /*<<< orphan*/  puzzle_get_min_bezier (float*,float*,float,float,int /*<<< orphan*/ *,size_t) ; 

int puzzle_generate_sect_bezier( filter_t *p_filter, piece_shape_t *ps_piece_shape, uint8_t i_pts_nbr, point_t *ps_pt, uint8_t i_plane, uint8_t i_border)
{
    /* generate data required to draw a sector of puzzle piece using bezier shape */
    if ((!ps_pt) || (!ps_piece_shape))
        return VLC_EGENERIC;

    filter_sys_t *p_sys = p_filter->p_sys;

    int32_t i_width = p_sys->ps_desk_planes[i_plane].i_pce_max_width;
    int32_t i_lines = p_sys->ps_desk_planes[i_plane].i_pce_max_lines;
    int32_t i_size_x_0 = p_sys->ps_desk_planes[0].i_pce_max_width;
    int32_t i_size_y_0 = p_sys->ps_desk_planes[0].i_pce_max_lines;

    float f_x_ratio =  ((float) i_width) / ((float) i_size_x_0);
    float f_y_ratio = ((float) i_lines) / ((float) i_size_y_0);

    /* first: get min x and min y */
    float f_min_curve_x, f_min_curve_y;
    puzzle_get_min_bezier(&f_min_curve_x, &f_min_curve_y, f_x_ratio, f_y_ratio, ps_pt, i_pts_nbr);

    f_min_curve_y = __MIN(0,floor(f_min_curve_y));
    f_min_curve_x = __MIN(0,floor(f_min_curve_x));

    /* next: process each horizontal pixel lines */
    int32_t i_min_y = (i_border==puzzle_SHAPE_TOP)?floor(f_min_curve_y):0;
    int32_t i_nb_y = (i_border==puzzle_SHAPE_TOP)?(i_lines / 2 - i_min_y):i_lines;

    /* allocate memory */
    ps_piece_shape->i_row_nbr = i_nb_y;
    ps_piece_shape->i_first_row_offset = i_min_y;
    ps_piece_shape->ps_piece_shape_row = malloc( sizeof( piece_shape_row_t ) * ps_piece_shape->i_row_nbr );
    if (!ps_piece_shape->ps_piece_shape_row)
        return VLC_ENOMEM;

    return puzzle_generate_shape_lines(p_filter, ps_piece_shape, i_min_y, i_nb_y, f_x_ratio, f_y_ratio, ps_pt, i_pts_nbr, i_border, i_plane);
}