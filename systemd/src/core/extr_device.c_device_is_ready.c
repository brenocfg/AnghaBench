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
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 scalar_t__ device_is_renaming (int /*<<< orphan*/ *) ; 
 scalar_t__ parse_boolean (char const*) ; 
 scalar_t__ sd_device_get_property_value (int /*<<< orphan*/ *,char*,char const**) ; 

__attribute__((used)) static bool device_is_ready(sd_device *dev) {
        const char *ready;

        assert(dev);

        if (device_is_renaming(dev) > 0)
                return false;

        if (sd_device_get_property_value(dev, "SYSTEMD_READY", &ready) < 0)
                return true;

        return parse_boolean(ready) != 0;
}