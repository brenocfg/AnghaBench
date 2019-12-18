#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_9__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  row_section_t ;
struct TYPE_11__ {int i_first_row_offset; int i_row_nbr; TYPE_9__* ps_piece_shape_row; } ;
typedef  TYPE_2__ piece_shape_t ;
typedef  int /*<<< orphan*/  piece_shape_row_t ;
typedef  int int8_t ;
typedef  int int32_t ;
struct TYPE_12__ {TYPE_4__* p_sys; } ;
typedef  TYPE_3__ filter_t ;
struct TYPE_13__ {TYPE_1__* ps_desk_planes; } ;
typedef  TYPE_4__ filter_sys_t ;
struct TYPE_14__ {int i_section_nbr; int i_width; struct TYPE_14__* ps_row_section; scalar_t__ i_type; } ;
struct TYPE_10__ {int i_pce_max_lines; } ;

/* Variables and functions */
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  free (TYPE_9__*) ; 
 void* malloc (int) ; 
 int puzzle_diagonal_limit (TYPE_3__*,int,int,size_t) ; 

int puzzle_generate_sectTop2Btm( filter_t *p_filter, piece_shape_t *ps_piece_shape, piece_shape_t *ps_top_piece_shape, uint8_t i_plane)
{
    if ((!ps_piece_shape) || (!ps_top_piece_shape))
        return VLC_EGENERIC;

    filter_sys_t *p_sys = p_filter->p_sys;

    int32_t i_top_min_y = ps_top_piece_shape->i_first_row_offset;
    int32_t i_top_nb_y = ps_top_piece_shape->i_row_nbr;
    int32_t i_lines = p_sys->ps_desk_planes[i_plane].i_pce_max_lines;
    int32_t i_max_y = p_sys->ps_desk_planes[i_plane].i_pce_max_lines - i_top_min_y;

    int32_t i_min_y = i_lines / 2;
    int32_t i_nb_y = i_max_y - i_min_y;

    /* allocate memory */
    ps_piece_shape->i_row_nbr = i_nb_y;
    ps_piece_shape->i_first_row_offset = i_min_y;
    ps_piece_shape->ps_piece_shape_row = malloc( sizeof( piece_shape_row_t ) * i_nb_y );
    if (!ps_piece_shape->ps_piece_shape_row)
        return VLC_ENOMEM;

    for (int32_t i_y = i_min_y; i_y < i_nb_y + i_min_y; i_y++) {
        int32_t i_top_y = 2 * i_min_y - i_y + (i_nb_y - i_top_nb_y);
        int32_t i_row = i_y - i_min_y;
        int32_t i_top_row = i_top_y - i_top_min_y;

        if ( i_top_row < 0 || i_top_row >= i_top_nb_y ) { /* the line does not exist in top */
            ps_piece_shape->ps_piece_shape_row[i_row].i_section_nbr = 1;
            ps_piece_shape->ps_piece_shape_row[i_row].ps_row_section = malloc (  sizeof(row_section_t) * 1);
            if (!ps_piece_shape->ps_piece_shape_row[i_row].ps_row_section) {
                for (uint8_t i=0; i<i_row;i++)
                    free(ps_piece_shape->ps_piece_shape_row[i].ps_row_section);
                free(ps_piece_shape->ps_piece_shape_row);
                ps_piece_shape->ps_piece_shape_row = NULL;
                return VLC_ENOMEM;
            }
            ps_piece_shape->ps_piece_shape_row[i_row].ps_row_section[0].i_type = 0;
            ps_piece_shape->ps_piece_shape_row[i_row].ps_row_section[0].i_width =
                puzzle_diagonal_limit( p_filter, i_y, false, i_plane ) - 1 - (puzzle_diagonal_limit( p_filter, i_y, true, i_plane ) - 1);
        }
        else { /* copy the line from TopShape */
            int32_t i_top_width =
                puzzle_diagonal_limit( p_filter, i_top_y, false, i_plane ) - 1 - (puzzle_diagonal_limit( p_filter, i_top_y, true, i_plane ) - 1);
            int32_t i_width =
                puzzle_diagonal_limit( p_filter, i_y, false, i_plane ) - 1 - (puzzle_diagonal_limit( p_filter, i_y, true, i_plane ) - 1);
            int32_t i_left_adjust = ( i_width - i_top_width ) / 2;
            int32_t i_right_adjust = ( i_width - i_top_width ) - i_left_adjust;

            int8_t i_section_nbr = ps_top_piece_shape->ps_piece_shape_row[i_top_row].i_section_nbr;
            ps_piece_shape->ps_piece_shape_row[i_row].i_section_nbr = i_section_nbr;
            ps_piece_shape->ps_piece_shape_row[i_row].ps_row_section = malloc (  sizeof(row_section_t) * i_section_nbr);
            if (!ps_piece_shape->ps_piece_shape_row[i_row].ps_row_section) {
                for (uint8_t i=0; i<i_row;i++)
                    free(ps_piece_shape->ps_piece_shape_row[i].ps_row_section);
                free(ps_piece_shape->ps_piece_shape_row);
                ps_piece_shape->ps_piece_shape_row = NULL;
                return VLC_ENOMEM;
            }

            for (int8_t i_s=0; i_s<i_section_nbr; i_s++) {
                ps_piece_shape->ps_piece_shape_row[i_row].ps_row_section[i_s].i_type =
                        ps_top_piece_shape->ps_piece_shape_row[i_top_row].ps_row_section[i_s].i_type;
                ps_piece_shape->ps_piece_shape_row[i_row].ps_row_section[i_s].i_width =
                        ps_top_piece_shape->ps_piece_shape_row[i_top_row].ps_row_section[i_s].i_width
                        + (i_s == 0 ? i_left_adjust : (i_s == i_section_nbr-1 ? i_right_adjust : 0));
            }
        }
    }
    return VLC_SUCCESS;
}