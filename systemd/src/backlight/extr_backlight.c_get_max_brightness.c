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
typedef  unsigned int sd_device ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  assert (unsigned int*) ; 
 int /*<<< orphan*/  log_device_warning (unsigned int*,char*) ; 
 int log_device_warning_errno (unsigned int*,int,char*,...) ; 
 int safe_atou (char const*,unsigned int*) ; 
 int sd_device_get_sysattr_value (unsigned int*,char*,char const**) ; 

__attribute__((used)) static int get_max_brightness(sd_device *device, unsigned *ret) {
        const char *max_brightness_str;
        unsigned max_brightness;
        int r;

        assert(device);
        assert(ret);

        r = sd_device_get_sysattr_value(device, "max_brightness", &max_brightness_str);
        if (r < 0)
                return log_device_warning_errno(device, r, "Failed to read 'max_brightness' attribute: %m");

        r = safe_atou(max_brightness_str, &max_brightness);
        if (r < 0)
                return log_device_warning_errno(device, r, "Failed to parse 'max_brightness' \"%s\": %m", max_brightness_str);

        if (max_brightness <= 0) {
                log_device_warning(device, "Maximum brightness is 0, ignoring device.");
                return -EINVAL;
        }

        *ret = max_brightness;
        return 0;
}