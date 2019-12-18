#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_6__ {int /*<<< orphan*/  dp_root_dir_obj; int /*<<< orphan*/  dp_meta_objset; int /*<<< orphan*/  dp_free_bpobj; int /*<<< orphan*/  dp_free_dir; int /*<<< orphan*/  dp_root_dir; } ;
typedef  TYPE_1__ dsl_pool_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
typedef  int /*<<< orphan*/  bpobj_phys_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMU_OT_BPOBJ ; 
 int /*<<< orphan*/  DMU_OT_BPOBJ_HDR ; 
 int /*<<< orphan*/  DMU_POOL_DIRECTORY_OBJECT ; 
 int /*<<< orphan*/  DMU_POOL_FREE_BPOBJ ; 
 int DS_FIND_CHILDREN ; 
 int DS_FIND_SERIALIZE ; 
 int /*<<< orphan*/  FREE_DIR_NAME ; 
 int /*<<< orphan*/  SPA_OLD_MAXBLOCKSIZE ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpobj_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_object_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_objset_find_dp (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dmu_tx_is_syncing (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dir_create_sync (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_pool_open_special_dir (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  upgrade_dir_clones_cb ; 
 int /*<<< orphan*/  zap_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
dsl_pool_upgrade_dir_clones(dsl_pool_t *dp, dmu_tx_t *tx)
{
	uint64_t obj;

	ASSERT(dmu_tx_is_syncing(tx));

	(void) dsl_dir_create_sync(dp, dp->dp_root_dir, FREE_DIR_NAME, tx);
	VERIFY0(dsl_pool_open_special_dir(dp,
	    FREE_DIR_NAME, &dp->dp_free_dir));

	/*
	 * We can't use bpobj_alloc(), because spa_version() still
	 * returns the old version, and we need a new-version bpobj with
	 * subobj support.  So call dmu_object_alloc() directly.
	 */
	obj = dmu_object_alloc(dp->dp_meta_objset, DMU_OT_BPOBJ,
	    SPA_OLD_MAXBLOCKSIZE, DMU_OT_BPOBJ_HDR, sizeof (bpobj_phys_t), tx);
	VERIFY0(zap_add(dp->dp_meta_objset, DMU_POOL_DIRECTORY_OBJECT,
	    DMU_POOL_FREE_BPOBJ, sizeof (uint64_t), 1, &obj, tx));
	VERIFY0(bpobj_open(&dp->dp_free_bpobj, dp->dp_meta_objset, obj));

	VERIFY0(dmu_objset_find_dp(dp, dp->dp_root_dir_obj,
	    upgrade_dir_clones_cb, tx, DS_FIND_CHILDREN | DS_FIND_SERIALIZE));
}