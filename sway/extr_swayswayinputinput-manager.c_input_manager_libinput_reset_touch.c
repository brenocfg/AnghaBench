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
typedef  int /*<<< orphan*/  uint32_t ;
struct wlr_input_device {int dummy; } ;
struct sway_input_device {int /*<<< orphan*/  identifier; struct wlr_input_device* wlr_device; } ;
struct libinput_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_DEBUG ; 
 int /*<<< orphan*/  libinput_device_config_send_events_get_default_mode (struct libinput_device*) ; 
 int /*<<< orphan*/  libinput_device_config_send_events_set_mode (struct libinput_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_libinput_config_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlr_input_device_is_libinput (struct wlr_input_device*) ; 
 struct libinput_device* wlr_libinput_get_device_handle (struct wlr_input_device*) ; 

__attribute__((used)) static void input_manager_libinput_reset_touch(
		struct sway_input_device *input_device) {
	struct wlr_input_device *wlr_device = input_device->wlr_device;
	struct libinput_device *libinput_device;

	if (!wlr_input_device_is_libinput(wlr_device)) {
		return;
	}

	libinput_device = wlr_libinput_get_device_handle(wlr_device);

	uint32_t send_events =
		libinput_device_config_send_events_get_default_mode(libinput_device);
	sway_log(SWAY_DEBUG, "libinput_reset_touch(%s) send_events_set_mode(%d)",
		input_device->identifier, send_events);
	log_libinput_config_status(libinput_device_config_send_events_set_mode(
				libinput_device, send_events));
}