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

/* Variables and functions */
 int /*<<< orphan*/  SWAY_DEBUG ; 
 int libinput_device_config_left_handed_get (struct libinput_device*) ; 
 int /*<<< orphan*/  libinput_device_config_left_handed_is_available (struct libinput_device*) ; 
 int /*<<< orphan*/  libinput_device_config_left_handed_set (struct libinput_device*,int) ; 
 int /*<<< orphan*/  log_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static bool set_left_handed(struct libinput_device *device, bool left) {
	if (!libinput_device_config_left_handed_is_available(device) ||
			libinput_device_config_left_handed_get(device) == left) {
		return false;
	}
	sway_log(SWAY_DEBUG, "left_handed_set(%d)", left);
	log_status(libinput_device_config_left_handed_set(device, left));
	return true;
}