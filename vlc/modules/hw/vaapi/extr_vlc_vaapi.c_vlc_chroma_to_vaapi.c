#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int VA_FOURCC_NV12 ; 
 int VA_FOURCC_P010 ; 
 unsigned int VA_RT_FORMAT_YUV420 ; 
 unsigned int VA_RT_FORMAT_YUV420_10BPP ; 
#define  VLC_CODEC_VAAPI_420 129 
#define  VLC_CODEC_VAAPI_420_10BPP 128 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 

void
vlc_chroma_to_vaapi(int i_vlc_chroma, unsigned *va_rt_format, int *va_fourcc)
{
    switch (i_vlc_chroma)
    {
        case VLC_CODEC_VAAPI_420:
            *va_rt_format = VA_RT_FORMAT_YUV420;
            *va_fourcc = VA_FOURCC_NV12;
            break;
        case VLC_CODEC_VAAPI_420_10BPP:
            *va_rt_format = VA_RT_FORMAT_YUV420_10BPP;
            *va_fourcc = VA_FOURCC_P010;
            break;
        default:
            vlc_assert_unreachable();
    }
}