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
typedef  int /*<<< orphan*/  filter_t ;

/* Variables and functions */
 int /*<<< orphan*/  ANDROID_FALLBACK_FONTS ; 
 int /*<<< orphan*/  ANDROID_SYSTEM_FONTS_LEGACY ; 
 int /*<<< orphan*/  ANDROID_SYSTEM_FONTS_NOUGAT ; 
 int /*<<< orphan*/  ANDROID_VENDOR_FONTS ; 
 scalar_t__ Android_ParseSystemFonts (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ VLC_ENOMEM ; 
 scalar_t__ VLC_SUCCESS ; 

int Android_Prepare( filter_t *p_filter )
{
    if( Android_ParseSystemFonts( p_filter, ANDROID_SYSTEM_FONTS_NOUGAT, true ) != VLC_SUCCESS )
    {
        if( Android_ParseSystemFonts( p_filter, ANDROID_SYSTEM_FONTS_LEGACY, false ) == VLC_ENOMEM )
            return VLC_ENOMEM;
        if( Android_ParseSystemFonts( p_filter, ANDROID_FALLBACK_FONTS, false ) == VLC_ENOMEM )
            return VLC_ENOMEM;
        if( Android_ParseSystemFonts( p_filter, ANDROID_VENDOR_FONTS, false ) == VLC_ENOMEM )
            return VLC_ENOMEM;
    }

    return VLC_SUCCESS;
}