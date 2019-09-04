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
struct acpi_device {int dummy; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_NOT_FOUND ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiGetData (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  DPRINT (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_bus_data_handler ; 
 int /*<<< orphan*/  return_VALUE (int /*<<< orphan*/ ) ; 

int
acpi_bus_get_device (
	ACPI_HANDLE		handle,
	struct acpi_device	**device)
{
	ACPI_STATUS		status = AE_OK;

	if (!device)
		return_VALUE(AE_BAD_PARAMETER);

	/* TBD: Support fixed-feature devices */

	status = AcpiGetData(handle, acpi_bus_data_handler, (void**)device);
	if (ACPI_FAILURE(status) || !*device) {
		DPRINT( "Error getting context for object [%p]\n",
			handle);
		return_VALUE(AE_NOT_FOUND);
	}

	return 0;
}