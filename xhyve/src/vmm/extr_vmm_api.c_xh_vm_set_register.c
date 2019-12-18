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

/* Variables and functions */
 int /*<<< orphan*/  vcpu_freeze (int,int) ; 
 int /*<<< orphan*/  vm ; 
 int vm_set_register (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

int
xh_vm_set_register(int vcpu, int reg, uint64_t val)
{
	int error;

	vcpu_freeze(vcpu, true);
	error = vm_set_register(vm, vcpu, reg, val);
	vcpu_freeze(vcpu, false);

	return (error);	
}