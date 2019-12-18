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
typedef  int uint32_t ;
struct vlapic {int esr_pending; int esr_firing; int /*<<< orphan*/  vcpuid; int /*<<< orphan*/  vm; } ;

/* Variables and functions */
 int APIC_LVT_DM_FIXED ; 
 int /*<<< orphan*/  APIC_OFFSET_ERROR_LVT ; 
 int /*<<< orphan*/  VLAPIC_INTR_ERROR ; 
 scalar_t__ vlapic_fire_lvt (struct vlapic*,int) ; 
 int vlapic_get_lvt (struct vlapic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmm_stat_incr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
vlapic_set_error(struct vlapic *vlapic, uint32_t mask)
{
	uint32_t lvt;

	vlapic->esr_pending |= mask;
	if (vlapic->esr_firing)
		return;
	vlapic->esr_firing = 1;

	// The error LVT always uses the fixed delivery mode.
	lvt = vlapic_get_lvt(vlapic, APIC_OFFSET_ERROR_LVT);
	if (vlapic_fire_lvt(vlapic, lvt | APIC_LVT_DM_FIXED)) {
		vmm_stat_incr(vlapic->vm, vlapic->vcpuid, VLAPIC_INTR_ERROR, 1);
	}
	vlapic->esr_firing = 0;
}