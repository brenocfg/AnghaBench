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
struct vm {int /*<<< orphan*/  active_cpus; int /*<<< orphan*/  suspended_cpus; } ;

/* Variables and functions */
 scalar_t__ CPU_CMP (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int EBUSY ; 
 int /*<<< orphan*/  vm_cleanup (struct vm*,int) ; 
 int /*<<< orphan*/  vm_init (struct vm*,int) ; 

int
vm_reinit(struct vm *vm)
{
	int error;

	/*
	 * A virtual machine can be reset only if all vcpus are suspended.
	 */
	if (CPU_CMP(&vm->suspended_cpus, &vm->active_cpus) == 0) {
		vm_cleanup(vm, false);
		vm_init(vm, false);
		error = 0;
	} else {
		error = EBUSY;
	}

	return (error);
}