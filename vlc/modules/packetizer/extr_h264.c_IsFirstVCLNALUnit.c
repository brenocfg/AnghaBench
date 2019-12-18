#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ i_frame_num; scalar_t__ i_pic_parameter_set_id; scalar_t__ i_field_pic_flag; int i_bottom_field_flag; int i_pic_order_cnt_type; scalar_t__ i_pic_order_cnt_lsb; scalar_t__ i_delta_pic_order_cnt_bottom; scalar_t__ i_delta_pic_order_cnt0; scalar_t__ i_delta_pic_order_cnt1; scalar_t__ i_nal_type; scalar_t__ i_idr_pic_id; int /*<<< orphan*/  i_nal_ref_idc; } ;
typedef  TYPE_1__ h264_slice_t ;

/* Variables and functions */
 scalar_t__ H264_NAL_SLICE_IDR ; 

__attribute__((used)) static bool IsFirstVCLNALUnit( const h264_slice_t *p_prev, const h264_slice_t *p_cur )
{
    /* Detection of the first VCL NAL unit of a primary coded picture
     * (cf. 7.4.1.2.4) */
    if( p_cur->i_frame_num != p_prev->i_frame_num ||
        p_cur->i_pic_parameter_set_id != p_prev->i_pic_parameter_set_id ||
        p_cur->i_field_pic_flag != p_prev->i_field_pic_flag ||
       !p_cur->i_nal_ref_idc != !p_prev->i_nal_ref_idc )
        return true;
    if( (p_cur->i_bottom_field_flag != -1) &&
        (p_prev->i_bottom_field_flag != -1) &&
        (p_cur->i_bottom_field_flag != p_prev->i_bottom_field_flag) )
        return true;
    if( p_cur->i_pic_order_cnt_type == 0 &&
       ( p_cur->i_pic_order_cnt_lsb != p_prev->i_pic_order_cnt_lsb ||
         p_cur->i_delta_pic_order_cnt_bottom != p_prev->i_delta_pic_order_cnt_bottom ) )
        return true;
    else if( p_cur->i_pic_order_cnt_type == 1 &&
           ( p_cur->i_delta_pic_order_cnt0 != p_prev->i_delta_pic_order_cnt0 ||
             p_cur->i_delta_pic_order_cnt1 != p_prev->i_delta_pic_order_cnt1 ) )
        return true;
    if( ( p_cur->i_nal_type == H264_NAL_SLICE_IDR || p_prev->i_nal_type == H264_NAL_SLICE_IDR ) &&
        ( p_cur->i_nal_type != p_prev->i_nal_type || p_cur->i_idr_pic_id != p_prev->i_idr_pic_id ) )
        return true;

    return false;
}