#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int zlp_rewind; int /*<<< orphan*/  zlp_txg; } ;
typedef  TYPE_1__ zpool_load_policy_t ;
struct TYPE_17__ {scalar_t__ spa_state; int spa_last_open_failed; scalar_t__ spa_load_txg; scalar_t__ spa_last_ubsync_txg; int /*<<< orphan*/  spa_load_info; int /*<<< orphan*/ * spa_config; int /*<<< orphan*/  spa_config_source; } ;
typedef  TYPE_2__ spa_t ;
typedef  scalar_t__ spa_load_state_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int B_FALSE ; 
 int B_TRUE ; 
 int EBADF ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 scalar_t__ MUTEX_NOT_HELD (int /*<<< orphan*/ *) ; 
 scalar_t__ POOL_STATE_UNINITIALIZED ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPA_CONFIG_SRC_CACHEFILE ; 
 scalar_t__ SPA_LOAD_OPEN ; 
 scalar_t__ SPA_LOAD_RECOVER ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_LOAD_INFO ; 
 int ZPOOL_DO_REWIND ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_add_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_dup (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_activate (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * spa_config_generate (TYPE_2__*,int /*<<< orphan*/ *,unsigned long long,int) ; 
 int /*<<< orphan*/  spa_deactivate (TYPE_2__*) ; 
 int spa_load_best (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* spa_lookup (char const*) ; 
 int /*<<< orphan*/  spa_mode_global ; 
 int /*<<< orphan*/  spa_name (TYPE_2__*) ; 
 int /*<<< orphan*/  spa_namespace_lock ; 
 int /*<<< orphan*/  spa_open_ref (TYPE_2__*,void*) ; 
 int /*<<< orphan*/  spa_remove (TYPE_2__*) ; 
 int /*<<< orphan*/  spa_unload (TYPE_2__*) ; 
 int /*<<< orphan*/  spa_write_cachefile (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  zfs_dbgmsg (char*,char const*) ; 
 int /*<<< orphan*/  zpool_get_load_policy (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  zvol_create_minors (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
spa_open_common(const char *pool, spa_t **spapp, void *tag, nvlist_t *nvpolicy,
    nvlist_t **config)
{
	spa_t *spa;
	spa_load_state_t state = SPA_LOAD_OPEN;
	int error;
	int locked = B_FALSE;
	int firstopen = B_FALSE;

	*spapp = NULL;

	/*
	 * As disgusting as this is, we need to support recursive calls to this
	 * function because dsl_dir_open() is called during spa_load(), and ends
	 * up calling spa_open() again.  The real fix is to figure out how to
	 * avoid dsl_dir_open() calling this in the first place.
	 */
	if (MUTEX_NOT_HELD(&spa_namespace_lock)) {
		mutex_enter(&spa_namespace_lock);
		locked = B_TRUE;
	}

	if ((spa = spa_lookup(pool)) == NULL) {
		if (locked)
			mutex_exit(&spa_namespace_lock);
		return (SET_ERROR(ENOENT));
	}

	if (spa->spa_state == POOL_STATE_UNINITIALIZED) {
		zpool_load_policy_t policy;

		firstopen = B_TRUE;

		zpool_get_load_policy(nvpolicy ? nvpolicy : spa->spa_config,
		    &policy);
		if (policy.zlp_rewind & ZPOOL_DO_REWIND)
			state = SPA_LOAD_RECOVER;

		spa_activate(spa, spa_mode_global);

		if (state != SPA_LOAD_RECOVER)
			spa->spa_last_ubsync_txg = spa->spa_load_txg = 0;
		spa->spa_config_source = SPA_CONFIG_SRC_CACHEFILE;

		zfs_dbgmsg("spa_open_common: opening %s", pool);
		error = spa_load_best(spa, state, policy.zlp_txg,
		    policy.zlp_rewind);

		if (error == EBADF) {
			/*
			 * If vdev_validate() returns failure (indicated by
			 * EBADF), it indicates that one of the vdevs indicates
			 * that the pool has been exported or destroyed.  If
			 * this is the case, the config cache is out of sync and
			 * we should remove the pool from the namespace.
			 */
			spa_unload(spa);
			spa_deactivate(spa);
			spa_write_cachefile(spa, B_TRUE, B_TRUE);
			spa_remove(spa);
			if (locked)
				mutex_exit(&spa_namespace_lock);
			return (SET_ERROR(ENOENT));
		}

		if (error) {
			/*
			 * We can't open the pool, but we still have useful
			 * information: the state of each vdev after the
			 * attempted vdev_open().  Return this to the user.
			 */
			if (config != NULL && spa->spa_config) {
				VERIFY(nvlist_dup(spa->spa_config, config,
				    KM_SLEEP) == 0);
				VERIFY(nvlist_add_nvlist(*config,
				    ZPOOL_CONFIG_LOAD_INFO,
				    spa->spa_load_info) == 0);
			}
			spa_unload(spa);
			spa_deactivate(spa);
			spa->spa_last_open_failed = error;
			if (locked)
				mutex_exit(&spa_namespace_lock);
			*spapp = NULL;
			return (error);
		}
	}

	spa_open_ref(spa, tag);

	if (config != NULL)
		*config = spa_config_generate(spa, NULL, -1ULL, B_TRUE);

	/*
	 * If we've recovered the pool, pass back any information we
	 * gathered while doing the load.
	 */
	if (state == SPA_LOAD_RECOVER) {
		VERIFY(nvlist_add_nvlist(*config, ZPOOL_CONFIG_LOAD_INFO,
		    spa->spa_load_info) == 0);
	}

	if (locked) {
		spa->spa_last_open_failed = 0;
		spa->spa_last_ubsync_txg = 0;
		spa->spa_load_txg = 0;
		mutex_exit(&spa_namespace_lock);
	}

	if (firstopen)
		zvol_create_minors(spa, spa_name(spa), B_TRUE);

	*spapp = spa;

	return (0);
}