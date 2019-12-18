#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  wl; } ;
struct TYPE_9__ {TYPE_1__ handle; } ;
typedef  TYPE_2__ vout_window_t ;
struct TYPE_10__ {TYPE_4__* p_sys; } ;
typedef  TYPE_3__ vlc_inhibit_t ;
struct TYPE_11__ {int /*<<< orphan*/  manager; int /*<<< orphan*/ * inhibitor; } ;
typedef  TYPE_4__ vlc_inhibit_sys_t ;

/* Variables and functions */
 unsigned int VLC_INHIBIT_DISPLAY ; 
 TYPE_2__* vlc_inhibit_GetWindow (TYPE_3__*) ; 
 int /*<<< orphan*/ * zwp_idle_inhibit_manager_v1_create_inhibitor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zwp_idle_inhibitor_v1_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Inhibit (vlc_inhibit_t *ih, unsigned mask)
{
    vout_window_t *wnd = vlc_inhibit_GetWindow(ih);
    vlc_inhibit_sys_t *sys = ih->p_sys;
    bool suspend = (mask & VLC_INHIBIT_DISPLAY) != 0;

    if (sys->inhibitor != NULL) {
        zwp_idle_inhibitor_v1_destroy(sys->inhibitor);
        sys->inhibitor = NULL;
    }

    if (suspend)
        sys->inhibitor = zwp_idle_inhibit_manager_v1_create_inhibitor(
            sys->manager, wnd->handle.wl);

}