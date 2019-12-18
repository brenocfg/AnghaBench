#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zprop_source_t ;
typedef  int /*<<< orphan*/  value ;
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_9__ {TYPE_4__* ds_dir; int /*<<< orphan*/  ds_lock; scalar_t__ ds_reserved; int /*<<< orphan*/  ds_dbuf; } ;
typedef  TYPE_1__ dsl_dataset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_11__ {scalar_t__ ds_unique_bytes; } ;
struct TYPE_10__ {int /*<<< orphan*/  dd_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DD_USED_REFRSRV ; 
 int /*<<< orphan*/  DS_UNIQUE_IS_ACCURATE (TYPE_1__*) ; 
 scalar_t__ MAX (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZFS_PROP_REFRESERVATION ; 
 int /*<<< orphan*/  dmu_buf_will_dirty (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_6__* dsl_dataset_phys (TYPE_1__*) ; 
 int /*<<< orphan*/  dsl_dir_diduse_space (TYPE_4__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_prop_get_int_ds (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  dsl_prop_set_sync_impl (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_prop_to_name (int /*<<< orphan*/ ) ; 

void
dsl_dataset_set_refreservation_sync_impl(dsl_dataset_t *ds,
    zprop_source_t source, uint64_t value, dmu_tx_t *tx)
{
	uint64_t newval;
	uint64_t unique;
	int64_t delta;

	dsl_prop_set_sync_impl(ds, zfs_prop_to_name(ZFS_PROP_REFRESERVATION),
	    source, sizeof (value), 1, &value, tx);

	VERIFY0(dsl_prop_get_int_ds(ds,
	    zfs_prop_to_name(ZFS_PROP_REFRESERVATION), &newval));

	dmu_buf_will_dirty(ds->ds_dbuf, tx);
	mutex_enter(&ds->ds_dir->dd_lock);
	mutex_enter(&ds->ds_lock);
	ASSERT(DS_UNIQUE_IS_ACCURATE(ds));
	unique = dsl_dataset_phys(ds)->ds_unique_bytes;
	delta = MAX(0, (int64_t)(newval - unique)) -
	    MAX(0, (int64_t)(ds->ds_reserved - unique));
	ds->ds_reserved = newval;
	mutex_exit(&ds->ds_lock);

	dsl_dir_diduse_space(ds->ds_dir, DD_USED_REFRSRV, delta, 0, 0, tx);
	mutex_exit(&ds->ds_dir->dd_lock);
}