#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_37__   TYPE_6__ ;
typedef  struct TYPE_36__   TYPE_5__ ;
typedef  struct TYPE_35__   TYPE_4__ ;
typedef  struct TYPE_34__   TYPE_3__ ;
typedef  struct TYPE_33__   TYPE_2__ ;
typedef  struct TYPE_32__   TYPE_1__ ;

/* Type definitions */
struct TYPE_36__ {int vdev_children; TYPE_1__* vdev_mg; struct TYPE_36__** vdev_child; } ;
typedef  TYPE_5__ vdev_t ;
struct TYPE_35__ {int sav_count; int /*<<< orphan*/ * sav_config; TYPE_5__** sav_vdevs; } ;
struct TYPE_34__ {int sav_count; int /*<<< orphan*/ * sav_config; TYPE_5__** sav_vdevs; } ;
struct TYPE_33__ {scalar_t__ mmp_thread; } ;
struct TYPE_37__ {int /*<<< orphan*/ * spa_comment; void* spa_indirect_vdevs_loaded; scalar_t__ spa_async_suspended; TYPE_4__ spa_l2cache; TYPE_3__ spa_spares; int /*<<< orphan*/ * spa_meta_objset; int /*<<< orphan*/ * spa_dsl_pool; TYPE_5__* spa_root_vdev; int /*<<< orphan*/  spa_deferred_bpobj; int /*<<< orphan*/ * spa_vdev_removal; TYPE_5__** spa_async_zio_root; TYPE_2__ spa_mmp; void* spa_sync_on; } ;
typedef  TYPE_6__ spa_t ;
struct TYPE_32__ {int /*<<< orphan*/  mg_taskq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 void* B_FALSE ; 
 int MUTEX_HELD (int /*<<< orphan*/ *) ; 
 scalar_t__ POOL_STATE_UNINITIALIZED ; 
 int /*<<< orphan*/  RW_WRITER ; 
 int /*<<< orphan*/  SCL_ALL ; 
 int /*<<< orphan*/  VDEV_INITIALIZE_ACTIVE ; 
 int /*<<< orphan*/  VDEV_TRIM_ACTIVE ; 
 int /*<<< orphan*/  bpobj_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ddt_unload (TYPE_6__*) ; 
 int /*<<< orphan*/  dsl_pool_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_free (TYPE_5__**,int) ; 
 int max_ncpus ; 
 int /*<<< orphan*/  mmp_thread_stop (TYPE_6__*) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_async_suspend (TYPE_6__*) ; 
 int /*<<< orphan*/  spa_condense_fini (TYPE_6__*) ; 
 int /*<<< orphan*/  spa_config_enter (TYPE_6__*,int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_exit (TYPE_6__*,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  spa_destroy_aux_threads (TYPE_6__*) ; 
 int /*<<< orphan*/  spa_guid (TYPE_6__*) ; 
 int /*<<< orphan*/  spa_import_progress_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_l2cache_drop (TYPE_6__*) ; 
 int /*<<< orphan*/  spa_load_note (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  spa_namespace_lock ; 
 scalar_t__ spa_should_flush_logs_on_unload (TYPE_6__*) ; 
 scalar_t__ spa_state (TYPE_6__*) ; 
 int /*<<< orphan*/  spa_strfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_unload_log_sm_flush_all (TYPE_6__*) ; 
 int /*<<< orphan*/  spa_unload_log_sm_metadata (TYPE_6__*) ; 
 int /*<<< orphan*/  spa_vdev_removal_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_wake_waiters (TYPE_6__*) ; 
 int /*<<< orphan*/  taskq_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txg_sync_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vdev_autotrim_stop_all (TYPE_6__*) ; 
 int /*<<< orphan*/  vdev_clear_stats (TYPE_5__*) ; 
 int /*<<< orphan*/  vdev_free (TYPE_5__*) ; 
 int /*<<< orphan*/  vdev_initialize_stop_all (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_trim_stop_all (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zio_wait (TYPE_5__*) ; 

__attribute__((used)) static void
spa_unload(spa_t *spa)
{
	ASSERT(MUTEX_HELD(&spa_namespace_lock));
	ASSERT(spa_state(spa) != POOL_STATE_UNINITIALIZED);

	spa_import_progress_remove(spa_guid(spa));
	spa_load_note(spa, "UNLOADING");

	spa_wake_waiters(spa);

	/*
	 * If the log space map feature is enabled and the pool is getting
	 * exported (but not destroyed), we want to spend some time flushing
	 * as many metaslabs as we can in an attempt to destroy log space
	 * maps and save import time.
	 */
	if (spa_should_flush_logs_on_unload(spa))
		spa_unload_log_sm_flush_all(spa);

	/*
	 * Stop async tasks.
	 */
	spa_async_suspend(spa);

	if (spa->spa_root_vdev) {
		vdev_t *root_vdev = spa->spa_root_vdev;
		vdev_initialize_stop_all(root_vdev, VDEV_INITIALIZE_ACTIVE);
		vdev_trim_stop_all(root_vdev, VDEV_TRIM_ACTIVE);
		vdev_autotrim_stop_all(spa);
	}

	/*
	 * Stop syncing.
	 */
	if (spa->spa_sync_on) {
		txg_sync_stop(spa->spa_dsl_pool);
		spa->spa_sync_on = B_FALSE;
	}

	/*
	 * This ensures that there is no async metaslab prefetching
	 * while we attempt to unload the spa.
	 */
	if (spa->spa_root_vdev != NULL) {
		for (int c = 0; c < spa->spa_root_vdev->vdev_children; c++) {
			vdev_t *vc = spa->spa_root_vdev->vdev_child[c];
			if (vc->vdev_mg != NULL)
				taskq_wait(vc->vdev_mg->mg_taskq);
		}
	}

	if (spa->spa_mmp.mmp_thread)
		mmp_thread_stop(spa);

	/*
	 * Wait for any outstanding async I/O to complete.
	 */
	if (spa->spa_async_zio_root != NULL) {
		for (int i = 0; i < max_ncpus; i++)
			(void) zio_wait(spa->spa_async_zio_root[i]);
		kmem_free(spa->spa_async_zio_root, max_ncpus * sizeof (void *));
		spa->spa_async_zio_root = NULL;
	}

	if (spa->spa_vdev_removal != NULL) {
		spa_vdev_removal_destroy(spa->spa_vdev_removal);
		spa->spa_vdev_removal = NULL;
	}

	spa_destroy_aux_threads(spa);

	spa_condense_fini(spa);

	bpobj_close(&spa->spa_deferred_bpobj);

	spa_config_enter(spa, SCL_ALL, spa, RW_WRITER);

	/*
	 * Close all vdevs.
	 */
	if (spa->spa_root_vdev)
		vdev_free(spa->spa_root_vdev);
	ASSERT(spa->spa_root_vdev == NULL);

	/*
	 * Close the dsl pool.
	 */
	if (spa->spa_dsl_pool) {
		dsl_pool_close(spa->spa_dsl_pool);
		spa->spa_dsl_pool = NULL;
		spa->spa_meta_objset = NULL;
	}

	ddt_unload(spa);
	spa_unload_log_sm_metadata(spa);

	/*
	 * Drop and purge level 2 cache
	 */
	spa_l2cache_drop(spa);

	for (int i = 0; i < spa->spa_spares.sav_count; i++)
		vdev_free(spa->spa_spares.sav_vdevs[i]);
	if (spa->spa_spares.sav_vdevs) {
		kmem_free(spa->spa_spares.sav_vdevs,
		    spa->spa_spares.sav_count * sizeof (void *));
		spa->spa_spares.sav_vdevs = NULL;
	}
	if (spa->spa_spares.sav_config) {
		nvlist_free(spa->spa_spares.sav_config);
		spa->spa_spares.sav_config = NULL;
	}
	spa->spa_spares.sav_count = 0;

	for (int i = 0; i < spa->spa_l2cache.sav_count; i++) {
		vdev_clear_stats(spa->spa_l2cache.sav_vdevs[i]);
		vdev_free(spa->spa_l2cache.sav_vdevs[i]);
	}
	if (spa->spa_l2cache.sav_vdevs) {
		kmem_free(spa->spa_l2cache.sav_vdevs,
		    spa->spa_l2cache.sav_count * sizeof (void *));
		spa->spa_l2cache.sav_vdevs = NULL;
	}
	if (spa->spa_l2cache.sav_config) {
		nvlist_free(spa->spa_l2cache.sav_config);
		spa->spa_l2cache.sav_config = NULL;
	}
	spa->spa_l2cache.sav_count = 0;

	spa->spa_async_suspended = 0;

	spa->spa_indirect_vdevs_loaded = B_FALSE;

	if (spa->spa_comment != NULL) {
		spa_strfree(spa->spa_comment);
		spa->spa_comment = NULL;
	}

	spa_config_exit(spa, SCL_ALL, spa);
}