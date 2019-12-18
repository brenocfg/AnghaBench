#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_7__ {void* i_matrix_coefficients; void* i_transfer_characteristics; void* i_colour_primaries; void* b_full_range; } ;
struct TYPE_8__ {int b_valid; int i_sar_num; int i_sar_den; int b_timing_info_present_flag; int b_hrd_parameters_present_flag; int b_bitstream_restriction_flag; scalar_t__ i_max_num_reorder_frames; void* b_pic_struct_present_flag; void* i_dpb_output_delay_length_minus1; void* i_cpb_removal_delay_length_minus1; void* b_fixed_frame_rate; void* i_time_scale; void* i_num_units_in_tick; TYPE_2__ colour; } ;
struct TYPE_6__ {scalar_t__ bottom_offset; scalar_t__ top_offset; scalar_t__ right_offset; scalar_t__ left_offset; } ;
struct TYPE_9__ {int i_profile; int i_chroma_idc; int i_bit_depth_luma; int i_bit_depth_chroma; int i_log2_max_frame_num; scalar_t__ i_pic_order_cnt_type; int i_log2_max_pic_order_cnt_lsb; int i_num_ref_frames_in_pic_order_cnt_cycle; TYPE_3__ vui; TYPE_1__ frame_crop; void* mb_adaptive_frame_field_flag; void* frame_mbs_only_flag; scalar_t__ pic_height_in_map_units_minus1; scalar_t__ pic_width_in_mbs_minus1; void** offset_for_ref_frame; void* offset_for_top_to_bottom_field; void* offset_for_non_ref_pic; void* i_delta_pic_order_always_zero_flag; scalar_t__ b_separate_colour_planes_flag; scalar_t__ i_id; void* i_level; void* i_constraint_set_flags; } ;
typedef  TYPE_4__ h264_sequence_parameter_set_t ;
typedef  int /*<<< orphan*/  bs_t ;

