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
struct vlapic {int /*<<< orphan*/  vcpuid; int /*<<< orphan*/  vm; } ;

/* Variables and functions */
 int /*<<< orphan*/  APIC_ESR_SEND_ILLEGAL_VECTOR ; 
 int APIC_LVT_DM ; 
#define  APIC_LVT_DM_EXTINT 130 
#define  APIC_LVT_DM_FIXED 129 
#define  APIC_LVT_DM_NMI 128 
 int APIC_LVT_M ; 
 int APIC_LVT_VECTOR ; 
 int /*<<< orphan*/  vcpu_notify_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vlapic_set_error (struct vlapic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlapic_set_intr_ready (struct vlapic*,int,int) ; 
 int /*<<< orphan*/  vm_inject_extint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_inject_nmi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vlapic_fire_lvt(struct vlapic *vlapic, uint32_t lvt)
{
	uint32_t vec, mode;

	if (lvt & APIC_LVT_M)
		return (0);

	vec = lvt & APIC_LVT_VECTOR;
	mode = lvt & APIC_LVT_DM;

	switch (mode) {
	case APIC_LVT_DM_FIXED:
		if (vec < 16) {
			vlapic_set_error(vlapic, APIC_ESR_SEND_ILLEGAL_VECTOR);
			return (0);
		}
		if (vlapic_set_intr_ready(vlapic, ((int) vec), false))
			vcpu_notify_event(vlapic->vm, vlapic->vcpuid, true);
		break;
	case APIC_LVT_DM_NMI:
		vm_inject_nmi(vlapic->vm, vlapic->vcpuid);
		break;
	case APIC_LVT_DM_EXTINT:
		vm_inject_extint(vlapic->vm, vlapic->vcpuid);
		break;
	default:
		// Other modes ignored
		return (0);
	}
	return (1);
}