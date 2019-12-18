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
typedef  int /*<<< orphan*/  video_transfer_func_t ;
typedef  int /*<<< orphan*/  video_color_space_t ;
typedef  int /*<<< orphan*/  video_color_range_t ;
typedef  int /*<<< orphan*/  video_color_primaries_t ;
struct hxxx_helper_nal {int /*<<< orphan*/ * hevc_sps; int /*<<< orphan*/  h264_sps; } ;
struct TYPE_2__ {size_t i_current_sps; struct hxxx_helper_nal* sps_list; } ;
struct hxxx_helper {int i_codec; TYPE_1__ hevc; } ;

/* Variables and functions */
#define  VLC_CODEC_H264 129 
#define  VLC_CODEC_HEVC 128 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int h264_get_colorimetry (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct hxxx_helper_nal* h264_helper_get_current_sps (struct hxxx_helper const*) ; 
 int hevc_get_colorimetry (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 

int
hxxx_helper_get_colorimetry(const struct hxxx_helper *hh,
                            video_color_primaries_t *p_primaries,
                            video_transfer_func_t *p_transfer,
                            video_color_space_t *p_colorspace,
                            video_color_range_t *p_full_range)
{
    switch (hh->i_codec)
    {
        case VLC_CODEC_H264:
        {
            const struct hxxx_helper_nal *hsps = h264_helper_get_current_sps(hh);
            if (hsps == NULL)
                return VLC_EGENERIC;
            return h264_get_colorimetry(hsps->h264_sps, p_primaries, p_transfer,
                                        p_colorspace, p_full_range)
                == true ? VLC_SUCCESS : VLC_EGENERIC;
        }
        case VLC_CODEC_HEVC:
        {
            const struct hxxx_helper_nal *hsps = &hh->hevc.sps_list[hh->hevc.i_current_sps];
            if (hsps == NULL || hsps->hevc_sps == NULL)
                return VLC_EGENERIC;

            return hevc_get_colorimetry(hsps->hevc_sps, p_primaries, p_transfer,
                                        p_colorspace, p_full_range)
                == true ? VLC_SUCCESS : VLC_EGENERIC;
        }
        default:
            vlc_assert_unreachable();
    }
}