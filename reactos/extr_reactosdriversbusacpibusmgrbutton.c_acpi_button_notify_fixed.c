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
struct acpi_button {int /*<<< orphan*/  handle; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_BUTTON_NOTIFY_STATUS ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (char*) ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_button_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_button*) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
acpi_button_notify_fixed (
	void			*data)
{
	struct acpi_button	*button = (struct acpi_button *) data;
	
	ACPI_FUNCTION_TRACE("acpi_button_notify_fixed");

	if (!button)
		return_ACPI_STATUS(AE_BAD_PARAMETER);

	acpi_button_notify(button->handle, ACPI_BUTTON_NOTIFY_STATUS, button);

	return_ACPI_STATUS(AE_OK);
}