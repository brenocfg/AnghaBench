#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* window; } ;
typedef  TYPE_3__ vlc_vk_t ;
struct TYPE_5__ {int /*<<< orphan*/  anativewindow; } ;
struct TYPE_6__ {TYPE_1__ handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  AWindowHandler_releaseANativeWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AWindow_Video ; 

void vlc_vk_ClosePlatform(vlc_vk_t *vk)
{
    AWindowHandler_releaseANativeWindow(vk->window->handle.anativewindow,
                                        AWindow_Video);
}