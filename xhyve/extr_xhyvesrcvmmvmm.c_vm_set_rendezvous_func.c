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
typedef  int /*<<< orphan*/  vm_rendezvous_func_t ;
struct vm {int /*<<< orphan*/  rendezvous_func; } ;

/* Variables and functions */
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void
vm_set_rendezvous_func(struct vm *vm, vm_rendezvous_func_t func)
{
	/*
	 * Update 'rendezvous_func' and execute a write memory barrier to
	 * ensure that it is visible across all host cpus. This is not needed
	 * for correctness but it does ensure that all the vcpus will notice
	 * that the rendezvous is requested immediately.
	 */
	vm->rendezvous_func = func;
	wmb();
}