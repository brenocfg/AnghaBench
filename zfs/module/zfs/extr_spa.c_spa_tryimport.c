#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {scalar_t__ zlp_txg; } ;
typedef  TYPE_2__ zpool_load_policy_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_17__ {int /*<<< orphan*/  ub_timestamp; } ;
struct TYPE_19__ {scalar_t__ spa_load_max_txg; scalar_t__ spa_bootfs; int /*<<< orphan*/  spa_errata; int /*<<< orphan*/  spa_load_info; TYPE_1__ spa_uberblock; int /*<<< orphan*/ * spa_root_vdev; int /*<<< orphan*/  spa_config_source; int /*<<< orphan*/  spa_extreme_rewind; int /*<<< orphan*/  spa_config; } ;
typedef  TYPE_3__ spa_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  longlong_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int EEXIST ; 
 int /*<<< orphan*/  FREAD ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  MAXPATHLEN ; 
 int /*<<< orphan*/  RW_READER ; 
 int /*<<< orphan*/  SCL_CONFIG ; 
 int /*<<< orphan*/  SPA_CONFIG_SRC_CACHEFILE ; 
 int /*<<< orphan*/  SPA_CONFIG_SRC_SCAN ; 
 int /*<<< orphan*/  SPA_IMPORT_EXISTING ; 
 int /*<<< orphan*/  SPA_LOAD_TRYIMPORT ; 
 int /*<<< orphan*/  TRYIMPORT_NAME ; 
 scalar_t__ UINT64_MAX ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_BOOTFS ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_CACHEFILE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_ERRATA ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_LOAD_INFO ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_POOL_NAME ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_POOL_STATE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_TIMESTAMP ; 
 scalar_t__ dsl_dsobj_to_dsname (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 char* kmem_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_add_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_add_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ nvlist_add_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_lookup_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 scalar_t__ nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  spa_activate (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* spa_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_add_l2cache (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_add_spares (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_config_enter (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_exit (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * spa_config_generate (TYPE_3__*,int /*<<< orphan*/ *,unsigned long long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_deactivate (TYPE_3__*) ; 
 int spa_load (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_name (TYPE_3__*) ; 
 int /*<<< orphan*/  spa_namespace_lock ; 
 int /*<<< orphan*/  spa_remove (TYPE_3__*) ; 
 int /*<<< orphan*/  spa_unload (TYPE_3__*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_dbgmsg (char*,char*,...) ; 
 int /*<<< orphan*/  zpool_get_load_policy (int /*<<< orphan*/ ,TYPE_2__*) ; 

nvlist_t *
spa_tryimport(nvlist_t *tryconfig)
{
	nvlist_t *config = NULL;
	char *poolname, *cachefile;
	spa_t *spa;
	uint64_t state;
	int error;
	zpool_load_policy_t policy;

	if (nvlist_lookup_string(tryconfig, ZPOOL_CONFIG_POOL_NAME, &poolname))
		return (NULL);

	if (nvlist_lookup_uint64(tryconfig, ZPOOL_CONFIG_POOL_STATE, &state))
		return (NULL);

	/*
	 * Create and initialize the spa structure.
	 */
	mutex_enter(&spa_namespace_lock);
	spa = spa_add(TRYIMPORT_NAME, tryconfig, NULL);
	spa_activate(spa, FREAD);

	/*
	 * Rewind pool if a max txg was provided.
	 */
	zpool_get_load_policy(spa->spa_config, &policy);
	if (policy.zlp_txg != UINT64_MAX) {
		spa->spa_load_max_txg = policy.zlp_txg;
		spa->spa_extreme_rewind = B_TRUE;
		zfs_dbgmsg("spa_tryimport: importing %s, max_txg=%lld",
		    poolname, (longlong_t)policy.zlp_txg);
	} else {
		zfs_dbgmsg("spa_tryimport: importing %s", poolname);
	}

	if (nvlist_lookup_string(tryconfig, ZPOOL_CONFIG_CACHEFILE, &cachefile)
	    == 0) {
		zfs_dbgmsg("spa_tryimport: using cachefile '%s'", cachefile);
		spa->spa_config_source = SPA_CONFIG_SRC_CACHEFILE;
	} else {
		spa->spa_config_source = SPA_CONFIG_SRC_SCAN;
	}

	error = spa_load(spa, SPA_LOAD_TRYIMPORT, SPA_IMPORT_EXISTING);

	/*
	 * If 'tryconfig' was at least parsable, return the current config.
	 */
	if (spa->spa_root_vdev != NULL) {
		config = spa_config_generate(spa, NULL, -1ULL, B_TRUE);
		VERIFY(nvlist_add_string(config, ZPOOL_CONFIG_POOL_NAME,
		    poolname) == 0);
		VERIFY(nvlist_add_uint64(config, ZPOOL_CONFIG_POOL_STATE,
		    state) == 0);
		VERIFY(nvlist_add_uint64(config, ZPOOL_CONFIG_TIMESTAMP,
		    spa->spa_uberblock.ub_timestamp) == 0);
		VERIFY(nvlist_add_nvlist(config, ZPOOL_CONFIG_LOAD_INFO,
		    spa->spa_load_info) == 0);
		VERIFY(nvlist_add_uint64(config, ZPOOL_CONFIG_ERRATA,
		    spa->spa_errata) == 0);

		/*
		 * If the bootfs property exists on this pool then we
		 * copy it out so that external consumers can tell which
		 * pools are bootable.
		 */
		if ((!error || error == EEXIST) && spa->spa_bootfs) {
			char *tmpname = kmem_alloc(MAXPATHLEN, KM_SLEEP);

			/*
			 * We have to play games with the name since the
			 * pool was opened as TRYIMPORT_NAME.
			 */
			if (dsl_dsobj_to_dsname(spa_name(spa),
			    spa->spa_bootfs, tmpname) == 0) {
				char *cp;
				char *dsname;

				dsname = kmem_alloc(MAXPATHLEN, KM_SLEEP);

				cp = strchr(tmpname, '/');
				if (cp == NULL) {
					(void) strlcpy(dsname, tmpname,
					    MAXPATHLEN);
				} else {
					(void) snprintf(dsname, MAXPATHLEN,
					    "%s/%s", poolname, ++cp);
				}
				VERIFY(nvlist_add_string(config,
				    ZPOOL_CONFIG_BOOTFS, dsname) == 0);
				kmem_free(dsname, MAXPATHLEN);
			}
			kmem_free(tmpname, MAXPATHLEN);
		}

		/*
		 * Add the list of hot spares and level 2 cache devices.
		 */
		spa_config_enter(spa, SCL_CONFIG, FTAG, RW_READER);
		spa_add_spares(spa, config);
		spa_add_l2cache(spa, config);
		spa_config_exit(spa, SCL_CONFIG, FTAG);
	}

	spa_unload(spa);
	spa_deactivate(spa);
	spa_remove(spa);
	mutex_exit(&spa_namespace_lock);

	return (config);
}