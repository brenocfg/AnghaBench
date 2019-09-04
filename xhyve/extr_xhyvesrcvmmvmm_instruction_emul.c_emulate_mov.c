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
typedef  int uint8_t ;
typedef  int uint64_t ;
struct TYPE_2__ {int op_byte; } ;
struct vie {int opsize; size_t reg; int /*<<< orphan*/  immediate; TYPE_1__ op; } ;
typedef  int (* mem_region_write_t ) (void*,int,int,int,int,void*) ;
typedef  int (* mem_region_read_t ) (void*,int,int,int*,int,void*) ;
typedef  enum vm_reg_name { ____Placeholder_vm_reg_name } vm_reg_name ;

/* Variables and functions */
 int EINVAL ; 
 int VM_REG_GUEST_RAX ; 
 int* gpr_map ; 
 int* size2mask ; 
 int vie_read_bytereg (void*,int,struct vie*,int*) ; 
 int vie_read_register (void*,int,int,int*) ; 
 int vie_update_register (void*,int,int,int,int) ; 
 int vie_write_bytereg (void*,int,struct vie*,int) ; 

__attribute__((used)) static int
emulate_mov(void *vm, int vcpuid, uint64_t gpa, struct vie *vie,
	    mem_region_read_t memread, mem_region_write_t memwrite, void *arg)
{
	int error, size;
	enum vm_reg_name reg;
	uint8_t byte;
	uint64_t val;

	size = vie->opsize;
	error = EINVAL;

	switch (vie->op.op_byte) {
	case 0x88:
		/*
		 * MOV byte from reg (ModRM:reg) to mem (ModRM:r/m)
		 * 88/r:	mov r/m8, r8
		 * REX + 88/r:	mov r/m8, r8 (%ah, %ch, %dh, %bh not available)
		 */
		size = 1;	/* override for byte operation */
		error = vie_read_bytereg(vm, vcpuid, vie, &byte);
		if (error == 0)
			error = memwrite(vm, vcpuid, gpa, byte, size, arg);
		break;
	case 0x89:
		/*
		 * MOV from reg (ModRM:reg) to mem (ModRM:r/m)
		 * 89/r:	mov r/m16, r16
		 * 89/r:	mov r/m32, r32
		 * REX.W + 89/r	mov r/m64, r64
		 */
		reg = gpr_map[vie->reg];
		error = vie_read_register(vm, vcpuid, reg, &val);
		if (error == 0) {
			val &= size2mask[size];
			error = memwrite(vm, vcpuid, gpa, val, size, arg);
		}
		break;
	case 0x8A:
		/*
		 * MOV byte from mem (ModRM:r/m) to reg (ModRM:reg)
		 * 8A/r:	mov r8, r/m8
		 * REX + 8A/r:	mov r8, r/m8
		 */
		size = 1;	/* override for byte operation */
		error = memread(vm, vcpuid, gpa, &val, size, arg);
		if (error == 0)
			error = vie_write_bytereg(vm, vcpuid, vie, ((uint8_t) val));
		break;
	case 0x8B:
		/*
		 * MOV from mem (ModRM:r/m) to reg (ModRM:reg)
		 * 8B/r:	mov r16, r/m16
		 * 8B/r:	mov r32, r/m32
		 * REX.W 8B/r:	mov r64, r/m64
		 */
		error = memread(vm, vcpuid, gpa, &val, size, arg);
		if (error == 0) {
			reg = gpr_map[vie->reg];
			error = vie_update_register(vm, vcpuid, reg, val, size);
		}
		break;
	case 0xA1:
		/*
		 * MOV from seg:moffset to AX/EAX/RAX
		 * A1:		mov AX, moffs16
		 * A1:		mov EAX, moffs32
		 * REX.W + A1:	mov RAX, moffs64
		 */
		error = memread(vm, vcpuid, gpa, &val, size, arg);
		if (error == 0) {
			reg = VM_REG_GUEST_RAX;
			error = vie_update_register(vm, vcpuid, reg, val, size);
		}
		break;
	case 0xA3:
		/*
		 * MOV from AX/EAX/RAX to seg:moffset
		 * A3:		mov moffs16, AX
		 * A3:		mov moffs32, EAX 
		 * REX.W + A3:	mov moffs64, RAX
		 */
		error = vie_read_register(vm, vcpuid, VM_REG_GUEST_RAX, &val);
		if (error == 0) {
			val &= size2mask[size];
			error = memwrite(vm, vcpuid, gpa, val, size, arg);
		}
		break;
	case 0xC6:
		/*
		 * MOV from imm8 to mem (ModRM:r/m)
		 * C6/0		mov r/m8, imm8
		 * REX + C6/0	mov r/m8, imm8
		 */
		size = 1;	/* override for byte operation */
		error = memwrite(vm, vcpuid, gpa, ((uint64_t) vie->immediate), size,
			arg);
		break;
	case 0xC7:
		/*
		 * MOV from imm16/imm32 to mem (ModRM:r/m)
		 * C7/0		mov r/m16, imm16
		 * C7/0		mov r/m32, imm32
		 * REX.W + C7/0	mov r/m64, imm32 (sign-extended to 64-bits)
		 */
		val = ((uint64_t) vie->immediate) & size2mask[size];
		error = memwrite(vm, vcpuid, gpa, val, size, arg);
		break;
	default:
		break;
	}

	return (error);
}