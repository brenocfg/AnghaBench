#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  p_awh; } ;
typedef  TYPE_1__ vout_display_sys_t ;
struct TYPE_6__ {int /*<<< orphan*/ * p_surface; int /*<<< orphan*/  id; } ;
typedef  TYPE_2__ android_window ;

/* Variables and functions */
 int /*<<< orphan*/  AWindowHandler_releaseANativeWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void AndroidWindow_DisconnectSurface(vout_display_sys_t *sys,
                                            android_window *p_window)
{
    if (p_window->p_surface) {
        AWindowHandler_releaseANativeWindow(sys->p_awh, p_window->id);
        p_window->p_surface = NULL;
    }
}