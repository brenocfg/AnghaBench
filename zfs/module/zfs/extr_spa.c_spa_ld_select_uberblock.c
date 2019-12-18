#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vdev_t ;
struct TYPE_21__ {scalar_t__ ub_checkpoint_txg; scalar_t__ ub_txg; scalar_t__ ub_mmp_magic; scalar_t__ ub_version; scalar_t__ ub_mmp_delay; } ;
typedef  TYPE_1__ uberblock_t ;
typedef  int /*<<< orphan*/  u_longlong_t ;
struct TYPE_22__ {scalar_t__ spa_load_max_txg; int /*<<< orphan*/ * spa_config_splitting; int /*<<< orphan*/  spa_config; int /*<<< orphan*/  spa_load_info; int /*<<< orphan*/ * spa_label_features; TYPE_1__ spa_uberblock; int /*<<< orphan*/ * spa_root_vdev; } ;
typedef  TYPE_2__ spa_t ;
typedef  scalar_t__ spa_import_type_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 int /*<<< orphan*/  ENOTSUP ; 
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  EREMOTEIO ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 scalar_t__ MMP_MAGIC ; 
 int /*<<< orphan*/  MMP_SEQ (TYPE_1__*) ; 
 scalar_t__ MMP_SEQ_VALID (TYPE_1__*) ; 
 scalar_t__ MMP_STATE_INACTIVE ; 
 scalar_t__ MMP_STATE_NO_HOSTID ; 
 int /*<<< orphan*/  NV_UNIQUE_NAME ; 
 int /*<<< orphan*/  RW_WRITER ; 
 int /*<<< orphan*/  SCL_ALL ; 
 scalar_t__ SPA_IMPORT_ASSEMBLE ; 
 scalar_t__ SPA_VERSION_FEATURES ; 
 int /*<<< orphan*/  SPA_VERSION_IS_SUPPORTED (scalar_t__) ; 
 scalar_t__ UINT64_MAX ; 
 int /*<<< orphan*/  VDEV_AUX_ACTIVE ; 
 int /*<<< orphan*/  VDEV_AUX_CORRUPT_DATA ; 
 int /*<<< orphan*/  VDEV_AUX_UNSUP_FEAT ; 
 int /*<<< orphan*/  VDEV_AUX_VERSION_NEWER ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_FEATURES_FOR_READ ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_MMP_SEQ ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_MMP_STATE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_MMP_TXG ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_UNSUP_FEAT ; 
 int /*<<< orphan*/  fnvlist_add_uint16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fnvlist_add_uint64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ nvlist_add_nvlist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_add_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ nvlist_alloc (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_dup (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_lookup_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvpair_name (int /*<<< orphan*/ *) ; 
 int spa_activity_check (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ spa_activity_check_required (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_enter (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_exit (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ spa_get_hostid (TYPE_2__*) ; 
 int /*<<< orphan*/  spa_guid (TYPE_2__*) ; 
 int /*<<< orphan*/  spa_import_progress_set_max_txg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ spa_importing_readonly_checkpoint (TYPE_2__*) ; 
 int /*<<< orphan*/  spa_ld_select_uberblock_done (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  spa_load_failed (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  spa_load_note (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_try_repair (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int spa_vdev_err (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_uberblock_load (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  zfeature_is_supported (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
spa_ld_select_uberblock(spa_t *spa, spa_import_type_t type)
{
	vdev_t *rvd = spa->spa_root_vdev;
	nvlist_t *label;
	uberblock_t *ub = &spa->spa_uberblock;
	boolean_t activity_check = B_FALSE;

	/*
	 * If we are opening the checkpointed state of the pool by
	 * rewinding to it, at this point we will have written the
	 * checkpointed uberblock to the vdev labels, so searching
	 * the labels will find the right uberblock.  However, if
	 * we are opening the checkpointed state read-only, we have
	 * not modified the labels. Therefore, we must ignore the
	 * labels and continue using the spa_uberblock that was set
	 * by spa_ld_checkpoint_rewind.
	 *
	 * Note that it would be fine to ignore the labels when
	 * rewinding (opening writeable) as well. However, if we
	 * crash just after writing the labels, we will end up
	 * searching the labels. Doing so in the common case means
	 * that this code path gets exercised normally, rather than
	 * just in the edge case.
	 */
	if (ub->ub_checkpoint_txg != 0 &&
	    spa_importing_readonly_checkpoint(spa)) {
		spa_ld_select_uberblock_done(spa, ub);
		return (0);
	}

	/*
	 * Find the best uberblock.
	 */
	vdev_uberblock_load(rvd, ub, &label);

	/*
	 * If we weren't able to find a single valid uberblock, return failure.
	 */
	if (ub->ub_txg == 0) {
		nvlist_free(label);
		spa_load_failed(spa, "no valid uberblock found");
		return (spa_vdev_err(rvd, VDEV_AUX_CORRUPT_DATA, ENXIO));
	}

	if (spa->spa_load_max_txg != UINT64_MAX) {
		(void) spa_import_progress_set_max_txg(spa_guid(spa),
		    (u_longlong_t)spa->spa_load_max_txg);
	}
	spa_load_note(spa, "using uberblock with txg=%llu",
	    (u_longlong_t)ub->ub_txg);


	/*
	 * For pools which have the multihost property on determine if the
	 * pool is truly inactive and can be safely imported.  Prevent
	 * hosts which don't have a hostid set from importing the pool.
	 */
	activity_check = spa_activity_check_required(spa, ub, label,
	    spa->spa_config);
	if (activity_check) {
		if (ub->ub_mmp_magic == MMP_MAGIC && ub->ub_mmp_delay &&
		    spa_get_hostid(spa) == 0) {
			nvlist_free(label);
			fnvlist_add_uint64(spa->spa_load_info,
			    ZPOOL_CONFIG_MMP_STATE, MMP_STATE_NO_HOSTID);
			return (spa_vdev_err(rvd, VDEV_AUX_ACTIVE, EREMOTEIO));
		}

		int error = spa_activity_check(spa, ub, spa->spa_config);
		if (error) {
			nvlist_free(label);
			return (error);
		}

		fnvlist_add_uint64(spa->spa_load_info,
		    ZPOOL_CONFIG_MMP_STATE, MMP_STATE_INACTIVE);
		fnvlist_add_uint64(spa->spa_load_info,
		    ZPOOL_CONFIG_MMP_TXG, ub->ub_txg);
		fnvlist_add_uint16(spa->spa_load_info,
		    ZPOOL_CONFIG_MMP_SEQ,
		    (MMP_SEQ_VALID(ub) ? MMP_SEQ(ub) : 0));
	}

	/*
	 * If the pool has an unsupported version we can't open it.
	 */
	if (!SPA_VERSION_IS_SUPPORTED(ub->ub_version)) {
		nvlist_free(label);
		spa_load_failed(spa, "version %llu is not supported",
		    (u_longlong_t)ub->ub_version);
		return (spa_vdev_err(rvd, VDEV_AUX_VERSION_NEWER, ENOTSUP));
	}

	if (ub->ub_version >= SPA_VERSION_FEATURES) {
		nvlist_t *features;

		/*
		 * If we weren't able to find what's necessary for reading the
		 * MOS in the label, return failure.
		 */
		if (label == NULL) {
			spa_load_failed(spa, "label config unavailable");
			return (spa_vdev_err(rvd, VDEV_AUX_CORRUPT_DATA,
			    ENXIO));
		}

		if (nvlist_lookup_nvlist(label, ZPOOL_CONFIG_FEATURES_FOR_READ,
		    &features) != 0) {
			nvlist_free(label);
			spa_load_failed(spa, "invalid label: '%s' missing",
			    ZPOOL_CONFIG_FEATURES_FOR_READ);
			return (spa_vdev_err(rvd, VDEV_AUX_CORRUPT_DATA,
			    ENXIO));
		}

		/*
		 * Update our in-core representation with the definitive values
		 * from the label.
		 */
		nvlist_free(spa->spa_label_features);
		VERIFY(nvlist_dup(features, &spa->spa_label_features, 0) == 0);
	}

	nvlist_free(label);

	/*
	 * Look through entries in the label nvlist's features_for_read. If
	 * there is a feature listed there which we don't understand then we
	 * cannot open a pool.
	 */
	if (ub->ub_version >= SPA_VERSION_FEATURES) {
		nvlist_t *unsup_feat;

		VERIFY(nvlist_alloc(&unsup_feat, NV_UNIQUE_NAME, KM_SLEEP) ==
		    0);

		for (nvpair_t *nvp = nvlist_next_nvpair(spa->spa_label_features,
		    NULL); nvp != NULL;
		    nvp = nvlist_next_nvpair(spa->spa_label_features, nvp)) {
			if (!zfeature_is_supported(nvpair_name(nvp))) {
				VERIFY(nvlist_add_string(unsup_feat,
				    nvpair_name(nvp), "") == 0);
			}
		}

		if (!nvlist_empty(unsup_feat)) {
			VERIFY(nvlist_add_nvlist(spa->spa_load_info,
			    ZPOOL_CONFIG_UNSUP_FEAT, unsup_feat) == 0);
			nvlist_free(unsup_feat);
			spa_load_failed(spa, "some features are unsupported");
			return (spa_vdev_err(rvd, VDEV_AUX_UNSUP_FEAT,
			    ENOTSUP));
		}

		nvlist_free(unsup_feat);
	}

	if (type != SPA_IMPORT_ASSEMBLE && spa->spa_config_splitting) {
		spa_config_enter(spa, SCL_ALL, FTAG, RW_WRITER);
		spa_try_repair(spa, spa->spa_config);
		spa_config_exit(spa, SCL_ALL, FTAG);
		nvlist_free(spa->spa_config_splitting);
		spa->spa_config_splitting = NULL;
	}

	/*
	 * Initialize internal SPA structures.
	 */
	spa_ld_select_uberblock_done(spa, ub);

	return (0);
}