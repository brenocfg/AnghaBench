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
typedef  int uint64_t ;
struct vmx {int dummy; } ;
typedef  scalar_t__ hv_x86_reg_t ;
typedef  int /*<<< orphan*/  hv_vcpuid_t ;

/* Variables and functions */
 int EFER_LMA ; 
 scalar_t__ HV_X86_REGISTERS_MAX ; 
 int VMCS_ENTRY_CTLS ; 
 int VMCS_IDENT (int) ; 
 int VM_ENTRY_GUEST_LMA ; 
 int VM_ENTRY_LOAD_EFER ; 
 int VM_REG_GUEST_CR3 ; 
 int VM_REG_GUEST_EFER ; 
 int VM_REG_GUEST_INTR_SHADOW ; 
 int entry_ctls ; 
 int /*<<< orphan*/  hv_vcpu_invalidate_tlb (int /*<<< orphan*/ ) ; 
 scalar_t__* hvregs ; 
 int /*<<< orphan*/  reg_write (int,scalar_t__,int) ; 
 int /*<<< orphan*/  vmcs_getreg (int,int,int*) ; 
 int vmcs_setreg (int,int,int) ; 
 int vmx_modify_intr_shadow (struct vmx*,int,int) ; 
 int vmx_shadow_reg (int) ; 

__attribute__((used)) static int
vmx_setreg(void *arg, int vcpu, int reg, uint64_t val)
{
	int error, shadow;
	uint64_t ctls;
	hv_x86_reg_t hvreg;
	struct vmx *vmx = arg;

	if (reg == VM_REG_GUEST_INTR_SHADOW)
		return (vmx_modify_intr_shadow(vmx, vcpu, val));

	hvreg = hvregs[reg];
	if (hvreg != HV_X86_REGISTERS_MAX) {
		reg_write(vcpu, hvreg, val);
		return (0);
	}

	error = vmcs_setreg(vcpu, reg, val);

	if (error == 0) {
		/*
		 * If the "load EFER" VM-entry control is 1 then the
		 * value of EFER.LMA must be identical to "IA-32e mode guest"
		 * bit in the VM-entry control.
		 */
		if ((entry_ctls & VM_ENTRY_LOAD_EFER) != 0 &&
		    (reg == VM_REG_GUEST_EFER)) {
			vmcs_getreg(vcpu, VMCS_IDENT(VMCS_ENTRY_CTLS), &ctls);
			if (val & EFER_LMA)
				ctls |= VM_ENTRY_GUEST_LMA;
			else
				ctls &= ~VM_ENTRY_GUEST_LMA;
			vmcs_setreg(vcpu, VMCS_IDENT(VMCS_ENTRY_CTLS), ctls);
		}

		shadow = vmx_shadow_reg(reg);
		if (shadow > 0) {
			/*
			 * Store the unmodified value in the shadow
			 */			
			error = vmcs_setreg(vcpu, VMCS_IDENT(shadow), val);
		}

		if (reg == VM_REG_GUEST_CR3) {
			/*
			 * Invalidate the guest vcpu's TLB mappings to emulate
			 * the behavior of updating %cr3.
			 */
			hv_vcpu_invalidate_tlb((hv_vcpuid_t) vcpu);
		}
	}

	return (error);
}