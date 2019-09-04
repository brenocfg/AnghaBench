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
struct acpi_button {int /*<<< orphan*/  pushed; int /*<<< orphan*/  device; } ;
typedef  int UINT32 ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;

/* Variables and functions */
#define  ACPI_BUTTON_NOTIFY_STATUS 128 
 int /*<<< orphan*/  ACPI_DB_INFO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (char*) ; 
 int /*<<< orphan*/  acpi_bus_generate_event (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  return_VOID ; 

void
acpi_button_notify (
	ACPI_HANDLE		handle,
	UINT32			event,
	void			*data)
{
	struct acpi_button	*button = (struct acpi_button *) data;

	ACPI_FUNCTION_TRACE("acpi_button_notify");

	if (!button || !button->device)
		return_VOID;

	switch (event) {
	case ACPI_BUTTON_NOTIFY_STATUS:
		acpi_bus_generate_event(button->device, event, ++button->pushed);
		break;
	default:
		ACPI_DEBUG_PRINT((ACPI_DB_INFO,
			"Unsupported event [0x%x]\n", event));
		break;
	}

	return_VOID;
}