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
 int GetWBE (void const*) ; 
#define  VLC_CODEC_THEORA 129 
#define  VLC_CODEC_VORBIS 128 

__attribute__((used)) static inline bool xiph_IsLavcFormat(const void *extra, unsigned i_extra,
                                     vlc_fourcc_t i_codec)
{
    switch(i_codec)
    {
        case VLC_CODEC_VORBIS:
            return i_extra >= 6 && GetWBE(extra) == 30;
        case VLC_CODEC_THEORA:
            return i_extra >= 6 && GetWBE(extra) == 42;
        default:
            return false;
    }
}