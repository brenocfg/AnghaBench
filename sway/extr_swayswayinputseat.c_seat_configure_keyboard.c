#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct wlr_keyboard {int /*<<< orphan*/  modifiers; int /*<<< orphan*/  num_keycodes; int /*<<< orphan*/  keycodes; } ;
struct sway_seat_device {TYPE_3__* input_device; int /*<<< orphan*/  keyboard; } ;
struct sway_seat {int /*<<< orphan*/  wlr_seat; } ;
struct sway_node {TYPE_2__* sway_container; } ;
struct TYPE_8__ {struct wlr_keyboard* keyboard; } ;
struct TYPE_7__ {TYPE_4__* wlr_device; } ;
struct TYPE_6__ {TYPE_1__* view; } ;
struct TYPE_5__ {int /*<<< orphan*/  surface; } ;

/* Variables and functions */
 scalar_t__ node_is_view (struct sway_node*) ; 
 struct sway_node* seat_get_focus (struct sway_seat*) ; 
 int /*<<< orphan*/  sway_keyboard_configure (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sway_keyboard_create (struct sway_seat*,struct sway_seat_device*) ; 
 int /*<<< orphan*/  wlr_seat_keyboard_clear_focus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlr_seat_keyboard_notify_enter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wlr_seat_set_keyboard (int /*<<< orphan*/ ,TYPE_4__*) ; 

__attribute__((used)) static void seat_configure_keyboard(struct sway_seat *seat,
		struct sway_seat_device *seat_device) {
	if (!seat_device->keyboard) {
		sway_keyboard_create(seat, seat_device);
	}
	struct wlr_keyboard *wlr_keyboard =
		seat_device->input_device->wlr_device->keyboard;
	sway_keyboard_configure(seat_device->keyboard);
	wlr_seat_set_keyboard(seat->wlr_seat,
			seat_device->input_device->wlr_device);
	struct sway_node *focus = seat_get_focus(seat);
	if (focus && node_is_view(focus)) {
		// force notify reenter to pick up the new configuration
		wlr_seat_keyboard_clear_focus(seat->wlr_seat);
		wlr_seat_keyboard_notify_enter(seat->wlr_seat,
				focus->sway_container->view->surface, wlr_keyboard->keycodes,
				wlr_keyboard->num_keycodes, &wlr_keyboard->modifiers);
	}
}