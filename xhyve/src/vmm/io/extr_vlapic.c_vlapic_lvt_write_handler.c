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
struct vlapic {int /*<<< orphan*/ * lvt_last; struct LAPIC* apic_page; } ;
struct LAPIC {int svr; } ;

/* Variables and functions */
 int APIC_LVTT_TM ; 
 int APIC_LVT_DM ; 
 int APIC_LVT_DS ; 
 int APIC_LVT_IIPP ; 
 int APIC_LVT_M ; 
 int APIC_LVT_RIRR ; 
 int APIC_LVT_TM ; 
 int APIC_LVT_VECTOR ; 
#define  APIC_OFFSET_ERROR_LVT 131 
#define  APIC_OFFSET_LINT0_LVT 130 
#define  APIC_OFFSET_LINT1_LVT 129 
#define  APIC_OFFSET_TIMER_LVT 128 
 int APIC_SVR_ENABLE ; 
 int /*<<< orphan*/  atomic_store_rel_32 (int /*<<< orphan*/ *,int) ; 
 int lvt_off_to_idx (int) ; 
 int* vlapic_get_lvtptr (struct vlapic*,int) ; 

void
vlapic_lvt_write_handler(struct vlapic *vlapic, uint32_t offset)
{
	uint32_t *lvtptr, mask, val;
	struct LAPIC *lapic;
	int idx;
	
	lapic = vlapic->apic_page;
	lvtptr = vlapic_get_lvtptr(vlapic, offset);	
	val = *lvtptr;
	idx = lvt_off_to_idx(offset);

	if (!(lapic->svr & APIC_SVR_ENABLE))
		val |= APIC_LVT_M;
	mask = APIC_LVT_M | APIC_LVT_DS | APIC_LVT_VECTOR;
	switch (offset) {
	case APIC_OFFSET_TIMER_LVT:
		mask |= APIC_LVTT_TM;
		break;
	case APIC_OFFSET_ERROR_LVT:
		break;
	case APIC_OFFSET_LINT0_LVT:
	case APIC_OFFSET_LINT1_LVT:
		mask |= APIC_LVT_TM | APIC_LVT_RIRR | APIC_LVT_IIPP;
		/* FALLTHROUGH */
	default:
		mask |= APIC_LVT_DM;
		break;
	}
	val &= mask;
	*lvtptr = val;
	atomic_store_rel_32(&vlapic->lvt_last[idx], val);
}