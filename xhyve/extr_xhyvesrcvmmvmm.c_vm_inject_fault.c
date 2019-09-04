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
typedef  int /*<<< orphan*/  uint32_t ;
struct vm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int vm_inject_exception (struct vm*,int,int,int,int /*<<< orphan*/ ,int) ; 

void
vm_inject_fault(void *vmarg, int vcpuid, int vector, int errcode_valid,
    int errcode)
{
	struct vm *vm;
	int error, restart_instruction;

	vm = vmarg;
	restart_instruction = 1;

	error = vm_inject_exception(vm, vcpuid, vector, errcode_valid,
	    ((uint32_t) errcode), restart_instruction);
	KASSERT(error == 0, ("vm_inject_exception error %d", error));
}