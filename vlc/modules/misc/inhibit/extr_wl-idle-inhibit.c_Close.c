#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  wl; } ;
struct TYPE_8__ {TYPE_1__ display; } ;
typedef  TYPE_2__ vout_window_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_9__ {TYPE_4__* p_sys; } ;
typedef  TYPE_3__ vlc_inhibit_t ;
struct TYPE_10__ {int /*<<< orphan*/  eventq; int /*<<< orphan*/  manager; int /*<<< orphan*/ * inhibitor; } ;
typedef  TYPE_4__ vlc_inhibit_sys_t ;

/* Variables and functions */
 TYPE_2__* vlc_inhibit_GetWindow (TYPE_3__*) ; 
 int /*<<< orphan*/  wl_display_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_event_queue_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zwp_idle_inhibit_manager_v1_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zwp_idle_inhibitor_v1_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Close(vlc_object_t *obj)
{
    vlc_inhibit_t *ih = (vlc_inhibit_t *)obj;
    vlc_inhibit_sys_t *sys = ih->p_sys;
    vout_window_t *wnd = vlc_inhibit_GetWindow(ih);

    if (sys->inhibitor != NULL)
        zwp_idle_inhibitor_v1_destroy(sys->inhibitor);

    zwp_idle_inhibit_manager_v1_destroy(sys->manager);
    wl_display_flush(wnd->display.wl);
    wl_event_queue_destroy(sys->eventq);
}