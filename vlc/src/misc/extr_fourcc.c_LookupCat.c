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
#define  AUDIO_ES 130 
 scalar_t__ LookupAudio (scalar_t__,char const**) ; 
 scalar_t__ LookupSpu (scalar_t__,char const**) ; 
 scalar_t__ LookupVideo (scalar_t__,char const**) ; 
#define  SPU_ES 129 
#define  VIDEO_ES 128 

__attribute__((used)) static vlc_fourcc_t LookupCat(vlc_fourcc_t fourcc, const char **restrict dsc,
                              int cat)
{
    switch (cat)
    {
        case VIDEO_ES:
            return LookupVideo(fourcc, dsc);
        case AUDIO_ES:
            return LookupAudio(fourcc, dsc);
        case SPU_ES:
            return LookupSpu(fourcc, dsc);
    }

    vlc_fourcc_t ret = LookupVideo(fourcc, dsc);
    if (!ret)
        ret = LookupAudio(fourcc, dsc);
    if (!ret)
        ret = LookupSpu(fourcc, dsc);
    return ret;
}