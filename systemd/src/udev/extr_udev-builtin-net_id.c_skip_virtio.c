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
 scalar_t__ sd_device_get_parent (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ sd_device_get_subsystem (int /*<<< orphan*/ *,char const**) ; 
 int /*<<< orphan*/  streq (char const*,char*) ; 

__attribute__((used)) static sd_device *skip_virtio(sd_device *dev) {
        sd_device *parent;

        /* there can only ever be one virtio bus per parent device, so we can
         * safely ignore any virtio buses. see
         * http://lists.linuxfoundation.org/pipermail/virtualization/2015-August/030331.html */
        for (parent = dev; parent; ) {
                const char *subsystem;

                if (sd_device_get_subsystem(parent, &subsystem) < 0)
                        break;

                if (!streq(subsystem, "virtio"))
                        break;

                if (sd_device_get_parent(parent, &parent) < 0)
                        return NULL;
        }

        return parent;
}