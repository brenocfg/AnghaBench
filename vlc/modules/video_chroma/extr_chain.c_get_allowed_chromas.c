#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_fourcc_t ;
struct TYPE_5__ {int i_chroma; } ;
struct TYPE_6__ {TYPE_1__ video; } ;
struct TYPE_7__ {TYPE_2__ fmt_out; } ;
typedef  TYPE_3__ filter_t ;

/* Variables and functions */
#define  VLC_CODEC_CVPX_P010 134 
#define  VLC_CODEC_D3D11_OPAQUE_10B 133 
#define  VLC_CODEC_D3D9_OPAQUE_10B 132 
#define  VLC_CODEC_I420_10B 131 
#define  VLC_CODEC_I420_10L 130 
#define  VLC_CODEC_I420_16L 129 
#define  VLC_CODEC_VAAPI_420_10BPP 128 
 int /*<<< orphan*/  const* pi_allowed_chromas_yuv ; 
 int /*<<< orphan*/  const* pi_allowed_chromas_yuv10 ; 

__attribute__((used)) static const vlc_fourcc_t *get_allowed_chromas( filter_t *p_filter )
{
    switch (p_filter->fmt_out.video.i_chroma)
    {
        case VLC_CODEC_I420_10L:
        case VLC_CODEC_I420_10B:
        case VLC_CODEC_I420_16L:
        case VLC_CODEC_CVPX_P010:
        case VLC_CODEC_D3D9_OPAQUE_10B:
        case VLC_CODEC_D3D11_OPAQUE_10B:
        case VLC_CODEC_VAAPI_420_10BPP:
            return pi_allowed_chromas_yuv10;
        default:
            return pi_allowed_chromas_yuv;
    }
}