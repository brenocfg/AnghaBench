#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  power_manageable; } ;
struct acpi_device {TYPE_1__ flags; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;

/* Variables and functions */
 int acpi_bus_get_device (int /*<<< orphan*/ ,struct acpi_device**) ; 

BOOLEAN acpi_bus_power_manageable(ACPI_HANDLE handle)
{
	struct acpi_device *device;
	int result;

	result = acpi_bus_get_device(handle, &device);
	return result ? 0 : device->flags.power_manageable;
}