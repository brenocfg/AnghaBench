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
typedef  scalar_t__ uint8_t ;
typedef  int uint64_t ;
struct vie {int dummy; } ;
typedef  enum vm_reg_name { ____Placeholder_vm_reg_name } vm_reg_name ;

/* Variables and functions */
 int /*<<< orphan*/  vie_calc_bytereg (struct vie*,int*,int*) ; 
 int vm_get_register (void*,int,int,int*) ; 

__attribute__((used)) static int
vie_read_bytereg(void *vm, int vcpuid, struct vie *vie, uint8_t *rval)
{
	uint64_t val;
	int error, lhbr;
	enum vm_reg_name reg;

	vie_calc_bytereg(vie, &reg, &lhbr);
	error = vm_get_register(vm, vcpuid, (int) reg, &val);

	/*
	 * To obtain the value of a legacy high byte register shift the
	 * base register right by 8 bits (%ah = %rax >> 8).
	 */
	if (lhbr)
		*rval = (uint8_t) (val >> 8);
	else
		*rval = (uint8_t) val;
	return (error);
}