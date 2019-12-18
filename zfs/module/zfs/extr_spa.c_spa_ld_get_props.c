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
typedef  int /*<<< orphan*/  vdev_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_9__ {int /*<<< orphan*/  zcs_bytes; } ;
struct TYPE_10__ {scalar_t__ spa_deflate; scalar_t__ spa_creation_version; scalar_t__ spa_errlog_last; scalar_t__ spa_errlog_scrub; scalar_t__ spa_livelists_to_delete; scalar_t__ spa_history; scalar_t__ spa_all_vdev_zaps; scalar_t__ spa_delegation; scalar_t__ spa_pool_props_object; scalar_t__ spa_bootfs; scalar_t__ spa_failmode; scalar_t__ spa_autoexpand; scalar_t__ spa_multihost; scalar_t__ spa_autotrim; int spa_autoreplace; scalar_t__ spa_missing_tvds; scalar_t__ spa_load_state; int /*<<< orphan*/ * spa_root_vdev; int /*<<< orphan*/  spa_avz_action; int /*<<< orphan*/  spa_config_object; int /*<<< orphan*/  spa_meta_objset; int /*<<< orphan*/  spa_deferred_bpobj; TYPE_1__ spa_cksum_salt; } ;
typedef  TYPE_2__ spa_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVZ_ACTION_DESTROY ; 
 int /*<<< orphan*/  AVZ_ACTION_INITIALIZE ; 
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  DMU_POOL_CHECKSUM_SALT ; 
 int /*<<< orphan*/  DMU_POOL_CREATION_VERSION ; 
 int /*<<< orphan*/  DMU_POOL_DEFLATE ; 
 int /*<<< orphan*/  DMU_POOL_DELETED_CLONES ; 
 int /*<<< orphan*/  DMU_POOL_DIRECTORY_OBJECT ; 
 int /*<<< orphan*/  DMU_POOL_ERRLOG_LAST ; 
 int /*<<< orphan*/  DMU_POOL_ERRLOG_SCRUB ; 
 int /*<<< orphan*/  DMU_POOL_HISTORY ; 
 int /*<<< orphan*/  DMU_POOL_PROPS ; 
 int /*<<< orphan*/  DMU_POOL_SYNC_BPOBJ ; 
 int /*<<< orphan*/  DMU_POOL_VDEV_ZAP_MAP ; 
 int /*<<< orphan*/  EIO ; 
 int ENOENT ; 
 scalar_t__ SPA_LOAD_TRYIMPORT ; 
 int /*<<< orphan*/  VDEV_AUX_CORRUPT_DATA ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 scalar_t__ ZIO_FAILURE_MODE_CONTINUE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_HAS_PER_VDEV_ZAPS ; 
 int /*<<< orphan*/  ZPOOL_PROP_AUTOEXPAND ; 
 int /*<<< orphan*/  ZPOOL_PROP_AUTOREPLACE ; 
 int /*<<< orphan*/  ZPOOL_PROP_AUTOTRIM ; 
 int /*<<< orphan*/  ZPOOL_PROP_BOOTFS ; 
 int /*<<< orphan*/  ZPOOL_PROP_DELEGATION ; 
 int /*<<< orphan*/  ZPOOL_PROP_FAILUREMODE ; 
 int /*<<< orphan*/  ZPOOL_PROP_MULTIHOST ; 
 int bpobj_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ load_nvlist (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nvlist_exists (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  random_get_pseudo_bytes (int /*<<< orphan*/ ,int) ; 
 int spa_dir_prop (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_load_failed (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  spa_load_note (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  spa_prop_find (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int spa_vdev_err (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_count_verify_zaps (int /*<<< orphan*/ *) ; 
 int zap_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ zpool_prop_default_numeric (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
spa_ld_get_props(spa_t *spa)
{
	int error = 0;
	uint64_t obj;
	vdev_t *rvd = spa->spa_root_vdev;

	/* Grab the checksum salt from the MOS. */
	error = zap_lookup(spa->spa_meta_objset, DMU_POOL_DIRECTORY_OBJECT,
	    DMU_POOL_CHECKSUM_SALT, 1,
	    sizeof (spa->spa_cksum_salt.zcs_bytes),
	    spa->spa_cksum_salt.zcs_bytes);
	if (error == ENOENT) {
		/* Generate a new salt for subsequent use */
		(void) random_get_pseudo_bytes(spa->spa_cksum_salt.zcs_bytes,
		    sizeof (spa->spa_cksum_salt.zcs_bytes));
	} else if (error != 0) {
		spa_load_failed(spa, "unable to retrieve checksum salt from "
		    "MOS [error=%d]", error);
		return (spa_vdev_err(rvd, VDEV_AUX_CORRUPT_DATA, EIO));
	}

	if (spa_dir_prop(spa, DMU_POOL_SYNC_BPOBJ, &obj, B_TRUE) != 0)
		return (spa_vdev_err(rvd, VDEV_AUX_CORRUPT_DATA, EIO));
	error = bpobj_open(&spa->spa_deferred_bpobj, spa->spa_meta_objset, obj);
	if (error != 0) {
		spa_load_failed(spa, "error opening deferred-frees bpobj "
		    "[error=%d]", error);
		return (spa_vdev_err(rvd, VDEV_AUX_CORRUPT_DATA, EIO));
	}

	/*
	 * Load the bit that tells us to use the new accounting function
	 * (raid-z deflation).  If we have an older pool, this will not
	 * be present.
	 */
	error = spa_dir_prop(spa, DMU_POOL_DEFLATE, &spa->spa_deflate, B_FALSE);
	if (error != 0 && error != ENOENT)
		return (spa_vdev_err(rvd, VDEV_AUX_CORRUPT_DATA, EIO));

	error = spa_dir_prop(spa, DMU_POOL_CREATION_VERSION,
	    &spa->spa_creation_version, B_FALSE);
	if (error != 0 && error != ENOENT)
		return (spa_vdev_err(rvd, VDEV_AUX_CORRUPT_DATA, EIO));

	/*
	 * Load the persistent error log.  If we have an older pool, this will
	 * not be present.
	 */
	error = spa_dir_prop(spa, DMU_POOL_ERRLOG_LAST, &spa->spa_errlog_last,
	    B_FALSE);
	if (error != 0 && error != ENOENT)
		return (spa_vdev_err(rvd, VDEV_AUX_CORRUPT_DATA, EIO));

	error = spa_dir_prop(spa, DMU_POOL_ERRLOG_SCRUB,
	    &spa->spa_errlog_scrub, B_FALSE);
	if (error != 0 && error != ENOENT)
		return (spa_vdev_err(rvd, VDEV_AUX_CORRUPT_DATA, EIO));

	/*
	 * Load the livelist deletion field. If a livelist is queued for
	 * deletion, indicate that in the spa
	 */
	error = spa_dir_prop(spa, DMU_POOL_DELETED_CLONES,
	    &spa->spa_livelists_to_delete, B_FALSE);
	if (error != 0 && error != ENOENT)
		return (spa_vdev_err(rvd, VDEV_AUX_CORRUPT_DATA, EIO));

	/*
	 * Load the history object.  If we have an older pool, this
	 * will not be present.
	 */
	error = spa_dir_prop(spa, DMU_POOL_HISTORY, &spa->spa_history, B_FALSE);
	if (error != 0 && error != ENOENT)
		return (spa_vdev_err(rvd, VDEV_AUX_CORRUPT_DATA, EIO));

	/*
	 * Load the per-vdev ZAP map. If we have an older pool, this will not
	 * be present; in this case, defer its creation to a later time to
	 * avoid dirtying the MOS this early / out of sync context. See
	 * spa_sync_config_object.
	 */

	/* The sentinel is only available in the MOS config. */
	nvlist_t *mos_config;
	if (load_nvlist(spa, spa->spa_config_object, &mos_config) != 0) {
		spa_load_failed(spa, "unable to retrieve MOS config");
		return (spa_vdev_err(rvd, VDEV_AUX_CORRUPT_DATA, EIO));
	}

	error = spa_dir_prop(spa, DMU_POOL_VDEV_ZAP_MAP,
	    &spa->spa_all_vdev_zaps, B_FALSE);

	if (error == ENOENT) {
		VERIFY(!nvlist_exists(mos_config,
		    ZPOOL_CONFIG_HAS_PER_VDEV_ZAPS));
		spa->spa_avz_action = AVZ_ACTION_INITIALIZE;
		ASSERT0(vdev_count_verify_zaps(spa->spa_root_vdev));
	} else if (error != 0) {
		return (spa_vdev_err(rvd, VDEV_AUX_CORRUPT_DATA, EIO));
	} else if (!nvlist_exists(mos_config, ZPOOL_CONFIG_HAS_PER_VDEV_ZAPS)) {
		/*
		 * An older version of ZFS overwrote the sentinel value, so
		 * we have orphaned per-vdev ZAPs in the MOS. Defer their
		 * destruction to later; see spa_sync_config_object.
		 */
		spa->spa_avz_action = AVZ_ACTION_DESTROY;
		/*
		 * We're assuming that no vdevs have had their ZAPs created
		 * before this. Better be sure of it.
		 */
		ASSERT0(vdev_count_verify_zaps(spa->spa_root_vdev));
	}
	nvlist_free(mos_config);

	spa->spa_delegation = zpool_prop_default_numeric(ZPOOL_PROP_DELEGATION);

	error = spa_dir_prop(spa, DMU_POOL_PROPS, &spa->spa_pool_props_object,
	    B_FALSE);
	if (error && error != ENOENT)
		return (spa_vdev_err(rvd, VDEV_AUX_CORRUPT_DATA, EIO));

	if (error == 0) {
		uint64_t autoreplace;

		spa_prop_find(spa, ZPOOL_PROP_BOOTFS, &spa->spa_bootfs);
		spa_prop_find(spa, ZPOOL_PROP_AUTOREPLACE, &autoreplace);
		spa_prop_find(spa, ZPOOL_PROP_DELEGATION, &spa->spa_delegation);
		spa_prop_find(spa, ZPOOL_PROP_FAILUREMODE, &spa->spa_failmode);
		spa_prop_find(spa, ZPOOL_PROP_AUTOEXPAND, &spa->spa_autoexpand);
		spa_prop_find(spa, ZPOOL_PROP_MULTIHOST, &spa->spa_multihost);
		spa_prop_find(spa, ZPOOL_PROP_AUTOTRIM, &spa->spa_autotrim);
		spa->spa_autoreplace = (autoreplace != 0);
	}

	/*
	 * If we are importing a pool with missing top-level vdevs,
	 * we enforce that the pool doesn't panic or get suspended on
	 * error since the likelihood of missing data is extremely high.
	 */
	if (spa->spa_missing_tvds > 0 &&
	    spa->spa_failmode != ZIO_FAILURE_MODE_CONTINUE &&
	    spa->spa_load_state != SPA_LOAD_TRYIMPORT) {
		spa_load_note(spa, "forcing failmode to 'continue' "
		    "as some top level vdevs are missing");
		spa->spa_failmode = ZIO_FAILURE_MODE_CONTINUE;
	}

	return (0);
}