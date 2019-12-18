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
struct vm_guest_paging {int dummy; } ;
struct vie {int reg; } ;
typedef  int /*<<< orphan*/  mem_region_write_t ;
typedef  int /*<<< orphan*/  mem_region_read_t ;

/* Variables and functions */
 int EINVAL ; 
 int emulate_stack_op (void*,int,int /*<<< orphan*/ ,struct vie*,struct vm_guest_paging*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int
emulate_pop(void *vm, int vcpuid, uint64_t mmio_gpa, struct vie *vie,
    struct vm_guest_paging *paging, mem_region_read_t memread,
    mem_region_write_t memwrite, void *arg)
{
	int error;

	/*
	 * Table A-6, "Opcode Extensions", Intel SDM, Vol 2.
	 *
	 * POP is part of the group 1A extended opcodes and is identified
	 * by ModRM:reg = b000.
	 */
	if ((vie->reg & 7) != 0)
		return (EINVAL);

	error = emulate_stack_op(vm, vcpuid, mmio_gpa, vie, paging, memread,
	    memwrite, arg);
	return (error);
}