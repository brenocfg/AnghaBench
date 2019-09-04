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
struct vm {int /*<<< orphan*/  cookie; } ;

/* Variables and functions */
 int EINVAL ; 
 int VMGETREG (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int VM_MAXCPU ; 
 int VM_REG_LAST ; 

int
vm_get_register(struct vm *vm, int vcpu, int reg, uint64_t *retval)
{

	if (vcpu < 0 || vcpu >= VM_MAXCPU)
		return (EINVAL);

	if (reg >= VM_REG_LAST)
		return (EINVAL);

	return (VMGETREG(vm->cookie, vcpu, reg, retval));
}