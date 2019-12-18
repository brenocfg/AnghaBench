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
typedef  char* sd_device ;

/* Variables and functions */
 int /*<<< orphan*/  assert (char**) ; 
 int /*<<< orphan*/  path_prepend (char**,char*,char const*,...) ; 
 scalar_t__ sd_device_get_sysattr_value (char**,char*,char const**) ; 
 scalar_t__ sd_device_get_sysname (char**,char const**) ; 
 char** skip_subsystem (char**,char*) ; 

__attribute__((used)) static sd_device *handle_ap(sd_device *parent, char **path) {
        const char *type, *func;

        assert(parent);
        assert(path);

        if (sd_device_get_sysattr_value(parent, "type", &type) >= 0 &&
            sd_device_get_sysattr_value(parent, "ap_functions", &func) >= 0)
                path_prepend(path, "ap-%s-%s", type, func);
        else {
                const char *sysname;

                if (sd_device_get_sysname(parent, &sysname) >= 0)
                        path_prepend(path, "ap-%s", sysname);
        }

        return skip_subsystem(parent, "ap");
}