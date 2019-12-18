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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  VM_REG_GUEST_CS ; 
 int /*<<< orphan*/  VM_REG_GUEST_RIP ; 
 int XHYVE_PAGE_SHIFT ; 
 int /*<<< orphan*/  assert (int) ; 
 int xh_vm_get_desc (int,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int xh_vm_set_desc (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xh_vm_set_register (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
spinup_ap_realmode(int newcpu, uint64_t *rip)
{
	int vector, error;
	uint16_t cs;
	uint64_t desc_base;
	uint32_t desc_limit, desc_access;

	vector = (int) (*rip >> XHYVE_PAGE_SHIFT);
	*rip = 0;

	/*
	 * Update the %cs and %rip of the guest so that it starts
	 * executing real mode code at at 'vector << 12'.
	 */
	error = xh_vm_set_register(newcpu, VM_REG_GUEST_RIP, *rip);
	assert(error == 0);

	error = xh_vm_get_desc(newcpu, VM_REG_GUEST_CS, &desc_base, &desc_limit,
		&desc_access);
	assert(error == 0);

	desc_base = (uint64_t) (vector << XHYVE_PAGE_SHIFT);
	error = xh_vm_set_desc(newcpu, VM_REG_GUEST_CS, desc_base, desc_limit,
		desc_access);
	assert(error == 0);

	cs = (uint16_t) ((vector << XHYVE_PAGE_SHIFT) >> 4);
	error = xh_vm_set_register(newcpu, VM_REG_GUEST_CS, cs);
	assert(error == 0);
}