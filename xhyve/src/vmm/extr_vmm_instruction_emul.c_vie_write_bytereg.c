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
typedef  int uint8_t ;
typedef  int uint64_t ;
struct vie {int dummy; } ;
typedef  enum vm_reg_name { ____Placeholder_vm_reg_name } vm_reg_name ;

/* Variables and functions */
 int /*<<< orphan*/  vie_calc_bytereg (struct vie*,int*,int*) ; 
 int vm_get_register (void*,int,int,int*) ; 
 int vm_set_register (void*,int,int,int) ; 

__attribute__((used)) static int
vie_write_bytereg(void *vm, int vcpuid, struct vie *vie, uint8_t byte)
{
	uint64_t origval, val, mask;
	int error, lhbr;
	enum vm_reg_name reg;

	vie_calc_bytereg(vie, &reg, &lhbr);
	error = vm_get_register(vm, vcpuid, (int) reg, &origval);
	if (error == 0) {
		val = byte;
		mask = 0xff;
		if (lhbr) {
			/*
			 * Shift left by 8 to store 'byte' in a legacy high
			 * byte register.
			 */
			val <<= 8;
			mask <<= 8;
		}
		val |= origval & ~mask;
		error = vm_set_register(vm, vcpuid, (int) reg, val);
	}
	return (error);
}