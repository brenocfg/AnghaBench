#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_13__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_18__ {int /*<<< orphan*/  tx_open_txg; } ;
struct TYPE_19__ {int /*<<< orphan*/  dp_config_rwlock; TYPE_1__ dp_tx; int /*<<< orphan*/  dp_tmp_userrefs_obj; int /*<<< orphan*/  dp_meta_objset; int /*<<< orphan*/  dp_empty_bpobj; int /*<<< orphan*/  dp_spa; int /*<<< orphan*/  dp_bptree_obj; int /*<<< orphan*/ * dp_leak_dir; int /*<<< orphan*/  dp_obsolete_bpobj; int /*<<< orphan*/  dp_free_bpobj; int /*<<< orphan*/ * dp_free_dir; int /*<<< orphan*/ * dp_origin_snap; int /*<<< orphan*/ * dp_mos_dir; int /*<<< orphan*/  dp_root_dir; int /*<<< orphan*/  dp_root_dir_obj; } ;
typedef  TYPE_2__ dsl_pool_t ;
typedef  int /*<<< orphan*/  dsl_dir_t ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;
struct TYPE_20__ {int /*<<< orphan*/  dd_head_dataset_obj; } ;
struct TYPE_17__ {int /*<<< orphan*/  ds_prev_snap_obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMU_POOL_BPTREE_OBJ ; 
 int /*<<< orphan*/  DMU_POOL_DIRECTORY_OBJECT ; 
 int /*<<< orphan*/  DMU_POOL_EMPTY_BPOBJ ; 
 int /*<<< orphan*/  DMU_POOL_FREE_BPOBJ ; 
 int /*<<< orphan*/  DMU_POOL_OBSOLETE_BPOBJ ; 
 int /*<<< orphan*/  DMU_POOL_ROOT_DATASET ; 
 int /*<<< orphan*/  DMU_POOL_TMP_USERREFS ; 
 int ENOENT ; 
 int /*<<< orphan*/  FREE_DIR_NAME ; 
 TYPE_2__* FTAG ; 
 int /*<<< orphan*/  LEAK_DIR_NAME ; 
 int /*<<< orphan*/  MOS_DIR_NAME ; 
 int /*<<< orphan*/  ORIGIN_DIR_NAME ; 
 int /*<<< orphan*/  RW_WRITER ; 
 int /*<<< orphan*/  SPA_FEATURE_ASYNC_DESTROY ; 
 int /*<<< orphan*/  SPA_FEATURE_EMPTY_BPOBJ ; 
 int /*<<< orphan*/  SPA_FEATURE_OBSOLETE_COUNTS ; 
 scalar_t__ SPA_VERSION_DEADLISTS ; 
 scalar_t__ SPA_VERSION_ORIGIN ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpobj_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dsl_dataset_hold_obj (TYPE_2__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ **) ; 
 TYPE_13__* dsl_dataset_phys (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dataset_rele (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int dsl_dir_hold_obj (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 TYPE_9__* dsl_dir_phys (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dir_rele (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int dsl_pool_open_special_dir (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int dsl_scan_init (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  rrw_exit (int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ spa_feature_is_active (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ spa_version (int /*<<< orphan*/ ) ; 
 int zap_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 

int
dsl_pool_open(dsl_pool_t *dp)
{
	int err;
	dsl_dir_t *dd;
	dsl_dataset_t *ds;
	uint64_t obj;

	rrw_enter(&dp->dp_config_rwlock, RW_WRITER, FTAG);
	err = zap_lookup(dp->dp_meta_objset, DMU_POOL_DIRECTORY_OBJECT,
	    DMU_POOL_ROOT_DATASET, sizeof (uint64_t), 1,
	    &dp->dp_root_dir_obj);
	if (err)
		goto out;

	err = dsl_dir_hold_obj(dp, dp->dp_root_dir_obj,
	    NULL, dp, &dp->dp_root_dir);
	if (err)
		goto out;

	err = dsl_pool_open_special_dir(dp, MOS_DIR_NAME, &dp->dp_mos_dir);
	if (err)
		goto out;

	if (spa_version(dp->dp_spa) >= SPA_VERSION_ORIGIN) {
		err = dsl_pool_open_special_dir(dp, ORIGIN_DIR_NAME, &dd);
		if (err)
			goto out;
		err = dsl_dataset_hold_obj(dp,
		    dsl_dir_phys(dd)->dd_head_dataset_obj, FTAG, &ds);
		if (err == 0) {
			err = dsl_dataset_hold_obj(dp,
			    dsl_dataset_phys(ds)->ds_prev_snap_obj, dp,
			    &dp->dp_origin_snap);
			dsl_dataset_rele(ds, FTAG);
		}
		dsl_dir_rele(dd, dp);
		if (err)
			goto out;
	}

	if (spa_version(dp->dp_spa) >= SPA_VERSION_DEADLISTS) {
		err = dsl_pool_open_special_dir(dp, FREE_DIR_NAME,
		    &dp->dp_free_dir);
		if (err)
			goto out;

		err = zap_lookup(dp->dp_meta_objset, DMU_POOL_DIRECTORY_OBJECT,
		    DMU_POOL_FREE_BPOBJ, sizeof (uint64_t), 1, &obj);
		if (err)
			goto out;
		VERIFY0(bpobj_open(&dp->dp_free_bpobj,
		    dp->dp_meta_objset, obj));
	}

	if (spa_feature_is_active(dp->dp_spa, SPA_FEATURE_OBSOLETE_COUNTS)) {
		err = zap_lookup(dp->dp_meta_objset, DMU_POOL_DIRECTORY_OBJECT,
		    DMU_POOL_OBSOLETE_BPOBJ, sizeof (uint64_t), 1, &obj);
		if (err == 0) {
			VERIFY0(bpobj_open(&dp->dp_obsolete_bpobj,
			    dp->dp_meta_objset, obj));
		} else if (err == ENOENT) {
			/*
			 * We might not have created the remap bpobj yet.
			 */
			err = 0;
		} else {
			goto out;
		}
	}

	/*
	 * Note: errors ignored, because the these special dirs, used for
	 * space accounting, are only created on demand.
	 */
	(void) dsl_pool_open_special_dir(dp, LEAK_DIR_NAME,
	    &dp->dp_leak_dir);

	if (spa_feature_is_active(dp->dp_spa, SPA_FEATURE_ASYNC_DESTROY)) {
		err = zap_lookup(dp->dp_meta_objset, DMU_POOL_DIRECTORY_OBJECT,
		    DMU_POOL_BPTREE_OBJ, sizeof (uint64_t), 1,
		    &dp->dp_bptree_obj);
		if (err != 0)
			goto out;
	}

	if (spa_feature_is_active(dp->dp_spa, SPA_FEATURE_EMPTY_BPOBJ)) {
		err = zap_lookup(dp->dp_meta_objset, DMU_POOL_DIRECTORY_OBJECT,
		    DMU_POOL_EMPTY_BPOBJ, sizeof (uint64_t), 1,
		    &dp->dp_empty_bpobj);
		if (err != 0)
			goto out;
	}

	err = zap_lookup(dp->dp_meta_objset, DMU_POOL_DIRECTORY_OBJECT,
	    DMU_POOL_TMP_USERREFS, sizeof (uint64_t), 1,
	    &dp->dp_tmp_userrefs_obj);
	if (err == ENOENT)
		err = 0;
	if (err)
		goto out;

	err = dsl_scan_init(dp, dp->dp_tx.tx_open_txg);

out:
	rrw_exit(&dp->dp_config_rwlock, FTAG);
	return (err);
}