#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_20__ ;
typedef  struct TYPE_26__   TYPE_1__ ;

/* Type definitions */
struct TYPE_26__ {int zlp_rewind; scalar_t__ zlp_txg; } ;
typedef  TYPE_1__ zpool_load_policy_t ;
typedef  int /*<<< orphan*/  uint_t ;
typedef  int uint64_t ;
struct TYPE_27__ {void* sav_sync; int /*<<< orphan*/ * sav_config; } ;
struct TYPE_28__ {int spa_import_flags; TYPE_20__ spa_l2cache; TYPE_20__ spa_spares; scalar_t__ spa_autoreplace; int /*<<< orphan*/  spa_load_info; scalar_t__ spa_load_txg; scalar_t__ spa_last_ubsync_txg; int /*<<< orphan*/  spa_config_source; } ;
typedef  TYPE_2__ spa_t ;
typedef  scalar_t__ spa_load_state_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  longlong_t ;

/* Variables and functions */
 int B_FALSE ; 
 void* B_TRUE ; 
 int /*<<< orphan*/  DATA_TYPE_NVLIST_ARRAY ; 
 int /*<<< orphan*/  EEXIST ; 
 int /*<<< orphan*/  ESC_ZFS_POOL_IMPORT ; 
 int FREAD ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  NV_UNIQUE_NAME ; 
 int /*<<< orphan*/  RW_WRITER ; 
 int /*<<< orphan*/  SCL_ALL ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPA_ASYNC_AUTOEXPAND ; 
 int /*<<< orphan*/  SPA_CONFIG_SRC_TRYIMPORT ; 
 int /*<<< orphan*/  SPA_CONFIG_UPDATE_POOL ; 
 scalar_t__ SPA_LOAD_IMPORT ; 
 scalar_t__ SPA_LOAD_RECOVER ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int ZFS_IMPORT_VERBATIM ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_L2CACHE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_LOAD_INFO ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_SPARES ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_TREE ; 
 int ZPOOL_DO_REWIND ; 
 int /*<<< orphan*/  ZPOOL_PROP_ALTROOT ; 
 int /*<<< orphan*/  ZPOOL_PROP_READONLY ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_add_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_add_nvlist_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_alloc (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_lookup_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ nvlist_lookup_nvlist_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ***,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_lookup_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ nvlist_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_activate (TYPE_2__*,int) ; 
 TYPE_2__* spa_add (char*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  spa_async_request (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_async_resume (TYPE_2__*) ; 
 int /*<<< orphan*/  spa_async_suspend (TYPE_2__*) ; 
 int /*<<< orphan*/  spa_aux_check_removed (TYPE_20__*) ; 
 int /*<<< orphan*/  spa_config_enter (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_exit (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_update (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_configfile_set (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spa_deactivate (TYPE_2__*) ; 
 int /*<<< orphan*/  spa_event_notify (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_history_log_version (TYPE_2__*,char*,int /*<<< orphan*/ *) ; 
 int spa_load_best (TYPE_2__*,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  spa_load_l2cache (TYPE_2__*) ; 
 int /*<<< orphan*/  spa_load_spares (TYPE_2__*) ; 
 int /*<<< orphan*/ * spa_lookup (char*) ; 
 int spa_mode_global ; 
 int /*<<< orphan*/  spa_namespace_lock ; 
 int spa_prop_set (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_remove (TYPE_2__*) ; 
 int /*<<< orphan*/  spa_unload (TYPE_2__*) ; 
 int /*<<< orphan*/  spa_write_cachefile (TYPE_2__*,int,void*) ; 
 scalar_t__ spa_writeable (TYPE_2__*) ; 
 int /*<<< orphan*/  zfs_dbgmsg (char*,char*,...) ; 
 int /*<<< orphan*/  zpool_get_load_policy (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  zpool_prop_to_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zvol_create_minors (TYPE_2__*,char*,void*) ; 

int
spa_import(char *pool, nvlist_t *config, nvlist_t *props, uint64_t flags)
{
	spa_t *spa;
	char *altroot = NULL;
	spa_load_state_t state = SPA_LOAD_IMPORT;
	zpool_load_policy_t policy;
	uint64_t mode = spa_mode_global;
	uint64_t readonly = B_FALSE;
	int error;
	nvlist_t *nvroot;
	nvlist_t **spares, **l2cache;
	uint_t nspares, nl2cache;

	/*
	 * If a pool with this name exists, return failure.
	 */
	mutex_enter(&spa_namespace_lock);
	if (spa_lookup(pool) != NULL) {
		mutex_exit(&spa_namespace_lock);
		return (SET_ERROR(EEXIST));
	}

	/*
	 * Create and initialize the spa structure.
	 */
	(void) nvlist_lookup_string(props,
	    zpool_prop_to_name(ZPOOL_PROP_ALTROOT), &altroot);
	(void) nvlist_lookup_uint64(props,
	    zpool_prop_to_name(ZPOOL_PROP_READONLY), &readonly);
	if (readonly)
		mode = FREAD;
	spa = spa_add(pool, config, altroot);
	spa->spa_import_flags = flags;

	/*
	 * Verbatim import - Take a pool and insert it into the namespace
	 * as if it had been loaded at boot.
	 */
	if (spa->spa_import_flags & ZFS_IMPORT_VERBATIM) {
		if (props != NULL)
			spa_configfile_set(spa, props, B_FALSE);

		spa_write_cachefile(spa, B_FALSE, B_TRUE);
		spa_event_notify(spa, NULL, NULL, ESC_ZFS_POOL_IMPORT);
		zfs_dbgmsg("spa_import: verbatim import of %s", pool);
		mutex_exit(&spa_namespace_lock);
		return (0);
	}

	spa_activate(spa, mode);

	/*
	 * Don't start async tasks until we know everything is healthy.
	 */
	spa_async_suspend(spa);

	zpool_get_load_policy(config, &policy);
	if (policy.zlp_rewind & ZPOOL_DO_REWIND)
		state = SPA_LOAD_RECOVER;

	spa->spa_config_source = SPA_CONFIG_SRC_TRYIMPORT;

	if (state != SPA_LOAD_RECOVER) {
		spa->spa_last_ubsync_txg = spa->spa_load_txg = 0;
		zfs_dbgmsg("spa_import: importing %s", pool);
	} else {
		zfs_dbgmsg("spa_import: importing %s, max_txg=%lld "
		    "(RECOVERY MODE)", pool, (longlong_t)policy.zlp_txg);
	}
	error = spa_load_best(spa, state, policy.zlp_txg, policy.zlp_rewind);

	/*
	 * Propagate anything learned while loading the pool and pass it
	 * back to caller (i.e. rewind info, missing devices, etc).
	 */
	VERIFY(nvlist_add_nvlist(config, ZPOOL_CONFIG_LOAD_INFO,
	    spa->spa_load_info) == 0);

	spa_config_enter(spa, SCL_ALL, FTAG, RW_WRITER);
	/*
	 * Toss any existing sparelist, as it doesn't have any validity
	 * anymore, and conflicts with spa_has_spare().
	 */
	if (spa->spa_spares.sav_config) {
		nvlist_free(spa->spa_spares.sav_config);
		spa->spa_spares.sav_config = NULL;
		spa_load_spares(spa);
	}
	if (spa->spa_l2cache.sav_config) {
		nvlist_free(spa->spa_l2cache.sav_config);
		spa->spa_l2cache.sav_config = NULL;
		spa_load_l2cache(spa);
	}

	VERIFY(nvlist_lookup_nvlist(config, ZPOOL_CONFIG_VDEV_TREE,
	    &nvroot) == 0);
	spa_config_exit(spa, SCL_ALL, FTAG);

	if (props != NULL)
		spa_configfile_set(spa, props, B_FALSE);

	if (error != 0 || (props && spa_writeable(spa) &&
	    (error = spa_prop_set(spa, props)))) {
		spa_unload(spa);
		spa_deactivate(spa);
		spa_remove(spa);
		mutex_exit(&spa_namespace_lock);
		return (error);
	}

	spa_async_resume(spa);

	/*
	 * Override any spares and level 2 cache devices as specified by
	 * the user, as these may have correct device names/devids, etc.
	 */
	if (nvlist_lookup_nvlist_array(nvroot, ZPOOL_CONFIG_SPARES,
	    &spares, &nspares) == 0) {
		if (spa->spa_spares.sav_config)
			VERIFY(nvlist_remove(spa->spa_spares.sav_config,
			    ZPOOL_CONFIG_SPARES, DATA_TYPE_NVLIST_ARRAY) == 0);
		else
			VERIFY(nvlist_alloc(&spa->spa_spares.sav_config,
			    NV_UNIQUE_NAME, KM_SLEEP) == 0);
		VERIFY(nvlist_add_nvlist_array(spa->spa_spares.sav_config,
		    ZPOOL_CONFIG_SPARES, spares, nspares) == 0);
		spa_config_enter(spa, SCL_ALL, FTAG, RW_WRITER);
		spa_load_spares(spa);
		spa_config_exit(spa, SCL_ALL, FTAG);
		spa->spa_spares.sav_sync = B_TRUE;
	}
	if (nvlist_lookup_nvlist_array(nvroot, ZPOOL_CONFIG_L2CACHE,
	    &l2cache, &nl2cache) == 0) {
		if (spa->spa_l2cache.sav_config)
			VERIFY(nvlist_remove(spa->spa_l2cache.sav_config,
			    ZPOOL_CONFIG_L2CACHE, DATA_TYPE_NVLIST_ARRAY) == 0);
		else
			VERIFY(nvlist_alloc(&spa->spa_l2cache.sav_config,
			    NV_UNIQUE_NAME, KM_SLEEP) == 0);
		VERIFY(nvlist_add_nvlist_array(spa->spa_l2cache.sav_config,
		    ZPOOL_CONFIG_L2CACHE, l2cache, nl2cache) == 0);
		spa_config_enter(spa, SCL_ALL, FTAG, RW_WRITER);
		spa_load_l2cache(spa);
		spa_config_exit(spa, SCL_ALL, FTAG);
		spa->spa_l2cache.sav_sync = B_TRUE;
	}

	/*
	 * Check for any removed devices.
	 */
	if (spa->spa_autoreplace) {
		spa_aux_check_removed(&spa->spa_spares);
		spa_aux_check_removed(&spa->spa_l2cache);
	}

	if (spa_writeable(spa)) {
		/*
		 * Update the config cache to include the newly-imported pool.
		 */
		spa_config_update(spa, SPA_CONFIG_UPDATE_POOL);
	}

	/*
	 * It's possible that the pool was expanded while it was exported.
	 * We kick off an async task to handle this for us.
	 */
	spa_async_request(spa, SPA_ASYNC_AUTOEXPAND);

	spa_history_log_version(spa, "import", NULL);

	spa_event_notify(spa, NULL, NULL, ESC_ZFS_POOL_IMPORT);

	mutex_exit(&spa_namespace_lock);

	zvol_create_minors(spa, pool, B_TRUE);

	return (0);
}