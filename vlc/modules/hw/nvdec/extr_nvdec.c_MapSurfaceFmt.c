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
typedef  int /*<<< orphan*/  cudaVideoSurfaceFormat ;

/* Variables and functions */
#define  VLC_CODEC_NV12 133 
#define  VLC_CODEC_NVDEC_OPAQUE 132 
#define  VLC_CODEC_NVDEC_OPAQUE_10B 131 
#define  VLC_CODEC_NVDEC_OPAQUE_16B 130 
#define  VLC_CODEC_P010 129 
#define  VLC_CODEC_P016 128 
 int /*<<< orphan*/  cudaVideoSurfaceFormat_NV12 ; 
 int /*<<< orphan*/  cudaVideoSurfaceFormat_P016 ; 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 

__attribute__((used)) static cudaVideoSurfaceFormat MapSurfaceFmt(int i_vlc_fourcc)
{
    switch (i_vlc_fourcc) {
        case VLC_CODEC_NVDEC_OPAQUE_10B:
        case VLC_CODEC_NVDEC_OPAQUE_16B:
        case VLC_CODEC_P010:
        case VLC_CODEC_P016:
            return cudaVideoSurfaceFormat_P016;
        case VLC_CODEC_NVDEC_OPAQUE:
        case VLC_CODEC_NV12:
            return cudaVideoSurfaceFormat_NV12;
        // case VLC_CODEC_I444:
        //     return cudaVideoSurfaceFormat_YUV444;
        // case VLC_CODEC_I444_16L:
        //      return cudaVideoSurfaceFormat_YUV444_16Bit;
        default:             vlc_assert_unreachable();
    }
}