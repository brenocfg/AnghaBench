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
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {int (* pending_intr ) (struct vlapic*,int*) ;} ;
struct vlapic {TYPE_1__ ops; struct LAPIC* apic_page; } ;
struct LAPIC {int ppr; scalar_t__ irr0; } ;

/* Variables and functions */
 unsigned int PRIO (int) ; 
 int /*<<< orphan*/  VLAPIC_CTR1 (struct vlapic*,char*,int) ; 
 scalar_t__ atomic_load_acq_int (scalar_t__*) ; 
 int fls (int) ; 
 int stub1 (struct vlapic*,int*) ; 

int
vlapic_pending_intr(struct vlapic *vlapic, int *vecptr)
{
	struct LAPIC	*lapic = vlapic->apic_page;
	int	  	 idx, i, bitpos, vector;
	uint32_t	*irrptr, val;

	if (vlapic->ops.pending_intr)
		return ((*vlapic->ops.pending_intr)(vlapic, vecptr));

	irrptr = &lapic->irr0;

	for (i = 7; i >= 0; i--) {
		idx = i * 4;
		val = atomic_load_acq_int(&irrptr[idx]);
		bitpos = fls((int) val);
		if (bitpos != 0) {
			vector = i * 32 + (bitpos - 1);
			if (((unsigned) PRIO(vector)) > PRIO(lapic->ppr)) {
				VLAPIC_CTR1(vlapic, "pending intr %d", vector);
				if (vecptr != NULL)
					*vecptr = vector;
				return (1);
			} else 
				break;
		}
	}
	return (0);
}