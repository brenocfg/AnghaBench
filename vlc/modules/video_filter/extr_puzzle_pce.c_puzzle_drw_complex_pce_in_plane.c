#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_17__ {size_t i_top_shape; size_t i_btm_shape; size_t i_right_shape; size_t i_left_shape; scalar_t__ i_step_x_x; scalar_t__ i_step_y_x; scalar_t__ i_step_x_y; scalar_t__ i_step_y_y; TYPE_2__* ps_piece_in_plane; } ;
typedef  TYPE_4__ piece_t ;
struct TYPE_18__ {scalar_t__ i_first_row_offset; scalar_t__ i_row_nbr; TYPE_6__* ps_piece_shape_row; } ;
typedef  TYPE_5__ piece_shape_t ;
struct TYPE_19__ {scalar_t__ i_section_nbr; TYPE_3__* ps_row_section; } ;
typedef  TYPE_6__ piece_shape_row_t ;
struct TYPE_20__ {TYPE_1__* p; } ;
typedef  TYPE_7__ picture_t ;
typedef  int int8_t ;
typedef  scalar_t__ int32_t ;
struct TYPE_21__ {TYPE_9__* p_sys; } ;
typedef  TYPE_8__ filter_t ;
struct TYPE_22__ {scalar_t__ i_mouse_x; scalar_t__ i_mouse_y; int /*<<< orphan*/  i_pointed_pce; TYPE_5__** ps_pieces_shapes; int /*<<< orphan*/ * ps_pieces; int /*<<< orphan*/ * ps_puzzle_array; } ;
typedef  TYPE_9__ filter_sys_t ;
struct TYPE_16__ {size_t i_type; scalar_t__ i_width; } ;
struct TYPE_15__ {scalar_t__ i_actual_x; scalar_t__ i_actual_y; scalar_t__ i_original_x; scalar_t__ i_original_y; } ;
struct TYPE_14__ {scalar_t__ i_pitch; scalar_t__ i_pixel_pitch; scalar_t__ i_visible_lines; size_t* p_pixels; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (size_t*,size_t*,scalar_t__ const) ; 

void puzzle_drw_complex_pce_in_plane( filter_t *p_filter, picture_t *p_pic_in, picture_t *p_pic_out, uint8_t i_plane, piece_t *ps_piece, uint32_t i_pce)
{
    /* "puzzle" shape and maybe angle != 0 */
    filter_sys_t *p_sys = p_filter->p_sys;

    if ((p_sys->ps_puzzle_array == NULL) || (p_sys->ps_pieces == NULL) || (ps_piece == NULL))
        return;

    const int32_t i_src_pitch    = p_pic_in->p[i_plane].i_pitch;
    const int32_t i_dst_pitch    = p_pic_out->p[i_plane].i_pitch;
    const int32_t i_src_width    = p_pic_in->p[i_plane].i_pitch / p_pic_in->p[i_plane].i_pixel_pitch;
    const int32_t i_dst_width    = p_pic_out->p[i_plane].i_pitch / p_pic_out->p[i_plane].i_pixel_pitch;
    const int32_t i_pixel_pitch  = p_pic_out->p[i_plane].i_pixel_pitch;
    const int32_t i_src_visible_lines    = p_pic_in->p[i_plane].i_visible_lines;
    const int32_t i_dst_visible_lines    = p_pic_out->p[i_plane].i_visible_lines;
    uint8_t *p_src = p_pic_in->p[i_plane].p_pixels;
    uint8_t *p_dst = p_pic_out->p[i_plane].p_pixels;

    const int32_t i_desk_start_x = ps_piece->ps_piece_in_plane[i_plane].i_actual_x;
    const int32_t i_desk_start_y = ps_piece->ps_piece_in_plane[i_plane].i_actual_y;
    const int32_t i_pic_start_x = ps_piece->ps_piece_in_plane[i_plane].i_original_x;
    const int32_t i_pic_start_y = ps_piece->ps_piece_in_plane[i_plane].i_original_y;

    piece_shape_t *ps_top_shape =   &p_sys->ps_pieces_shapes[ps_piece->i_top_shape][i_plane];
    piece_shape_t *ps_btm_shape =   &p_sys->ps_pieces_shapes[ps_piece->i_btm_shape][i_plane];
    piece_shape_t *ps_right_shape = &p_sys->ps_pieces_shapes[ps_piece->i_right_shape][i_plane];
    piece_shape_t *ps_left_shape =  &p_sys->ps_pieces_shapes[ps_piece->i_left_shape][i_plane];
    piece_shape_t *ps_shape;

    int32_t i_min_y = ps_top_shape->i_first_row_offset;
    int32_t i_max_y = ps_btm_shape->i_first_row_offset + ps_btm_shape->i_row_nbr - 1;

    for (int32_t i_y = i_min_y; i_y <= i_max_y; i_y++) {
        int32_t i_current_src_y = i_pic_start_y + i_y;

        if ( ( i_current_src_y >= 0 ) && ( i_current_src_y < i_src_visible_lines ) ) {
            int32_t i_sect_start_x = 0;

            /* process each sub shape (each quarter) */
            for (int8_t i_shape=0; i_shape < 4; i_shape++) {
                switch ( i_shape )
                {
                  case 0:
                    ps_shape = ps_left_shape;
                    break;
                  case 1:
                    ps_shape = ps_top_shape;
                    break;
                  case 2:
                    ps_shape = ps_btm_shape;
                    break;
                  case 3:
                    ps_shape = ps_right_shape;
                    break;
                }

                int32_t i_r = i_y - ps_shape->i_first_row_offset;

                if (i_r <0 || i_r >= ps_shape->i_row_nbr)
                    continue;

                piece_shape_row_t *ps_piece_shape_row = &ps_shape->ps_piece_shape_row[i_r];

                for (int32_t i_s = 0; i_s < ps_piece_shape_row->i_section_nbr; i_s++) {
                    uint8_t i_type = ps_piece_shape_row->ps_row_section[i_s].i_type;
                    int32_t i_width = ps_piece_shape_row->ps_row_section[i_s].i_width;
                    if (i_type == 0) {
                        /* copy pixel line from input image to puzzle desk */
                        for (int32_t i_x = 0; i_x < i_width; i_x++) {
                            int32_t i_current_dst_x = i_desk_start_x + (i_sect_start_x + i_x) * ps_piece->i_step_x_x + i_y * ps_piece->i_step_y_x;
                            int32_t i_current_dst_y = i_desk_start_y + (i_sect_start_x + i_x) * ps_piece->i_step_x_y + i_y * ps_piece->i_step_y_y;
                            int32_t i_current_src_x = i_pic_start_x + (i_sect_start_x + i_x);

                            if (    i_current_dst_x < 0 || i_current_dst_x >= i_dst_width
                                 || i_current_src_x < 0 || i_current_src_x >= i_src_width
                                 || i_current_dst_y < 0 || i_current_dst_y >= i_dst_visible_lines )
                                continue;

                            memcpy( p_dst + i_current_dst_y * i_dst_pitch + i_current_dst_x * i_pixel_pitch,
                                    p_src + i_current_src_y * i_src_pitch + i_current_src_x * i_pixel_pitch,
                                    i_pixel_pitch );

                            /* Check if mouse pointer is over this pixel
                             * Yes: set i_pointed_pce = current drawn piece
                             */
                            if ((i_plane == 0)  && (p_sys->i_mouse_x == i_current_dst_x )
                                                && (p_sys->i_mouse_y == i_current_dst_y ))
                                p_sys->i_pointed_pce = i_pce;
                        }
                    }
                    i_sect_start_x += i_width;
                }
            }
        }
    }

    return;
}