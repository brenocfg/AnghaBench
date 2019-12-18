#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  void* uint32_t ;
struct vmx {TYPE_2__* state; TYPE_1__* cap; } ;
typedef  scalar_t__ hv_vcpuid_t ;
struct TYPE_4__ {int /*<<< orphan*/  nextrip; } ;
struct TYPE_3__ {void* proc_ctls2; void* proc_ctls; scalar_t__ set; } ;

/* Variables and functions */
 int /*<<< orphan*/  HV_VCPU_DEFAULT ; 
 int IDT_MC ; 
 int /*<<< orphan*/  MSR_FSBASE ; 
 int /*<<< orphan*/  MSR_GSBASE ; 
 int /*<<< orphan*/  MSR_IA32_TSC_AUX ; 
 int /*<<< orphan*/  MSR_SYSENTER_CS_MSR ; 
 int /*<<< orphan*/  MSR_SYSENTER_EIP_MSR ; 
 int /*<<< orphan*/  MSR_SYSENTER_ESP_MSR ; 
 int /*<<< orphan*/  MSR_TSC ; 
 int /*<<< orphan*/  VMCS_ENTRY_CTLS ; 
 int /*<<< orphan*/  VMCS_EXCEPTION_BITMAP ; 
 int /*<<< orphan*/  VMCS_EXIT_CTLS ; 
 int /*<<< orphan*/  VMCS_PIN_BASED_CTLS ; 
 int /*<<< orphan*/  VMCS_PRI_PROC_BASED_CTLS ; 
 int /*<<< orphan*/  VMCS_SEC_PROC_BASED_CTLS ; 
 void* entry_ctls ; 
 void* exit_ctls ; 
 scalar_t__ hv_vcpu_create (scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ hv_vcpu_enable_native_msr (scalar_t__,int /*<<< orphan*/ ,int) ; 
 void* pinbased_ctls ; 
 void* procbased_ctls ; 
 void* procbased_ctls2 ; 
 scalar_t__ vcpu_trace_exceptions () ; 
 int /*<<< orphan*/  vmcs_write (int,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  vmx_msr_guest_init (struct vmx*,int) ; 
 int vmx_setup_cr0_shadow (int,int) ; 
 int vmx_setup_cr4_shadow (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhyve_abort (char*,...) ; 

__attribute__((used)) static int
vmx_vcpu_init(void *arg, int vcpuid) {
	uint32_t exc_bitmap;
	struct vmx *vmx;
	hv_vcpuid_t hvid;
	int error;

	vmx = (struct vmx *) arg;

	if (hv_vcpu_create(&hvid, HV_VCPU_DEFAULT)) {
		xhyve_abort("hv_vcpu_create failed\n");
	}

	if (hvid != ((hv_vcpuid_t) vcpuid)) {
		/* FIXME */
		xhyve_abort("vcpu id mismatch\n");
	}

	if (hv_vcpu_enable_native_msr(hvid, MSR_GSBASE, 1) ||
		hv_vcpu_enable_native_msr(hvid, MSR_FSBASE, 1) ||
		hv_vcpu_enable_native_msr(hvid, MSR_SYSENTER_CS_MSR, 1) ||
		hv_vcpu_enable_native_msr(hvid, MSR_SYSENTER_ESP_MSR, 1) ||
		hv_vcpu_enable_native_msr(hvid, MSR_SYSENTER_EIP_MSR, 1) ||
		hv_vcpu_enable_native_msr(hvid, MSR_TSC, 1) ||
		hv_vcpu_enable_native_msr(hvid, MSR_IA32_TSC_AUX, 1))
	{
		xhyve_abort("vmx_vcpu_init: error setting guest msr access\n");
	}

	vmx_msr_guest_init(vmx, vcpuid);

	vmcs_write(vcpuid, VMCS_PIN_BASED_CTLS, pinbased_ctls);
	vmcs_write(vcpuid, VMCS_PRI_PROC_BASED_CTLS, procbased_ctls);
	vmcs_write(vcpuid, VMCS_SEC_PROC_BASED_CTLS, procbased_ctls2);
	vmcs_write(vcpuid, VMCS_EXIT_CTLS, exit_ctls);
	vmcs_write(vcpuid, VMCS_ENTRY_CTLS, entry_ctls);

	/* exception bitmap */
	if (vcpu_trace_exceptions())
		exc_bitmap = 0xffffffff;
	else
		exc_bitmap = 1 << IDT_MC;

	vmcs_write(vcpuid, VMCS_EXCEPTION_BITMAP, exc_bitmap);

	vmx->cap[vcpuid].set = 0;
	vmx->cap[vcpuid].proc_ctls = procbased_ctls;
	vmx->cap[vcpuid].proc_ctls2 = procbased_ctls2;
	vmx->state[vcpuid].nextrip = ~(uint64_t) 0;

	/*
	 * Set up the CR0/4 shadows, and init the read shadow
	 * to the power-on register value from the Intel Sys Arch.
	 *  CR0 - 0x60000010
	 *  CR4 - 0
	 */
	error = vmx_setup_cr0_shadow(vcpuid, 0x60000010);
	if (error != 0)
		xhyve_abort("vmx_setup_cr0_shadow %d\n", error);

	error = vmx_setup_cr4_shadow(vcpuid, 0);

	if (error != 0)
		xhyve_abort("vmx_setup_cr4_shadow %d\n", error);

	return (0);
}