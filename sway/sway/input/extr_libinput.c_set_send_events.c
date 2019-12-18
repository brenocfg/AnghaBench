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
typedef  scalar_t__ uint32_t ;
struct libinput_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_DEBUG ; 
 scalar_t__ libinput_device_config_send_events_get_mode (struct libinput_device*) ; 
 int /*<<< orphan*/  libinput_device_config_send_events_set_mode (struct libinput_device*,scalar_t__) ; 
 int /*<<< orphan*/  log_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static bool set_send_events(struct libinput_device *device, uint32_t mode) {
	if (libinput_device_config_send_events_get_mode(device) == mode) {
		return false;
	}
	sway_log(SWAY_DEBUG, "send_events_set_mode(%d)", mode);
	log_status(libinput_device_config_send_events_set_mode(device, mode));
	return true;
}