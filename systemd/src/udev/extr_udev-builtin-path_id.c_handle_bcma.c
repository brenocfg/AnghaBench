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
 int /*<<< orphan*/  path_prepend (char**,char*,unsigned int) ; 
 scalar_t__ sd_device_get_sysname (int /*<<< orphan*/ *,char const**) ; 
 int sscanf (char const*,char*,unsigned int*) ; 

__attribute__((used)) static sd_device *handle_bcma(sd_device *parent, char **path) {
        const char *sysname;
        unsigned core;

        if (sd_device_get_sysname(parent, &sysname) < 0)
                return NULL;
        if (sscanf(sysname, "bcma%*u:%u", &core) != 1)
                return NULL;

        path_prepend(path, "bcma-%u", core);
        return parent;
}