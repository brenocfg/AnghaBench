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
typedef  int vlc_fourcc_t ;
typedef  int /*<<< orphan*/  VdpYCbCrFormat ;
typedef  int /*<<< orphan*/  VdpChromaType ;

/* Variables and functions */
 int /*<<< orphan*/  VDP_CHROMA_TYPE_420 ; 
 int /*<<< orphan*/  VDP_CHROMA_TYPE_422 ; 
 int /*<<< orphan*/  VDP_CHROMA_TYPE_444 ; 
 int /*<<< orphan*/  VDP_YCBCR_FORMAT_NV12 ; 
 int /*<<< orphan*/  VDP_YCBCR_FORMAT_UYVY ; 
 int /*<<< orphan*/  VDP_YCBCR_FORMAT_YUYV ; 
 int /*<<< orphan*/  VDP_YCBCR_FORMAT_YV12 ; 
#define  VLC_CODEC_I420 136 
#define  VLC_CODEC_I422 135 
#define  VLC_CODEC_I444 134 
#define  VLC_CODEC_NV12 133 
#define  VLC_CODEC_NV16 132 
#define  VLC_CODEC_NV24 131 
#define  VLC_CODEC_UYVY 130 
#define  VLC_CODEC_YUYV 129 
#define  VLC_CODEC_YV12 128 

__attribute__((used)) static inline
bool vlc_fourcc_to_vdp_ycc(vlc_fourcc_t fourcc,
                 VdpChromaType *restrict type, VdpYCbCrFormat *restrict format)
{
    switch (fourcc)
    {
        case VLC_CODEC_I420:
        case VLC_CODEC_YV12:
            *type = VDP_CHROMA_TYPE_420;
            *format = VDP_YCBCR_FORMAT_YV12;
            break;
        case VLC_CODEC_NV12:
            *type = VDP_CHROMA_TYPE_420;
            *format = VDP_YCBCR_FORMAT_NV12;
            break;
        case VLC_CODEC_I422:
            *type = VDP_CHROMA_TYPE_422;
            *format = VDP_YCBCR_FORMAT_YV12;
            break;
        case VLC_CODEC_NV16:
            *type = VDP_CHROMA_TYPE_422;
            *format = VDP_YCBCR_FORMAT_NV12;
            break;
        case VLC_CODEC_YUYV:
            *type = VDP_CHROMA_TYPE_422;
            *format = VDP_YCBCR_FORMAT_YUYV;
            break;
        case VLC_CODEC_UYVY:
            *type = VDP_CHROMA_TYPE_422;
            *format = VDP_YCBCR_FORMAT_UYVY;
            break;
        case VLC_CODEC_I444:
            *type = VDP_CHROMA_TYPE_444;
            *format = VDP_YCBCR_FORMAT_YV12;
            break;
        case VLC_CODEC_NV24:
            *type = VDP_CHROMA_TYPE_444;
            *format = VDP_YCBCR_FORMAT_NV12;
            break;
        default:
            return false;
    }
    return true;
}