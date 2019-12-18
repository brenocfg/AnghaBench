#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_10__ {int /*<<< orphan*/  dp_spa; } ;
typedef  TYPE_1__ dsl_pool_t ;
struct TYPE_11__ {scalar_t__ ds_reserved; int /*<<< orphan*/  ds_dir; scalar_t__ ds_is_snapshot; } ;
typedef  TYPE_2__ dsl_dataset_t ;
struct TYPE_12__ {int /*<<< orphan*/  ddsqra_value; int /*<<< orphan*/  ddsqra_source; int /*<<< orphan*/  ddsqra_name; } ;
typedef  TYPE_3__ dsl_dataset_set_qr_arg_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_13__ {scalar_t__ ds_referenced_bytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOSPC ; 
 int /*<<< orphan*/  ENOTSUP ; 
 int /*<<< orphan*/  FTAG ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ SPA_VERSION_REFQUOTA ; 
 int /*<<< orphan*/  ZFS_PROP_REFQUOTA ; 
 TYPE_1__* dmu_tx_pool (int /*<<< orphan*/ *) ; 
 int dsl_dataset_hold (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__**) ; 
 TYPE_5__* dsl_dataset_phys (TYPE_2__*) ; 
 int /*<<< orphan*/  dsl_dataset_rele (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int dsl_prop_predict (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ spa_version (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_prop_to_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dsl_dataset_set_refquota_check(void *arg, dmu_tx_t *tx)
{
	dsl_dataset_set_qr_arg_t *ddsqra = arg;
	dsl_pool_t *dp = dmu_tx_pool(tx);
	dsl_dataset_t *ds;
	int error;
	uint64_t newval;

	if (spa_version(dp->dp_spa) < SPA_VERSION_REFQUOTA)
		return (SET_ERROR(ENOTSUP));

	error = dsl_dataset_hold(dp, ddsqra->ddsqra_name, FTAG, &ds);
	if (error != 0)
		return (error);

	if (ds->ds_is_snapshot) {
		dsl_dataset_rele(ds, FTAG);
		return (SET_ERROR(EINVAL));
	}

	error = dsl_prop_predict(ds->ds_dir,
	    zfs_prop_to_name(ZFS_PROP_REFQUOTA),
	    ddsqra->ddsqra_source, ddsqra->ddsqra_value, &newval);
	if (error != 0) {
		dsl_dataset_rele(ds, FTAG);
		return (error);
	}

	if (newval == 0) {
		dsl_dataset_rele(ds, FTAG);
		return (0);
	}

	if (newval < dsl_dataset_phys(ds)->ds_referenced_bytes ||
	    newval < ds->ds_reserved) {
		dsl_dataset_rele(ds, FTAG);
		return (SET_ERROR(ENOSPC));
	}

	dsl_dataset_rele(ds, FTAG);
	return (0);
}