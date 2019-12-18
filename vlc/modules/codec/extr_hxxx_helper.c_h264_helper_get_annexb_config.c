#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hxxx_helper_nal {int dummy; } ;
struct TYPE_2__ {scalar_t__ i_sps_count; scalar_t__ i_pps_count; struct hxxx_helper_nal const* pps_list; struct hxxx_helper_nal const* sps_list; } ;
struct hxxx_helper {TYPE_1__ h264; } ;
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */
 int /*<<< orphan*/  H264_PPS_ID_MAX ; 
 int /*<<< orphan*/  H264_SPS_ID_MAX ; 
 int /*<<< orphan*/ * hxxx_helper_get_annexb_config (struct hxxx_helper_nal const**,size_t const*,size_t const*,int) ; 

block_t *
h264_helper_get_annexb_config(const struct hxxx_helper *hh)
{
    if (hh->h264.i_sps_count == 0 || hh->h264.i_pps_count == 0)
        return NULL;

    const struct hxxx_helper_nal *pp_nal_lists[] = {
        hh->h264.sps_list, hh->h264.pps_list };
    const size_t p_nal_counts[] = { hh->h264.i_sps_count, hh->h264.i_pps_count };
    const size_t p_nal_maxs[] = { H264_SPS_ID_MAX+1, H264_PPS_ID_MAX+1 };

    return hxxx_helper_get_annexb_config( pp_nal_lists, p_nal_counts, p_nal_maxs, 2 );
}