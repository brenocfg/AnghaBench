#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_14__ {int /*<<< orphan*/  dp_obsolete_bpobj; } ;
typedef  TYPE_2__ dsl_pool_t ;
struct TYPE_15__ {int /*<<< orphan*/  ds_remap_deadlist; int /*<<< orphan*/  ds_remap_deadlist_lock; TYPE_1__* ds_dir; } ;
typedef  TYPE_3__ dsl_dataset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_16__ {int /*<<< orphan*/  ds_prev_snap_txg; } ;
struct TYPE_13__ {TYPE_2__* dd_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  bpobj_is_open (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dataset_create_remap_deadlist (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dataset_destroy_remap_deadlist (TYPE_3__*,int /*<<< orphan*/ *) ; 
 scalar_t__ dsl_dataset_get_remap_deadlist_object (TYPE_3__*) ; 
 TYPE_8__* dsl_dataset_phys (TYPE_3__*) ; 
 scalar_t__ dsl_dataset_remap_deadlist_exists (TYPE_3__*) ; 
 int /*<<< orphan*/  dsl_deadlist_merge (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_deadlist_move_bpobj (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_pool_create_obsolete_bpobj (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dsl_destroy_snapshot_handle_remaps(dsl_dataset_t *ds, dsl_dataset_t *ds_next,
    dmu_tx_t *tx)
{
	dsl_pool_t *dp = ds->ds_dir->dd_pool;

	/* Move blocks to be obsoleted to pool's obsolete list. */
	if (dsl_dataset_remap_deadlist_exists(ds_next)) {
		if (!bpobj_is_open(&dp->dp_obsolete_bpobj))
			dsl_pool_create_obsolete_bpobj(dp, tx);

		dsl_deadlist_move_bpobj(&ds_next->ds_remap_deadlist,
		    &dp->dp_obsolete_bpobj,
		    dsl_dataset_phys(ds)->ds_prev_snap_txg, tx);
	}

	/* Merge our deadlist into next's and free it. */
	if (dsl_dataset_remap_deadlist_exists(ds)) {
		uint64_t remap_deadlist_object =
		    dsl_dataset_get_remap_deadlist_object(ds);
		ASSERT(remap_deadlist_object != 0);

		mutex_enter(&ds_next->ds_remap_deadlist_lock);
		if (!dsl_dataset_remap_deadlist_exists(ds_next))
			dsl_dataset_create_remap_deadlist(ds_next, tx);
		mutex_exit(&ds_next->ds_remap_deadlist_lock);

		dsl_deadlist_merge(&ds_next->ds_remap_deadlist,
		    remap_deadlist_object, tx);
		dsl_dataset_destroy_remap_deadlist(ds, tx);
	}
}