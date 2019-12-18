#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {unsigned int vps_num_units_in_tick; unsigned int vps_time_scale; scalar_t__ vps_timing_info_present_flag; } ;
typedef  TYPE_3__ hevc_video_parameter_set_t ;
struct TYPE_7__ {unsigned int vui_num_units_in_tick; unsigned int vui_time_scale; } ;
struct TYPE_8__ {TYPE_1__ timing; scalar_t__ vui_timing_info_present_flag; } ;
struct TYPE_10__ {TYPE_2__ vui; scalar_t__ vui_parameters_present_flag; } ;
typedef  TYPE_4__ hevc_sequence_parameter_set_t ;

/* Variables and functions */

bool hevc_get_frame_rate( const hevc_sequence_parameter_set_t *p_sps,
                          const hevc_video_parameter_set_t *p_vps,
                          unsigned *pi_num, unsigned *pi_den )
{
    if( p_sps->vui_parameters_present_flag && p_sps->vui.vui_timing_info_present_flag )
    {
        *pi_den = p_sps->vui.timing.vui_num_units_in_tick;
        *pi_num = p_sps->vui.timing.vui_time_scale;
        return (*pi_den && *pi_num);
    }
    else if( p_vps && p_vps->vps_timing_info_present_flag )
    {
        *pi_den = p_vps->vps_num_units_in_tick;
        *pi_num = p_vps->vps_time_scale;
        return (*pi_den && *pi_num);
    }
    return false;
}