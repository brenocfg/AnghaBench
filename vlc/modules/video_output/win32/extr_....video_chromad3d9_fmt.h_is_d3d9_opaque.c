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

/* Variables and functions */
#define  VLC_CODEC_D3D9_OPAQUE 129 
#define  VLC_CODEC_D3D9_OPAQUE_10B 128 

__attribute__((used)) static inline bool is_d3d9_opaque(vlc_fourcc_t chroma)
{
    switch (chroma)
    {
    case VLC_CODEC_D3D9_OPAQUE:
    case VLC_CODEC_D3D9_OPAQUE_10B:
        return true;
    default:
        return false;
    }
}