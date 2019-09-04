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
 int /*<<< orphan*/  vm ; 
 int vm_get_x2apic_state (int /*<<< orphan*/ ,int,int*) ; 

int
xh_vm_get_x2apic_state(int vcpu, enum x2apic_state *s)
{
	return (vm_get_x2apic_state(vm, vcpu, s));
}