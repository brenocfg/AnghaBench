#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_2__ ;
typedef  struct TYPE_33__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  u_longlong_t ;
struct TYPE_33__ {scalar_t__ ub_checkpoint_txg; } ;
struct TYPE_34__ {int spa_import_flags; scalar_t__ spa_config_source; scalar_t__ spa_load_state; scalar_t__ spa_load_max_txg; int /*<<< orphan*/  spa_root_vdev; int /*<<< orphan*/  spa_dsl_pool; int /*<<< orphan*/  spa_claim_max_txg; void* spa_sync_on; TYPE_1__ spa_uberblock; int /*<<< orphan*/  spa_config_txg; } ;
typedef  TYPE_2__ spa_t ;
typedef  int /*<<< orphan*/  spa_import_type_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int B_FALSE ; 
 void* B_TRUE ; 
 int /*<<< orphan*/  DS_FIND_CHILDREN ; 
 int /*<<< orphan*/  ENOTSUP ; 
 int /*<<< orphan*/  FTAG ; 
 int MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RW_READER ; 
 int /*<<< orphan*/  SCL_CONFIG ; 
 int /*<<< orphan*/  SPA_ASYNC_RESILVER ; 
 scalar_t__ SPA_CONFIG_SRC_NONE ; 
 scalar_t__ SPA_LOAD_RECOVER ; 
 scalar_t__ SPA_LOAD_TRYIMPORT ; 
 scalar_t__ UINT64_MAX ; 
 int /*<<< orphan*/  VDEV_AUX_UNSUP_FEAT ; 
 int ZFS_IMPORT_CHECKPOINT ; 
 int /*<<< orphan*/  dmu_objset_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_destroy_inconsistent ; 
 int /*<<< orphan*/  dsl_pool_clean_tmp_userrefs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_scan_resilvering (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmp_thread_start (TYPE_2__*) ; 
 int /*<<< orphan*/  spa_async_request (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_enter (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_exit (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_guid (TYPE_2__*) ; 
 int /*<<< orphan*/  spa_history_log_internal (TYPE_2__*,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_history_log_version (TYPE_2__*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_import_progress_remove (int /*<<< orphan*/ ) ; 
 int spa_ld_check_features (TYPE_2__*,int*) ; 
 int /*<<< orphan*/  spa_ld_check_for_config_update (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int spa_ld_checkpoint_rewind (TYPE_2__*) ; 
 int /*<<< orphan*/  spa_ld_claim_log_blocks (TYPE_2__*) ; 
 int spa_ld_get_props (TYPE_2__*) ; 
 int spa_ld_load_dedup_tables (TYPE_2__*) ; 
 int spa_ld_load_special_directories (TYPE_2__*) ; 
 int spa_ld_load_vdev_metadata (TYPE_2__*) ; 
 int spa_ld_mos_with_trusted_config (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 int spa_ld_open_aux_vdevs (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int spa_ld_open_indirect_vdev_metadata (TYPE_2__*) ; 
 int /*<<< orphan*/  spa_ld_prepare_for_reload (TYPE_2__*) ; 
 int spa_ld_read_checkpoint_txg (TYPE_2__*) ; 
 int spa_ld_verify_logs (TYPE_2__*,int /*<<< orphan*/ ,char**) ; 
 int spa_ld_verify_pool_data (TYPE_2__*) ; 
 int /*<<< orphan*/  spa_load_note (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  spa_name (TYPE_2__*) ; 
 int /*<<< orphan*/  spa_namespace_lock ; 
 int /*<<< orphan*/  spa_restart_removal (TYPE_2__*) ; 
 int /*<<< orphan*/  spa_spawn_aux_threads (TYPE_2__*) ; 
 int /*<<< orphan*/  spa_update_dspace (TYPE_2__*) ; 
 int spa_vdev_err (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ spa_writeable (TYPE_2__*) ; 
 int /*<<< orphan*/  txg_sync_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txg_wait_synced (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_autotrim_restart (TYPE_2__*) ; 
 int /*<<< orphan*/  vdev_initialize_restart (int /*<<< orphan*/ ) ; 
 scalar_t__ vdev_resilver_needed (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vdev_trim_restart (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
spa_load_impl(spa_t *spa, spa_import_type_t type, char **ereport)
{
	int error = 0;
	boolean_t missing_feat_write = B_FALSE;
	boolean_t checkpoint_rewind =
	    (spa->spa_import_flags & ZFS_IMPORT_CHECKPOINT);
	boolean_t update_config_cache = B_FALSE;

	ASSERT(MUTEX_HELD(&spa_namespace_lock));
	ASSERT(spa->spa_config_source != SPA_CONFIG_SRC_NONE);

	spa_load_note(spa, "LOADING");

	error = spa_ld_mos_with_trusted_config(spa, type, &update_config_cache);
	if (error != 0)
		return (error);

	/*
	 * If we are rewinding to the checkpoint then we need to repeat
	 * everything we've done so far in this function but this time
	 * selecting the checkpointed uberblock and using that to open
	 * the MOS.
	 */
	if (checkpoint_rewind) {
		/*
		 * If we are rewinding to the checkpoint update config cache
		 * anyway.
		 */
		update_config_cache = B_TRUE;

		/*
		 * Extract the checkpointed uberblock from the current MOS
		 * and use this as the pool's uberblock from now on. If the
		 * pool is imported as writeable we also write the checkpoint
		 * uberblock to the labels, making the rewind permanent.
		 */
		error = spa_ld_checkpoint_rewind(spa);
		if (error != 0)
			return (error);

		/*
		 * Redo the loading process again with the
		 * checkpointed uberblock.
		 */
		spa_ld_prepare_for_reload(spa);
		spa_load_note(spa, "LOADING checkpointed uberblock");
		error = spa_ld_mos_with_trusted_config(spa, type, NULL);
		if (error != 0)
			return (error);
	}

	/*
	 * Retrieve the checkpoint txg if the pool has a checkpoint.
	 */
	error = spa_ld_read_checkpoint_txg(spa);
	if (error != 0)
		return (error);

	/*
	 * Retrieve the mapping of indirect vdevs. Those vdevs were removed
	 * from the pool and their contents were re-mapped to other vdevs. Note
	 * that everything that we read before this step must have been
	 * rewritten on concrete vdevs after the last device removal was
	 * initiated. Otherwise we could be reading from indirect vdevs before
	 * we have loaded their mappings.
	 */
	error = spa_ld_open_indirect_vdev_metadata(spa);
	if (error != 0)
		return (error);

	/*
	 * Retrieve the full list of active features from the MOS and check if
	 * they are all supported.
	 */
	error = spa_ld_check_features(spa, &missing_feat_write);
	if (error != 0)
		return (error);

	/*
	 * Load several special directories from the MOS needed by the dsl_pool
	 * layer.
	 */
	error = spa_ld_load_special_directories(spa);
	if (error != 0)
		return (error);

	/*
	 * Retrieve pool properties from the MOS.
	 */
	error = spa_ld_get_props(spa);
	if (error != 0)
		return (error);

	/*
	 * Retrieve the list of auxiliary devices - cache devices and spares -
	 * and open them.
	 */
	error = spa_ld_open_aux_vdevs(spa, type);
	if (error != 0)
		return (error);

	/*
	 * Load the metadata for all vdevs. Also check if unopenable devices
	 * should be autoreplaced.
	 */
	error = spa_ld_load_vdev_metadata(spa);
	if (error != 0)
		return (error);

	error = spa_ld_load_dedup_tables(spa);
	if (error != 0)
		return (error);

	/*
	 * Verify the logs now to make sure we don't have any unexpected errors
	 * when we claim log blocks later.
	 */
	error = spa_ld_verify_logs(spa, type, ereport);
	if (error != 0)
		return (error);

	if (missing_feat_write) {
		ASSERT(spa->spa_load_state == SPA_LOAD_TRYIMPORT);

		/*
		 * At this point, we know that we can open the pool in
		 * read-only mode but not read-write mode. We now have enough
		 * information and can return to userland.
		 */
		return (spa_vdev_err(spa->spa_root_vdev, VDEV_AUX_UNSUP_FEAT,
		    ENOTSUP));
	}

	/*
	 * Traverse the last txgs to make sure the pool was left off in a safe
	 * state. When performing an extreme rewind, we verify the whole pool,
	 * which can take a very long time.
	 */
	error = spa_ld_verify_pool_data(spa);
	if (error != 0)
		return (error);

	/*
	 * Calculate the deflated space for the pool. This must be done before
	 * we write anything to the pool because we'd need to update the space
	 * accounting using the deflated sizes.
	 */
	spa_update_dspace(spa);

	/*
	 * We have now retrieved all the information we needed to open the
	 * pool. If we are importing the pool in read-write mode, a few
	 * additional steps must be performed to finish the import.
	 */
	if (spa_writeable(spa) && (spa->spa_load_state == SPA_LOAD_RECOVER ||
	    spa->spa_load_max_txg == UINT64_MAX)) {
		uint64_t config_cache_txg = spa->spa_config_txg;

		ASSERT(spa->spa_load_state != SPA_LOAD_TRYIMPORT);

		/*
		 * In case of a checkpoint rewind, log the original txg
		 * of the checkpointed uberblock.
		 */
		if (checkpoint_rewind) {
			spa_history_log_internal(spa, "checkpoint rewind",
			    NULL, "rewound state to txg=%llu",
			    (u_longlong_t)spa->spa_uberblock.ub_checkpoint_txg);
		}

		/*
		 * Traverse the ZIL and claim all blocks.
		 */
		spa_ld_claim_log_blocks(spa);

		/*
		 * Kick-off the syncing thread.
		 */
		spa->spa_sync_on = B_TRUE;
		txg_sync_start(spa->spa_dsl_pool);
		mmp_thread_start(spa);

		/*
		 * Wait for all claims to sync.  We sync up to the highest
		 * claimed log block birth time so that claimed log blocks
		 * don't appear to be from the future.  spa_claim_max_txg
		 * will have been set for us by ZIL traversal operations
		 * performed above.
		 */
		txg_wait_synced(spa->spa_dsl_pool, spa->spa_claim_max_txg);

		/*
		 * Check if we need to request an update of the config. On the
		 * next sync, we would update the config stored in vdev labels
		 * and the cachefile (by default /etc/zfs/zpool.cache).
		 */
		spa_ld_check_for_config_update(spa, config_cache_txg,
		    update_config_cache);

		/*
		 * Check all DTLs to see if anything needs resilvering.
		 */
		if (!dsl_scan_resilvering(spa->spa_dsl_pool) &&
		    vdev_resilver_needed(spa->spa_root_vdev, NULL, NULL))
			spa_async_request(spa, SPA_ASYNC_RESILVER);

		/*
		 * Log the fact that we booted up (so that we can detect if
		 * we rebooted in the middle of an operation).
		 */
		spa_history_log_version(spa, "open", NULL);

		spa_restart_removal(spa);
		spa_spawn_aux_threads(spa);

		/*
		 * Delete any inconsistent datasets.
		 *
		 * Note:
		 * Since we may be issuing deletes for clones here,
		 * we make sure to do so after we've spawned all the
		 * auxiliary threads above (from which the livelist
		 * deletion zthr is part of).
		 */
		(void) dmu_objset_find(spa_name(spa),
		    dsl_destroy_inconsistent, NULL, DS_FIND_CHILDREN);

		/*
		 * Clean up any stale temporary dataset userrefs.
		 */
		dsl_pool_clean_tmp_userrefs(spa->spa_dsl_pool);

		spa_config_enter(spa, SCL_CONFIG, FTAG, RW_READER);
		vdev_initialize_restart(spa->spa_root_vdev);
		vdev_trim_restart(spa->spa_root_vdev);
		vdev_autotrim_restart(spa);
		spa_config_exit(spa, SCL_CONFIG, FTAG);
	}

	spa_import_progress_remove(spa_guid(spa));
	spa_load_note(spa, "LOADED");

	return (0);
}