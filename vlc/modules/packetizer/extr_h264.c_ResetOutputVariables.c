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
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
struct TYPE_5__ {int b_new_sps; int b_new_pps; int b_slice; int /*<<< orphan*/  i_recovery_frame_cnt; int /*<<< orphan*/  i_pic_struct; scalar_t__ i_dpb_output_delay; TYPE_1__ slice; void* i_frame_pts; void* i_frame_dts; } ;
typedef  TYPE_2__ decoder_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  H264_SLICE_TYPE_UNKNOWN ; 
 int /*<<< orphan*/  UINT8_MAX ; 
 int /*<<< orphan*/  UINT_MAX ; 
 void* VLC_TICK_INVALID ; 

__attribute__((used)) static void ResetOutputVariables( decoder_sys_t *p_sys )
{
    p_sys->i_frame_dts = VLC_TICK_INVALID;
    p_sys->i_frame_pts = VLC_TICK_INVALID;
    p_sys->slice.type = H264_SLICE_TYPE_UNKNOWN;
    p_sys->b_new_sps = false;
    p_sys->b_new_pps = false;
    p_sys->b_slice = false;
    /* From SEI */
    p_sys->i_dpb_output_delay = 0;
    p_sys->i_pic_struct = UINT8_MAX;
    p_sys->i_recovery_frame_cnt = UINT_MAX;
}