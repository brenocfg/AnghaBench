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
typedef  int /*<<< orphan*/  spa_t ;
typedef  enum ddt_type { ____Placeholder_ddt_type } ddt_type ;
typedef  enum ddt_class { ____Placeholder_ddt_class } ddt_class ;
typedef  int /*<<< orphan*/  ddt_t ;
struct TYPE_3__ {int /*<<< orphan*/  dde_key; } ;
typedef  TYPE_1__ ddt_entry_t ;
typedef  int /*<<< orphan*/  blkptr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BP_GET_DEDUP (int /*<<< orphan*/  const*) ; 
 int DDT_CLASSES ; 
 int DDT_TYPES ; 
 int /*<<< orphan*/  ddt_key_fill (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ddt_object_prefetch (int /*<<< orphan*/ *,int,int,TYPE_1__*) ; 
 int /*<<< orphan*/ * ddt_select (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  zfs_dedup_prefetch ; 

void
ddt_prefetch(spa_t *spa, const blkptr_t *bp)
{
	ddt_t *ddt;
	ddt_entry_t dde;

	if (!zfs_dedup_prefetch || bp == NULL || !BP_GET_DEDUP(bp))
		return;

	/*
	 * We only remove the DDT once all tables are empty and only
	 * prefetch dedup blocks when there are entries in the DDT.
	 * Thus no locking is required as the DDT can't disappear on us.
	 */
	ddt = ddt_select(spa, bp);
	ddt_key_fill(&dde.dde_key, bp);

	for (enum ddt_type type = 0; type < DDT_TYPES; type++) {
		for (enum ddt_class class = 0; class < DDT_CLASSES; class++) {
			ddt_object_prefetch(ddt, type, class, &dde);
		}
	}
}