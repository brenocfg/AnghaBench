#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct hxxx_helper_nal {scalar_t__ hevc_sps; TYPE_2__* h264_sps; } ;
struct TYPE_6__ {size_t i_current_sps; struct hxxx_helper_nal* sps_list; } ;
struct hxxx_helper {scalar_t__ i_codec; TYPE_3__ hevc; } ;
struct TYPE_4__ {int i_sar_num; int i_sar_den; } ;
struct TYPE_5__ {TYPE_1__ vui; } ;

/* Variables and functions */
 scalar_t__ VLC_CODEC_H264 ; 
 scalar_t__ VLC_CODEC_HEVC ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 struct hxxx_helper_nal* h264_helper_get_current_sps (struct hxxx_helper const*) ; 
 scalar_t__ hevc_get_aspect_ratio (scalar_t__,unsigned int*,unsigned int*) ; 

int
hxxx_helper_get_current_sar(const struct hxxx_helper *hh, int *p_num, int *p_den)
{
    if(hh->i_codec == VLC_CODEC_H264)
    {
        const struct hxxx_helper_nal *hsps = h264_helper_get_current_sps(hh);
        if (hsps)
        {
            *p_num = hsps->h264_sps->vui.i_sar_num;
            *p_den = hsps->h264_sps->vui.i_sar_den;
            return VLC_SUCCESS;
        }
    }
    else if(hh->i_codec == VLC_CODEC_HEVC)
    {
        const struct hxxx_helper_nal *hsps = &hh->hevc.sps_list[hh->hevc.i_current_sps];
        unsigned num, den;
        if(hsps && hsps->hevc_sps && hevc_get_aspect_ratio(hsps->hevc_sps, &num, &den))
        {
            *p_num = num;
            *p_den = den;
            return VLC_SUCCESS;
        }
    }
    return VLC_EGENERIC;
}