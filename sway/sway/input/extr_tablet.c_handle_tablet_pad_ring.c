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
struct wlr_event_tablet_pad_ring {scalar_t__ source; int /*<<< orphan*/  time_msec; int /*<<< orphan*/  position; int /*<<< orphan*/  ring; } ;
struct wl_listener {int dummy; } ;
struct sway_tablet_pad {int /*<<< orphan*/  tablet_v2_pad; int /*<<< orphan*/  current_surface; } ;

/* Variables and functions */
 scalar_t__ WLR_TABLET_PAD_RING_SOURCE_FINGER ; 
 struct sway_tablet_pad* pad ; 
 int /*<<< orphan*/  ring ; 
 struct sway_tablet_pad* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlr_tablet_v2_tablet_pad_notify_ring (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_tablet_pad_ring(struct wl_listener *listener, void *data) {
	struct sway_tablet_pad *pad = wl_container_of(listener, pad, ring);
	struct wlr_event_tablet_pad_ring *event = data;

	if (!pad->current_surface) {
		return;
	}

	wlr_tablet_v2_tablet_pad_notify_ring(pad->tablet_v2_pad,
		event->ring, event->position,
		event->source == WLR_TABLET_PAD_RING_SOURCE_FINGER,
		event->time_msec);
}