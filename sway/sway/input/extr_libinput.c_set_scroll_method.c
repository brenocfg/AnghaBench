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
typedef  int uint32_t ;
struct libinput_device {int dummy; } ;
typedef  enum libinput_config_scroll_method { ____Placeholder_libinput_config_scroll_method } libinput_config_scroll_method ;

/* Variables and functions */
 int LIBINPUT_CONFIG_SCROLL_NO_SCROLL ; 
 int /*<<< orphan*/  SWAY_DEBUG ; 
 int libinput_device_config_scroll_get_method (struct libinput_device*) ; 
 int libinput_device_config_scroll_get_methods (struct libinput_device*) ; 
 int /*<<< orphan*/  libinput_device_config_scroll_set_method (struct libinput_device*,int) ; 
 int /*<<< orphan*/  log_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static bool set_scroll_method(struct libinput_device *device,
		enum libinput_config_scroll_method method) {
	uint32_t scroll = libinput_device_config_scroll_get_methods(device);
	if ((scroll & ~LIBINPUT_CONFIG_SCROLL_NO_SCROLL) == 0 ||
			libinput_device_config_scroll_get_method(device) == method) {
		return false;
	}
	sway_log(SWAY_DEBUG, "scroll_set_method(%d)", method);
	log_status(libinput_device_config_scroll_set_method(device, method));
	return true;
}