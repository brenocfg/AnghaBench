#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_17__ {TYPE_6__* ds; int /*<<< orphan*/ * spa; } ;
typedef  TYPE_3__ try_condense_arg_t ;
typedef  int /*<<< orphan*/  spa_t ;
struct TYPE_18__ {int /*<<< orphan*/  dd_livelist; int /*<<< orphan*/  dd_pending_frees; int /*<<< orphan*/  dd_pending_allocs; TYPE_1__* dd_pool; } ;
typedef  TYPE_4__ dsl_dir_t ;
struct TYPE_22__ {TYPE_2__* bpo_phys; } ;
struct TYPE_19__ {TYPE_8__ dle_bpobj; } ;
typedef  TYPE_5__ dsl_deadlist_entry_t ;
struct TYPE_20__ {TYPE_4__* ds_dir; } ;
typedef  TYPE_6__ dsl_dataset_t ;
struct TYPE_21__ {scalar_t__ tx_txg; } ;
typedef  TYPE_7__ dmu_tx_t ;
typedef  TYPE_8__ bpobj_t ;
struct TYPE_16__ {scalar_t__ bpo_num_blkptrs; scalar_t__ bpo_num_freed; } ;
struct TYPE_15__ {int /*<<< orphan*/ * dp_spa; } ;

/* Variables and functions */
 int /*<<< orphan*/  bplist_iterate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_7__*) ; 
 int /*<<< orphan*/  dsl_deadlist_add_key (int /*<<< orphan*/ *,scalar_t__,TYPE_7__*) ; 
 int /*<<< orphan*/  dsl_deadlist_insert_alloc_cb ; 
 int /*<<< orphan*/  dsl_deadlist_insert_free_cb ; 
 int /*<<< orphan*/  dsl_deadlist_iterate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*) ; 
 TYPE_5__* dsl_deadlist_last (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_livelist_try_condense ; 
 int spa_sync_pass (int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_livelist_max_entries ; 

__attribute__((used)) static void
dsl_flush_pending_livelist(dsl_dataset_t *ds, dmu_tx_t *tx)
{
	dsl_dir_t *dd = ds->ds_dir;
	spa_t *spa = ds->ds_dir->dd_pool->dp_spa;
	dsl_deadlist_entry_t *last = dsl_deadlist_last(&dd->dd_livelist);

	/* Check if we need to add a new sub-livelist */
	if (last == NULL) {
		/* The livelist is empty */
		dsl_deadlist_add_key(&dd->dd_livelist,
		    tx->tx_txg - 1, tx);
	} else if (spa_sync_pass(spa) == 1) {
		/*
		 * Check if the newest entry is full. If it is, make a new one.
		 * We only do this once per sync because we could overfill a
		 * sublist in one sync pass and don't want to add another entry
		 * for a txg that is already represented. This ensures that
		 * blkptrs born in the same txg are stored in the same sublist.
		 */
		bpobj_t bpobj = last->dle_bpobj;
		uint64_t all = bpobj.bpo_phys->bpo_num_blkptrs;
		uint64_t free = bpobj.bpo_phys->bpo_num_freed;
		uint64_t alloc = all - free;
		if (alloc > zfs_livelist_max_entries) {
			dsl_deadlist_add_key(&dd->dd_livelist,
			    tx->tx_txg - 1, tx);
		}
	}

	/* Insert each entry into the on-disk livelist */
	bplist_iterate(&dd->dd_pending_allocs,
	    dsl_deadlist_insert_alloc_cb, &dd->dd_livelist, tx);
	bplist_iterate(&dd->dd_pending_frees,
	    dsl_deadlist_insert_free_cb, &dd->dd_livelist, tx);

	/* Attempt to condense every pair of adjacent entries */
	try_condense_arg_t arg = {
	    .spa = spa,
	    .ds = ds
	};
	dsl_deadlist_iterate(&dd->dd_livelist, dsl_livelist_try_condense,
	    &arg);
}