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
typedef  int /*<<< orphan*/  uint8_t ;
struct hxxx_helper_nal {int /*<<< orphan*/ * hevc_sps; int /*<<< orphan*/  h264_sps; } ;
struct TYPE_2__ {size_t i_current_sps; struct hxxx_helper_nal* sps_list; } ;
struct hxxx_helper {int i_codec; TYPE_1__ hevc; } ;

/* Variables and functions */
#define  VLC_CODEC_H264 129 
#define  VLC_CODEC_HEVC 128 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int h264_get_chroma_luma (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct hxxx_helper_nal* h264_helper_get_current_sps (struct hxxx_helper const*) ; 
 int hevc_get_chroma_luma (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 

int
hxxx_helper_get_chroma_chroma(const struct hxxx_helper *hh, uint8_t *pi_chroma_format,
                              uint8_t *pi_depth_luma, uint8_t *pi_depth_chroma)
{
    switch (hh->i_codec)
    {
        case VLC_CODEC_H264:
        {
            const struct hxxx_helper_nal *hsps = h264_helper_get_current_sps(hh);
            if (hsps == NULL)
                return VLC_EGENERIC;
            return h264_get_chroma_luma(hsps->h264_sps, pi_chroma_format, pi_depth_luma,
                                        pi_depth_chroma)
                == true ? VLC_SUCCESS : VLC_EGENERIC;
        }
        case VLC_CODEC_HEVC:
        {
            const struct hxxx_helper_nal *hsps = &hh->hevc.sps_list[hh->hevc.i_current_sps];
            if (hsps == NULL || hsps->hevc_sps == NULL)
                return VLC_EGENERIC;

            return hevc_get_chroma_luma(hsps->hevc_sps, pi_chroma_format, pi_depth_luma,
                                        pi_depth_chroma)
                == true ? VLC_SUCCESS : VLC_EGENERIC;
        }
        default:
            vlc_assert_unreachable();
    }
}