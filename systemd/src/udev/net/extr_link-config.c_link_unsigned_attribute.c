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
 int /*<<< orphan*/  log_device_debug (int /*<<< orphan*/ *,char*,char const*,unsigned int) ; 
 int log_device_debug_errno (int /*<<< orphan*/ *,int,char*,char const*) ; 
 int log_device_warning_errno (int /*<<< orphan*/ *,int,char*,char const*,char const*) ; 
 int safe_atou (char const*,unsigned int*) ; 
 int sd_device_get_sysattr_value (int /*<<< orphan*/ *,char const*,char const**) ; 

__attribute__((used)) static int link_unsigned_attribute(sd_device *device, const char *attr, unsigned *type) {
        const char *s;
        int r;

        r = sd_device_get_sysattr_value(device, attr, &s);
        if (r < 0)
                return log_device_debug_errno(device, r, "Failed to query %s: %m", attr);

        r = safe_atou(s, type);
        if (r < 0)
                return log_device_warning_errno(device, r, "Failed to parse %s \"%s\": %m", attr, s);

        log_device_debug(device, "Device has %s=%u", attr, *type);
        return 0;
}