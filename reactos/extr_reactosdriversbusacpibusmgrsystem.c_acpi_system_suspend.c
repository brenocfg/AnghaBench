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
typedef  int UINT32 ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
#define  ACPI_STATE_S1 130 
#define  ACPI_STATE_S4 129 
#define  ACPI_STATE_S5 128 
 int /*<<< orphan*/  AE_ERROR ; 
 int /*<<< orphan*/  AcpiEnterSleepState (int) ; 

ACPI_STATUS
acpi_system_suspend(
	UINT32		state)
{
	ACPI_STATUS		status = AE_ERROR;
	//unsigned long		flags = 0;

	//local_irq_save(flags);
	/* kernel_fpu_begin(); */

	switch (state) {
	case ACPI_STATE_S1:
	case ACPI_STATE_S5:
		//barrier();
		status = AcpiEnterSleepState(state);
		break;
	case ACPI_STATE_S4:
		//do_suspend_lowlevel_s4bios(0);
		break;
	}

	/* kernel_fpu_end(); */
	//local_irq_restore(flags);

	return status;
}