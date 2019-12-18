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

/* Variables and functions */
 int lapic_set_local_intr (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  vm ; 

int
xh_vm_lapic_local_irq(int vcpu, int vector)
{
	return (lapic_set_local_intr(vm, vcpu, vector));
}