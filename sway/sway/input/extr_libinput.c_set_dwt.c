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
 int libinput_device_config_dwt_get_enabled (struct libinput_device*) ; 
 int /*<<< orphan*/  libinput_device_config_dwt_is_available (struct libinput_device*) ; 
 int /*<<< orphan*/  libinput_device_config_dwt_set_enabled (struct libinput_device*,int) ; 
 int /*<<< orphan*/  log_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static bool set_dwt(struct libinput_device *device, bool dwt) {
	if (!libinput_device_config_dwt_is_available(device) ||
			libinput_device_config_dwt_get_enabled(device) == dwt) {
		return false;
	}
	sway_log(SWAY_DEBUG, "dwt_set_enabled(%d)", dwt);
	log_status(libinput_device_config_dwt_set_enabled(device, dwt));
	return true;
}