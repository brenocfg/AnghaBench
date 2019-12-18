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
struct udev_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert_se (int) ; 
 struct udev_device* udev_device_unref (struct udev_device*) ; 

__attribute__((used)) static void* thread(void *p) {
        struct udev_device **d = p;

        assert_se(!(*d = udev_device_unref(*d)));

        return NULL;
}