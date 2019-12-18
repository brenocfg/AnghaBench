#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_5__ {TYPE_1__* dde_phys; } ;
typedef  TYPE_2__ ddt_entry_t ;
struct TYPE_4__ {scalar_t__ ddp_refcnt; } ;

/* Variables and functions */
 int DDT_PHYS_SINGLE ; 
 int DDT_PHYS_TRIPLE ; 

uint64_t
ddt_phys_total_refcnt(const ddt_entry_t *dde)
{
	uint64_t refcnt = 0;

	for (int p = DDT_PHYS_SINGLE; p <= DDT_PHYS_TRIPLE; p++)
		refcnt += dde->dde_phys[p].ddp_refcnt;

	return (refcnt);
}