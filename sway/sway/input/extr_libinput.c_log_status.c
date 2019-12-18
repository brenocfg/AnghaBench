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
typedef  enum libinput_config_status { ____Placeholder_libinput_config_status } libinput_config_status ;

/* Variables and functions */
 int LIBINPUT_CONFIG_STATUS_SUCCESS ; 
 int /*<<< orphan*/  SWAY_ERROR ; 
 int /*<<< orphan*/  libinput_config_status_to_str (int) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void log_status(enum libinput_config_status status) {
	if (status != LIBINPUT_CONFIG_STATUS_SUCCESS) {
		sway_log(SWAY_ERROR, "Failed to apply libinput config: %s",
			libinput_config_status_to_str(status));
	}
}