#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
struct TYPE_11__ {scalar_t__ scn_async_destroying; } ;
typedef  TYPE_1__ dsl_scan_t ;
struct TYPE_12__ {int /*<<< orphan*/  dp_free_dir; int /*<<< orphan*/  dp_bptree_obj; int /*<<< orphan*/  dp_spa; TYPE_1__* dp_scan; int /*<<< orphan*/ * dp_meta_objset; } ;
typedef  TYPE_2__ dsl_pool_t ;
struct TYPE_13__ {int /*<<< orphan*/  ds_dir; int /*<<< orphan*/  ds_bp_rwlock; } ;
typedef  TYPE_3__ dsl_dataset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_15__ {int /*<<< orphan*/  ds_prev_snap_txg; int /*<<< orphan*/  ds_bp; int /*<<< orphan*/  ds_unique_bytes; } ;
struct TYPE_14__ {int /*<<< orphan*/  dd_uncompressed_bytes; int /*<<< orphan*/  dd_compressed_bytes; int /*<<< orphan*/  dd_used_bytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ B_TRUE ; 
 int /*<<< orphan*/  DD_USED_HEAD ; 
 int /*<<< orphan*/  DMU_POOL_BPTREE_OBJ ; 
 int /*<<< orphan*/  DMU_POOL_DIRECTORY_OBJECT ; 
 int /*<<< orphan*/  DS_UNIQUE_IS_ACCURATE (TYPE_3__*) ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  RW_READER ; 
 int /*<<< orphan*/  SPA_FEATURE_ASYNC_DESTROY ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bptree_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bptree_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_objset_from_ds (TYPE_3__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dmu_objset_zil (int /*<<< orphan*/ *) ; 
 TYPE_2__* dmu_tx_pool (int /*<<< orphan*/ *) ; 
 TYPE_5__* dsl_dataset_phys (TYPE_3__*) ; 
 int /*<<< orphan*/  dsl_dir_diduse_space (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_4__* dsl_dir_phys (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrw_exit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_feature_incr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_feature_is_active (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zap_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zil_destroy_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dsl_async_dataset_destroy(dsl_dataset_t *ds, dmu_tx_t *tx)
{
	uint64_t used, comp, uncomp;
	objset_t *os;

	VERIFY0(dmu_objset_from_ds(ds, &os));
	dsl_pool_t *dp = dmu_tx_pool(tx);
	objset_t *mos = dp->dp_meta_objset;

	zil_destroy_sync(dmu_objset_zil(os), tx);

	if (!spa_feature_is_active(dp->dp_spa,
	    SPA_FEATURE_ASYNC_DESTROY)) {
		dsl_scan_t *scn = dp->dp_scan;
		spa_feature_incr(dp->dp_spa, SPA_FEATURE_ASYNC_DESTROY,
		    tx);
		dp->dp_bptree_obj = bptree_alloc(mos, tx);
		VERIFY0(zap_add(mos,
		    DMU_POOL_DIRECTORY_OBJECT,
		    DMU_POOL_BPTREE_OBJ, sizeof (uint64_t), 1,
		    &dp->dp_bptree_obj, tx));
		ASSERT(!scn->scn_async_destroying);
		scn->scn_async_destroying = B_TRUE;
	}

	used = dsl_dir_phys(ds->ds_dir)->dd_used_bytes;
	comp = dsl_dir_phys(ds->ds_dir)->dd_compressed_bytes;
	uncomp = dsl_dir_phys(ds->ds_dir)->dd_uncompressed_bytes;

	ASSERT(!DS_UNIQUE_IS_ACCURATE(ds) ||
	    dsl_dataset_phys(ds)->ds_unique_bytes == used);

	rrw_enter(&ds->ds_bp_rwlock, RW_READER, FTAG);
	bptree_add(mos, dp->dp_bptree_obj,
	    &dsl_dataset_phys(ds)->ds_bp,
	    dsl_dataset_phys(ds)->ds_prev_snap_txg,
	    used, comp, uncomp, tx);
	rrw_exit(&ds->ds_bp_rwlock, FTAG);
	dsl_dir_diduse_space(ds->ds_dir, DD_USED_HEAD,
	    -used, -comp, -uncomp, tx);
	dsl_dir_diduse_space(dp->dp_free_dir, DD_USED_HEAD,
	    used, comp, uncomp, tx);
}