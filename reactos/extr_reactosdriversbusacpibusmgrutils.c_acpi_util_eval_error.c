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
typedef  int /*<<< orphan*/  ACPI_STRING ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;

/* Variables and functions */

__attribute__((used)) static void
acpi_util_eval_error(ACPI_HANDLE h, ACPI_STRING p, ACPI_STATUS s)
{
#ifdef ACPI_DEBUG_OUTPUT
	char prefix[80] = {'\0'};
	ACPI_BUFFER buffer = {sizeof(prefix), prefix};
	AcpiGetName(h, ACPI_FULL_PATHNAME, &buffer);
	ACPI_DEBUG_PRINT((ACPI_DB_INFO, "Evaluate [%s.%s]: %s\n",
		(char *) prefix, p, AcpiFormatException(s)));
#else
	return;
#endif
}