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
typedef  scalar_t__ u_int ;
struct vm {int dummy; } ;
struct vlapic {int dummy; } ;

/* Variables and functions */
 scalar_t__ MSR_APICBASE ; 
 int vlapic_set_apicbase (struct vlapic*,int /*<<< orphan*/ ) ; 
 int vlapic_write (struct vlapic*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int*) ; 
 struct vlapic* vm_lapic (struct vm*,int) ; 
 scalar_t__ x2apic_msr_to_regoff (scalar_t__) ; 

int
lapic_wrmsr(struct vm *vm, int cpu, u_int msr, uint64_t val, bool *retu)
{
	int error;
	u_int offset;
	struct vlapic *vlapic;

	vlapic = vm_lapic(vm, cpu);

	if (msr == MSR_APICBASE) {
		error = vlapic_set_apicbase(vlapic, val);
	} else {
		offset = x2apic_msr_to_regoff(msr);
		error = vlapic_write(vlapic, 0, offset, val, retu);
	}

	return (error);
}