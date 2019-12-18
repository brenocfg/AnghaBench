#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int left_offset; unsigned int right_offset; unsigned int bottom_offset; unsigned int top_offset; } ;
struct TYPE_5__ {int frame_mbs_only_flag; int b_separate_colour_planes_flag; int i_chroma_idc; int pic_width_in_mbs_minus1; int pic_height_in_map_units_minus1; TYPE_1__ frame_crop; } ;
typedef  TYPE_2__ h264_sequence_parameter_set_t ;

/* Variables and functions */

bool h264_get_picture_size( const h264_sequence_parameter_set_t *p_sps, unsigned *p_w, unsigned *p_h,
                            unsigned *p_vw, unsigned *p_vh )
{
    unsigned CropUnitX = 1;
    unsigned CropUnitY = 2 - p_sps->frame_mbs_only_flag;
    if( p_sps->b_separate_colour_planes_flag != 1 )
    {
        if( p_sps->i_chroma_idc > 0 )
        {
            unsigned SubWidthC = 2;
            unsigned SubHeightC = 2;
            if( p_sps->i_chroma_idc > 1 )
            {
                SubHeightC = 1;
                if( p_sps->i_chroma_idc > 2 )
                    SubWidthC = 1;
            }
            CropUnitX *= SubWidthC;
            CropUnitY *= SubHeightC;
        }
    }

    *p_w = 16 * p_sps->pic_width_in_mbs_minus1 + 16;
    *p_h = 16 * p_sps->pic_height_in_map_units_minus1 + 16;
    *p_h *= ( 2 - p_sps->frame_mbs_only_flag );

    *p_vw = *p_w - ( p_sps->frame_crop.left_offset + p_sps->frame_crop.right_offset ) * CropUnitX;
    *p_vh = *p_h - ( p_sps->frame_crop.bottom_offset + p_sps->frame_crop.top_offset ) * CropUnitY;

    return true;
}