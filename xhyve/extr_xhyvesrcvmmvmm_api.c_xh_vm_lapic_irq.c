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
 int lapic_intr_edge (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  vm ; 

int
xh_vm_lapic_irq(int vcpu, int vector)
{
	return (lapic_intr_edge(vm, vcpu, vector));
}