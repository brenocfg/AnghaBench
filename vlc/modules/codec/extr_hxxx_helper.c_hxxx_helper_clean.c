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
struct hxxx_helper_nal {int /*<<< orphan*/  hevc_pps; int /*<<< orphan*/  hevc_sps; int /*<<< orphan*/  hevc_vps; int /*<<< orphan*/  h264_pps; int /*<<< orphan*/  h264_sps; } ;
struct TYPE_2__ {int /*<<< orphan*/  pps_list; int /*<<< orphan*/  sps_list; int /*<<< orphan*/  vps_list; } ;
struct hxxx_helper {int i_codec; TYPE_1__ hevc; TYPE_1__ h264; } ;

/* Variables and functions */
 int /*<<< orphan*/  H264_PPS_ID_MAX ; 
 int /*<<< orphan*/  H264_SPS_ID_MAX ; 
 int /*<<< orphan*/  HEVC_PPS_ID_MAX ; 
 int /*<<< orphan*/  HEVC_SPS_ID_MAX ; 
 int /*<<< orphan*/  HEVC_VPS_ID_MAX ; 
 int /*<<< orphan*/  RELEASE_NALS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  VLC_CODEC_H264 129 
#define  VLC_CODEC_HEVC 128 
 int /*<<< orphan*/  h264_release_pps (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h264_release_sps (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  helper_clear_sei (struct hxxx_helper*) ; 
 int /*<<< orphan*/  hevc_rbsp_release_pps (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hevc_rbsp_release_sps (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hevc_rbsp_release_vps (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 

void
hxxx_helper_clean(struct hxxx_helper *hh)
{
    struct hxxx_helper_nal *hnal;
    switch (hh->i_codec)
    {
        case VLC_CODEC_H264:
            RELEASE_NALS(hh->h264.sps_list, H264_SPS_ID_MAX,
                         h264_release_sps(hnal->h264_sps));
            RELEASE_NALS(hh->h264.pps_list, H264_PPS_ID_MAX,
                         h264_release_pps(hnal->h264_pps));
            memset(&hh->h264, 0, sizeof(hh->h264));
            break;
        case VLC_CODEC_HEVC:
            RELEASE_NALS(hh->hevc.vps_list, HEVC_VPS_ID_MAX,
                         hevc_rbsp_release_vps(hnal->hevc_vps));
            RELEASE_NALS(hh->hevc.sps_list, HEVC_SPS_ID_MAX,
                         hevc_rbsp_release_sps(hnal->hevc_sps));
            RELEASE_NALS(hh->hevc.pps_list, HEVC_PPS_ID_MAX,
                         hevc_rbsp_release_pps(hnal->hevc_pps));
            helper_clear_sei(hh);
            memset(&hh->hevc, 0, sizeof(hh->hevc));
            break;
        default:
            vlc_assert_unreachable();
    }
}