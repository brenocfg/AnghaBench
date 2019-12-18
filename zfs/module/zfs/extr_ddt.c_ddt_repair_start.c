#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  enum ddt_type { ____Placeholder_ddt_type } ddt_type ;
typedef  enum ddt_class { ____Placeholder_ddt_class } ddt_class ;
typedef  int /*<<< orphan*/  ddt_t ;
typedef  int /*<<< orphan*/  ddt_key_t ;
struct TYPE_5__ {int /*<<< orphan*/  dde_phys; } ;
typedef  TYPE_1__ ddt_entry_t ;
typedef  int /*<<< orphan*/  blkptr_t ;

/* Variables and functions */
 int DDT_CLASSES ; 
 int DDT_CLASS_UNIQUE ; 
 int DDT_TYPES ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* ddt_alloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ddt_key_fill (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 scalar_t__ ddt_object_lookup (int /*<<< orphan*/ *,int,int,TYPE_1__*) ; 

ddt_entry_t *
ddt_repair_start(ddt_t *ddt, const blkptr_t *bp)
{
	ddt_key_t ddk;
	ddt_entry_t *dde;

	ddt_key_fill(&ddk, bp);

	dde = ddt_alloc(&ddk);

	for (enum ddt_type type = 0; type < DDT_TYPES; type++) {
		for (enum ddt_class class = 0; class < DDT_CLASSES; class++) {
			/*
			 * We can only do repair if there are multiple copies
			 * of the block.  For anything in the UNIQUE class,
			 * there's definitely only one copy, so don't even try.
			 */
			if (class != DDT_CLASS_UNIQUE &&
			    ddt_object_lookup(ddt, type, class, dde) == 0)
				return (dde);
		}
	}

	bzero(dde->dde_phys, sizeof (dde->dde_phys));

	return (dde);
}