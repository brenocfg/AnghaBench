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
typedef  enum vm_paging_mode { ____Placeholder_vm_paging_mode } vm_paging_mode ;

/* Variables and functions */
 int CR0_PG ; 
 int CR4_PAE ; 
 int EFER_LME ; 
 int PAGING_MODE_32 ; 
 int PAGING_MODE_64 ; 
 int PAGING_MODE_FLAT ; 
 int PAGING_MODE_PAE ; 
 int /*<<< orphan*/  VMCS_GUEST_CR0 ; 
 int /*<<< orphan*/  VMCS_GUEST_CR4 ; 
 int /*<<< orphan*/  VMCS_GUEST_IA32_EFER ; 
 int vmcs_read (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum vm_paging_mode
vmx_paging_mode(int vcpu)
{

	if (!(vmcs_read(vcpu, VMCS_GUEST_CR0) & CR0_PG))
		return (PAGING_MODE_FLAT);
	if (!(vmcs_read(vcpu, VMCS_GUEST_CR4) & CR4_PAE))
		return (PAGING_MODE_32);
	if (vmcs_read(vcpu, VMCS_GUEST_IA32_EFER) & EFER_LME)
		return (PAGING_MODE_64);
	else
		return (PAGING_MODE_PAE);
}