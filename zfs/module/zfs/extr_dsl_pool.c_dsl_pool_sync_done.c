#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  zl_os; } ;
typedef  TYPE_1__ zilog_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_11__ {int /*<<< orphan*/  dp_meta_objset; int /*<<< orphan*/  dp_dirty_zilogs; } ;
typedef  TYPE_2__ dsl_pool_t ;
struct TYPE_12__ {int /*<<< orphan*/  ds_dbuf; } ;
typedef  TYPE_3__ dsl_dataset_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  dmu_buf_rele (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_3__* dmu_objset_ds (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_objset_is_dirty (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* txg_list_head (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txg_list_remove_this (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zil_clean (TYPE_1__*,int /*<<< orphan*/ ) ; 

void
dsl_pool_sync_done(dsl_pool_t *dp, uint64_t txg)
{
	zilog_t *zilog;

	while ((zilog = txg_list_head(&dp->dp_dirty_zilogs, txg))) {
		dsl_dataset_t *ds = dmu_objset_ds(zilog->zl_os);
		/*
		 * We don't remove the zilog from the dp_dirty_zilogs
		 * list until after we've cleaned it. This ensures that
		 * callers of zilog_is_dirty() receive an accurate
		 * answer when they are racing with the spa sync thread.
		 */
		zil_clean(zilog, txg);
		(void) txg_list_remove_this(&dp->dp_dirty_zilogs, zilog, txg);
		ASSERT(!dmu_objset_is_dirty(zilog->zl_os, txg));
		dmu_buf_rele(ds->ds_dbuf, zilog);
	}
	ASSERT(!dmu_objset_is_dirty(dp->dp_meta_objset, txg));
}