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
struct vlapic {scalar_t__ isrvec_stk_top; int /*<<< orphan*/  vcpuid; int /*<<< orphan*/  vm; struct LAPIC* apic_page; } ;
struct LAPIC {int isr0; int tmr0; } ;

/* Variables and functions */
 int /*<<< orphan*/  VCPU_CTR0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  VCPU_CTR1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  VLAPIC_CTR_ISR (struct vlapic*,char*) ; 
 int /*<<< orphan*/  VLAPIC_GRATUITOUS_EOI ; 
 int fls (int) ; 
 int /*<<< orphan*/  vioapic_process_eoi (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vlapic_update_ppr (struct vlapic*) ; 
 int /*<<< orphan*/  vmm_stat_incr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xhyve_abort (char*,scalar_t__) ; 

__attribute__((used)) static void
vlapic_process_eoi(struct vlapic *vlapic)
{
	struct LAPIC	*lapic = vlapic->apic_page;
	uint32_t	*isrptr, *tmrptr;
	int		i, idx, bitpos, vector;

	isrptr = &lapic->isr0;
	tmrptr = &lapic->tmr0;

	for (i = 7; i >= 0; i--) {
		idx = i * 4;
		bitpos = fls((int) isrptr[idx]);
		if (bitpos-- != 0) {
			if (vlapic->isrvec_stk_top <= 0) {
				xhyve_abort("invalid vlapic isrvec_stk_top %d\n",
				      vlapic->isrvec_stk_top);
			}
			isrptr[idx] &= ~(1 << bitpos);
			vector = i * 32 + bitpos;
			VCPU_CTR1(vlapic->vm, vlapic->vcpuid, "EOI vector %d",
			    vector);
			VLAPIC_CTR_ISR(vlapic, "vlapic_process_eoi");
			vlapic->isrvec_stk_top--;
			vlapic_update_ppr(vlapic);
			if ((tmrptr[idx] & (1 << bitpos)) != 0) {
				vioapic_process_eoi(vlapic->vm, vlapic->vcpuid,
				    vector);
			}
			return;
		}
	}
	VCPU_CTR0(vlapic->vm, vlapic->vcpuid, "Gratuitous EOI");
	vmm_stat_incr(vlapic->vm, vlapic->vcpuid, VLAPIC_GRATUITOUS_EOI, 1);
}