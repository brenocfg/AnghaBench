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
struct vcpu {int dummy; } ;
typedef  enum vcpu_state { ____Placeholder_vcpu_state } vcpu_state ;

/* Variables and functions */
 int VM_MAXCPU ; 
 int /*<<< orphan*/  vcpu_lock (struct vcpu*) ; 
 int vcpu_set_state_locked (struct vcpu*,int,int) ; 
 int /*<<< orphan*/  vcpu_unlock (struct vcpu*) ; 
 int /*<<< orphan*/  xhyve_abort (char*,int) ; 

int
vcpu_set_state(struct vm *vm, int vcpuid, enum vcpu_state newstate,
    bool from_idle)
{
	int error;
	struct vcpu *vcpu;

	if (vcpuid < 0 || vcpuid >= VM_MAXCPU)
		xhyve_abort("vm_set_run_state: invalid vcpuid %d\n", vcpuid);

	vcpu = &vm->vcpu[vcpuid];

	vcpu_lock(vcpu);
	error = vcpu_set_state_locked(vcpu, newstate, from_idle);
	vcpu_unlock(vcpu);
	return (error);
}