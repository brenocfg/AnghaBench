#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ pps_pic_parameter_set_id; scalar_t__ pps_seq_parameter_set_id; int num_tile_columns_minus1; int num_tile_rows_minus1; void* pps_extension_5bits; void* pps_3d_extension_flag; void* pps_multilayer_extension_flag; void* pps_range_extension_flag; void* pps_extension_present_flag; void* slice_header_extension_present_flag; void* log2_parallel_merge_level_minus2; void* lists_modification_present_flag; void* scaling_list_data_present_flag; void* pps_tc_offset_div2; void* pps_beta_offset_div2; void* pps_deblocking_filter_disabled_flag; void* deblocking_filter_override_enabled_flag; void* deblocking_filter_control_present_flag; void* pps_loop_filter_across_slices_enabled_flag; void* loop_filter_across_tiles_enabled_flag; void* uniform_spacing_flag; void* tiles_enabled_flag; void* entropy_coding_sync_enabled_flag; void* transquant_bypass_enable_flag; void* weighted_bipred_flag; void* weighted_pred_flag; void* pic_slice_level_chroma_qp_offsets_present_flag; void* pps_cr_qp_offset; void* pps_cb_qp_offset; void* diff_cu_qp_delta_depth; void* cu_qp_delta_enabled_flag; void* transform_skip_enabled_flag; void* constrained_intra_pred_flag; void* init_qp_minus26; void* num_ref_idx_l1_default_active_minus1; void* num_ref_idx_l0_default_active_minus1; void* cabac_init_present_flag; void* sign_data_hiding_enabled_flag; void* num_extra_slice_header_bits; void* output_flag_present_flag; void* dependent_slice_segments_enabled_flag; } ;
typedef  TYPE_1__ hevc_picture_parameter_set_t ;
typedef  int /*<<< orphan*/  bs_t ;

/* Variables and functions */
 scalar_t__ HEVC_PPS_ID_MAX ; 
 scalar_t__ HEVC_SPS_ID_MAX ; 
 void* bs_read (int /*<<< orphan*/ *,int) ; 
 void* bs_read1 (int /*<<< orphan*/ *) ; 
 void* bs_read_se (int /*<<< orphan*/ *) ; 
 void* bs_read_ue (int /*<<< orphan*/ *) ; 
 int bs_remain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hevc_parse_scaling_list_rbsp (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool hevc_parse_pic_parameter_set_rbsp( bs_t *p_bs,
                                               hevc_picture_parameter_set_t *p_pps )
{
    if( bs_remain( p_bs ) < 1 )
        return false;
    p_pps->pps_pic_parameter_set_id = bs_read_ue( p_bs );
    if( p_pps->pps_pic_parameter_set_id > HEVC_PPS_ID_MAX || bs_remain( p_bs ) < 1 )
        return false;
    p_pps->pps_seq_parameter_set_id = bs_read_ue( p_bs );
    if( p_pps->pps_seq_parameter_set_id > HEVC_SPS_ID_MAX )
        return false;
    p_pps->dependent_slice_segments_enabled_flag = bs_read1( p_bs );
    p_pps->output_flag_present_flag = bs_read1( p_bs );
    p_pps->num_extra_slice_header_bits = bs_read( p_bs, 3 );
    p_pps->sign_data_hiding_enabled_flag = bs_read1( p_bs );
    p_pps->cabac_init_present_flag = bs_read1( p_bs );

    p_pps->num_ref_idx_l0_default_active_minus1 = bs_read_ue( p_bs );
    p_pps->num_ref_idx_l1_default_active_minus1 = bs_read_ue( p_bs );

    p_pps->init_qp_minus26 = bs_read_se( p_bs );
    p_pps->constrained_intra_pred_flag = bs_read1( p_bs );
    p_pps->transform_skip_enabled_flag = bs_read1( p_bs );
    p_pps->cu_qp_delta_enabled_flag = bs_read1( p_bs );
    if( p_pps->cu_qp_delta_enabled_flag )
        p_pps->diff_cu_qp_delta_depth = bs_read_ue( p_bs );

    if( bs_remain( p_bs ) < 1 )
        return false;

    p_pps->pps_cb_qp_offset = bs_read_se( p_bs );
    p_pps->pps_cr_qp_offset = bs_read_se( p_bs );
    p_pps->pic_slice_level_chroma_qp_offsets_present_flag = bs_read1( p_bs );
    p_pps->weighted_pred_flag = bs_read1( p_bs );
    p_pps->weighted_bipred_flag = bs_read1( p_bs );
    p_pps->transquant_bypass_enable_flag = bs_read1( p_bs );
    p_pps->tiles_enabled_flag = bs_read1( p_bs );
    p_pps->entropy_coding_sync_enabled_flag = bs_read1( p_bs );

    if( p_pps->tiles_enabled_flag )
    {
        p_pps->num_tile_columns_minus1 = bs_read_ue( p_bs ); /* TODO: validate max col/row values */
        p_pps->num_tile_rows_minus1 = bs_read_ue( p_bs );    /*       against sps PicWidthInCtbsY */
        p_pps->uniform_spacing_flag = bs_read1( p_bs );
        if( !p_pps->uniform_spacing_flag )
        {
            if( bs_remain( p_bs ) < p_pps->num_tile_columns_minus1 +
                                    p_pps->num_tile_rows_minus1 + 1 )
                return false;
            for( unsigned i=0; i< p_pps->num_tile_columns_minus1; i++ )
                (void) bs_read_ue( p_bs );
            for( unsigned i=0; i< p_pps->num_tile_rows_minus1; i++ )
                (void) bs_read_ue( p_bs );
        }
        p_pps->loop_filter_across_tiles_enabled_flag = bs_read1( p_bs );
    }

    p_pps->pps_loop_filter_across_slices_enabled_flag = bs_read1( p_bs );
    p_pps->deblocking_filter_control_present_flag = bs_read1( p_bs );
    if( p_pps->deblocking_filter_control_present_flag )
    {
        p_pps->deblocking_filter_override_enabled_flag = bs_read1( p_bs );
        p_pps->pps_deblocking_filter_disabled_flag = bs_read1( p_bs );
        if( !p_pps->pps_deblocking_filter_disabled_flag )
        {
            p_pps->pps_beta_offset_div2 = bs_read_se( p_bs );
            p_pps->pps_tc_offset_div2 = bs_read_se( p_bs );
        }
    }

    p_pps->scaling_list_data_present_flag = bs_read1( p_bs );
    if( p_pps->scaling_list_data_present_flag && !hevc_parse_scaling_list_rbsp( p_bs ) )
        return false;

    p_pps->lists_modification_present_flag = bs_read1( p_bs );
    p_pps->log2_parallel_merge_level_minus2 = bs_read_ue( p_bs );
    p_pps->slice_header_extension_present_flag = bs_read1( p_bs );

    if( bs_remain( p_bs ) < 1 )
        return false;

    p_pps->pps_extension_present_flag = bs_read1( p_bs );
    if( p_pps->pps_extension_present_flag )
    {
        p_pps->pps_range_extension_flag = bs_read1( p_bs );
        p_pps->pps_multilayer_extension_flag = bs_read1( p_bs );
        p_pps->pps_3d_extension_flag = bs_read1( p_bs );
        if( bs_remain( p_bs ) < 5 )
            return false;
        p_pps->pps_extension_5bits = bs_read( p_bs, 5 );
    }

    return true;
}