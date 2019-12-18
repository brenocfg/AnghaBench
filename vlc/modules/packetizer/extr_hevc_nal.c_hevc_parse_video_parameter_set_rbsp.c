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
struct TYPE_5__ {unsigned int vps_max_sub_layers_minus1; int vps_max_layer_id; int vps_num_layer_set_minus1; void* vps_time_scale; void* vps_num_units_in_tick; void* vps_timing_info_present_flag; TYPE_1__* vps_max; void* vps_sub_layer_ordering_info_present_flag; int /*<<< orphan*/  profile_tier_level; void* vps_temporal_id_nesting_flag; void* vps_max_layers_minus1; void* vps_base_layer_available_flag; void* vps_base_layer_internal_flag; void* vps_video_parameter_set_id; } ;
typedef  TYPE_2__ hevc_video_parameter_set_t ;
typedef  int /*<<< orphan*/  bs_t ;
struct TYPE_4__ {void* max_latency_increase_plus1; void* num_reorder_pics; void* dec_pic_buffering_minus1; } ;

/* Variables and functions */
 void* bs_read (int /*<<< orphan*/ *,int) ; 
 void* bs_read1 (int /*<<< orphan*/ *) ; 
 void* bs_read_ue (int /*<<< orphan*/ *) ; 
 int bs_remain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bs_skip (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hevc_parse_profile_tier_level_rbsp (int /*<<< orphan*/ *,int,unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool hevc_parse_video_parameter_set_rbsp( bs_t *p_bs,
                                                 hevc_video_parameter_set_t *p_vps )
{
    if( bs_remain( p_bs ) < 134 )
        return false;

    p_vps->vps_video_parameter_set_id = bs_read( p_bs, 4 );
    p_vps->vps_base_layer_internal_flag = bs_read1( p_bs );
    p_vps->vps_base_layer_available_flag = bs_read1( p_bs );
    p_vps->vps_max_layers_minus1 = bs_read( p_bs, 6 );
    p_vps->vps_max_sub_layers_minus1 = bs_read( p_bs, 3 );
    p_vps->vps_temporal_id_nesting_flag = bs_read1( p_bs );
    bs_skip( p_bs, 16 );

    if( !hevc_parse_profile_tier_level_rbsp( p_bs, true, p_vps->vps_max_sub_layers_minus1,
                                            &p_vps->profile_tier_level ) )
        return false;

    p_vps->vps_sub_layer_ordering_info_present_flag = bs_read1( p_bs );
    for( unsigned i= (p_vps->vps_sub_layer_ordering_info_present_flag ?
                      0 : p_vps->vps_max_sub_layers_minus1);
         i<= p_vps->vps_max_sub_layers_minus1; i++ )
    {
        p_vps->vps_max[i].dec_pic_buffering_minus1 = bs_read_ue( p_bs );
        p_vps->vps_max[i].num_reorder_pics = bs_read_ue( p_bs );
        p_vps->vps_max[i].max_latency_increase_plus1 = bs_read_ue( p_bs );
    }
    if( bs_remain( p_bs ) < 10 )
        return false;

    p_vps->vps_max_layer_id = bs_read( p_bs, 6 );
    p_vps->vps_num_layer_set_minus1 = bs_read_ue( p_bs );
    // layer_id_included_flag; read but discarded
    bs_skip( p_bs, p_vps->vps_num_layer_set_minus1 * (p_vps->vps_max_layer_id + 1) );
    if( bs_remain( p_bs ) < 2 )
        return false;

    p_vps->vps_timing_info_present_flag = bs_read1( p_bs );
    if( p_vps->vps_timing_info_present_flag )
    {
        p_vps->vps_num_units_in_tick = bs_read( p_bs, 32 );
        p_vps->vps_time_scale = bs_read( p_bs, 32 );
    }
    /* parsing incomplete */

    if( bs_remain( p_bs ) < 1 )
        return false;

    return true;
}