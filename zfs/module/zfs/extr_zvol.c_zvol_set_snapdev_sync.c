#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * zsda_tx; int /*<<< orphan*/  zsda_value; int /*<<< orphan*/  zsda_source; int /*<<< orphan*/  zsda_name; } ;
typedef  TYPE_1__ zvol_set_prop_int_arg_t ;
typedef  int /*<<< orphan*/  dsl_pool_t ;
struct TYPE_7__ {int /*<<< orphan*/  dd_object; } ;
typedef  TYPE_2__ dsl_dir_t ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  DS_FIND_CHILDREN ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZFS_PROP_SNAPDEV ; 
 int /*<<< orphan*/  dmu_objset_find_dp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dmu_tx_pool (int /*<<< orphan*/ *) ; 
 int dsl_dataset_hold (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dsl_dataset_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_dir_hold (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dir_rele (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_prop_set_sync_impl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_prop_to_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zvol_set_snapdev_sync_cb ; 

__attribute__((used)) static void
zvol_set_snapdev_sync(void *arg, dmu_tx_t *tx)
{
	zvol_set_prop_int_arg_t *zsda = arg;
	dsl_pool_t *dp = dmu_tx_pool(tx);
	dsl_dir_t *dd;
	dsl_dataset_t *ds;
	int error;

	VERIFY0(dsl_dir_hold(dp, zsda->zsda_name, FTAG, &dd, NULL));
	zsda->zsda_tx = tx;

	error = dsl_dataset_hold(dp, zsda->zsda_name, FTAG, &ds);
	if (error == 0) {
		dsl_prop_set_sync_impl(ds, zfs_prop_to_name(ZFS_PROP_SNAPDEV),
		    zsda->zsda_source, sizeof (zsda->zsda_value), 1,
		    &zsda->zsda_value, zsda->zsda_tx);
		dsl_dataset_rele(ds, FTAG);
	}
	dmu_objset_find_dp(dp, dd->dd_object, zvol_set_snapdev_sync_cb,
	    zsda, DS_FIND_CHILDREN);

	dsl_dir_rele(dd, FTAG);
}