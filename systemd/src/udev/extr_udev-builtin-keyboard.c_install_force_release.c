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
typedef  unsigned int const sd_device ;
typedef  int /*<<< orphan*/  codes ;

/* Variables and functions */
 int /*<<< orphan*/  assert (unsigned int const*) ; 
 int /*<<< orphan*/  log_device_debug (unsigned int const*,char*,char*) ; 
 int log_device_error_errno (unsigned int const*,int,char*) ; 
 int sd_device_get_parent_with_subsystem_devtype (unsigned int const*,char*,int /*<<< orphan*/ *,unsigned int const**) ; 
 int sd_device_get_sysattr_value (unsigned int const*,char*,char const**) ; 
 int sd_device_set_sysattr_value (unsigned int const*,char*,char*) ; 
 size_t strpcpy (char**,size_t,char const*) ; 
 size_t strpcpyf (char**,size_t,char*,unsigned int const) ; 

__attribute__((used)) static int install_force_release(sd_device *dev, const unsigned *release, unsigned release_count) {
        sd_device *atkbd;
        const char *cur;
        char codes[4096];
        char *s;
        size_t l;
        unsigned i;
        int r;

        assert(dev);
        assert(release);

        r = sd_device_get_parent_with_subsystem_devtype(dev, "serio", NULL, &atkbd);
        if (r < 0)
                return log_device_error_errno(dev, r, "Failed to get serio parent: %m");

        r = sd_device_get_sysattr_value(atkbd, "force_release", &cur);
        if (r < 0)
                return log_device_error_errno(atkbd, r, "Failed to get force-release attribute: %m");

        s = codes;
        l = sizeof(codes);

        /* copy current content */
        l = strpcpy(&s, l, cur);

        /* append new codes */
        for (i = 0; i < release_count; i++)
                l = strpcpyf(&s, l, ",%u", release[i]);

        log_device_debug(atkbd, "keyboard: updating force-release list with '%s'", codes);
        r = sd_device_set_sysattr_value(atkbd, "force_release", codes);
        if (r < 0)
                return log_device_error_errno(atkbd, r, "Failed to set force-release attribute: %m");

        return 0;
}