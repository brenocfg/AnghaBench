#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int i_chroma; } ;
typedef  TYPE_1__ video_format_t ;
typedef  int uint8_t ;

/* Variables and functions */
 int VLC_CODEC_I420 ; 
 int VLC_CODEC_I420_10L ; 
 int VLC_CODEC_P010 ; 
#define  VLC_CODEC_VAAPI_420 129 
#define  VLC_CODEC_VAAPI_420_10BPP 128 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 

__attribute__((used)) static int CheckFmt(const video_format_t *in, const video_format_t *out,
                    bool *upload, uint8_t *pixel_bytes)
{
    *pixel_bytes = 1;
    *upload = false;
    switch (in->i_chroma)
    {
        case VLC_CODEC_VAAPI_420:
            if (out->i_chroma == VLC_CODEC_I420)
                return VLC_SUCCESS;
            break;
        case VLC_CODEC_VAAPI_420_10BPP:
            if (out->i_chroma == VLC_CODEC_P010
             || out->i_chroma == VLC_CODEC_I420_10L)
            {
                *pixel_bytes = 2;
                return VLC_SUCCESS;
            }
            break;
    }

    *upload = true;
    switch (out->i_chroma)
    {
        case VLC_CODEC_VAAPI_420:
            if (in->i_chroma == VLC_CODEC_I420)
                return VLC_SUCCESS;
            break;
        case VLC_CODEC_VAAPI_420_10BPP:
            if (in->i_chroma == VLC_CODEC_P010
             || in->i_chroma == VLC_CODEC_I420_10L)
            {
                *pixel_bytes = 2;
                return VLC_SUCCESS;
            }
            break;
    }
    return VLC_EGENERIC;
}