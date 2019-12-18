#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_5__* sys; } ;
typedef  TYPE_4__ vout_display_t ;
struct TYPE_13__ {scalar_t__ active_buffers; int /*<<< orphan*/  eventq; int /*<<< orphan*/  shm; int /*<<< orphan*/ * viewporter; int /*<<< orphan*/ * viewport; TYPE_3__* embed; } ;
typedef  TYPE_5__ vout_display_sys_t ;
struct wl_surface {int dummy; } ;
struct wl_display {int dummy; } ;
struct TYPE_10__ {struct wl_surface* wl; } ;
struct TYPE_9__ {struct wl_display* wl; } ;
struct TYPE_11__ {TYPE_2__ handle; TYPE_1__ display; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_5__*) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_4__*,char*,...) ; 
 int /*<<< orphan*/  wl_display_flush (struct wl_display*) ; 
 int /*<<< orphan*/  wl_display_roundtrip_queue (struct wl_display*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_event_queue_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_shm_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_surface_attach (struct wl_surface*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_surface_commit (struct wl_surface*) ; 
 int /*<<< orphan*/  wp_viewport_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wp_viewporter_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Close(vout_display_t *vd)
{
    vout_display_sys_t *sys = vd->sys;
    struct wl_display *display = sys->embed->display.wl;
    struct wl_surface *surface = sys->embed->handle.wl;

    wl_surface_attach(surface, NULL, 0, 0);
    wl_surface_commit(surface);

    /* Wait until all picture buffers are released by the server */
    while (sys->active_buffers > 0) {
        msg_Dbg(vd, "%zu buffer(s) still active", sys->active_buffers);
        wl_display_roundtrip_queue(display, sys->eventq);
    }
    msg_Dbg(vd, "no active buffers left");

    if (sys->viewport != NULL)
        wp_viewport_destroy(sys->viewport);
    if (sys->viewporter != NULL)
        wp_viewporter_destroy(sys->viewporter);
    wl_shm_destroy(sys->shm);
    wl_display_flush(display);
    wl_event_queue_destroy(sys->eventq);
    free(sys);
}