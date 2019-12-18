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
typedef  int cudaVideoChromaFormat ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_CODEC_NV12 ; 
 int /*<<< orphan*/  VLC_CODEC_P010 ; 
 int /*<<< orphan*/  VLC_CODEC_P016 ; 
#define  cudaVideoChromaFormat_420 128 

__attribute__((used)) static vlc_fourcc_t MapSurfaceChroma(cudaVideoChromaFormat chroma, unsigned bitDepth)
{
    switch (chroma) {
        case cudaVideoChromaFormat_420:
            if (bitDepth <= 8)
                return VLC_CODEC_NV12;
            if (bitDepth <= 10)
                return VLC_CODEC_P010;
            return VLC_CODEC_P016;
        // case cudaVideoChromaFormat_444:
        //     if (bitDepth <= 8)
        //         return VLC_CODEC_I444;
        //     return VLC_CODEC_I444_16L;
        default:
            return 0;
    }
}