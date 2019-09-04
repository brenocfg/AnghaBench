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
struct vlapic {scalar_t__ vcpuid; int /*<<< orphan*/  vm; } ;
typedef  int /*<<< orphan*/  cpuset_t ;

/* Variables and functions */
 int APIC_DELMODE_FIXED ; 
 int APIC_DELMODE_LOWPRIO ; 
 int /*<<< orphan*/  CPU_ISSET (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  VLAPIC_CTR1 (struct vlapic*,char*,int) ; 
 int /*<<< orphan*/  vlapic_calcdest (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  vlapic_set_tmr (struct vlapic*,int,int) ; 

void
vlapic_set_tmr_level(struct vlapic *vlapic, uint32_t dest, bool phys,
    int delmode, int vector)
{
	cpuset_t dmask;
	bool lowprio;

	KASSERT(vector >= 0 && vector <= 255, ("invalid vector %d", vector));

	/*
	 * A level trigger is valid only for fixed and lowprio delivery modes.
	 */
	if (delmode != APIC_DELMODE_FIXED && delmode != APIC_DELMODE_LOWPRIO) {
		VLAPIC_CTR1(vlapic, "Ignoring level trigger-mode for "
		    "delivery-mode %d", delmode);
		return;
	}

	lowprio = (delmode == APIC_DELMODE_LOWPRIO);
	vlapic_calcdest(vlapic->vm, &dmask, dest, phys, lowprio, false);

	if (!CPU_ISSET(((unsigned) vlapic->vcpuid), &dmask))
		return;

	VLAPIC_CTR1(vlapic, "vector %d set to level-triggered", vector);
	vlapic_set_tmr(vlapic, vector, true);
}