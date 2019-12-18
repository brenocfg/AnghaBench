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
struct TYPE_8__ {int rate; } ;
struct wlr_keyboard {TYPE_4__ repeat_info; } ;
struct sway_keyboard {scalar_t__ repeat_binding; TYPE_3__* seat_device; int /*<<< orphan*/  key_repeat_source; } ;
struct TYPE_7__ {int /*<<< orphan*/  sway_seat; TYPE_2__* input_device; } ;
struct TYPE_6__ {TYPE_1__* wlr_device; } ;
struct TYPE_5__ {struct wlr_keyboard* keyboard; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_DEBUG ; 
 int /*<<< orphan*/  seat_execute_command (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  transaction_commit_dirty () ; 
 scalar_t__ wl_event_source_timer_update (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int handle_keyboard_repeat(void *data) {
	struct sway_keyboard *keyboard = (struct sway_keyboard *)data;
	struct wlr_keyboard *wlr_device =
			keyboard->seat_device->input_device->wlr_device->keyboard;
	if (keyboard->repeat_binding) {
		if (wlr_device->repeat_info.rate > 0) {
			// We queue the next event first, as the command might cancel it
			if (wl_event_source_timer_update(keyboard->key_repeat_source,
					1000 / wlr_device->repeat_info.rate) < 0) {
				sway_log(SWAY_DEBUG, "failed to update key repeat timer");
			}
		}

		seat_execute_command(keyboard->seat_device->sway_seat,
				keyboard->repeat_binding);
		transaction_commit_dirty();
	}
	return 0;
}