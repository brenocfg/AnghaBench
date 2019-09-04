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
struct wlr_input_device {int dummy; } ;
struct sway_input_device {struct wlr_input_device* wlr_device; } ;
struct libinput_device {int dummy; } ;
struct input_config {scalar_t__ send_events; int /*<<< orphan*/  identifier; } ;

/* Variables and functions */
 scalar_t__ INT_MIN ; 
 int /*<<< orphan*/  SWAY_DEBUG ; 
 struct input_config* input_device_get_config (struct sway_input_device*) ; 
 int /*<<< orphan*/  libinput_device_config_send_events_set_mode (struct libinput_device*,scalar_t__) ; 
 int /*<<< orphan*/  log_libinput_config_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  wlr_input_device_is_libinput (struct wlr_input_device*) ; 
 struct libinput_device* wlr_libinput_get_device_handle (struct wlr_input_device*) ; 

__attribute__((used)) static void input_manager_libinput_config_keyboard(
		struct sway_input_device *input_device) {
	struct wlr_input_device *wlr_device = input_device->wlr_device;
	struct input_config *ic = input_device_get_config(input_device);
	struct libinput_device *libinput_device;

	if (!ic || !wlr_input_device_is_libinput(wlr_device)) {
		return;
	}

	libinput_device = wlr_libinput_get_device_handle(wlr_device);
	sway_log(SWAY_DEBUG, "input_manager_libinput_config_keyboard(%s)",
		ic->identifier);

	if (ic->send_events != INT_MIN) {
		sway_log(SWAY_DEBUG, "libinput_config_keyboard(%s) send_events_set_mode(%d)",
			ic->identifier, ic->send_events);
		log_libinput_config_status(libinput_device_config_send_events_set_mode(
					libinput_device, ic->send_events));
	}
}