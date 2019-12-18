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
 int asprintf (char**,char*,char const*) ; 
 char* udev_device_get_devnode (struct udev_device*) ; 
 int /*<<< orphan*/  v4l_can_capture (struct udev_device*) ; 
 scalar_t__ v4l_is_legacy (struct udev_device*) ; 

__attribute__((used)) static char *v4l_get_mrl (struct udev_device *dev)
{
    /* Determine media location */
    if (v4l_is_legacy (dev) || !v4l_can_capture (dev))
        return NULL;

    const char *node = udev_device_get_devnode (dev);
    char *mrl;

    if (asprintf (&mrl, "v4l2://%s", node) == -1)
        mrl = NULL;
    return mrl;
}