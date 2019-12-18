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
 int /*<<< orphan*/ * skip_subsystem (int /*<<< orphan*/ *,char*) ; 
 int sscanf (char const*,char*,unsigned int*,unsigned int*) ; 

__attribute__((used)) static sd_device *handle_cciss(sd_device *parent, char **path) {
        const char *str;
        unsigned controller, disk;

        if (sd_device_get_sysname(parent, &str) < 0)
                return NULL;
        if (sscanf(str, "c%ud%u%*s", &controller, &disk) != 2)
                return NULL;

        path_prepend(path, "cciss-disk%u", disk);
        return skip_subsystem(parent, "cciss");
}