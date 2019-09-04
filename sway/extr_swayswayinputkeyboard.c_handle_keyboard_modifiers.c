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
typedef  int /*<<< orphan*/  uint32_t ;
struct wlr_seat {int dummy; } ;
struct wlr_input_device {TYPE_4__* keyboard; } ;
struct wl_listener {int dummy; } ;
struct sway_keyboard {TYPE_3__* seat_device; } ;
struct TYPE_8__ {int /*<<< orphan*/  modifiers; } ;
struct TYPE_7__ {TYPE_2__* input_device; TYPE_1__* sway_seat; } ;
struct TYPE_6__ {struct wlr_input_device* wlr_device; } ;
struct TYPE_5__ {struct wlr_seat* wlr_seat; } ;

/* Variables and functions */
 int /*<<< orphan*/  determine_bar_visibility (int /*<<< orphan*/ ) ; 
 struct sway_keyboard* keyboard ; 
 int /*<<< orphan*/  keyboard_modifiers ; 
 struct sway_keyboard* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlr_keyboard_get_modifiers (TYPE_4__*) ; 
 int /*<<< orphan*/  wlr_seat_keyboard_notify_modifiers (struct wlr_seat*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wlr_seat_set_keyboard (struct wlr_seat*,struct wlr_input_device*) ; 

__attribute__((used)) static void handle_keyboard_modifiers(struct wl_listener *listener,
		void *data) {
	struct sway_keyboard *keyboard =
		wl_container_of(listener, keyboard, keyboard_modifiers);
	struct wlr_seat *wlr_seat = keyboard->seat_device->sway_seat->wlr_seat;
	struct wlr_input_device *wlr_device =
		keyboard->seat_device->input_device->wlr_device;
	wlr_seat_set_keyboard(wlr_seat, wlr_device);
	wlr_seat_keyboard_notify_modifiers(wlr_seat, &wlr_device->keyboard->modifiers);

	uint32_t modifiers = wlr_keyboard_get_modifiers(wlr_device->keyboard);
	determine_bar_visibility(modifiers);
}