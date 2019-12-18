#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_8__ {int /*<<< orphan*/ * dp_origin_snap; int /*<<< orphan*/  dp_root_dir; int /*<<< orphan*/  dp_config_rwlock; } ;
typedef  TYPE_1__ dsl_pool_t ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_9__ {int /*<<< orphan*/  ds_prev_snap_obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 TYPE_1__* FTAG ; 
 int /*<<< orphan*/  ORIGIN_DIR_NAME ; 
 int /*<<< orphan*/  RW_WRITER ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_tx_is_syncing (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dataset_create_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dataset_hold_obj (TYPE_1__*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ **) ; 
 TYPE_4__* dsl_dataset_phys (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dataset_rele (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  dsl_dataset_snapshot_sync_impl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kcred ; 
 int /*<<< orphan*/  rrw_held (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
dsl_pool_create_origin(dsl_pool_t *dp, dmu_tx_t *tx)
{
	uint64_t dsobj;
	dsl_dataset_t *ds;

	ASSERT(dmu_tx_is_syncing(tx));
	ASSERT(dp->dp_origin_snap == NULL);
	ASSERT(rrw_held(&dp->dp_config_rwlock, RW_WRITER));

	/* create the origin dir, ds, & snap-ds */
	dsobj = dsl_dataset_create_sync(dp->dp_root_dir, ORIGIN_DIR_NAME,
	    NULL, 0, kcred, NULL, tx);
	VERIFY0(dsl_dataset_hold_obj(dp, dsobj, FTAG, &ds));
	dsl_dataset_snapshot_sync_impl(ds, ORIGIN_DIR_NAME, tx);
	VERIFY0(dsl_dataset_hold_obj(dp, dsl_dataset_phys(ds)->ds_prev_snap_obj,
	    dp, &dp->dp_origin_snap));
	dsl_dataset_rele(ds, FTAG);
}