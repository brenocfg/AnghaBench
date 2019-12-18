#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zfs_all_blkstats_t ;
struct TYPE_9__ {TYPE_2__* dp_blkstats; int /*<<< orphan*/  dp_iput_taskq; int /*<<< orphan*/  dp_unlinked_drain_taskq; int /*<<< orphan*/  dp_spaceavail_cv; int /*<<< orphan*/  dp_lock; int /*<<< orphan*/  dp_config_rwlock; int /*<<< orphan*/  dp_spa; int /*<<< orphan*/  dp_sync_taskq; int /*<<< orphan*/  dp_zil_clean_taskq; int /*<<< orphan*/  dp_dirty_dirs; int /*<<< orphan*/  dp_early_sync_tasks; int /*<<< orphan*/  dp_sync_tasks; int /*<<< orphan*/  dp_dirty_zilogs; int /*<<< orphan*/  dp_dirty_datasets; int /*<<< orphan*/ * dp_meta_objset; int /*<<< orphan*/  dp_obsolete_bpobj; int /*<<< orphan*/  dp_free_bpobj; int /*<<< orphan*/ * dp_root_dir; int /*<<< orphan*/ * dp_leak_dir; int /*<<< orphan*/ * dp_free_dir; int /*<<< orphan*/ * dp_mos_dir; int /*<<< orphan*/ * dp_origin_snap; } ;
typedef  TYPE_1__ dsl_pool_t ;
struct TYPE_10__ {int /*<<< orphan*/  zab_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  arc_flush (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpobj_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_buf_user_evict_wait () ; 
 int /*<<< orphan*/  dmu_objset_evict (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dataset_rele (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  dsl_dir_rele (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  dsl_scan_fini (TYPE_1__*) ; 
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 
 int /*<<< orphan*/  mmp_fini (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rrw_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskq_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txg_fini (TYPE_1__*) ; 
 int /*<<< orphan*/  txg_list_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmem_free (TYPE_2__*,int) ; 

void
dsl_pool_close(dsl_pool_t *dp)
{
	/*
	 * Drop our references from dsl_pool_open().
	 *
	 * Since we held the origin_snap from "syncing" context (which
	 * includes pool-opening context), it actually only got a "ref"
	 * and not a hold, so just drop that here.
	 */
	if (dp->dp_origin_snap != NULL)
		dsl_dataset_rele(dp->dp_origin_snap, dp);
	if (dp->dp_mos_dir != NULL)
		dsl_dir_rele(dp->dp_mos_dir, dp);
	if (dp->dp_free_dir != NULL)
		dsl_dir_rele(dp->dp_free_dir, dp);
	if (dp->dp_leak_dir != NULL)
		dsl_dir_rele(dp->dp_leak_dir, dp);
	if (dp->dp_root_dir != NULL)
		dsl_dir_rele(dp->dp_root_dir, dp);

	bpobj_close(&dp->dp_free_bpobj);
	bpobj_close(&dp->dp_obsolete_bpobj);

	/* undo the dmu_objset_open_impl(mos) from dsl_pool_open() */
	if (dp->dp_meta_objset != NULL)
		dmu_objset_evict(dp->dp_meta_objset);

	txg_list_destroy(&dp->dp_dirty_datasets);
	txg_list_destroy(&dp->dp_dirty_zilogs);
	txg_list_destroy(&dp->dp_sync_tasks);
	txg_list_destroy(&dp->dp_early_sync_tasks);
	txg_list_destroy(&dp->dp_dirty_dirs);

	taskq_destroy(dp->dp_zil_clean_taskq);
	taskq_destroy(dp->dp_sync_taskq);

	/*
	 * We can't set retry to TRUE since we're explicitly specifying
	 * a spa to flush. This is good enough; any missed buffers for
	 * this spa won't cause trouble, and they'll eventually fall
	 * out of the ARC just like any other unused buffer.
	 */
	arc_flush(dp->dp_spa, FALSE);

	mmp_fini(dp->dp_spa);
	txg_fini(dp);
	dsl_scan_fini(dp);
	dmu_buf_user_evict_wait();

	rrw_destroy(&dp->dp_config_rwlock);
	mutex_destroy(&dp->dp_lock);
	cv_destroy(&dp->dp_spaceavail_cv);
	taskq_destroy(dp->dp_unlinked_drain_taskq);
	taskq_destroy(dp->dp_iput_taskq);
	if (dp->dp_blkstats != NULL) {
		mutex_destroy(&dp->dp_blkstats->zab_lock);
		vmem_free(dp->dp_blkstats, sizeof (zfs_all_blkstats_t));
	}
	kmem_free(dp, sizeof (dsl_pool_t));
}