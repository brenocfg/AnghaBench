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
 int /*<<< orphan*/  vm ; 
 int vm_inject_nmi (int /*<<< orphan*/ ,int) ; 

int
xh_vm_inject_nmi(int vcpu)
{
	return (vm_inject_nmi(vm, vcpu));
}