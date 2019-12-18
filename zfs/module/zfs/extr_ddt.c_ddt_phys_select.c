#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ ddp_phys_birth; int /*<<< orphan*/ * ddp_dva; } ;
typedef  TYPE_1__ ddt_phys_t ;
struct TYPE_6__ {scalar_t__ dde_phys; } ;
typedef  TYPE_2__ ddt_entry_t ;
typedef  int /*<<< orphan*/  blkptr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BP_IDENTITY (int /*<<< orphan*/  const*) ; 
 scalar_t__ BP_PHYSICAL_BIRTH (int /*<<< orphan*/  const*) ; 
 int DDT_PHYS_TYPES ; 
 scalar_t__ DVA_EQUAL (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

ddt_phys_t *
ddt_phys_select(const ddt_entry_t *dde, const blkptr_t *bp)
{
	ddt_phys_t *ddp = (ddt_phys_t *)dde->dde_phys;

	for (int p = 0; p < DDT_PHYS_TYPES; p++, ddp++) {
		if (DVA_EQUAL(BP_IDENTITY(bp), &ddp->ddp_dva[0]) &&
		    BP_PHYSICAL_BIRTH(bp) == ddp->ddp_phys_birth)
			return (ddp);
	}
	return (NULL);
}