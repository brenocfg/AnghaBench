#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_12__ {scalar_t__ ds_trysnap_txg; int /*<<< orphan*/  ds_dir; } ;
typedef  TYPE_1__ dsl_dataset_t ;
struct TYPE_13__ {scalar_t__ tx_txg; } ;
typedef  TYPE_2__ dmu_tx_t ;
typedef  int /*<<< orphan*/  cred_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_14__ {scalar_t__ ds_prev_snap_txg; } ;

/* Variables and functions */
 scalar_t__ DS_IS_INCONSISTENT (TYPE_1__*) ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  EEXIST ; 
 int ENOENT ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZFS_PROP_SNAPSHOT_LIMIT ; 
 int /*<<< orphan*/  dmu_tx_is_syncing (TYPE_2__*) ; 
 TYPE_8__* dsl_dataset_phys (TYPE_1__*) ; 
 int dsl_dataset_snap_lookup (TYPE_1__*,char const*,scalar_t__*) ; 
 int dsl_dataset_snapshot_reserve_space (TYPE_1__*,TYPE_2__*) ; 
 int dsl_fs_ss_limit_check (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
dsl_dataset_snapshot_check_impl(dsl_dataset_t *ds, const char *snapname,
    dmu_tx_t *tx, boolean_t recv, uint64_t cnt, cred_t *cr)
{
	int error;
	uint64_t value;

	ds->ds_trysnap_txg = tx->tx_txg;

	if (!dmu_tx_is_syncing(tx))
		return (0);

	/*
	 * We don't allow multiple snapshots of the same txg.  If there
	 * is already one, try again.
	 */
	if (dsl_dataset_phys(ds)->ds_prev_snap_txg >= tx->tx_txg)
		return (SET_ERROR(EAGAIN));

	/*
	 * Check for conflicting snapshot name.
	 */
	error = dsl_dataset_snap_lookup(ds, snapname, &value);
	if (error == 0)
		return (SET_ERROR(EEXIST));
	if (error != ENOENT)
		return (error);

	/*
	 * We don't allow taking snapshots of inconsistent datasets, such as
	 * those into which we are currently receiving.  However, if we are
	 * creating this snapshot as part of a receive, this check will be
	 * executed atomically with respect to the completion of the receive
	 * itself but prior to the clearing of DS_FLAG_INCONSISTENT; in this
	 * case we ignore this, knowing it will be fixed up for us shortly in
	 * dmu_recv_end_sync().
	 */
	if (!recv && DS_IS_INCONSISTENT(ds))
		return (SET_ERROR(EBUSY));

	/*
	 * Skip the check for temporary snapshots or if we have already checked
	 * the counts in dsl_dataset_snapshot_check. This means we really only
	 * check the count here when we're receiving a stream.
	 */
	if (cnt != 0 && cr != NULL) {
		error = dsl_fs_ss_limit_check(ds->ds_dir, cnt,
		    ZFS_PROP_SNAPSHOT_LIMIT, NULL, cr);
		if (error != 0)
			return (error);
	}

	error = dsl_dataset_snapshot_reserve_space(ds, tx);
	if (error != 0)
		return (error);

	return (0);
}