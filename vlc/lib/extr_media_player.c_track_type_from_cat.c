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
typedef  enum es_format_category_e { ____Placeholder_es_format_category_e } es_format_category_e ;

/* Variables and functions */
#define  AUDIO_ES 130 
#define  SPU_ES 129 
#define  VIDEO_ES 128 
 int libvlc_track_audio ; 
 int libvlc_track_text ; 
 int libvlc_track_unknown ; 
 int libvlc_track_video ; 

__attribute__((used)) static int
track_type_from_cat(enum es_format_category_e cat)
{
    switch (cat)
    {
        case VIDEO_ES:
            return libvlc_track_video;
        case AUDIO_ES:
            return libvlc_track_audio;
        case SPU_ES:
            return libvlc_track_text;
        default:
            return libvlc_track_unknown;
    }
}