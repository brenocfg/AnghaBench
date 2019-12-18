#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zio_t ;
typedef  size_t spa_feature_t ;
struct TYPE_14__ {scalar_t__* ds_resume_bytes; scalar_t__* ds_resume_object; scalar_t__* ds_resume_offset; int /*<<< orphan*/ * ds_feature_activation; int /*<<< orphan*/ * ds_feature; int /*<<< orphan*/  ds_object; int /*<<< orphan*/ * ds_objset; int /*<<< orphan*/  ds_fsid_guid; int /*<<< orphan*/  ds_dbuf; } ;
typedef  TYPE_2__ dsl_dataset_t ;
struct TYPE_15__ {size_t tx_txg; TYPE_1__* tx_pool; } ;
typedef  TYPE_3__ dmu_tx_t ;
struct TYPE_16__ {scalar_t__ ds_next_snap_obj; int /*<<< orphan*/  ds_fsid_guid; } ;
struct TYPE_13__ {int /*<<< orphan*/  dp_meta_objset; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  DS_FIELD_RESUME_BYTES ; 
 int /*<<< orphan*/  DS_FIELD_RESUME_OBJECT ; 
 int /*<<< orphan*/  DS_FIELD_RESUME_OFFSET ; 
 size_t SPA_FEATURES ; 
 size_t TXG_MASK ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_buf_will_dirty (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  dmu_objset_sync (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int dmu_tx_is_syncing (TYPE_3__*) ; 
 int /*<<< orphan*/  dsl_dataset_activate_feature (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,TYPE_3__*) ; 
 TYPE_7__* dsl_dataset_phys (TYPE_2__*) ; 
 int /*<<< orphan*/  zap_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,scalar_t__*,TYPE_3__*) ; 
 scalar_t__ zfeature_active (size_t,int /*<<< orphan*/ ) ; 

void
dsl_dataset_sync(dsl_dataset_t *ds, zio_t *zio, dmu_tx_t *tx)
{
	ASSERT(dmu_tx_is_syncing(tx));
	ASSERT(ds->ds_objset != NULL);
	ASSERT(dsl_dataset_phys(ds)->ds_next_snap_obj == 0);

	/*
	 * in case we had to change ds_fsid_guid when we opened it,
	 * sync it out now.
	 */
	dmu_buf_will_dirty(ds->ds_dbuf, tx);
	dsl_dataset_phys(ds)->ds_fsid_guid = ds->ds_fsid_guid;

	if (ds->ds_resume_bytes[tx->tx_txg & TXG_MASK] != 0) {
		VERIFY0(zap_update(tx->tx_pool->dp_meta_objset,
		    ds->ds_object, DS_FIELD_RESUME_OBJECT, 8, 1,
		    &ds->ds_resume_object[tx->tx_txg & TXG_MASK], tx));
		VERIFY0(zap_update(tx->tx_pool->dp_meta_objset,
		    ds->ds_object, DS_FIELD_RESUME_OFFSET, 8, 1,
		    &ds->ds_resume_offset[tx->tx_txg & TXG_MASK], tx));
		VERIFY0(zap_update(tx->tx_pool->dp_meta_objset,
		    ds->ds_object, DS_FIELD_RESUME_BYTES, 8, 1,
		    &ds->ds_resume_bytes[tx->tx_txg & TXG_MASK], tx));
		ds->ds_resume_object[tx->tx_txg & TXG_MASK] = 0;
		ds->ds_resume_offset[tx->tx_txg & TXG_MASK] = 0;
		ds->ds_resume_bytes[tx->tx_txg & TXG_MASK] = 0;
	}

	dmu_objset_sync(ds->ds_objset, zio, tx);

	for (spa_feature_t f = 0; f < SPA_FEATURES; f++) {
		if (zfeature_active(f, ds->ds_feature_activation[f])) {
			if (zfeature_active(f, ds->ds_feature[f]))
				continue;
			dsl_dataset_activate_feature(ds->ds_object, f,
			    ds->ds_feature_activation[f], tx);
			ds->ds_feature[f] = ds->ds_feature_activation[f];
		}
	}
}