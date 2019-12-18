#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct send_range* dnp; } ;
struct TYPE_4__ {TYPE_1__ object; } ;
struct send_range {scalar_t__ type; int dn_extra_slots; TYPE_2__ sru; } ;
typedef  int /*<<< orphan*/  dnode_phys_t ;

/* Variables and functions */
 scalar_t__ OBJECT ; 
 int /*<<< orphan*/  kmem_free (struct send_range*,int) ; 

__attribute__((used)) static void
range_free(struct send_range *range)
{
	if (range->type == OBJECT) {
		size_t size = sizeof (dnode_phys_t) *
		    (range->sru.object.dnp->dn_extra_slots + 1);
		kmem_free(range->sru.object.dnp, size);
	}
	kmem_free(range, sizeof (*range));
}