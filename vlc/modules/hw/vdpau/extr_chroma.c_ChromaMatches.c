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
typedef  int /*<<< orphan*/  VdpChromaType ;

/* Variables and functions */
 int /*<<< orphan*/  VDP_CHROMA_TYPE_420 ; 
 int /*<<< orphan*/  VDP_CHROMA_TYPE_422 ; 
 int /*<<< orphan*/  VDP_CHROMA_TYPE_444 ; 
#define  VLC_CODEC_VDPAU_VIDEO_420 130 
#define  VLC_CODEC_VDPAU_VIDEO_422 129 
#define  VLC_CODEC_VDPAU_VIDEO_444 128 

__attribute__((used)) static bool ChromaMatches(VdpChromaType vdp_type, vlc_fourcc_t vlc_chroma)
{
    switch (vlc_chroma)
    {
        case VLC_CODEC_VDPAU_VIDEO_420:
            return vdp_type == VDP_CHROMA_TYPE_420;
        case VLC_CODEC_VDPAU_VIDEO_422:
            return vdp_type == VDP_CHROMA_TYPE_422;
        case VLC_CODEC_VDPAU_VIDEO_444:
            return vdp_type == VDP_CHROMA_TYPE_444;
        default:
            return false;
    }
}