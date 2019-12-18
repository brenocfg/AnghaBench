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
 int /*<<< orphan*/  path_prepend (char**,char*,char const) ; 
 scalar_t__ sd_device_get_sysname (int /*<<< orphan*/ *,char const**) ; 
 scalar_t__ startswith (char const*,char*) ; 
 scalar_t__ strchr (char*,char const) ; 

__attribute__((used)) static void handle_scsi_tape(sd_device *dev, char **path) {
        const char *name;

        /* must be the last device in the syspath */
        if (*path)
                return;

        if (sd_device_get_sysname(dev, &name) < 0)
                return;

        if (startswith(name, "nst") && strchr("lma", name[3]))
                path_prepend(path, "nst%c", name[3]);
        else if (startswith(name, "st") && strchr("lma", name[2]))
                path_prepend(path, "st%c", name[2]);
}