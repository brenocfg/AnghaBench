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
struct vm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IDT_PF ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  VCPU_CTR2 (struct vm*,int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_REG_GUEST_CR2 ; 
 int /*<<< orphan*/  vm_inject_fault (struct vm*,int,int /*<<< orphan*/ ,int,int) ; 
 int vm_set_register (struct vm*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
vm_inject_pf(void *vmarg, int vcpuid, int error_code, uint64_t cr2)
{
	struct vm *vm;
	int error;

	vm = vmarg;
	VCPU_CTR2(vm, vcpuid, "Injecting page fault: error_code %#x, cr2 %#llx",
	    error_code, cr2);

	error = vm_set_register(vm, vcpuid, VM_REG_GUEST_CR2, cr2);
	KASSERT(error == 0, ("vm_set_register(cr2) error %d", error));

	vm_inject_fault(vm, vcpuid, IDT_PF, 1, error_code);
}