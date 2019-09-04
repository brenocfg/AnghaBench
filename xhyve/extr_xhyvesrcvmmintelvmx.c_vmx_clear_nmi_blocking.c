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
typedef  int /*<<< orphan*/  uint32_t ;
struct vmx {int /*<<< orphan*/  vm; } ;

/* Variables and functions */
 int /*<<< orphan*/  VCPU_CTR0 (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  VMCS_GUEST_INTERRUPTIBILITY ; 
 int /*<<< orphan*/  VMCS_INTERRUPTIBILITY_NMI_BLOCKING ; 
 scalar_t__ vmcs_read (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmcs_write (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vmx_clear_nmi_blocking(struct vmx *vmx, int vcpuid)
{
	uint32_t gi;

	VCPU_CTR0(vmx->vm, vcpuid, "Clear Virtual-NMI blocking");
	gi = (uint32_t) vmcs_read(vcpuid, VMCS_GUEST_INTERRUPTIBILITY);
	gi &= ~VMCS_INTERRUPTIBILITY_NMI_BLOCKING;
	vmcs_write(vcpuid, VMCS_GUEST_INTERRUPTIBILITY, gi);
}