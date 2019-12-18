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
 int /*<<< orphan*/  vcpu_freeze (int,int) ; 
 int /*<<< orphan*/  vm ; 
 int vm_restart_instruction (int /*<<< orphan*/ ,int) ; 

int
xh_vm_restart_instruction(int vcpu)
{
	int error;

	vcpu_freeze(vcpu, true);
	error = vm_restart_instruction(vm, vcpu);
	vcpu_freeze(vcpu, false);

	return (error);
}