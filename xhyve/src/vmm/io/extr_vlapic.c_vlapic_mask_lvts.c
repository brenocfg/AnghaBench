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
struct vlapic {struct LAPIC* apic_page; } ;
struct LAPIC {int /*<<< orphan*/  lvt_error; int /*<<< orphan*/  lvt_lint1; int /*<<< orphan*/  lvt_lint0; int /*<<< orphan*/  lvt_pcint; int /*<<< orphan*/  lvt_thermal; int /*<<< orphan*/  lvt_timer; int /*<<< orphan*/  lvt_cmci; } ;

/* Variables and functions */
 int /*<<< orphan*/  APIC_LVT_M ; 
 int /*<<< orphan*/  APIC_OFFSET_CMCI_LVT ; 
 int /*<<< orphan*/  APIC_OFFSET_ERROR_LVT ; 
 int /*<<< orphan*/  APIC_OFFSET_LINT0_LVT ; 
 int /*<<< orphan*/  APIC_OFFSET_LINT1_LVT ; 
 int /*<<< orphan*/  APIC_OFFSET_PERF_LVT ; 
 int /*<<< orphan*/  APIC_OFFSET_THERM_LVT ; 
 int /*<<< orphan*/  APIC_OFFSET_TIMER_LVT ; 
 int /*<<< orphan*/  vlapic_lvt_write_handler (struct vlapic*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vlapic_mask_lvts(struct vlapic *vlapic)
{
	struct LAPIC *lapic = vlapic->apic_page;

	lapic->lvt_cmci |= APIC_LVT_M;
	vlapic_lvt_write_handler(vlapic, APIC_OFFSET_CMCI_LVT);

	lapic->lvt_timer |= APIC_LVT_M;
	vlapic_lvt_write_handler(vlapic, APIC_OFFSET_TIMER_LVT);

	lapic->lvt_thermal |= APIC_LVT_M;
	vlapic_lvt_write_handler(vlapic, APIC_OFFSET_THERM_LVT);

	lapic->lvt_pcint |= APIC_LVT_M;
	vlapic_lvt_write_handler(vlapic, APIC_OFFSET_PERF_LVT);

	lapic->lvt_lint0 |= APIC_LVT_M;
	vlapic_lvt_write_handler(vlapic, APIC_OFFSET_LINT0_LVT);

	lapic->lvt_lint1 |= APIC_LVT_M;
	vlapic_lvt_write_handler(vlapic, APIC_OFFSET_LINT1_LVT);

	lapic->lvt_error |= APIC_LVT_M;
	vlapic_lvt_write_handler(vlapic, APIC_OFFSET_ERROR_LVT);
}