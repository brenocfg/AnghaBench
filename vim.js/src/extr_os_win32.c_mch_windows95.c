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
 scalar_t__ VER_PLATFORM_WIN32_WINDOWS ; 
 scalar_t__ g_PlatformId ; 

int
mch_windows95(void)
{
    return g_PlatformId == VER_PLATFORM_WIN32_WINDOWS;
}