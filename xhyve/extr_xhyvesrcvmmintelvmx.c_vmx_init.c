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
 int CR0_CD ; 
 int CR0_ET ; 
 int CR0_NE ; 
 int CR0_NW ; 
 int HV_NO_DEVICE ; 
 int /*<<< orphan*/  HV_VMX_CAP_ENTRY ; 
 int /*<<< orphan*/  HV_VMX_CAP_EXIT ; 
 int /*<<< orphan*/  HV_VMX_CAP_PINBASED ; 
 int /*<<< orphan*/  HV_VMX_CAP_PROCBASED ; 
 int /*<<< orphan*/  HV_VMX_CAP_PROCBASED2 ; 
 int /*<<< orphan*/  HV_VM_DEFAULT ; 
 int /*<<< orphan*/  PINBASED_CTLS_ONE_SETTING ; 
 int /*<<< orphan*/  PINBASED_CTLS_ZERO_SETTING ; 
 int /*<<< orphan*/  PROCBASED_CTLS2_ONE_SETTING ; 
 int /*<<< orphan*/  PROCBASED_CTLS2_ZERO_SETTING ; 
 int /*<<< orphan*/  PROCBASED_CTLS_ONE_SETTING ; 
 int /*<<< orphan*/  PROCBASED_CTLS_WINDOW_SETTING ; 
 int /*<<< orphan*/  PROCBASED_CTLS_ZERO_SETTING ; 
 int /*<<< orphan*/  VM_ENTRY_CTLS_ONE_SETTING ; 
 int /*<<< orphan*/  VM_ENTRY_CTLS_ZERO_SETTING ; 
 int /*<<< orphan*/  VM_EXIT_CTLS_ONE_SETTING ; 
 int /*<<< orphan*/  VM_EXIT_CTLS_ZERO_SETTING ; 
 int cap_halt_exit ; 
 int cap_monitor_trap ; 
 int cap_pause_exit ; 
 int cr0_ones_mask ; 
 int cr0_zeros_mask ; 
 int cr4_ones_mask ; 
 int cr4_zeros_mask ; 
 int /*<<< orphan*/  entry_ctls ; 
 int /*<<< orphan*/  exit_ctls ; 
 int hv_vm_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pinbased_ctls ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  procbased_ctls ; 
 int /*<<< orphan*/  procbased_ctls2 ; 
 int /*<<< orphan*/  vmx_msr_init () ; 
 int vmx_set_ctlreg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xhyve_abort (char*) ; 

__attribute__((used)) static int
vmx_init(void)
{
	int error = hv_vm_create(HV_VM_DEFAULT);
	if (error) {
		if (error == HV_NO_DEVICE) {
			printf("vmx_init: processor not supported by "
			       "Hypervisor.framework\n");
			return (error);
		}
		else
			xhyve_abort("hv_vm_create failed\n");
	}

	/* Check support for primary processor-based VM-execution controls */
	error = vmx_set_ctlreg(HV_VMX_CAP_PROCBASED,
			       PROCBASED_CTLS_ONE_SETTING,
			       PROCBASED_CTLS_ZERO_SETTING, &procbased_ctls);
	if (error) {
		printf("vmx_init: processor does not support desired primary "
		       "processor-based controls\n");
		return (error);
	}

	/* Clear the processor-based ctl bits that are set on demand */
	procbased_ctls &= ~PROCBASED_CTLS_WINDOW_SETTING;

	/* Check support for secondary processor-based VM-execution controls */
	error = vmx_set_ctlreg(HV_VMX_CAP_PROCBASED2,
			       PROCBASED_CTLS2_ONE_SETTING,
			       PROCBASED_CTLS2_ZERO_SETTING, &procbased_ctls2);
	if (error) {
		printf("vmx_init: processor does not support desired secondary "
		       "processor-based controls\n");
		return (error);
	}

	/* Check support for pin-based VM-execution controls */
	error = vmx_set_ctlreg(HV_VMX_CAP_PINBASED,
			       PINBASED_CTLS_ONE_SETTING,
			       PINBASED_CTLS_ZERO_SETTING, &pinbased_ctls);
	if (error) {
		printf("vmx_init: processor does not support desired "
		       "pin-based controls\n");
		return (error);
	}

	/* Check support for VM-exit controls */
	error = vmx_set_ctlreg(HV_VMX_CAP_EXIT,
			       VM_EXIT_CTLS_ONE_SETTING,
			       VM_EXIT_CTLS_ZERO_SETTING,
			       &exit_ctls);
	if (error) {
		printf("vmx_init: processor does not support desired "
		    "exit controls\n");
		return (error);
	}

	/* Check support for VM-entry controls */
	error = vmx_set_ctlreg(HV_VMX_CAP_ENTRY,
	    VM_ENTRY_CTLS_ONE_SETTING, VM_ENTRY_CTLS_ZERO_SETTING,
	    &entry_ctls);
	if (error) {
		printf("vmx_init: processor does not support desired "
		    "entry controls\n");
		return (error);
	}

	/*
	 * Check support for optional features by testing them
	 * as individual bits
	 */
	cap_halt_exit = 1;
	cap_monitor_trap = 1;
	cap_pause_exit = 1;
	// cap_unrestricted_guest = 1;
	// cap_invpcid = 1;

	/* FIXME */
  	cr0_ones_mask = cr4_ones_mask = 0;
  	cr0_zeros_mask = cr4_zeros_mask = 0;

  	cr0_ones_mask |= (CR0_NE | CR0_ET);
  	cr0_zeros_mask |= (CR0_NW | CR0_CD);
  	cr4_ones_mask = 0x2000;

	vmx_msr_init();

	return (0);
}