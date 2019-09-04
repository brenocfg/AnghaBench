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
struct vm {struct vcpu* vcpu; } ;
struct vcpu {scalar_t__ nmi_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  VCPU_NMI_COUNT ; 
 int VM_MAXCPU ; 
 int /*<<< orphan*/  vmm_stat_incr (struct vm*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xhyve_abort (char*,...) ; 

void
vm_nmi_clear(struct vm *vm, int vcpuid)
{
	struct vcpu *vcpu;

	if (vcpuid < 0 || vcpuid >= VM_MAXCPU)
		xhyve_abort("vm_nmi_pending: invalid vcpuid %d\n", vcpuid);

	vcpu = &vm->vcpu[vcpuid];

	if (vcpu->nmi_pending == 0)
		xhyve_abort("vm_nmi_clear: inconsistent nmi_pending state\n");

	vcpu->nmi_pending = 0;
	vmm_stat_incr(vm, vcpuid, VCPU_NMI_COUNT, 1);
}