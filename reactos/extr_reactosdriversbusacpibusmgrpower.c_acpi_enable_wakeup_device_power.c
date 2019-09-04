#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ valid; } ;
struct TYPE_4__ {unsigned int count; int /*<<< orphan*/ * handles; } ;
struct TYPE_6__ {scalar_t__ prepare_count; TYPE_2__ flags; TYPE_1__ resources; } ;
struct acpi_device {TYPE_3__ wakeup; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*) ; 
 int acpi_device_sleep_wake (struct acpi_device*,int,int,int) ; 
 int acpi_power_on (int /*<<< orphan*/ ,struct acpi_device*) ; 

int acpi_enable_wakeup_device_power(struct acpi_device *dev, int sleep_state)
{
	unsigned int i;
	int err = 0;

	if (!dev || !dev->wakeup.flags.valid)
		return -1;

	//mutex_lock(&acpi_device_lock);

	if (dev->wakeup.prepare_count++)
		goto out;

	/* Open power resource */
	for (i = 0; i < dev->wakeup.resources.count; i++) {
		int ret = acpi_power_on(dev->wakeup.resources.handles[i], dev);
		if (ret) {
			DPRINT( "Transition power state\n");
			dev->wakeup.flags.valid = 0;
			err = -1;
			goto err_out;
		}
	}

	/*
	 * Passing 3 as the third argument below means the device may be placed
	 * in arbitrary power state afterwards.
	 */
	err = acpi_device_sleep_wake(dev, 1, sleep_state, 3);

 err_out:
	if (err)
		dev->wakeup.prepare_count = 0;

 out:
	//mutex_unlock(&acpi_device_lock);
	return err;
}