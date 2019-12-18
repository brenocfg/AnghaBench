#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct TYPE_13__ {size_t i_planes; TYPE_1__* p; } ;
typedef  TYPE_4__ picture_t ;
typedef  int int32_t ;
struct TYPE_14__ {TYPE_6__* p_sys; } ;
typedef  TYPE_5__ filter_t ;
struct TYPE_12__ {int i_preview_size; } ;
struct TYPE_15__ {int i_preview_pos; TYPE_3__ s_current_param; TYPE_2__* ps_desk_planes; } ;
typedef  TYPE_6__ filter_sys_t ;
struct TYPE_11__ {int i_width; int /*<<< orphan*/  i_lines; } ;
struct TYPE_10__ {int i_visible_lines; int i_pixel_pitch; int i_pitch; size_t* p_pixels; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (size_t*,size_t*,int) ; 

void puzzle_draw_preview( filter_t *p_filter, picture_t *p_pic_in, picture_t *p_pic_out)
{
    filter_sys_t *p_sys = p_filter->p_sys;

    for( uint8_t  i_plane = 0; i_plane < p_pic_out->i_planes; i_plane++ ) {
        int32_t i_preview_offset = 0;
        int32_t i_preview_width  = p_sys->ps_desk_planes[i_plane].i_width * p_sys->s_current_param.i_preview_size / 100;
        int32_t i_preview_lines  = p_pic_out->p[i_plane].i_visible_lines * p_sys->s_current_param.i_preview_size / 100;
        int32_t i_pixel_pitch    = p_pic_out->p[i_plane].i_pixel_pitch;

        const int32_t i_src_pitch  = p_pic_in->p[i_plane].i_pitch;
        const int32_t i_dst_pitch  = p_pic_out->p[i_plane].i_pitch;

        uint8_t *p_src = p_pic_in->p[i_plane].p_pixels;
        uint8_t *p_dst = p_pic_out->p[i_plane].p_pixels;

        switch ( p_sys->i_preview_pos ) {
        case 0:
            i_preview_offset = 0;
            break;
        case 1:
            i_preview_offset =
                (p_sys->ps_desk_planes[i_plane].i_width - 1 - i_preview_width) * i_pixel_pitch;
            break;
        case 2:
            i_preview_offset =
                (p_sys->ps_desk_planes[i_plane].i_width - 1 - i_preview_width) * i_pixel_pitch
                + ((int32_t) ( p_sys->ps_desk_planes[i_plane].i_lines - 1 - i_preview_lines )) * i_dst_pitch;
            break;
        case 3:
            i_preview_offset = ((int32_t) ( p_sys->ps_desk_planes[i_plane].i_lines - 1 - i_preview_lines )) * i_dst_pitch;
            break;
        default:
            i_preview_offset = 0;
            break;
        }

        for ( int32_t y = 0; y < i_preview_lines; y++ )
            for ( int32_t x = 0; x < i_preview_width; x++ )
                memcpy( &p_dst[ y * i_dst_pitch + x * i_pixel_pitch + i_preview_offset ],
                        &p_src[ ( y * 100 / p_sys->s_current_param.i_preview_size ) * i_src_pitch
                                + ( x * 100 / p_sys->s_current_param.i_preview_size ) * i_pixel_pitch ],
                        i_pixel_pitch );
    }
}