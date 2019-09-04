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
typedef  int /*<<< orphan*/  uint64_t ;
struct vm {struct vcpu* vcpu; int /*<<< orphan*/  cookie; } ;
struct vcpu {int /*<<< orphan*/  nextrip; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  VCPU_CTR1 (struct vm*,int,char*,int /*<<< orphan*/ ) ; 
 int VMSETREG (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int VM_MAXCPU ; 
 int VM_REG_GUEST_RIP ; 
 int VM_REG_LAST ; 

int
vm_set_register(struct vm *vm, int vcpuid, int reg, uint64_t val)
{
	struct vcpu *vcpu;
	int error;

	if (vcpuid < 0 || vcpuid >= VM_MAXCPU)
		return (EINVAL);

	if (reg >= VM_REG_LAST)
		return (EINVAL);

	error = VMSETREG(vm->cookie, vcpuid, reg, val);
	if (error || reg != VM_REG_GUEST_RIP)
		return (error);

	/* Set 'nextrip' to match the value of %rip */
	VCPU_CTR1(vm, vcpuid, "Setting nextrip to %#llx", val);
	vcpu = &vm->vcpu[vcpuid];
	vcpu->nextrip = val;
	return (0);
}