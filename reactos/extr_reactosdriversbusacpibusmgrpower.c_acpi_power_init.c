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

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int acpi_bus_register_driver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_power_driver ; 
 int /*<<< orphan*/  acpi_power_resource_list ; 
 int /*<<< orphan*/  return_VALUE (int) ; 

int
acpi_power_init (void)
{
	int			result = 0;

	DPRINT("acpi_power_init\n");

	INIT_LIST_HEAD(&acpi_power_resource_list);


	result = acpi_bus_register_driver(&acpi_power_driver);
	if (result < 0) {
		return_VALUE(-15);
	}

	return_VALUE(0);
}