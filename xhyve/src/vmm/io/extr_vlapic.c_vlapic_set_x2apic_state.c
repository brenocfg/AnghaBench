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
typedef  scalar_t__ uint64_t ;
struct vm {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* enable_x2apic_mode ) (struct vlapic*) ;} ;
struct vlapic {TYPE_1__ ops; struct LAPIC* apic_page; scalar_t__ msr_apicbase; } ;
struct LAPIC {int dfr; scalar_t__ ldr; int /*<<< orphan*/  id; } ;
typedef  enum x2apic_state { ____Placeholder_x2apic_state } x2apic_state ;

/* Variables and functions */
 scalar_t__ APICBASE_X2APIC ; 
 int X2APIC_DISABLED ; 
 int X2APIC_ENABLED ; 
 int /*<<< orphan*/  stub1 (struct vlapic*) ; 
 int /*<<< orphan*/  vlapic_get_id (struct vlapic*) ; 
 struct vlapic* vm_lapic (struct vm*,int) ; 
 scalar_t__ x2apic (struct vlapic*) ; 
 scalar_t__ x2apic_ldr (struct vlapic*) ; 

void
vlapic_set_x2apic_state(struct vm *vm, int vcpuid, enum x2apic_state state)
{
	struct vlapic *vlapic;
	struct LAPIC *lapic;

	vlapic = vm_lapic(vm, vcpuid);

	if (state == X2APIC_DISABLED)
		vlapic->msr_apicbase &= ~((uint64_t) APICBASE_X2APIC);
	else
		vlapic->msr_apicbase |= APICBASE_X2APIC;

	/*
	 * Reset the local APIC registers whose values are mode-dependent.
	 *
	 * XXX this works because the APIC mode can be changed only at vcpu
	 * initialization time.
	 */
	lapic = vlapic->apic_page;
	lapic->id = vlapic_get_id(vlapic);
	if (x2apic(vlapic)) {
		lapic->ldr = x2apic_ldr(vlapic);
		lapic->dfr = 0;
	} else {
		lapic->ldr = 0;
		lapic->dfr = 0xffffffff;
	}

	if (state == X2APIC_ENABLED) {
		if (vlapic->ops.enable_x2apic_mode)
			(*vlapic->ops.enable_x2apic_mode)(vlapic);
	}
}