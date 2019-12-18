#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  longlong_t ;
struct TYPE_13__ {int /*<<< orphan*/  dp_spa; } ;
typedef  TYPE_1__ dsl_pool_t ;
struct TYPE_14__ {scalar_t__ ddsqra_value; int /*<<< orphan*/  ddsqra_source; int /*<<< orphan*/  ddsqra_name; } ;
typedef  TYPE_2__ dsl_dir_set_qr_arg_t ;
struct TYPE_15__ {TYPE_8__* ds_dir; } ;
typedef  TYPE_3__ dsl_dataset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_17__ {int /*<<< orphan*/  dd_lock; int /*<<< orphan*/  dd_dbuf; } ;
struct TYPE_16__ {scalar_t__ dd_quota; } ;

/* Variables and functions */
 int /*<<< orphan*/  FTAG ; 
 scalar_t__ SPA_VERSION_RECVD_PROPS ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZFS_PROP_QUOTA ; 
 int /*<<< orphan*/  dmu_buf_will_dirty (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* dmu_tx_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dataset_hold (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__**) ; 
 int /*<<< orphan*/  dsl_dataset_rele (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_7__* dsl_dir_phys (TYPE_8__*) ; 
 int /*<<< orphan*/  dsl_prop_get_int_ds (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  dsl_prop_set_sync_impl (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_history_log_internal_ds (TYPE_3__*,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ spa_version (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_prop_to_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dsl_dir_set_quota_sync(void *arg, dmu_tx_t *tx)
{
	dsl_dir_set_qr_arg_t *ddsqra = arg;
	dsl_pool_t *dp = dmu_tx_pool(tx);
	dsl_dataset_t *ds;
	uint64_t newval;

	VERIFY0(dsl_dataset_hold(dp, ddsqra->ddsqra_name, FTAG, &ds));

	if (spa_version(dp->dp_spa) >= SPA_VERSION_RECVD_PROPS) {
		dsl_prop_set_sync_impl(ds, zfs_prop_to_name(ZFS_PROP_QUOTA),
		    ddsqra->ddsqra_source, sizeof (ddsqra->ddsqra_value), 1,
		    &ddsqra->ddsqra_value, tx);

		VERIFY0(dsl_prop_get_int_ds(ds,
		    zfs_prop_to_name(ZFS_PROP_QUOTA), &newval));
	} else {
		newval = ddsqra->ddsqra_value;
		spa_history_log_internal_ds(ds, "set", tx, "%s=%lld",
		    zfs_prop_to_name(ZFS_PROP_QUOTA), (longlong_t)newval);
	}

	dmu_buf_will_dirty(ds->ds_dir->dd_dbuf, tx);
	mutex_enter(&ds->ds_dir->dd_lock);
	dsl_dir_phys(ds->ds_dir)->dd_quota = newval;
	mutex_exit(&ds->ds_dir->dd_lock);
	dsl_dataset_rele(ds, FTAG);
}