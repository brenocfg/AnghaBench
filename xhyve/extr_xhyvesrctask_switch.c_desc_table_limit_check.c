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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 scalar_t__ ISLDT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEG_DESC_PRESENT (scalar_t__) ; 
 scalar_t__ SEG_DESC_UNUSABLE (scalar_t__) ; 
 scalar_t__ SEL_LIMIT (int /*<<< orphan*/ ) ; 
 int VM_REG_GUEST_GDTR ; 
 int VM_REG_GUEST_LDTR ; 
 int /*<<< orphan*/  assert (int) ; 
 int xh_vm_get_desc (int,int,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static int
desc_table_limit_check(int vcpu, uint16_t sel)
{
	uint64_t base;
	uint32_t limit, access;
	int error, reg;

	reg = ISLDT(sel) ? VM_REG_GUEST_LDTR : VM_REG_GUEST_GDTR;
	error = xh_vm_get_desc(vcpu, reg, &base, &limit, &access);
	assert(error == 0);

	if (reg == VM_REG_GUEST_LDTR) {
		if (SEG_DESC_UNUSABLE(access) || !SEG_DESC_PRESENT(access))
			return (-1);
	}

	if (limit < SEL_LIMIT(sel))
		return (-1);
	else
		return (0);
}