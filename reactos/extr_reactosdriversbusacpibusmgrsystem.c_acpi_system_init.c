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
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (char*) ; 
 int /*<<< orphan*/  AE_NOT_FOUND ; 
 int acpi_bus_register_driver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_system_driver ; 
 int /*<<< orphan*/  return_VALUE (int /*<<< orphan*/ ) ; 

int 
acpi_system_init (void)
{
	int			result = 0;

	ACPI_FUNCTION_TRACE("acpi_system_init");

	result = acpi_bus_register_driver(&acpi_system_driver);
	if (result < 0)
		return_VALUE(AE_NOT_FOUND);

	return_VALUE(0);
}