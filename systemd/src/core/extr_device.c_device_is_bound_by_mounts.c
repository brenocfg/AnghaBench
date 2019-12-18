#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int bind_mounts; } ;
typedef  TYPE_1__ sd_device ;
typedef  TYPE_1__ Device ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  log_device_warning_errno (TYPE_1__*,int,char*,char const*) ; 
 int parse_boolean (char const*) ; 
 scalar_t__ sd_device_get_property_value (TYPE_1__*,char*,char const**) ; 

__attribute__((used)) static bool device_is_bound_by_mounts(Device *d, sd_device *dev) {
        const char *bound_by;
        int r;

        assert(d);
        assert(dev);

        if (sd_device_get_property_value(dev, "SYSTEMD_MOUNT_DEVICE_BOUND", &bound_by) >= 0) {
                r = parse_boolean(bound_by);
                if (r < 0)
                        log_device_warning_errno(dev, r, "Failed to parse SYSTEMD_MOUNT_DEVICE_BOUND='%s' udev property, ignoring: %m", bound_by);

                d->bind_mounts = r > 0;
        } else
                d->bind_mounts = false;

        return d->bind_mounts;
}