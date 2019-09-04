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
struct TYPE_2__ {int dynamic_status; int compatible_ids; int removable; int ejectable; int lockable; int power_manageable; } ;
struct acpi_device {TYPE_1__ flags; int /*<<< orphan*/  handle; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/ * ACPI_HANDLE ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiGetHandle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  return_VALUE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
acpi_bus_get_flags (
	struct acpi_device	*device)
{
	ACPI_STATUS		status = AE_OK;
	ACPI_HANDLE		temp = NULL;

	/* Presence of _STA indicates 'dynamic_status' */
	status = AcpiGetHandle(device->handle, "_STA", &temp);
	if (ACPI_SUCCESS(status))
		device->flags.dynamic_status = 1;

	/* Presence of _CID indicates 'compatible_ids' */
	status = AcpiGetHandle(device->handle, "_CID", &temp);
	if (ACPI_SUCCESS(status))
		device->flags.compatible_ids = 1;

	/* Presence of _RMV indicates 'removable' */
	status = AcpiGetHandle(device->handle, "_RMV", &temp);
	if (ACPI_SUCCESS(status))
		device->flags.removable = 1;

	/* Presence of _EJD|_EJ0 indicates 'ejectable' */
	status = AcpiGetHandle(device->handle, "_EJD", &temp);
	if (ACPI_SUCCESS(status))
		device->flags.ejectable = 1;
	else {
		status = AcpiGetHandle(device->handle, "_EJ0", &temp);
		if (ACPI_SUCCESS(status))
			device->flags.ejectable = 1;
	}

	/* Presence of _LCK indicates 'lockable' */
	status = AcpiGetHandle(device->handle, "_LCK", &temp);
	if (ACPI_SUCCESS(status))
		device->flags.lockable = 1;

	/* Presence of _PS0|_PR0 indicates 'power manageable' */
	status = AcpiGetHandle(device->handle, "_PS0", &temp);
	if (ACPI_FAILURE(status))
		status = AcpiGetHandle(device->handle, "_PR0", &temp);
	if (ACPI_SUCCESS(status))
		device->flags.power_manageable = 1;

	/* TBD: Performance management */

	return_VALUE(0);
}