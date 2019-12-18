#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ i_nal_ref_idc; scalar_t__ type; } ;
typedef  TYPE_2__ h264_slice_t ;
struct TYPE_6__ {scalar_t__ i_max_num_reorder_frames; scalar_t__ b_valid; } ;
struct TYPE_8__ {scalar_t__ i_profile; TYPE_1__ vui; } ;
typedef  TYPE_3__ h264_sequence_parameter_set_t ;

/* Variables and functions */
 scalar_t__ H264_SLICE_TYPE_B ; 
 scalar_t__ PROFILE_H264_CAVLC_INTRA ; 

__attribute__((used)) static bool CanSwapPTSwithDTS( const h264_slice_t *p_slice,
                               const h264_sequence_parameter_set_t *p_sps )
{
    if( p_slice->i_nal_ref_idc == 0 && p_slice->type == H264_SLICE_TYPE_B )
        return true;
    else if( p_sps->vui.b_valid )
        return p_sps->vui.i_max_num_reorder_frames == 0;
    else
        return p_sps->i_profile == PROFILE_H264_CAVLC_INTRA;
}