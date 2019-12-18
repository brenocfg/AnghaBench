#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int spa_import_flags; scalar_t__ spa_ccw_fail_time; int /*<<< orphan*/  spa_config_list; int /*<<< orphan*/  spa_props_lock; int /*<<< orphan*/ * spa_config; } ;
typedef  TYPE_1__ spa_t ;
struct TYPE_18__ {int /*<<< orphan*/ * scd_path; } ;
typedef  TYPE_2__ spa_config_dirent_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ B_FALSE ; 
 scalar_t__ B_TRUE ; 
 int /*<<< orphan*/  ESC_ZFS_CONFIG_SYNC ; 
 int /*<<< orphan*/  FM_EREPORT_ZFS_CONFIG_CACHE_WRITE ; 
 int FWRITE ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SPA_ASYNC_CONFIG_UPDATE ; 
 int ZFS_IMPORT_TEMP_NAME ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_POOL_NAME ; 
 int /*<<< orphan*/  fnvlist_add_nvlist (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 char* fnvlist_lookup_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ gethrtime () ; 
 int /*<<< orphan*/  kmem_free (TYPE_2__*,int) ; 
 TYPE_2__* list_head (int /*<<< orphan*/ *) ; 
 TYPE_2__* list_next (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * rootdir ; 
 int /*<<< orphan*/  spa_async_request (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_generation ; 
 int spa_config_write (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_event_notify (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int spa_mode_global ; 
 char* spa_name (TYPE_1__*) ; 
 int /*<<< orphan*/  spa_namespace_lock ; 
 TYPE_1__* spa_next (TYPE_1__*) ; 
 int /*<<< orphan*/  spa_strfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_writeable (TYPE_1__*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_ereport_post (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
spa_write_cachefile(spa_t *target, boolean_t removing, boolean_t postsysevent)
{
	spa_config_dirent_t *dp, *tdp;
	nvlist_t *nvl;
	char *pool_name;
	boolean_t ccw_failure;
	int error = 0;

	ASSERT(MUTEX_HELD(&spa_namespace_lock));

	if (rootdir == NULL || !(spa_mode_global & FWRITE))
		return;

	/*
	 * Iterate over all cachefiles for the pool, past or present.  When the
	 * cachefile is changed, the new one is pushed onto this list, allowing
	 * us to update previous cachefiles that no longer contain this pool.
	 */
	ccw_failure = B_FALSE;
	for (dp = list_head(&target->spa_config_list); dp != NULL;
	    dp = list_next(&target->spa_config_list, dp)) {
		spa_t *spa = NULL;
		if (dp->scd_path == NULL)
			continue;

		/*
		 * Iterate over all pools, adding any matching pools to 'nvl'.
		 */
		nvl = NULL;
		while ((spa = spa_next(spa)) != NULL) {
			/*
			 * Skip over our own pool if we're about to remove
			 * ourselves from the spa namespace or any pool that
			 * is readonly. Since we cannot guarantee that a
			 * readonly pool would successfully import upon reboot,
			 * we don't allow them to be written to the cache file.
			 */
			if ((spa == target && removing) ||
			    !spa_writeable(spa))
				continue;

			mutex_enter(&spa->spa_props_lock);
			tdp = list_head(&spa->spa_config_list);
			if (spa->spa_config == NULL ||
			    tdp == NULL ||
			    tdp->scd_path == NULL ||
			    strcmp(tdp->scd_path, dp->scd_path) != 0) {
				mutex_exit(&spa->spa_props_lock);
				continue;
			}

			if (nvl == NULL)
				nvl = fnvlist_alloc();

			if (spa->spa_import_flags & ZFS_IMPORT_TEMP_NAME)
				pool_name = fnvlist_lookup_string(
				    spa->spa_config, ZPOOL_CONFIG_POOL_NAME);
			else
				pool_name = spa_name(spa);

			fnvlist_add_nvlist(nvl, pool_name, spa->spa_config);
			mutex_exit(&spa->spa_props_lock);
		}

		error = spa_config_write(dp, nvl);
		if (error != 0)
			ccw_failure = B_TRUE;
		nvlist_free(nvl);
	}

	if (ccw_failure) {
		/*
		 * Keep trying so that configuration data is
		 * written if/when any temporary filesystem
		 * resource issues are resolved.
		 */
		if (target->spa_ccw_fail_time == 0) {
			zfs_ereport_post(FM_EREPORT_ZFS_CONFIG_CACHE_WRITE,
			    target, NULL, NULL, NULL, 0, 0);
		}
		target->spa_ccw_fail_time = gethrtime();
		spa_async_request(target, SPA_ASYNC_CONFIG_UPDATE);
	} else {
		/*
		 * Do not rate limit future attempts to update
		 * the config cache.
		 */
		target->spa_ccw_fail_time = 0;
	}

	/*
	 * Remove any config entries older than the current one.
	 */
	dp = list_head(&target->spa_config_list);
	while ((tdp = list_next(&target->spa_config_list, dp)) != NULL) {
		list_remove(&target->spa_config_list, tdp);
		if (tdp->scd_path != NULL)
			spa_strfree(tdp->scd_path);
		kmem_free(tdp, sizeof (spa_config_dirent_t));
	}

	spa_config_generation++;

	if (postsysevent)
		spa_event_notify(target, NULL, NULL, ESC_ZFS_CONFIG_SYNC);
}