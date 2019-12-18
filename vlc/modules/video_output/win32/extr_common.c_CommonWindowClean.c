#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ event; } ;
typedef  TYPE_1__ vout_display_sys_win32_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  CommonChangeThumbnailClip (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  EventThreadDestroy (scalar_t__) ; 
 int /*<<< orphan*/  EventThreadStop (scalar_t__) ; 

void CommonWindowClean(vlc_object_t *obj, vout_display_sys_win32_t *sys)
{
    if (sys->event) {
        CommonChangeThumbnailClip(obj, sys, false);
        EventThreadStop(sys->event);
        EventThreadDestroy(sys->event);
    }
}