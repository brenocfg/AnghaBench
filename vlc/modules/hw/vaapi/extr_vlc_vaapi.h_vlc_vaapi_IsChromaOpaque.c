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
 int VLC_CODEC_VAAPI_420 ; 
 int VLC_CODEC_VAAPI_420_10BPP ; 

__attribute__((used)) static inline bool
vlc_vaapi_IsChromaOpaque(int i_vlc_chroma)
{
    return i_vlc_chroma == VLC_CODEC_VAAPI_420
        || i_vlc_chroma == VLC_CODEC_VAAPI_420_10BPP;
}