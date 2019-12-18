#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zfs_bookmark_phys_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_16__ {int /*<<< orphan*/  dp_meta_objset; } ;
typedef  TYPE_1__ dsl_pool_t ;
struct TYPE_17__ {int /*<<< orphan*/  ds_bookmarks; int /*<<< orphan*/  ds_bookmarks_obj; } ;
typedef  TYPE_2__ dsl_dataset_t ;
struct TYPE_19__ {scalar_t__ zbm_creation_txg; int zbm_flags; } ;
struct TYPE_18__ {scalar_t__ dbn_dirty; TYPE_4__ dbn_phys; int /*<<< orphan*/  dbn_name; } ;
typedef  TYPE_3__ dsl_bookmark_node_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_20__ {scalar_t__ ds_prev_snap_txg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 TYPE_3__* AVL_NEXT (int /*<<< orphan*/ *,TYPE_3__*) ; 
 TYPE_3__* AVL_PREV (int /*<<< orphan*/ *,TYPE_3__*) ; 
 scalar_t__ B_FALSE ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int ZBM_FLAG_HAS_FBN ; 
 TYPE_3__* avl_first (int /*<<< orphan*/ *) ; 
 TYPE_3__* avl_last (int /*<<< orphan*/ *) ; 
 TYPE_1__* dmu_tx_pool (int /*<<< orphan*/ *) ; 
 scalar_t__ dsl_dataset_is_snapshot (TYPE_2__*) ; 
 TYPE_5__* dsl_dataset_phys (TYPE_2__*) ; 
 int /*<<< orphan*/  zap_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,TYPE_4__*,int /*<<< orphan*/ *) ; 

void
dsl_bookmark_sync_done(dsl_dataset_t *ds, dmu_tx_t *tx)
{
	dsl_pool_t *dp = dmu_tx_pool(tx);

	if (dsl_dataset_is_snapshot(ds))
		return;

	/*
	 * We only dirty bookmarks that are at or after the most recent
	 * snapshot.  We can't create snapshots between
	 * dsl_bookmark_block_killed() and dsl_bookmark_sync_done(), so we
	 * don't need to look at any bookmarks before ds_prev_snap_txg.
	 */
	for (dsl_bookmark_node_t *dbn = avl_last(&ds->ds_bookmarks);
	    dbn != NULL && dbn->dbn_phys.zbm_creation_txg >=
	    dsl_dataset_phys(ds)->ds_prev_snap_txg;
	    dbn = AVL_PREV(&ds->ds_bookmarks, dbn)) {
		if (dbn->dbn_dirty) {
			/*
			 * We only dirty nodes with HAS_FBN, therefore
			 * we can always use the current bookmark struct size.
			 */
			ASSERT(dbn->dbn_phys.zbm_flags & ZBM_FLAG_HAS_FBN);
			VERIFY0(zap_update(dp->dp_meta_objset,
			    ds->ds_bookmarks_obj,
			    dbn->dbn_name, sizeof (uint64_t),
			    sizeof (zfs_bookmark_phys_t) / sizeof (uint64_t),
			    &dbn->dbn_phys, tx));
			dbn->dbn_dirty = B_FALSE;
		}
	}
#ifdef ZFS_DEBUG
	for (dsl_bookmark_node_t *dbn = avl_first(&ds->ds_bookmarks);
	    dbn != NULL; dbn = AVL_NEXT(&ds->ds_bookmarks, dbn)) {
		ASSERT(!dbn->dbn_dirty);
	}
#endif
}