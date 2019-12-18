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
 size_t ARRAY_SIZE (scalar_t__ const**) ; 
#define  VLC_CODEC_I420 135 
#define  VLC_CODEC_I422 134 
#define  VLC_CODEC_I440 133 
#define  VLC_CODEC_I444 132 
#define  VLC_CODEC_J420 131 
#define  VLC_CODEC_J422 130 
#define  VLC_CODEC_J440 129 
#define  VLC_CODEC_J444 128 

__attribute__((used)) static bool chroma_compatible(vlc_fourcc_t a, vlc_fourcc_t b)
{
    static const vlc_fourcc_t compat_lists[][2] = {
        {VLC_CODEC_J420, VLC_CODEC_I420},
        {VLC_CODEC_J422, VLC_CODEC_I422},
        {VLC_CODEC_J440, VLC_CODEC_I440},
        {VLC_CODEC_J444, VLC_CODEC_I444},
    };

    if (a == b)
        return true;

    for (size_t i = 0; i < ARRAY_SIZE(compat_lists); i++) {
        if ((a == compat_lists[i][0] || a == compat_lists[i][1]) &&
            (b == compat_lists[i][0] || b == compat_lists[i][1]))
            return true;
    }
    return false;
}