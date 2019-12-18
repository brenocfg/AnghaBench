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
struct TYPE_2__ {scalar_t__ i_vps_count; scalar_t__ i_sps_count; scalar_t__ i_pps_count; struct hxxx_helper_nal const* pps_list; struct hxxx_helper_nal const* sps_list; struct hxxx_helper_nal const* vps_list; } ;
struct hxxx_helper {TYPE_1__ hevc; } ;
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */
 int /*<<< orphan*/  HEVC_PPS_ID_MAX ; 
 int /*<<< orphan*/  HEVC_SPS_ID_MAX ; 
 int /*<<< orphan*/  HEVC_VPS_ID_MAX ; 
 int /*<<< orphan*/ * hxxx_helper_get_annexb_config (struct hxxx_helper_nal const**,size_t const*,size_t const*,int) ; 

block_t *
hevc_helper_get_annexb_config(const struct hxxx_helper *hh)
{
    if (hh->hevc.i_vps_count == 0 || hh->hevc.i_sps_count == 0 ||
        hh->hevc.i_pps_count == 0 )
        return NULL;

    const struct hxxx_helper_nal *pp_nal_lists[] = {
        hh->hevc.vps_list, hh->hevc.sps_list, hh->hevc.pps_list };
    const size_t p_nal_counts[] = { hh->hevc.i_vps_count, hh->hevc.i_sps_count,
                                    hh->hevc.i_pps_count };
    const size_t p_nal_maxs[] = { HEVC_VPS_ID_MAX+1, HEVC_SPS_ID_MAX+1, HEVC_PPS_ID_MAX+1 };

    return hxxx_helper_get_annexb_config( pp_nal_lists, p_nal_counts, p_nal_maxs, 3 );
}