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
typedef  enum vm_cpu_mode { ____Placeholder_vm_cpu_mode } vm_cpu_mode ;

/* Variables and functions */
 int CPU_MODE_64BIT ; 
 int CPU_MODE_COMPATIBILITY ; 
 int CPU_MODE_PROTECTED ; 
 int CPU_MODE_REAL ; 
 int CR0_PE ; 
 int EFER_LMA ; 
 int /*<<< orphan*/  VMCS_GUEST_CR0 ; 
 int /*<<< orphan*/  VMCS_GUEST_CS_ACCESS_RIGHTS ; 
 int /*<<< orphan*/  VMCS_GUEST_IA32_EFER ; 
 int vmcs_read (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum vm_cpu_mode
vmx_cpu_mode(int vcpu)
{
	uint32_t csar;

	if (vmcs_read(vcpu, VMCS_GUEST_IA32_EFER) & EFER_LMA) {
		csar = (uint32_t) vmcs_read(vcpu, VMCS_GUEST_CS_ACCESS_RIGHTS);
		if (csar & 0x2000)
			return (CPU_MODE_64BIT);	/* CS.L = 1 */
		else
			return (CPU_MODE_COMPATIBILITY);
	} else if (vmcs_read(vcpu, VMCS_GUEST_CR0) & CR0_PE) {
		return (CPU_MODE_PROTECTED);
	} else {
		return (CPU_MODE_REAL);
	}
}