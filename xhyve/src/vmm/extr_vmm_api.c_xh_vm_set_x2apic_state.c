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
typedef  enum x2apic_state { ____Placeholder_x2apic_state } x2apic_state ;

/* Variables and functions */
 int /*<<< orphan*/  vcpu_freeze (int,int) ; 
 int /*<<< orphan*/  vm ; 
 int vm_set_x2apic_state (int /*<<< orphan*/ ,int,int) ; 

int
xh_vm_set_x2apic_state(int vcpu, enum x2apic_state s)
{
	int error;

	vcpu_freeze(vcpu, true);
	error = vm_set_x2apic_state(vm, vcpu, s);
	vcpu_freeze(vcpu, false);

	return (error);
}