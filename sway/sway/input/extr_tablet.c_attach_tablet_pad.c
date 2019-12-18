#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  notify; int /*<<< orphan*/  link; } ;
struct sway_tablet_pad {TYPE_8__ tablet_destroy; struct sway_tablet* tablet; TYPE_6__* seat_device; } ;
struct sway_tablet {TYPE_4__* seat_device; } ;
struct TYPE_15__ {TYPE_5__* wlr_device; } ;
struct TYPE_14__ {TYPE_7__* input_device; } ;
struct TYPE_13__ {int /*<<< orphan*/  name; } ;
struct TYPE_12__ {TYPE_3__* input_device; } ;
struct TYPE_11__ {TYPE_2__* wlr_device; } ;
struct TYPE_9__ {int /*<<< orphan*/  destroy; } ;
struct TYPE_10__ {TYPE_1__ events; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_DEBUG ; 
 int /*<<< orphan*/  handle_pad_tablet_destroy ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_list_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_signal_add (int /*<<< orphan*/ *,TYPE_8__*) ; 

__attribute__((used)) static void attach_tablet_pad(struct sway_tablet_pad *tablet_pad,
		struct sway_tablet *tablet) {
	sway_log(SWAY_DEBUG, "Attaching tablet pad \"%s\" to tablet tool \"%s\"",
		tablet_pad->seat_device->input_device->wlr_device->name,
		tablet->seat_device->input_device->wlr_device->name);

	tablet_pad->tablet = tablet;

	wl_list_remove(&tablet_pad->tablet_destroy.link);
	tablet_pad->tablet_destroy.notify = handle_pad_tablet_destroy;
	wl_signal_add(&tablet->seat_device->input_device->wlr_device->events.destroy,
		&tablet_pad->tablet_destroy);
}