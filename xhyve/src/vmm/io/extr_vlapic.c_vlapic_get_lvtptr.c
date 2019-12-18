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
struct vlapic {struct LAPIC* apic_page; } ;
struct LAPIC {int lvt_cmci; int lvt_timer; } ;

/* Variables and functions */
#define  APIC_OFFSET_CMCI_LVT 134 
#define  APIC_OFFSET_ERROR_LVT 133 
#define  APIC_OFFSET_LINT0_LVT 132 
#define  APIC_OFFSET_LINT1_LVT 131 
#define  APIC_OFFSET_PERF_LVT 130 
#define  APIC_OFFSET_THERM_LVT 129 
#define  APIC_OFFSET_TIMER_LVT 128 
 int /*<<< orphan*/  xhyve_abort (char*) ; 

__attribute__((used)) static __inline uint32_t *
vlapic_get_lvtptr(struct vlapic *vlapic, uint32_t offset)
{
	struct LAPIC	*lapic = vlapic->apic_page;
	int 		 i;

	switch (offset) {
	case APIC_OFFSET_CMCI_LVT:
		return (&lapic->lvt_cmci);
	case APIC_OFFSET_TIMER_LVT:
	case APIC_OFFSET_THERM_LVT:
	case APIC_OFFSET_PERF_LVT:
	case APIC_OFFSET_LINT0_LVT:
	case APIC_OFFSET_LINT1_LVT:
	case APIC_OFFSET_ERROR_LVT:
		i = (offset - APIC_OFFSET_TIMER_LVT) >> 2;
		return ((&lapic->lvt_timer) + i);;
	default:
		xhyve_abort("vlapic_get_lvt: invalid LVT\n");
	}
}