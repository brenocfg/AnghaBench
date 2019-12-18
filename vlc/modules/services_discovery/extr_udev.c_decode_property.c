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
 char* decode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udev_device_get_property_value (struct udev_device*,char const*) ; 

__attribute__((used)) static char *decode_property (struct udev_device *dev, const char *name)
{
    return decode (udev_device_get_property_value (dev, name));
}