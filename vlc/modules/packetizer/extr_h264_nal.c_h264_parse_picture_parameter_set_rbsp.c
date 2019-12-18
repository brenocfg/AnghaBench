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
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {void* i_redundant_pic_present_flag; void* weighted_bipred_idc; void* weighted_pred_flag; void* i_pic_order_present_flag; scalar_t__ i_sps_id; scalar_t__ i_id; } ;
typedef  TYPE_1__ h264_picture_parameter_set_t ;
typedef  int /*<<< orphan*/  bs_t ;

/* Variables and functions */
 scalar_t__ H264_PPS_ID_MAX ; 
 scalar_t__ H264_SPS_ID_MAX ; 
 void* bs_read (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bs_read1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bs_read_se (int /*<<< orphan*/ *) ; 
 int bs_read_ue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bs_skip (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static bool h264_parse_picture_parameter_set_rbsp( bs_t *p_bs,
                                                   h264_picture_parameter_set_t *p_pps )
{
    uint32_t i_pps_id = bs_read_ue( p_bs ); // pps id
    uint32_t i_sps_id = bs_read_ue( p_bs ); // sps id
    if( i_pps_id > H264_PPS_ID_MAX || i_sps_id > H264_SPS_ID_MAX )
        return false;
    p_pps->i_id = i_pps_id;
    p_pps->i_sps_id = i_sps_id;

    bs_skip( p_bs, 1 ); // entropy coding mode flag
    p_pps->i_pic_order_present_flag = bs_read( p_bs, 1 );

    unsigned num_slice_groups = bs_read_ue( p_bs ) + 1;
    if( num_slice_groups > 8 ) /* never has value > 7. Annex A, G & J */
        return false;
    if( num_slice_groups > 1 )
    {
        unsigned slice_group_map_type = bs_read_ue( p_bs );
        if( slice_group_map_type == 0 )
        {
            for( unsigned i = 0; i < num_slice_groups; i++ )
                bs_read_ue( p_bs ); /* run_length_minus1[group] */
        }
        else if( slice_group_map_type == 2 )
        {
            for( unsigned i = 0; i < num_slice_groups; i++ )
            {
                bs_read_ue( p_bs ); /* top_left[group] */
                bs_read_ue( p_bs ); /* bottom_right[group] */
            }
        }
        else if( slice_group_map_type > 2 && slice_group_map_type < 6 )
        {
            bs_read1( p_bs );   /* slice_group_change_direction_flag */
            bs_read_ue( p_bs ); /* slice_group_change_rate_minus1 */
        }
        else if( slice_group_map_type == 6 )
        {
            unsigned pic_size_in_maps_units = bs_read_ue( p_bs ) + 1;
            unsigned sliceGroupSize = 1;
            while(num_slice_groups > 1)
            {
                sliceGroupSize++;
                num_slice_groups = ((num_slice_groups - 1) >> 1) + 1;
            }
            for( unsigned i = 0; i < pic_size_in_maps_units; i++ )
            {
                bs_skip( p_bs, sliceGroupSize );
            }
        }
    }

    bs_read_ue( p_bs ); /* num_ref_idx_l0_default_active_minus1 */
    bs_read_ue( p_bs ); /* num_ref_idx_l1_default_active_minus1 */
    p_pps->weighted_pred_flag = bs_read( p_bs, 1 );
    p_pps->weighted_bipred_idc = bs_read( p_bs, 2 );
    bs_read_se( p_bs ); /* pic_init_qp_minus26 */
    bs_read_se( p_bs ); /* pic_init_qs_minus26 */
    bs_read_se( p_bs ); /* chroma_qp_index_offset */
    bs_read( p_bs, 1 ); /* deblocking_filter_control_present_flag */
    bs_read( p_bs, 1 ); /* constrained_intra_pred_flag */
    p_pps->i_redundant_pic_present_flag = bs_read( p_bs, 1 );

    /* TODO */

    return true;
}