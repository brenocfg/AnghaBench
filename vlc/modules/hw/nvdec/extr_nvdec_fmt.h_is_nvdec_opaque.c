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
typedef  scalar_t__ vlc_fourcc_t ;

/* Variables and functions */
 scalar_t__ VLC_CODEC_NVDEC_OPAQUE ; 
 scalar_t__ VLC_CODEC_NVDEC_OPAQUE_10B ; 
 scalar_t__ VLC_CODEC_NVDEC_OPAQUE_16B ; 

__attribute__((used)) static inline bool is_nvdec_opaque(vlc_fourcc_t fourcc)
{
    return fourcc == VLC_CODEC_NVDEC_OPAQUE ||
           fourcc == VLC_CODEC_NVDEC_OPAQUE_10B ||
           fourcc == VLC_CODEC_NVDEC_OPAQUE_16B;
}