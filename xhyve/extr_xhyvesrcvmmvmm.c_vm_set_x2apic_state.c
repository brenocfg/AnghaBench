#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vm {TYPE_1__* vcpu; } ;
typedef  enum x2apic_state { ____Placeholder_x2apic_state } x2apic_state ;
struct TYPE_2__ {int x2apic_state; } ;

/* Variables and functions */
 int EINVAL ; 
 int VM_MAXCPU ; 
 int X2APIC_STATE_LAST ; 
 int /*<<< orphan*/  vlapic_set_x2apic_state (struct vm*,int,int) ; 

int
vm_set_x2apic_state(struct vm *vm, int vcpuid, enum x2apic_state state)
{
	if (vcpuid < 0 || vcpuid >= VM_MAXCPU)
		return (EINVAL);

	if (state >= X2APIC_STATE_LAST)
		return (EINVAL);

	vm->vcpu[vcpuid].x2apic_state = state;

	vlapic_set_x2apic_state(vm, vcpuid, state);

	return (0);
}