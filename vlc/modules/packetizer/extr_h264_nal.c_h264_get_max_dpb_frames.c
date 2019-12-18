#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_6__ {int pic_height_in_map_units_minus1; int frame_mbs_only_flag; int pic_width_in_mbs_minus1; } ;
typedef  TYPE_1__ h264_sequence_parameter_set_t ;
struct TYPE_7__ {unsigned int i_max_dpb_mbs; } ;
typedef  TYPE_2__ h264_level_limits_t ;

/* Variables and functions */
 TYPE_2__* h264_get_level_limits (TYPE_1__ const*) ; 

__attribute__((used)) static uint8_t h264_get_max_dpb_frames( const h264_sequence_parameter_set_t *p_sps )
{
    const h264_level_limits_t *limits = h264_get_level_limits( p_sps );
    if( limits )
    {
        unsigned i_frame_height_in_mbs = ( p_sps->pic_height_in_map_units_minus1 + 1 ) *
                                         ( 2 - p_sps->frame_mbs_only_flag );
        unsigned i_den = ( p_sps->pic_width_in_mbs_minus1 + 1 ) * i_frame_height_in_mbs;
        uint8_t i_max_dpb_frames = limits->i_max_dpb_mbs / i_den;
        if( i_max_dpb_frames < 16 )
            return i_max_dpb_frames;
    }
    return 16;
}