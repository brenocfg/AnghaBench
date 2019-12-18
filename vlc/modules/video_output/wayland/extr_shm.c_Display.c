#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_5__* sys; } ;
typedef  TYPE_4__ vout_display_t ;
struct TYPE_11__ {int /*<<< orphan*/  eventq; TYPE_3__* embed; } ;
typedef  TYPE_5__ vout_display_sys_t ;
struct wl_surface {int dummy; } ;
struct wl_display {int dummy; } ;
typedef  int /*<<< orphan*/  picture_t ;
struct TYPE_8__ {struct wl_surface* wl; } ;
struct TYPE_7__ {struct wl_display* wl; } ;
struct TYPE_9__ {TYPE_2__ handle; TYPE_1__ display; } ;

/* Variables and functions */
 int /*<<< orphan*/  wl_display_roundtrip_queue (struct wl_display*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_surface_commit (struct wl_surface*) ; 

__attribute__((used)) static void Display(vout_display_t *vd, picture_t *pic)
{
    vout_display_sys_t *sys = vd->sys;
    struct wl_display *display = sys->embed->display.wl;
    struct wl_surface *surface = sys->embed->handle.wl;

    wl_surface_commit(surface);
    wl_display_roundtrip_queue(display, sys->eventq);

    (void) pic;
}