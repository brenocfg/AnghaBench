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
struct udev_enumerate {int /*<<< orphan*/  enumerator; int /*<<< orphan*/  devices_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct udev_enumerate*) ; 
 struct udev_enumerate* mfree (struct udev_enumerate*) ; 
 int /*<<< orphan*/  sd_device_enumerator_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udev_list_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct udev_enumerate *udev_enumerate_free(struct udev_enumerate *udev_enumerate) {
        assert(udev_enumerate);

        udev_list_free(udev_enumerate->devices_list);
        sd_device_enumerator_unref(udev_enumerate->enumerator);
        return mfree(udev_enumerate);
}