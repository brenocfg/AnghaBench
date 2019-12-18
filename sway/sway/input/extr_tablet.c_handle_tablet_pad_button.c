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
struct wlr_event_tablet_pad_button {scalar_t__ state; int /*<<< orphan*/  time_msec; int /*<<< orphan*/  button; int /*<<< orphan*/  mode; int /*<<< orphan*/  group; } ;
struct wl_listener {int dummy; } ;
struct sway_tablet_pad {int /*<<< orphan*/  tablet_v2_pad; int /*<<< orphan*/  current_surface; } ;
typedef  enum zwp_tablet_pad_v2_button_state { ____Placeholder_zwp_tablet_pad_v2_button_state } zwp_tablet_pad_v2_button_state ;

/* Variables and functions */
 int /*<<< orphan*/  button ; 
 struct sway_tablet_pad* pad ; 
 struct sway_tablet_pad* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlr_tablet_v2_tablet_pad_notify_button (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wlr_tablet_v2_tablet_pad_notify_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_tablet_pad_button(struct wl_listener *listener, void *data) {
	struct sway_tablet_pad *pad = wl_container_of(listener, pad, button);
	struct wlr_event_tablet_pad_button *event = data;

	if (!pad->current_surface) {
		return;
	}

	wlr_tablet_v2_tablet_pad_notify_mode(pad->tablet_v2_pad,
		event->group, event->mode, event->time_msec);

	wlr_tablet_v2_tablet_pad_notify_button(pad->tablet_v2_pad,
		event->button, event->time_msec,
		(enum zwp_tablet_pad_v2_button_state)event->state);
}