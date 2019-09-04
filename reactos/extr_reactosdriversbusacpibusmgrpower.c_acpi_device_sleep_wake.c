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
struct TYPE_4__ {int Value; } ;
union acpi_object {TYPE_1__ Integer; void* Type; } ;
struct acpi_object_list {int member_0; int Count; union acpi_object* member_1; } ;
struct TYPE_5__ {scalar_t__ valid; } ;
struct TYPE_6__ {TYPE_2__ flags; } ;
struct acpi_device {TYPE_3__ wakeup; int /*<<< orphan*/  handle; } ;
typedef  scalar_t__ ACPI_STATUS ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (scalar_t__) ; 
 scalar_t__ ACPI_SUCCESS (scalar_t__) ; 
 void* ACPI_TYPE_INTEGER ; 
 scalar_t__ AE_NOT_FOUND ; 
 scalar_t__ AE_OK ; 
 scalar_t__ AcpiEvaluateObject (int /*<<< orphan*/ ,char*,struct acpi_object_list*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DPRINT1 (char*) ; 

int acpi_device_sleep_wake(struct acpi_device *dev,
                           int enable, int sleep_state, int dev_state)
{
	union acpi_object in_arg[3];
	struct acpi_object_list arg_list = { 3, in_arg };
	ACPI_STATUS status = AE_OK;

	/*
	 * Try to execute _DSW first.
	 *
	 * Three arguments are needed for the _DSW object:
	 * Argument 0: enable/disable the wake capabilities
	 * Argument 1: target system state
	 * Argument 2: target device state
	 * When _DSW object is called to disable the wake capabilities, maybe
	 * the first argument is filled. The values of the other two arguments
	 * are meaningless.
	 */
	in_arg[0].Type = ACPI_TYPE_INTEGER;
	in_arg[0].Integer.Value = enable;
	in_arg[1].Type = ACPI_TYPE_INTEGER;
	in_arg[1].Integer.Value = sleep_state;
	in_arg[2].Type = ACPI_TYPE_INTEGER;
	in_arg[2].Integer.Value = dev_state;
	status = AcpiEvaluateObject(dev->handle, "_DSW", &arg_list, NULL);
	if (ACPI_SUCCESS(status)) {
		return 0;
	} else if (status != AE_NOT_FOUND) {
		DPRINT1("_DSW execution failed\n");
		dev->wakeup.flags.valid = 0;
		return -1;
	}

	/* Execute _PSW */
	arg_list.Count = 1;
	in_arg[0].Integer.Value = enable;
	status = AcpiEvaluateObject(dev->handle, "_PSW", &arg_list, NULL);
	if (ACPI_FAILURE(status) && (status != AE_NOT_FOUND)) {
		DPRINT1("_PSW execution failed\n");
		dev->wakeup.flags.valid = 0;
		return -1;
	}

	return 0;
}