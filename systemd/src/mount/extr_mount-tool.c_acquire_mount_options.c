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
 scalar_t__ arg_mount_options ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_debug (char*,scalar_t__) ; 
 int log_oom () ; 
 scalar_t__ sd_device_get_property_value (int /*<<< orphan*/ *,char*,char const**) ; 
 scalar_t__ strdup (char const*) ; 

__attribute__((used)) static int acquire_mount_options(sd_device *d) {
        const char *v;

        assert(d);

        if (arg_mount_options)
                return 0;

        if (sd_device_get_property_value(d, "SYSTEMD_MOUNT_OPTIONS", &v) < 0)
                return 0;

        arg_mount_options = strdup(v);
        if (!arg_mount_options)
                return log_oom();

        log_debug("Discovered options=%s", arg_mount_options);
        return 1;
}