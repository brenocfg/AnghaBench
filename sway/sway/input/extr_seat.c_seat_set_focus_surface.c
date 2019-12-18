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
struct wlr_surface {int dummy; } ;
struct sway_seat {int has_focus; } ;
struct sway_node {int dummy; } ;

/* Variables and functions */
 struct sway_node* seat_get_focus (struct sway_seat*) ; 
 int /*<<< orphan*/  seat_keyboard_notify_enter (struct sway_seat*,struct wlr_surface*) ; 
 int /*<<< orphan*/  seat_send_unfocus (struct sway_node*,struct sway_seat*) ; 
 int /*<<< orphan*/  seat_tablet_pads_notify_enter (struct sway_seat*,struct wlr_surface*) ; 

void seat_set_focus_surface(struct sway_seat *seat,
		struct wlr_surface *surface, bool unfocus) {
	if (seat->has_focus && unfocus) {
		struct sway_node *focus = seat_get_focus(seat);
		seat_send_unfocus(focus, seat);
		seat->has_focus = false;
	}
	seat_keyboard_notify_enter(seat, surface);
	seat_tablet_pads_notify_enter(seat, surface);
}