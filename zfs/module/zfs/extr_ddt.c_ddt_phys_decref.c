#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ ddp_refcnt; } ;
typedef  TYPE_1__ ddt_phys_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 

void
ddt_phys_decref(ddt_phys_t *ddp)
{
	if (ddp) {
		ASSERT(ddp->ddp_refcnt > 0);
		ddp->ddp_refcnt--;
	}
}