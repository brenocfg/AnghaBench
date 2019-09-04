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

/* Variables and functions */
 int APIC_LVT_CMCI ; 
 int APIC_LVT_ERROR ; 
 int APIC_LVT_LINT0 ; 
 int APIC_LVT_LINT1 ; 
 int APIC_LVT_PMC ; 
 int APIC_LVT_THERMAL ; 
 int APIC_LVT_TIMER ; 
#define  APIC_OFFSET_CMCI_LVT 134 
#define  APIC_OFFSET_ERROR_LVT 133 
#define  APIC_OFFSET_LINT0_LVT 132 
#define  APIC_OFFSET_LINT1_LVT 131 
#define  APIC_OFFSET_PERF_LVT 130 
#define  APIC_OFFSET_THERM_LVT 129 
#define  APIC_OFFSET_TIMER_LVT 128 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int VLAPIC_MAXLVT_INDEX ; 

__attribute__((used)) static __inline int
lvt_off_to_idx(uint32_t offset)
{
	int index;

	switch (offset) {
	case APIC_OFFSET_CMCI_LVT:
		index = APIC_LVT_CMCI;
		break;
	case APIC_OFFSET_TIMER_LVT:
		index = APIC_LVT_TIMER;
		break;
	case APIC_OFFSET_THERM_LVT:
		index = APIC_LVT_THERMAL;
		break;
	case APIC_OFFSET_PERF_LVT:
		index = APIC_LVT_PMC;
		break;
	case APIC_OFFSET_LINT0_LVT:
		index = APIC_LVT_LINT0;
		break;
	case APIC_OFFSET_LINT1_LVT:
		index = APIC_LVT_LINT1;
		break;
	case APIC_OFFSET_ERROR_LVT:
		index = APIC_LVT_ERROR;
		break;
	default:
		index = -1;
		break;
	}
	KASSERT(index >= 0 && index <= VLAPIC_MAXLVT_INDEX, ("lvt_off_to_idx: "
	    "invalid lvt index %d for offset %#x", index, offset));

	return (index);
}