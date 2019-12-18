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
struct udev_monitor {int /*<<< orphan*/  monitor; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct udev_monitor*) ; 
 struct udev_monitor* mfree (struct udev_monitor*) ; 
 int /*<<< orphan*/  sd_device_monitor_unref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct udev_monitor *udev_monitor_free(struct udev_monitor *udev_monitor) {
        assert(udev_monitor);

        sd_device_monitor_unref(udev_monitor->monitor);
        return mfree(udev_monitor);
}