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
 double libinput_device_config_accel_get_speed (struct libinput_device*) ; 
 int /*<<< orphan*/  libinput_device_config_accel_is_available (struct libinput_device*) ; 
 int /*<<< orphan*/  libinput_device_config_accel_set_speed (struct libinput_device*,double) ; 
 int /*<<< orphan*/  log_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,double) ; 

__attribute__((used)) static bool set_accel_speed(struct libinput_device *device, double speed) {
	if (!libinput_device_config_accel_is_available(device) ||
			libinput_device_config_accel_get_speed(device) == speed) {
		return false;
	}
	sway_log(SWAY_DEBUG, "accel_set_speed(%f)", speed);
	log_status(libinput_device_config_accel_set_speed(device, speed));
	return true;
}