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
typedef  char const sd_device ;

/* Variables and functions */
 int /*<<< orphan*/  assert (char const*) ; 
 scalar_t__ sd_device_get_parent (char const*,char const**) ; 
 scalar_t__ sd_device_get_subsystem (char const*,char const**) ; 
 int /*<<< orphan*/  streq (char const*,char const*) ; 

__attribute__((used)) static sd_device *skip_subsystem(sd_device *dev, const char *subsys) {
        sd_device *parent;

        assert(dev);
        assert(subsys);

        for (parent = dev; ; ) {
                const char *subsystem;

                if (sd_device_get_subsystem(parent, &subsystem) < 0)
                        break;

                if (!streq(subsystem, subsys))
                        break;

                dev = parent;
                if (sd_device_get_parent(dev, &parent) < 0)
                        break;
        }

        return dev;
}