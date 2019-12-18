#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  destroy; } ;
struct wlr_input_device {TYPE_1__ events; struct sway_input_device* data; } ;
struct wlr_virtual_keyboard_v1 {struct wlr_input_device input_device; } ;
struct wl_listener {int dummy; } ;
struct sway_seat {int dummy; } ;
struct sway_input_manager {int /*<<< orphan*/  devices; } ;
struct TYPE_4__ {int /*<<< orphan*/  notify; } ;
struct sway_input_device {TYPE_2__ device_destroy; int /*<<< orphan*/  identifier; int /*<<< orphan*/  link; struct wlr_input_device* wlr_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_DEBUG ; 
 struct sway_input_device* calloc (int,int) ; 
 int /*<<< orphan*/  handle_device_destroy ; 
 int /*<<< orphan*/  input_device_get_identifier (struct wlr_input_device*) ; 
 struct sway_input_manager* input_manager ; 
 struct sway_seat* input_manager_get_default_seat () ; 
 int /*<<< orphan*/  seat_add_device (struct sway_seat*,struct sway_input_device*) ; 
 int /*<<< orphan*/  sway_assert (struct sway_input_device*,char*) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtual_keyboard_new ; 
 struct sway_input_manager* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_list_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_signal_add (int /*<<< orphan*/ *,TYPE_2__*) ; 

void handle_virtual_keyboard(struct wl_listener *listener, void *data) {
	struct sway_input_manager *input_manager =
		wl_container_of(listener, input_manager, virtual_keyboard_new);
	struct wlr_virtual_keyboard_v1 *keyboard = data;
	struct wlr_input_device *device = &keyboard->input_device;

	struct sway_seat *seat = input_manager_get_default_seat();

	// TODO: The user might want this on a different seat
	struct sway_input_device *input_device =
		calloc(1, sizeof(struct sway_input_device));
	if (!sway_assert(input_device, "could not allocate input device")) {
		return;
	}
	device->data = input_device;

	input_device->wlr_device = device;
	input_device->identifier = input_device_get_identifier(device);
	wl_list_insert(&input_manager->devices, &input_device->link);

	sway_log(SWAY_DEBUG, "adding virtual keyboard: '%s'",
		input_device->identifier);

	wl_signal_add(&device->events.destroy, &input_device->device_destroy);
	input_device->device_destroy.notify = handle_device_destroy;

	seat_add_device(seat, input_device);
}