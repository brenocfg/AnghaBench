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
struct TYPE_2__ {int (* add ) (struct acpi_device*) ;int (* start ) (struct acpi_device*) ;int /*<<< orphan*/  (* scan ) (struct acpi_device*) ;int /*<<< orphan*/  (* remove ) (struct acpi_device*,int /*<<< orphan*/ ) ;} ;
struct acpi_driver {TYPE_1__ ops; } ;
struct acpi_device {struct acpi_driver* driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_BUS_REMOVAL_NORMAL ; 
 int AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  DPRINT (char*) ; 
 int /*<<< orphan*/  return_VALUE (int) ; 
 int stub1 (struct acpi_device*) ; 
 int stub2 (struct acpi_device*) ; 
 int /*<<< orphan*/  stub3 (struct acpi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct acpi_device*) ; 

__attribute__((used)) static int
acpi_bus_driver_init (
	struct acpi_device	*device,
	struct acpi_driver	*driver)
{
	int			result = 0;

	if (!device || !driver)
		return_VALUE(AE_BAD_PARAMETER);

	if (!driver->ops.add)
		return_VALUE(-38);

	result = driver->ops.add(device);
	if (result) {
		device->driver = NULL;
		//acpi_driver_data(device) = NULL;
		return_VALUE(result);
	}

	device->driver = driver;

	/*
	 * TBD - Configuration Management: Assign resources to device based
	 * upon possible configuration and currently allocated resources.
	 */

	if (driver->ops.start) {
		result = driver->ops.start(device);
		if (result && driver->ops.remove)
			driver->ops.remove(device, ACPI_BUS_REMOVAL_NORMAL);
		return_VALUE(result);
	}

	DPRINT("Driver successfully bound to device\n");

	if (driver->ops.scan) {
		driver->ops.scan(device);
	}

	return_VALUE(0);
}