#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_40__   TYPE_6__ ;
typedef  struct TYPE_39__   TYPE_5__ ;
typedef  struct TYPE_38__   TYPE_4__ ;
typedef  struct TYPE_37__   TYPE_3__ ;
typedef  struct TYPE_36__   TYPE_2__ ;
typedef  struct TYPE_35__   TYPE_1__ ;
typedef  struct TYPE_34__   TYPE_15__ ;
typedef  struct TYPE_33__   TYPE_10__ ;

/* Type definitions */
typedef  void* uint64_t ;
typedef  size_t spa_feature_t ;
typedef  int /*<<< orphan*/  objset_t ;
struct TYPE_35__ {int /*<<< orphan*/  dp_spa; TYPE_3__* dp_origin_snap; int /*<<< orphan*/ * dp_meta_objset; } ;
typedef  TYPE_1__ dsl_pool_t ;
struct TYPE_36__ {TYPE_6__* dd_dbuf; int /*<<< orphan*/  dd_object; TYPE_1__* dd_pool; } ;
typedef  TYPE_2__ dsl_dir_t ;
struct TYPE_37__ {TYPE_2__* ds_dir; int /*<<< orphan*/  ds_object; int /*<<< orphan*/  ds_deadlist; TYPE_6__* ds_dbuf; int /*<<< orphan*/ * ds_feature; int /*<<< orphan*/  ds_bp_rwlock; } ;
typedef  TYPE_3__ dsl_dataset_t ;
struct TYPE_38__ {int ds_flags; int ds_creation_txg; int /*<<< orphan*/  ds_prev_snap_obj; int /*<<< orphan*/  ds_prev_snap_txg; int /*<<< orphan*/  ds_deadlist_obj; int /*<<< orphan*/  ds_bp; int /*<<< orphan*/  ds_uncompressed_bytes; int /*<<< orphan*/  ds_compressed_bytes; int /*<<< orphan*/  ds_referenced_bytes; int /*<<< orphan*/  ds_creation_time; int /*<<< orphan*/  ds_snapnames_zapobj; int /*<<< orphan*/  ds_guid; int /*<<< orphan*/  ds_fsid_guid; int /*<<< orphan*/  ds_dir_obj; } ;
typedef  TYPE_4__ dsl_dataset_phys_t ;
typedef  int /*<<< orphan*/  dsl_crypto_params_t ;
struct TYPE_39__ {int tx_txg; } ;
typedef  TYPE_5__ dmu_tx_t ;
struct TYPE_40__ {TYPE_4__* db_data; } ;
typedef  TYPE_6__ dmu_buf_t ;
struct TYPE_34__ {scalar_t__ ds_num_children; int ds_flags; scalar_t__ ds_next_clones_obj; int /*<<< orphan*/  ds_bp; int /*<<< orphan*/  ds_uncompressed_bytes; int /*<<< orphan*/  ds_compressed_bytes; int /*<<< orphan*/  ds_referenced_bytes; int /*<<< orphan*/  ds_creation_txg; } ;
struct TYPE_33__ {scalar_t__ dd_head_dataset_obj; scalar_t__ dd_clones; int /*<<< orphan*/  dd_origin_obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  DMU_OT_DSL_CLONES ; 
 int /*<<< orphan*/  DMU_OT_DSL_DATASET ; 
 int /*<<< orphan*/  DMU_OT_DSL_DS_SNAP_MAP ; 
 int /*<<< orphan*/  DMU_OT_NEXT_CLONES ; 
 int /*<<< orphan*/  DMU_OT_NONE ; 
 int DS_FLAG_CI_DATASET ; 
 int DS_FLAG_INCONSISTENT ; 
 int DS_FLAG_UNIQUE_ACCURATE ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  RW_READER ; 
 size_t SPA_FEATURES ; 
 scalar_t__ SPA_VERSION_DIR_CLONES ; 
 scalar_t__ SPA_VERSION_NEXT_CLONES ; 
 scalar_t__ SPA_VERSION_UNIQUE_ACCURATE ; 
 int TXG_INITIAL ; 
 int /*<<< orphan*/  U8_TEXTPREP_TOUPPER ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (TYPE_4__*,int) ; 
 int /*<<< orphan*/  dmu_bonus_hold (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,TYPE_6__**) ; 
 int /*<<< orphan*/  dmu_buf_rele (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_buf_will_dirty (TYPE_6__*,TYPE_5__*) ; 
 void* dmu_object_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_5__*) ; 
 int dmu_tx_is_syncing (TYPE_5__*) ; 
 int /*<<< orphan*/  dsl_dataset_activate_feature (void*,size_t,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  dsl_dataset_create_crypt_sync (void*,TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  dsl_dataset_hold_obj (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,TYPE_3__**) ; 
 TYPE_15__* dsl_dataset_phys (TYPE_3__*) ; 
 int /*<<< orphan*/  dsl_dataset_rele (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_deadlist_alloc (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  dsl_deadlist_clone (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 
 TYPE_10__* dsl_dir_phys (TYPE_2__*) ; 
 int /*<<< orphan*/  gethrestime_sec () ; 
 int /*<<< orphan*/  random_get_pseudo_bytes (void*,int) ; 
 int /*<<< orphan*/  rrw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrw_exit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ spa_version (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unique_create () ; 
 int /*<<< orphan*/  zap_add_int (int /*<<< orphan*/ *,scalar_t__,void*,TYPE_5__*) ; 
 void* zap_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  zap_create_norm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 
 scalar_t__ zfeature_active (size_t,int /*<<< orphan*/ ) ; 

uint64_t
dsl_dataset_create_sync_dd(dsl_dir_t *dd, dsl_dataset_t *origin,
    dsl_crypto_params_t *dcp, uint64_t flags, dmu_tx_t *tx)
{
	dsl_pool_t *dp = dd->dd_pool;
	dmu_buf_t *dbuf;
	dsl_dataset_phys_t *dsphys;
	uint64_t dsobj;
	objset_t *mos = dp->dp_meta_objset;

	if (origin == NULL)
		origin = dp->dp_origin_snap;

	ASSERT(origin == NULL || origin->ds_dir->dd_pool == dp);
	ASSERT(origin == NULL || dsl_dataset_phys(origin)->ds_num_children > 0);
	ASSERT(dmu_tx_is_syncing(tx));
	ASSERT(dsl_dir_phys(dd)->dd_head_dataset_obj == 0);

	dsobj = dmu_object_alloc(mos, DMU_OT_DSL_DATASET, 0,
	    DMU_OT_DSL_DATASET, sizeof (dsl_dataset_phys_t), tx);
	VERIFY0(dmu_bonus_hold(mos, dsobj, FTAG, &dbuf));
	dmu_buf_will_dirty(dbuf, tx);
	dsphys = dbuf->db_data;
	bzero(dsphys, sizeof (dsl_dataset_phys_t));
	dsphys->ds_dir_obj = dd->dd_object;
	dsphys->ds_flags = flags;
	dsphys->ds_fsid_guid = unique_create();
	(void) random_get_pseudo_bytes((void*)&dsphys->ds_guid,
	    sizeof (dsphys->ds_guid));
	dsphys->ds_snapnames_zapobj =
	    zap_create_norm(mos, U8_TEXTPREP_TOUPPER, DMU_OT_DSL_DS_SNAP_MAP,
	    DMU_OT_NONE, 0, tx);
	dsphys->ds_creation_time = gethrestime_sec();
	dsphys->ds_creation_txg = tx->tx_txg == TXG_INITIAL ? 1 : tx->tx_txg;

	if (origin == NULL) {
		dsphys->ds_deadlist_obj = dsl_deadlist_alloc(mos, tx);
	} else {
		dsl_dataset_t *ohds; /* head of the origin snapshot */

		dsphys->ds_prev_snap_obj = origin->ds_object;
		dsphys->ds_prev_snap_txg =
		    dsl_dataset_phys(origin)->ds_creation_txg;
		dsphys->ds_referenced_bytes =
		    dsl_dataset_phys(origin)->ds_referenced_bytes;
		dsphys->ds_compressed_bytes =
		    dsl_dataset_phys(origin)->ds_compressed_bytes;
		dsphys->ds_uncompressed_bytes =
		    dsl_dataset_phys(origin)->ds_uncompressed_bytes;
		rrw_enter(&origin->ds_bp_rwlock, RW_READER, FTAG);
		dsphys->ds_bp = dsl_dataset_phys(origin)->ds_bp;
		rrw_exit(&origin->ds_bp_rwlock, FTAG);

		/*
		 * Inherit flags that describe the dataset's contents
		 * (INCONSISTENT) or properties (Case Insensitive).
		 */
		dsphys->ds_flags |= dsl_dataset_phys(origin)->ds_flags &
		    (DS_FLAG_INCONSISTENT | DS_FLAG_CI_DATASET);

		for (spa_feature_t f = 0; f < SPA_FEATURES; f++) {
			if (zfeature_active(f, origin->ds_feature[f])) {
				dsl_dataset_activate_feature(dsobj, f,
				    origin->ds_feature[f], tx);
			}
		}

		dmu_buf_will_dirty(origin->ds_dbuf, tx);
		dsl_dataset_phys(origin)->ds_num_children++;

		VERIFY0(dsl_dataset_hold_obj(dp,
		    dsl_dir_phys(origin->ds_dir)->dd_head_dataset_obj,
		    FTAG, &ohds));
		dsphys->ds_deadlist_obj = dsl_deadlist_clone(&ohds->ds_deadlist,
		    dsphys->ds_prev_snap_txg, dsphys->ds_prev_snap_obj, tx);
		dsl_dataset_rele(ohds, FTAG);

		if (spa_version(dp->dp_spa) >= SPA_VERSION_NEXT_CLONES) {
			if (dsl_dataset_phys(origin)->ds_next_clones_obj == 0) {
				dsl_dataset_phys(origin)->ds_next_clones_obj =
				    zap_create(mos,
				    DMU_OT_NEXT_CLONES, DMU_OT_NONE, 0, tx);
			}
			VERIFY0(zap_add_int(mos,
			    dsl_dataset_phys(origin)->ds_next_clones_obj,
			    dsobj, tx));
		}

		dmu_buf_will_dirty(dd->dd_dbuf, tx);
		dsl_dir_phys(dd)->dd_origin_obj = origin->ds_object;
		if (spa_version(dp->dp_spa) >= SPA_VERSION_DIR_CLONES) {
			if (dsl_dir_phys(origin->ds_dir)->dd_clones == 0) {
				dmu_buf_will_dirty(origin->ds_dir->dd_dbuf, tx);
				dsl_dir_phys(origin->ds_dir)->dd_clones =
				    zap_create(mos,
				    DMU_OT_DSL_CLONES, DMU_OT_NONE, 0, tx);
			}
			VERIFY0(zap_add_int(mos,
			    dsl_dir_phys(origin->ds_dir)->dd_clones,
			    dsobj, tx));
		}
	}

	/* handle encryption */
	dsl_dataset_create_crypt_sync(dsobj, dd, origin, dcp, tx);

	if (spa_version(dp->dp_spa) >= SPA_VERSION_UNIQUE_ACCURATE)
		dsphys->ds_flags |= DS_FLAG_UNIQUE_ACCURATE;

	dmu_buf_rele(dbuf, FTAG);

	dmu_buf_will_dirty(dd->dd_dbuf, tx);
	dsl_dir_phys(dd)->dd_head_dataset_obj = dsobj;

	return (dsobj);
}