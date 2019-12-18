#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_9__ {int i_profile; } ;
typedef  TYPE_1__ es_format_t ;
struct TYPE_10__ {int* p_profiles; scalar_t__ codec; } ;
typedef  TYPE_2__ directx_va_mode_t ;
struct TYPE_11__ {int profile; } ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_H264 ; 
 scalar_t__ AV_CODEC_ID_HEVC ; 
 int const FF_PROFILE_UNKNOWN ; 
 scalar_t__ h264_get_profile_level (TYPE_1__ const*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ hevc_get_profile_level (TYPE_1__ const*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool profile_supported(const directx_va_mode_t *mode, const es_format_t *fmt,
                              const AVCodecContext *avctx)
{
    if (mode->p_profiles == NULL)
        return true;

    int profile = fmt->i_profile >= 0 ? fmt->i_profile : avctx->profile;
    if (mode->codec == AV_CODEC_ID_H264)
    {
        uint8_t h264_profile;
        if ( h264_get_profile_level(fmt, &h264_profile, NULL, NULL) )
            profile = h264_profile;
    }
    if (mode->codec == AV_CODEC_ID_HEVC)
    {
        uint8_t hevc_profile;
        if (hevc_get_profile_level(fmt, &hevc_profile, NULL, NULL) )
            profile = hevc_profile;
    }

    bool is_supported = false;
    if (profile <= 0)
        is_supported = true;
    else for (const int *p_profile = &mode->p_profiles[0]; *p_profile != FF_PROFILE_UNKNOWN; ++p_profile)
    {
        if (*p_profile == profile)
        {
            is_supported = true;
            break;
        }
    }
    return is_supported;
}