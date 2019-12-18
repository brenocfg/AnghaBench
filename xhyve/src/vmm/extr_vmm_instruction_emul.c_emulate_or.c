#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_2__ {int op_byte; } ;
struct vie {int opsize; scalar_t__ immediate; TYPE_1__ op; } ;
typedef  int (* mem_region_write_t ) (void*,int,int,int,int,void*) ;
typedef  int (* mem_region_read_t ) (void*,int,int,int*,int,void*) ;

/* Variables and functions */
 int EINVAL ; 
 int PSL_N ; 
 int PSL_PF ; 
 int PSL_Z ; 
 scalar_t__ RFLAGS_STATUS_BITS ; 
 int /*<<< orphan*/  VM_REG_GUEST_RFLAGS ; 
 int getcc (int,int,int /*<<< orphan*/ ) ; 
 int vie_read_register (void*,int,int /*<<< orphan*/ ,int*) ; 
 int vie_update_register (void*,int,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
emulate_or(void *vm, int vcpuid, uint64_t gpa, struct vie *vie,
	    mem_region_read_t memread, mem_region_write_t memwrite, void *arg)
{
	int error, size;
	uint64_t val1, result, rflags, rflags2;

	size = vie->opsize;
	result = 0;
	error = EINVAL;

	switch (vie->op.op_byte) {
	case 0x81:
	case 0x83:
		/*
		 * OR mem (ModRM:r/m) with immediate and store the
		 * result in mem.
		 *
		 * 81 /1		or r/m16, imm16
		 * 81 /1		or r/m32, imm32
		 * REX.W + 81 /1	or r/m64, imm32 sign-extended to 64
		 *
		 * 83 /1		or r/m16, imm8 sign-extended to 16
		 * 83 /1		or r/m32, imm8 sign-extended to 32
		 * REX.W + 83/1		or r/m64, imm8 sign-extended to 64
		 */

		/* get the first operand */
                error = memread(vm, vcpuid, gpa, &val1, size, arg);
                if (error)
			break;

                /*
		 * perform the operation with the pre-fetched immediate
		 * operand and write the result
		 */
                result = val1 | ((uint64_t) vie->immediate);
                error = memwrite(vm, vcpuid, gpa, result, size, arg);
		break;
	default:
		break;
	}
	if (error)
		return (error);

	error = vie_read_register(vm, vcpuid, VM_REG_GUEST_RFLAGS, &rflags);
	if (error)
		return (error);

	/*
	 * OF and CF are cleared; the SF, ZF and PF flags are set according
	 * to the result; AF is undefined.
	 *
	 * The updated status flags are obtained by subtracting 0 from 'result'.
	 */
	rflags2 = getcc(size, result, 0);
	rflags &= ~((uint64_t) RFLAGS_STATUS_BITS);
	rflags |= rflags2 & (PSL_PF | PSL_Z | PSL_N);

	error = vie_update_register(vm, vcpuid, VM_REG_GUEST_RFLAGS, rflags, 8);
	return (error);
}