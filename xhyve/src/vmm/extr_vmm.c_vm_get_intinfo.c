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
struct vm {struct vcpu* vcpu; } ;
struct vcpu {int /*<<< orphan*/  exitintinfo; } ;

/* Variables and functions */
 int EINVAL ; 
 int VM_MAXCPU ; 
 int /*<<< orphan*/  vcpu_exception_intinfo (struct vcpu*) ; 

int
vm_get_intinfo(struct vm *vm, int vcpuid, uint64_t *info1, uint64_t *info2)
{
	struct vcpu *vcpu;

	if (vcpuid < 0 || vcpuid >= VM_MAXCPU)
		return (EINVAL);

	vcpu = &vm->vcpu[vcpuid];
	*info1 = vcpu->exitintinfo;
	*info2 = vcpu_exception_intinfo(vcpu);
	return (0);
}