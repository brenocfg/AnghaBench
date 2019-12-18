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
struct TYPE_3__ {int i_nal_type; int i_nal_ref_idc; int i_idr_pic_id; int i_pic_parameter_set_id; int i_bottom_field_flag; int i_pic_order_cnt_type; int i_pic_order_cnt_lsb; int i_delta_pic_order_cnt_bottom; int has_mmco5; scalar_t__ i_delta_pic_order_cnt1; scalar_t__ i_delta_pic_order_cnt0; scalar_t__ i_field_pic_flag; int /*<<< orphan*/  type; scalar_t__ i_frame_num; } ;
typedef  TYPE_1__ h264_slice_t ;

/* Variables and functions */
 int /*<<< orphan*/  H264_SLICE_TYPE_UNKNOWN ; 

__attribute__((used)) static inline void h264_slice_init( h264_slice_t *p_slice )
{
    p_slice->i_nal_type = -1;
    p_slice->i_nal_ref_idc = -1;
    p_slice->i_idr_pic_id = -1;
    p_slice->i_frame_num = 0;
    p_slice->type = H264_SLICE_TYPE_UNKNOWN;
    p_slice->i_pic_parameter_set_id = -1;
    p_slice->i_field_pic_flag = 0;
    p_slice->i_bottom_field_flag = -1;
    p_slice->i_pic_order_cnt_type = -1;
    p_slice->i_pic_order_cnt_lsb = -1;
    p_slice->i_delta_pic_order_cnt_bottom = -1;
    p_slice->i_delta_pic_order_cnt0 = 0;
    p_slice->i_delta_pic_order_cnt1 = 0;
    p_slice->has_mmco5 = false;
}