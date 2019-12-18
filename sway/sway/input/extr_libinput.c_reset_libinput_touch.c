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
 int /*<<< orphan*/  libinput_device_config_calibration_get_default_matrix (struct libinput_device*,float*) ; 
 int /*<<< orphan*/  libinput_device_config_send_events_get_default_mode (struct libinput_device*) ; 
 int set_calibration_matrix (struct libinput_device*,float*) ; 
 int set_send_events (struct libinput_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static bool reset_libinput_touch(struct libinput_device *device,
		const char *device_id) {
	sway_log(SWAY_DEBUG, "reset_libinput_touch(%s)", device_id);
	bool changed = false;

	changed |= set_send_events(device,
		libinput_device_config_send_events_get_default_mode(device));

	float matrix[6];
	libinput_device_config_calibration_get_default_matrix(device, matrix);
	changed |= set_calibration_matrix(device, matrix);

	return changed;
}