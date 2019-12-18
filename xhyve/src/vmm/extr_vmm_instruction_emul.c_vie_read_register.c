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
typedef  enum vm_reg_name { ____Placeholder_vm_reg_name } vm_reg_name ;

/* Variables and functions */
 int vm_get_register (void*,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
vie_read_register(void *vm, int vcpuid, enum vm_reg_name reg, uint64_t *rval)
{
	int error;

	error = vm_get_register(vm, vcpuid, (int) reg, rval);

	return (error);
}