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
 int libinput_device_config_scroll_get_natural_scroll_enabled (struct libinput_device*) ; 
 int /*<<< orphan*/  libinput_device_config_scroll_has_natural_scroll (struct libinput_device*) ; 
 int /*<<< orphan*/  libinput_device_config_scroll_set_natural_scroll_enabled (struct libinput_device*,int) ; 
 int /*<<< orphan*/  log_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static bool set_natural_scroll(struct libinput_device *d, bool n) {
	if (!libinput_device_config_scroll_has_natural_scroll(d) ||
			libinput_device_config_scroll_get_natural_scroll_enabled(d) == n) {
		return false;
	}
	sway_log(SWAY_DEBUG, "scroll_set_natural_scroll(%d)", n);
	log_status(libinput_device_config_scroll_set_natural_scroll_enabled(d, n));
	return true;
}