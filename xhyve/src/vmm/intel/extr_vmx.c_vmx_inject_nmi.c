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
typedef  int uint32_t ;
struct vmx {int /*<<< orphan*/  vm; } ;

/* Variables and functions */
 int IDT_NMI ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int NMI_BLOCKING ; 
 int /*<<< orphan*/  VCPU_CTR0 (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  VMCS_ENTRY_INTR_INFO ; 
 int /*<<< orphan*/  VMCS_GUEST_INTERRUPTIBILITY ; 
 int VMCS_INTR_T_NMI ; 
 int VMCS_INTR_VALID ; 
 int /*<<< orphan*/  vm_nmi_clear (int /*<<< orphan*/ ,int) ; 
 scalar_t__ vmcs_read (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmcs_write (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
vmx_inject_nmi(struct vmx *vmx, int vcpu)
{
	uint32_t gi, info;

	gi = (uint32_t) vmcs_read(vcpu, VMCS_GUEST_INTERRUPTIBILITY);
	KASSERT((gi & NMI_BLOCKING) == 0, ("vmx_inject_nmi: invalid guest "
	    "interruptibility-state %#x", gi));

	info = (uint32_t) vmcs_read(vcpu, VMCS_ENTRY_INTR_INFO);
	KASSERT((info & VMCS_INTR_VALID) == 0, ("vmx_inject_nmi: invalid "
	    "VM-entry interruption information %#x", info));

	/*
	 * Inject the virtual NMI. The vector must be the NMI IDT entry
	 * or the VMCS entry check will fail.
	 */
	info = IDT_NMI | VMCS_INTR_T_NMI | VMCS_INTR_VALID;
	vmcs_write(vcpu, VMCS_ENTRY_INTR_INFO, info);

	VCPU_CTR0(vmx->vm, vcpu, "Injecting vNMI");

	/* Clear the request */
	vm_nmi_clear(vmx->vm, vcpu);
}