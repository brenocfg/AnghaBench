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
typedef  int /*<<< orphan*/  sd_device ;

/* Variables and functions */
 scalar_t__ ACTION_AUTOMOUNT ; 
 scalar_t__ ACTION_DEFAULT ; 
 int /*<<< orphan*/  USEC_PER_SEC ; 
 scalar_t__ arg_action ; 
 int arg_bind_device ; 
 int /*<<< orphan*/  arg_timeout_idle ; 
 scalar_t__ arg_timeout_idle_set ; 
 int /*<<< orphan*/  log_debug (char*) ; 
 scalar_t__ parse_boolean (char const*) ; 
 scalar_t__ sd_device_get_parent (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ sd_device_get_subsystem (int /*<<< orphan*/ *,char const**) ; 
 scalar_t__ sd_device_get_sysattr_value (int /*<<< orphan*/ *,char*,char const**) ; 
 int /*<<< orphan*/  streq (char const*,char*) ; 

__attribute__((used)) static int acquire_removable(sd_device *d) {
        const char *v;

        /* Shortcut this if there's no reason to check it */
        if (arg_action != ACTION_DEFAULT && arg_timeout_idle_set && arg_bind_device >= 0)
                return 0;

        for (;;) {
                if (sd_device_get_sysattr_value(d, "removable", &v) > 0)
                        break;

                if (sd_device_get_parent(d, &d) < 0)
                        return 0;

                if (sd_device_get_subsystem(d, &v) < 0 || !streq(v, "block"))
                        return 0;
        }

        if (parse_boolean(v) <= 0)
                return 0;

        log_debug("Discovered removable device.");

        if (arg_action == ACTION_DEFAULT) {
                log_debug("Automatically turning on automount.");
                arg_action = ACTION_AUTOMOUNT;
        }

        if (!arg_timeout_idle_set) {
                log_debug("Setting idle timeout to 1s.");
                arg_timeout_idle = USEC_PER_SEC;
        }

        if (arg_bind_device < 0) {
                log_debug("Binding automount unit to device.");
                arg_bind_device = true;
        }

        return 1;
}