/* Variables and functions */
 scalar_t__ H264_SPS_ID_MAX ; 
 void* ISO_23001_8_CP_UNSPECIFIED ; 
 void* ISO_23001_8_MC_UNSPECIFIED ; 
 void* ISO_23001_8_TC_UNSPECIFIED ; 
 int PROFILE_H264_CAVLC_INTRA ; 
 int PROFILE_H264_HIGH ; 
 int PROFILE_H264_HIGH_10 ; 
 int PROFILE_H264_HIGH_422 ; 
 int PROFILE_H264_HIGH_444 ; 
 int PROFILE_H264_HIGH_444_PREDICTIVE ; 
 int PROFILE_H264_MFC_HIGH ; 
 int PROFILE_H264_MVC_ENHANCED_MULTIVIEW_DEPTH_HIGH ; 
 int PROFILE_H264_MVC_MULTIVIEW_DEPTH_HIGH ; 
 int PROFILE_H264_MVC_MULTIVIEW_HIGH ; 
 int PROFILE_H264_MVC_STEREO_HIGH ; 
 int PROFILE_H264_SVC_BASELINE ; 
 int PROFILE_H264_SVC_HIGH ; 
 void* bs_read (int /*<<< orphan*/ *,int) ; 
 scalar_t__ bs_read1 (int /*<<< orphan*/ *) ; 
 void* bs_read_se (int /*<<< orphan*/ *) ; 
 scalar_t__ bs_read_ue (int /*<<< orphan*/ *) ; 
 int bs_remain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bs_skip (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool h264_parse_sequence_parameter_set_rbsp( bs_t *p_bs,
                                                    h264_sequence_parameter_set_t *p_sps )
{
    int i_tmp;

    int i_profile_idc = bs_read( p_bs, 8 );
    p_sps->i_profile = i_profile_idc;
    p_sps->i_constraint_set_flags = bs_read( p_bs, 8 );
    p_sps->i_level = bs_read( p_bs, 8 );
    /* sps id */
    uint32_t i_sps_id = bs_read_ue( p_bs );
    if( i_sps_id > H264_SPS_ID_MAX )
        return false;
    p_sps->i_id = i_sps_id;

    if( i_profile_idc == PROFILE_H264_HIGH ||
        i_profile_idc == PROFILE_H264_HIGH_10 ||
        i_profile_idc == PROFILE_H264_HIGH_422 ||
        i_profile_idc == PROFILE_H264_HIGH_444 || /* Old one, no longer on spec */
        i_profile_idc == PROFILE_H264_HIGH_444_PREDICTIVE ||
        i_profile_idc == PROFILE_H264_CAVLC_INTRA ||
        i_profile_idc == PROFILE_H264_SVC_BASELINE ||
        i_profile_idc == PROFILE_H264_SVC_HIGH ||
        i_profile_idc == PROFILE_H264_MVC_MULTIVIEW_HIGH ||
        i_profile_idc == PROFILE_H264_MVC_STEREO_HIGH ||
        i_profile_idc == PROFILE_H264_MVC_MULTIVIEW_DEPTH_HIGH ||
        i_profile_idc == PROFILE_H264_MVC_ENHANCED_MULTIVIEW_DEPTH_HIGH ||
        i_profile_idc == PROFILE_H264_MFC_HIGH )
    {
        /* chroma_format_idc */
        p_sps->i_chroma_idc = bs_read_ue( p_bs );
        if( p_sps->i_chroma_idc == 3 )
            p_sps->b_separate_colour_planes_flag = bs_read1( p_bs );
        else
            p_sps->b_separate_colour_planes_flag = 0;
        /* bit_depth_luma_minus8 */
        p_sps->i_bit_depth_luma = bs_read_ue( p_bs ) + 8;
        /* bit_depth_chroma_minus8 */
        p_sps->i_bit_depth_chroma = bs_read_ue( p_bs ) + 8;
        /* qpprime_y_zero_transform_bypass_flag */
        bs_skip( p_bs, 1 );
        /* seq_scaling_matrix_present_flag */
        i_tmp = bs_read( p_bs, 1 );
        if( i_tmp )
        {
            for( int i = 0; i < ((3 != p_sps->i_chroma_idc) ? 8 : 12); i++ )
            {
                /* seq_scaling_list_present_flag[i] */
                i_tmp = bs_read( p_bs, 1 );
                if( !i_tmp )
                    continue;
                const int i_size_of_scaling_list = (i < 6 ) ? 16 : 64;
                /* scaling_list (...) */
                int i_lastscale = 8;
                int i_nextscale = 8;
                for( int j = 0; j < i_size_of_scaling_list; j++ )
                {
                    if( i_nextscale != 0 )
                    {
                        /* delta_scale */
                        i_tmp = bs_read_se( p_bs );
                        i_nextscale = ( i_lastscale + i_tmp + 256 ) % 256;
                        /* useDefaultScalingMatrixFlag = ... */
                    }
                    /* scalinglist[j] */
                    i_lastscale = ( i_nextscale == 0 ) ? i_lastscale : i_nextscale;
                }
            }
        }
    }
    else
    {
        p_sps->i_chroma_idc = 1; /* Not present == inferred to 4:2:0 */
        p_sps->i_bit_depth_luma = 8;
        p_sps->i_bit_depth_chroma = 8;
    }

    /* Skip i_log2_max_frame_num */
    p_sps->i_log2_max_frame_num = bs_read_ue( p_bs );
    if( p_sps->i_log2_max_frame_num > 12)
        p_sps->i_log2_max_frame_num = 12;
    /* Read poc_type */
    p_sps->i_pic_order_cnt_type = bs_read_ue( p_bs );
    if( p_sps->i_pic_order_cnt_type == 0 )
    {
        /* skip i_log2_max_poc_lsb */
        p_sps->i_log2_max_pic_order_cnt_lsb = bs_read_ue( p_bs );
        if( p_sps->i_log2_max_pic_order_cnt_lsb > 12 )
            p_sps->i_log2_max_pic_order_cnt_lsb = 12;
    }
    else if( p_sps->i_pic_order_cnt_type == 1 )
    {
        p_sps->i_delta_pic_order_always_zero_flag = bs_read( p_bs, 1 );
        p_sps->offset_for_non_ref_pic = bs_read_se( p_bs );
        p_sps->offset_for_top_to_bottom_field = bs_read_se( p_bs );
        p_sps->i_num_ref_frames_in_pic_order_cnt_cycle = bs_read_ue( p_bs );
        if( p_sps->i_num_ref_frames_in_pic_order_cnt_cycle > 255 )
            return false;
        for( int i=0; i<p_sps->i_num_ref_frames_in_pic_order_cnt_cycle; i++ )
            p_sps->offset_for_ref_frame[i] = bs_read_se( p_bs );
    }
    /* i_num_ref_frames */
    bs_read_ue( p_bs );
    /* b_gaps_in_frame_num_value_allowed */
    bs_skip( p_bs, 1 );

    /* Read size */
    p_sps->pic_width_in_mbs_minus1 = bs_read_ue( p_bs );
    p_sps->pic_height_in_map_units_minus1 = bs_read_ue( p_bs );

    /* b_frame_mbs_only */
    p_sps->frame_mbs_only_flag = bs_read( p_bs, 1 );
    if( !p_sps->frame_mbs_only_flag )
        p_sps->mb_adaptive_frame_field_flag = bs_read( p_bs, 1 );

    /* b_direct8x8_inference */
    bs_skip( p_bs, 1 );

    /* crop */
    if( bs_read1( p_bs ) ) /* frame_cropping_flag */
    {
        p_sps->frame_crop.left_offset = bs_read_ue( p_bs );
        p_sps->frame_crop.right_offset = bs_read_ue( p_bs );
        p_sps->frame_crop.top_offset = bs_read_ue( p_bs );
        p_sps->frame_crop.bottom_offset = bs_read_ue( p_bs );
    }

    /* vui */
    i_tmp = bs_read( p_bs, 1 );
    if( i_tmp )
    {
        p_sps->vui.b_valid = true;
        /* read the aspect ratio part if any */
        i_tmp = bs_read( p_bs, 1 );
        if( i_tmp )
        {
            static const struct { int w, h; } sar[17] =
            {
                { 0,   0 }, { 1,   1 }, { 12, 11 }, { 10, 11 },
                { 16, 11 }, { 40, 33 }, { 24, 11 }, { 20, 11 },
                { 32, 11 }, { 80, 33 }, { 18, 11 }, { 15, 11 },
                { 64, 33 }, { 160,99 }, {  4,  3 }, {  3,  2 },
                {  2,  1 },
            };
            int i_sar = bs_read( p_bs, 8 );
            int w, h;

            if( i_sar < 17 )
            {
                w = sar[i_sar].w;
                h = sar[i_sar].h;
            }
            else if( i_sar == 255 )
            {
                w = bs_read( p_bs, 16 );
                h = bs_read( p_bs, 16 );
            }
            else
            {
                w = 0;
                h = 0;
            }

            if( w != 0 && h != 0 )
            {
                p_sps->vui.i_sar_num = w;
                p_sps->vui.i_sar_den = h;
            }
            else
            {
                p_sps->vui.i_sar_num = 1;
                p_sps->vui.i_sar_den = 1;
            }
        }

        /* overscan */
        i_tmp = bs_read( p_bs, 1 );
        if ( i_tmp )
            bs_read( p_bs, 1 );

        /* video signal type */
        i_tmp = bs_read( p_bs, 1 );
        if( i_tmp )
        {
            bs_read( p_bs, 3 );
            p_sps->vui.colour.b_full_range = bs_read( p_bs, 1 );
            /* colour desc */
            i_tmp = bs_read( p_bs, 1 );
            if ( i_tmp )
            {
                p_sps->vui.colour.i_colour_primaries = bs_read( p_bs, 8 );
                p_sps->vui.colour.i_transfer_characteristics = bs_read( p_bs, 8 );
                p_sps->vui.colour.i_matrix_coefficients = bs_read( p_bs, 8 );
            }
            else
            {
                p_sps->vui.colour.i_colour_primaries = ISO_23001_8_CP_UNSPECIFIED;
                p_sps->vui.colour.i_transfer_characteristics = ISO_23001_8_TC_UNSPECIFIED;
                p_sps->vui.colour.i_matrix_coefficients = ISO_23001_8_MC_UNSPECIFIED;
            }
        }

        /* chroma loc info */
        i_tmp = bs_read( p_bs, 1 );
        if( i_tmp )
        {
            bs_read_ue( p_bs );
            bs_read_ue( p_bs );
        }

        /* timing info */
        p_sps->vui.b_timing_info_present_flag = bs_read( p_bs, 1 );
        if( p_sps->vui.b_timing_info_present_flag )
        {
            p_sps->vui.i_num_units_in_tick = bs_read( p_bs, 32 );
            p_sps->vui.i_time_scale = bs_read( p_bs, 32 );
            p_sps->vui.b_fixed_frame_rate = bs_read( p_bs, 1 );
        }

        /* Nal hrd & VC1 hrd parameters */
        p_sps->vui.b_hrd_parameters_present_flag = false;
        for ( int i=0; i<2; i++ )
        {
            i_tmp = bs_read( p_bs, 1 );
            if( i_tmp )
            {
                p_sps->vui.b_hrd_parameters_present_flag = true;
                uint32_t count = bs_read_ue( p_bs ) + 1;
                if( count > 31 )
                    return false;
                bs_read( p_bs, 4 );
                bs_read( p_bs, 4 );
                for( uint32_t j = 0; j < count; j++ )
                {
                    if( bs_remain( p_bs ) < 23 )
                        return false;
                    bs_read_ue( p_bs );
                    bs_read_ue( p_bs );
                    bs_read( p_bs, 1 );
                }
                bs_read( p_bs, 5 );
                p_sps->vui.i_cpb_removal_delay_length_minus1 = bs_read( p_bs, 5 );
                p_sps->vui.i_dpb_output_delay_length_minus1 = bs_read( p_bs, 5 );
                bs_read( p_bs, 5 );
            }
        }

        if( p_sps->vui.b_hrd_parameters_present_flag )
            bs_read( p_bs, 1 ); /* low delay hrd */

        /* pic struct info */
        p_sps->vui.b_pic_struct_present_flag = bs_read( p_bs, 1 );

        p_sps->vui.b_bitstream_restriction_flag = bs_read( p_bs, 1 );
        if( p_sps->vui.b_bitstream_restriction_flag )
        {
            bs_read( p_bs, 1 ); /* motion vector pic boundaries */
            bs_read_ue( p_bs ); /* max bytes per pic */
            bs_read_ue( p_bs ); /* max bits per mb */
            bs_read_ue( p_bs ); /* log2 max mv h */
            bs_read_ue( p_bs ); /* log2 max mv v */
            p_sps->vui.i_max_num_reorder_frames = bs_read_ue( p_bs );
            bs_read_ue( p_bs ); /* max dec frame buffering */
        }
    }

    return true;
}