#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vdev_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_11__ {int ub_txg; int ub_timestamp; int ub_mmp_config; } ;
typedef  TYPE_1__ uberblock_t ;
struct TYPE_12__ {int /*<<< orphan*/  spa_load_info; int /*<<< orphan*/ * spa_root_vdev; } ;
typedef  TYPE_2__ spa_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  kmutex_t ;
typedef  int /*<<< orphan*/  kcondvar_t ;
typedef  scalar_t__ hrtime_t ;

/* Variables and functions */
 int /*<<< orphan*/  CV_DEFAULT ; 
 int EINTR ; 
 int EREMOTEIO ; 
 int /*<<< orphan*/  MMP_SEQ (TYPE_1__*) ; 
 scalar_t__ MMP_SEQ_VALID (TYPE_1__*) ; 
 int MMP_STATE_ACTIVE ; 
 int /*<<< orphan*/  MUTEX_DEFAULT ; 
 int /*<<< orphan*/  NSEC2SEC (scalar_t__) ; 
 int SET_ERROR (int) ; 
 int /*<<< orphan*/  VDEV_AUX_ACTIVE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_HOSTID ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_HOSTNAME ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_LOAD_INFO ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_MMP_HOSTID ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_MMP_HOSTNAME ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_MMP_STATE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_MMP_TXG ; 
 int /*<<< orphan*/  cv_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int cv_timedwait_sig (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ ddi_get_lbolt () ; 
 int /*<<< orphan*/  fnvlist_add_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fnvlist_add_uint64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * fnvlist_lookup_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* fnvlist_lookup_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ fnvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ gethrtime () ; 
 scalar_t__ hz ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_exists (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int spa_activity_check_duration (TYPE_2__*,TYPE_1__*) ; 
 int spa_get_random (int) ; 
 int /*<<< orphan*/  spa_guid (TYPE_2__*) ; 
 int /*<<< orphan*/  spa_import_progress_set_mmp_check (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int spa_vdev_err (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vdev_uberblock_load (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  zfs_dbgmsg (char*,int,int,int,int,int,int) ; 

__attribute__((used)) static int
spa_activity_check(spa_t *spa, uberblock_t *ub, nvlist_t *config)
{
	uint64_t txg = ub->ub_txg;
	uint64_t timestamp = ub->ub_timestamp;
	uint64_t mmp_config = ub->ub_mmp_config;
	uint16_t mmp_seq = MMP_SEQ_VALID(ub) ? MMP_SEQ(ub) : 0;
	uint64_t import_delay;
	hrtime_t import_expire;
	nvlist_t *mmp_label = NULL;
	vdev_t *rvd = spa->spa_root_vdev;
	kcondvar_t cv;
	kmutex_t mtx;
	int error = 0;

	cv_init(&cv, NULL, CV_DEFAULT, NULL);
	mutex_init(&mtx, NULL, MUTEX_DEFAULT, NULL);
	mutex_enter(&mtx);

	/*
	 * If ZPOOL_CONFIG_MMP_TXG is present an activity check was performed
	 * during the earlier tryimport.  If the txg recorded there is 0 then
	 * the pool is known to be active on another host.
	 *
	 * Otherwise, the pool might be in use on another host.  Check for
	 * changes in the uberblocks on disk if necessary.
	 */
	if (nvlist_exists(config, ZPOOL_CONFIG_LOAD_INFO)) {
		nvlist_t *nvinfo = fnvlist_lookup_nvlist(config,
		    ZPOOL_CONFIG_LOAD_INFO);

		if (nvlist_exists(nvinfo, ZPOOL_CONFIG_MMP_TXG) &&
		    fnvlist_lookup_uint64(nvinfo, ZPOOL_CONFIG_MMP_TXG) == 0) {
			vdev_uberblock_load(rvd, ub, &mmp_label);
			error = SET_ERROR(EREMOTEIO);
			goto out;
		}
	}

	import_delay = spa_activity_check_duration(spa, ub);

	/* Add a small random factor in case of simultaneous imports (0-25%) */
	import_delay += import_delay * spa_get_random(250) / 1000;

	import_expire = gethrtime() + import_delay;

	while (gethrtime() < import_expire) {
		(void) spa_import_progress_set_mmp_check(spa_guid(spa),
		    NSEC2SEC(import_expire - gethrtime()));

		vdev_uberblock_load(rvd, ub, &mmp_label);

		if (txg != ub->ub_txg || timestamp != ub->ub_timestamp ||
		    mmp_seq != (MMP_SEQ_VALID(ub) ? MMP_SEQ(ub) : 0)) {
			zfs_dbgmsg("multihost activity detected "
			    "txg %llu ub_txg  %llu "
			    "timestamp %llu ub_timestamp  %llu "
			    "mmp_config %#llx ub_mmp_config %#llx",
			    txg, ub->ub_txg, timestamp, ub->ub_timestamp,
			    mmp_config, ub->ub_mmp_config);

			error = SET_ERROR(EREMOTEIO);
			break;
		}

		if (mmp_label) {
			nvlist_free(mmp_label);
			mmp_label = NULL;
		}

		error = cv_timedwait_sig(&cv, &mtx, ddi_get_lbolt() + hz);
		if (error != -1) {
			error = SET_ERROR(EINTR);
			break;
		}
		error = 0;
	}

out:
	mutex_exit(&mtx);
	mutex_destroy(&mtx);
	cv_destroy(&cv);

	/*
	 * If the pool is determined to be active store the status in the
	 * spa->spa_load_info nvlist.  If the remote hostname or hostid are
	 * available from configuration read from disk store them as well.
	 * This allows 'zpool import' to generate a more useful message.
	 *
	 * ZPOOL_CONFIG_MMP_STATE    - observed pool status (mandatory)
	 * ZPOOL_CONFIG_MMP_HOSTNAME - hostname from the active pool
	 * ZPOOL_CONFIG_MMP_HOSTID   - hostid from the active pool
	 */
	if (error == EREMOTEIO) {
		char *hostname = "<unknown>";
		uint64_t hostid = 0;

		if (mmp_label) {
			if (nvlist_exists(mmp_label, ZPOOL_CONFIG_HOSTNAME)) {
				hostname = fnvlist_lookup_string(mmp_label,
				    ZPOOL_CONFIG_HOSTNAME);
				fnvlist_add_string(spa->spa_load_info,
				    ZPOOL_CONFIG_MMP_HOSTNAME, hostname);
			}

			if (nvlist_exists(mmp_label, ZPOOL_CONFIG_HOSTID)) {
				hostid = fnvlist_lookup_uint64(mmp_label,
				    ZPOOL_CONFIG_HOSTID);
				fnvlist_add_uint64(spa->spa_load_info,
				    ZPOOL_CONFIG_MMP_HOSTID, hostid);
			}
		}

		fnvlist_add_uint64(spa->spa_load_info,
		    ZPOOL_CONFIG_MMP_STATE, MMP_STATE_ACTIVE);
		fnvlist_add_uint64(spa->spa_load_info,
		    ZPOOL_CONFIG_MMP_TXG, 0);

		error = spa_vdev_err(rvd, VDEV_AUX_ACTIVE, EREMOTEIO);
	}

	if (mmp_label)
		nvlist_free(mmp_label);

	return (error);
}