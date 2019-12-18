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
typedef  enum libinput_config_accel_profile { ____Placeholder_libinput_config_accel_profile } libinput_config_accel_profile ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_DEBUG ; 
 int libinput_device_config_accel_get_profile (struct libinput_device*) ; 
 int /*<<< orphan*/  libinput_device_config_accel_is_available (struct libinput_device*) ; 
 int /*<<< orphan*/  libinput_device_config_accel_set_profile (struct libinput_device*,int) ; 
 int /*<<< orphan*/  log_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static bool set_accel_profile(struct libinput_device *device,
		enum libinput_config_accel_profile profile) {
	if (!libinput_device_config_accel_is_available(device) ||
			libinput_device_config_accel_get_profile(device) == profile) {
		return false;
	}
	sway_log(SWAY_DEBUG, "accel_set_profile(%d)", profile);
	log_status(libinput_device_config_accel_set_profile(device, profile));
	return true;
}