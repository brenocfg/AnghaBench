#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sway_seat_device {TYPE_2__* input_device; int /*<<< orphan*/  keyboard; } ;
struct sway_seat {int /*<<< orphan*/  wlr_seat; } ;
struct sway_node {TYPE_1__* sway_container; } ;
struct TYPE_6__ {int /*<<< orphan*/  surface; } ;
struct TYPE_5__ {int /*<<< orphan*/  wlr_device; } ;
struct TYPE_4__ {TYPE_3__* view; } ;

/* Variables and functions */
 scalar_t__ node_is_view (struct sway_node*) ; 
 struct sway_node* seat_get_focus (struct sway_seat*) ; 
 int /*<<< orphan*/  seat_keyboard_notify_enter (struct sway_seat*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sway_keyboard_configure (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sway_keyboard_create (struct sway_seat*,struct sway_seat_device*) ; 
 int /*<<< orphan*/  wlr_seat_keyboard_clear_focus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlr_seat_set_keyboard (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void seat_configure_keyboard(struct sway_seat *seat,
		struct sway_seat_device *seat_device) {
	if (!seat_device->keyboard) {
		sway_keyboard_create(seat, seat_device);
	}
	sway_keyboard_configure(seat_device->keyboard);
	wlr_seat_set_keyboard(seat->wlr_seat,
			seat_device->input_device->wlr_device);
	struct sway_node *focus = seat_get_focus(seat);
	if (focus && node_is_view(focus)) {
		// force notify reenter to pick up the new configuration
		wlr_seat_keyboard_clear_focus(seat->wlr_seat);
		seat_keyboard_notify_enter(seat, focus->sway_container->view->surface);
	}
}