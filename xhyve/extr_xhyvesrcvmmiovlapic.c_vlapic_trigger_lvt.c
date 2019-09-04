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
typedef  int /*<<< orphan*/  uint32_t ;
struct vlapic {int /*<<< orphan*/  vcpuid; int /*<<< orphan*/  vm; } ;

/* Variables and functions */
#define  APIC_LVT_CMCI 134 
 int /*<<< orphan*/  APIC_LVT_DM_FIXED ; 
#define  APIC_LVT_ERROR 133 
#define  APIC_LVT_LINT0 132 
#define  APIC_LVT_LINT1 131 
#define  APIC_LVT_PMC 130 
#define  APIC_LVT_THERMAL 129 
#define  APIC_LVT_TIMER 128 
 int /*<<< orphan*/  APIC_OFFSET_CMCI_LVT ; 
 int /*<<< orphan*/  APIC_OFFSET_ERROR_LVT ; 
 int /*<<< orphan*/  APIC_OFFSET_LINT0_LVT ; 
 int /*<<< orphan*/  APIC_OFFSET_LINT1_LVT ; 
 int /*<<< orphan*/  APIC_OFFSET_PERF_LVT ; 
 int /*<<< orphan*/  APIC_OFFSET_THERM_LVT ; 
 int /*<<< orphan*/  APIC_OFFSET_TIMER_LVT ; 
 int EINVAL ; 
 int /*<<< orphan*/  LVTS_TRIGGERRED ; 
 int vlapic_enabled (struct vlapic*) ; 
 scalar_t__ vlapic_fire_lvt (struct vlapic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlapic_get_lvt (struct vlapic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_inject_extint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_inject_nmi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmm_stat_array_incr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

int
vlapic_trigger_lvt(struct vlapic *vlapic, int vector)
{
	uint32_t lvt;

	if (vlapic_enabled(vlapic) == false) {
		/*
		 * When the local APIC is global/hardware disabled,
		 * LINT[1:0] pins are configured as INTR and NMI pins,
		 * respectively.
		*/
		switch (vector) {
			case APIC_LVT_LINT0:
				vm_inject_extint(vlapic->vm, vlapic->vcpuid);
				break;
			case APIC_LVT_LINT1:
				vm_inject_nmi(vlapic->vm, vlapic->vcpuid);
				break;
			default:
				break;
		}
		return (0);
	}

	switch (vector) {
	case APIC_LVT_LINT0:
		lvt = vlapic_get_lvt(vlapic, APIC_OFFSET_LINT0_LVT);
		break;
	case APIC_LVT_LINT1:
		lvt = vlapic_get_lvt(vlapic, APIC_OFFSET_LINT1_LVT);
		break;
	case APIC_LVT_TIMER:
		lvt = vlapic_get_lvt(vlapic, APIC_OFFSET_TIMER_LVT);
		lvt |= APIC_LVT_DM_FIXED;
		break;
	case APIC_LVT_ERROR:
		lvt = vlapic_get_lvt(vlapic, APIC_OFFSET_ERROR_LVT);
		lvt |= APIC_LVT_DM_FIXED;
		break;
	case APIC_LVT_PMC:
		lvt = vlapic_get_lvt(vlapic, APIC_OFFSET_PERF_LVT);
		break;
	case APIC_LVT_THERMAL:
		lvt = vlapic_get_lvt(vlapic, APIC_OFFSET_THERM_LVT);
		break;
	case APIC_LVT_CMCI:
		lvt = vlapic_get_lvt(vlapic, APIC_OFFSET_CMCI_LVT);
		break;
	default:
		return (EINVAL);
	}
	if (vlapic_fire_lvt(vlapic, lvt)) {
		vmm_stat_array_incr(vlapic->vm, vlapic->vcpuid,
		    LVTS_TRIGGERRED, vector, 1);
	}
	return (0);
}