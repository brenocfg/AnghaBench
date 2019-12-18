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
 int /*<<< orphan*/  STR_IN_SET (char const*,char*,char*) ; 
 int /*<<< orphan*/  path_prepend (char**,char*,char const*) ; 
 scalar_t__ sd_device_get_devtype (int /*<<< orphan*/ *,char const**) ; 
 scalar_t__ sd_device_get_sysname (int /*<<< orphan*/ *,char const**) ; 
 int /*<<< orphan*/ * skip_subsystem (int /*<<< orphan*/ *,char*) ; 
 char* strchr (char const*,char) ; 

__attribute__((used)) static sd_device *handle_usb(sd_device *parent, char **path) {
        const char *devtype, *str, *port;

        if (sd_device_get_devtype(parent, &devtype) < 0)
                return parent;
        if (!STR_IN_SET(devtype, "usb_interface", "usb_device"))
                return parent;

        if (sd_device_get_sysname(parent, &str) < 0)
                return parent;
        port = strchr(str, '-');
        if (!port)
                return parent;
        port++;

        path_prepend(path, "usb-0:%s", port);
        return skip_subsystem(parent, "usb");
}