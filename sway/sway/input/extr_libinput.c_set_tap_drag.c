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
struct libinput_device {int dummy; } ;
typedef  enum libinput_config_drag_state { ____Placeholder_libinput_config_drag_state } libinput_config_drag_state ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_DEBUG ; 
 int libinput_device_config_tap_get_drag_enabled (struct libinput_device*) ; 
 scalar_t__ libinput_device_config_tap_get_finger_count (struct libinput_device*) ; 
 int /*<<< orphan*/  libinput_device_config_tap_set_drag_enabled (struct libinput_device*,int) ; 
 int /*<<< orphan*/  log_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static bool set_tap_drag(struct libinput_device *device,
		enum libinput_config_drag_state drag) {
	if (libinput_device_config_tap_get_finger_count(device) <= 0 ||
			libinput_device_config_tap_get_drag_enabled(device) == drag) {
		return false;
	}
	sway_log(SWAY_DEBUG, "tap_set_drag_enabled(%d)", drag);
	log_status(libinput_device_config_tap_set_drag_enabled(device, drag));
	return true;
}