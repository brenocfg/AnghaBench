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
struct wlr_event_tablet_pad_strip {scalar_t__ source; int /*<<< orphan*/  time_msec; int /*<<< orphan*/  position; int /*<<< orphan*/  strip; } ;
struct wl_listener {int dummy; } ;
struct sway_tablet_pad {int /*<<< orphan*/  tablet_v2_pad; int /*<<< orphan*/  current_surface; } ;

/* Variables and functions */
 scalar_t__ WLR_TABLET_PAD_STRIP_SOURCE_FINGER ; 
 struct sway_tablet_pad* pad ; 
 int /*<<< orphan*/  strip ; 
 struct sway_tablet_pad* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlr_tablet_v2_tablet_pad_notify_strip (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_tablet_pad_strip(struct wl_listener *listener, void *data) {
	struct sway_tablet_pad *pad = wl_container_of(listener, pad, strip);
	struct wlr_event_tablet_pad_strip *event = data;

	if (!pad->current_surface) {
		return;
	}

	wlr_tablet_v2_tablet_pad_notify_strip(pad->tablet_v2_pad,
		event->strip, event->position,
		event->source == WLR_TABLET_PAD_STRIP_SOURCE_FINGER,
		event->time_msec);
}