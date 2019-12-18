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
typedef  int /*<<< orphan*/  vlc_fourcc_t ;
typedef  enum PixelFormat { ____Placeholder_PixelFormat } PixelFormat ;

/* Variables and functions */
#define  AV_PIX_FMT_D3D11VA_VLD 138 
#define  AV_PIX_FMT_DXVA2_VLD 137 
#define  AV_PIX_FMT_VAAPI_VLD 136 
#define  AV_PIX_FMT_VDPAU 135 
#define  AV_PIX_FMT_YUV420P 134 
#define  AV_PIX_FMT_YUV420P10LE 133 
#define  AV_PIX_FMT_YUV422P 132 
#define  AV_PIX_FMT_YUV444P 131 
#define  AV_PIX_FMT_YUVJ420P 130 
#define  AV_PIX_FMT_YUVJ422P 129 
#define  AV_PIX_FMT_YUVJ444P 128 
 int /*<<< orphan*/  VLC_CODEC_D3D11_OPAQUE ; 
 int /*<<< orphan*/  VLC_CODEC_D3D11_OPAQUE_10B ; 
 int /*<<< orphan*/  VLC_CODEC_D3D9_OPAQUE ; 
 int /*<<< orphan*/  VLC_CODEC_D3D9_OPAQUE_10B ; 
 int /*<<< orphan*/  VLC_CODEC_VAAPI_420 ; 
 int /*<<< orphan*/  VLC_CODEC_VAAPI_420_10BPP ; 
 int /*<<< orphan*/  VLC_CODEC_VDPAU_VIDEO_420 ; 
 int /*<<< orphan*/  VLC_CODEC_VDPAU_VIDEO_422 ; 
 int /*<<< orphan*/  VLC_CODEC_VDPAU_VIDEO_444 ; 

vlc_fourcc_t vlc_va_GetChroma(enum PixelFormat hwfmt, enum PixelFormat swfmt)
{
    /* NOTE: At the time of writing this comment, the return value was only
     * used to probe support as decoder output. So incorrect values were not
     * fatal, especially not if a software format. */
    switch (hwfmt)
    {
        case AV_PIX_FMT_VAAPI_VLD:
            switch (swfmt)
            {
                case AV_PIX_FMT_YUVJ420P:
                case AV_PIX_FMT_YUV420P:
                    return VLC_CODEC_VAAPI_420;
                case AV_PIX_FMT_YUV420P10LE:
                    return VLC_CODEC_VAAPI_420_10BPP;
                default:
                    return 0;
            }
        case AV_PIX_FMT_DXVA2_VLD:
            switch (swfmt)
            {
                case AV_PIX_FMT_YUV420P10LE:
                    return VLC_CODEC_D3D9_OPAQUE_10B;
                case AV_PIX_FMT_YUVJ420P:
                case AV_PIX_FMT_YUV420P:
                    return VLC_CODEC_D3D9_OPAQUE;
                default:
                    return 0;
            }
            break;

        case AV_PIX_FMT_D3D11VA_VLD:
            switch (swfmt)
            {
                case AV_PIX_FMT_YUV420P10LE:
                    return VLC_CODEC_D3D11_OPAQUE_10B;
                case AV_PIX_FMT_YUVJ420P:
                case AV_PIX_FMT_YUV420P:
                    return VLC_CODEC_D3D11_OPAQUE;
                default:
                    return 0;
            }
        break;

        case AV_PIX_FMT_VDPAU:
            switch (swfmt)
            {
                case AV_PIX_FMT_YUVJ444P:
                case AV_PIX_FMT_YUV444P:
                    return VLC_CODEC_VDPAU_VIDEO_444;
                case AV_PIX_FMT_YUVJ422P:
                case AV_PIX_FMT_YUV422P:
                    return VLC_CODEC_VDPAU_VIDEO_422;
                case AV_PIX_FMT_YUVJ420P:
                case AV_PIX_FMT_YUV420P:
                    return VLC_CODEC_VDPAU_VIDEO_420;
                default:
                    return 0;
            }
            break;
        default:
            return 0;
    }
}