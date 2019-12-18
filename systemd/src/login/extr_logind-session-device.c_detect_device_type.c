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
typedef  int /*<<< orphan*/  DeviceType ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_TYPE_DRM ; 
 int /*<<< orphan*/  DEVICE_TYPE_EVDEV ; 
 int /*<<< orphan*/  DEVICE_TYPE_UNKNOWN ; 
 scalar_t__ sd_device_get_subsystem (int /*<<< orphan*/ *,char const**) ; 
 scalar_t__ sd_device_get_sysname (int /*<<< orphan*/ *,char const**) ; 
 scalar_t__ startswith (char const*,char*) ; 
 scalar_t__ streq (char const*,char*) ; 

__attribute__((used)) static DeviceType detect_device_type(sd_device *dev) {
        const char *sysname, *subsystem;
        DeviceType type = DEVICE_TYPE_UNKNOWN;

        if (sd_device_get_sysname(dev, &sysname) < 0 ||
            sd_device_get_subsystem(dev, &subsystem) < 0)
                return type;

        if (streq(subsystem, "drm")) {
                if (startswith(sysname, "card"))
                        type = DEVICE_TYPE_DRM;
        } else if (streq(subsystem, "input")) {
                if (startswith(sysname, "event"))
                        type = DEVICE_TYPE_EVDEV;
        }

        return type;
}