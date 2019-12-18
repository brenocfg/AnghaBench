#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  dsl_pool_t ;
struct TYPE_15__ {scalar_t__ ds_dir; scalar_t__ ds_object; scalar_t__ ds_quota; int /*<<< orphan*/  ds_reserved; struct TYPE_15__* ds_prev; scalar_t__ ds_is_snapshot; } ;
typedef  TYPE_1__ dsl_dataset_t ;
struct TYPE_16__ {int /*<<< orphan*/  ddra_owner; int /*<<< orphan*/ * ddra_tosnap; int /*<<< orphan*/ * ddra_fsname; } ;
typedef  TYPE_2__ dsl_dataset_rollback_arg_t ;
struct TYPE_17__ {scalar_t__ tx_txg; } ;
typedef  TYPE_3__ dmu_tx_t ;
struct TYPE_19__ {scalar_t__ ds_prev_snap_txg; scalar_t__ ds_referenced_bytes; int /*<<< orphan*/  ds_unique_bytes; } ;
struct TYPE_18__ {scalar_t__ dd_origin_obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (scalar_t__) ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  EDQUOT ; 
 int /*<<< orphan*/  EEXIST ; 
 int /*<<< orphan*/  EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  ENOSPC ; 
 int /*<<< orphan*/  ESRCH ; 
 int EXDEV ; 
 int /*<<< orphan*/  FTAG ; 
 scalar_t__ MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ TXG_INITIAL ; 
 scalar_t__ dmu_tx_is_syncing (TYPE_3__*) ; 
 int /*<<< orphan*/ * dmu_tx_pool (TYPE_3__*) ; 
 scalar_t__ dsl_bookmark_latest_txg (TYPE_1__*) ; 
 int dsl_dataset_handoff_check (TYPE_1__*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int dsl_dataset_hold (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__**) ; 
 TYPE_7__* dsl_dataset_phys (TYPE_1__*) ; 
 int /*<<< orphan*/  dsl_dataset_rele (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ dsl_dir_is_clone (scalar_t__) ; 
 TYPE_4__* dsl_dir_phys (scalar_t__) ; 
 scalar_t__ dsl_dir_space_available (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
dsl_dataset_rollback_check(void *arg, dmu_tx_t *tx)
{
	dsl_dataset_rollback_arg_t *ddra = arg;
	dsl_pool_t *dp = dmu_tx_pool(tx);
	dsl_dataset_t *ds;
	int64_t unused_refres_delta;
	int error;

	error = dsl_dataset_hold(dp, ddra->ddra_fsname, FTAG, &ds);
	if (error != 0)
		return (error);

	/* must not be a snapshot */
	if (ds->ds_is_snapshot) {
		dsl_dataset_rele(ds, FTAG);
		return (SET_ERROR(EINVAL));
	}

	/* must have a most recent snapshot */
	if (dsl_dataset_phys(ds)->ds_prev_snap_txg < TXG_INITIAL) {
		dsl_dataset_rele(ds, FTAG);
		return (SET_ERROR(ESRCH));
	}

	/*
	 * No rollback to a snapshot created in the current txg, because
	 * the rollback may dirty the dataset and create blocks that are
	 * not reachable from the rootbp while having a birth txg that
	 * falls into the snapshot's range.
	 */
	if (dmu_tx_is_syncing(tx) &&
	    dsl_dataset_phys(ds)->ds_prev_snap_txg >= tx->tx_txg) {
		dsl_dataset_rele(ds, FTAG);
		return (SET_ERROR(EAGAIN));
	}

	/*
	 * If the expected target snapshot is specified, then check that
	 * the latest snapshot is it.
	 */
	if (ddra->ddra_tosnap != NULL) {
		dsl_dataset_t *snapds;

		/* Check if the target snapshot exists at all. */
		error = dsl_dataset_hold(dp, ddra->ddra_tosnap, FTAG, &snapds);
		if (error != 0) {
			/*
			 * ESRCH is used to signal that the target snapshot does
			 * not exist, while ENOENT is used to report that
			 * the rolled back dataset does not exist.
			 * ESRCH is also used to cover other cases where the
			 * target snapshot is not related to the dataset being
			 * rolled back such as being in a different pool.
			 */
			if (error == ENOENT || error == EXDEV)
				error = SET_ERROR(ESRCH);
			dsl_dataset_rele(ds, FTAG);
			return (error);
		}
		ASSERT(snapds->ds_is_snapshot);

		/* Check if the snapshot is the latest snapshot indeed. */
		if (snapds != ds->ds_prev) {
			/*
			 * Distinguish between the case where the only problem
			 * is intervening snapshots (EEXIST) vs the snapshot
			 * not being a valid target for rollback (ESRCH).
			 */
			if (snapds->ds_dir == ds->ds_dir ||
			    (dsl_dir_is_clone(ds->ds_dir) &&
			    dsl_dir_phys(ds->ds_dir)->dd_origin_obj ==
			    snapds->ds_object)) {
				error = SET_ERROR(EEXIST);
			} else {
				error = SET_ERROR(ESRCH);
			}
			dsl_dataset_rele(snapds, FTAG);
			dsl_dataset_rele(ds, FTAG);
			return (error);
		}
		dsl_dataset_rele(snapds, FTAG);
	}

	/* must not have any bookmarks after the most recent snapshot */
	if (dsl_bookmark_latest_txg(ds) >
	    dsl_dataset_phys(ds)->ds_prev_snap_txg) {
		dsl_dataset_rele(ds, FTAG);
		return (SET_ERROR(EEXIST));
	}

	error = dsl_dataset_handoff_check(ds, ddra->ddra_owner, tx);
	if (error != 0) {
		dsl_dataset_rele(ds, FTAG);
		return (error);
	}

	/*
	 * Check if the snap we are rolling back to uses more than
	 * the refquota.
	 */
	if (ds->ds_quota != 0 &&
	    dsl_dataset_phys(ds->ds_prev)->ds_referenced_bytes > ds->ds_quota) {
		dsl_dataset_rele(ds, FTAG);
		return (SET_ERROR(EDQUOT));
	}

	/*
	 * When we do the clone swap, we will temporarily use more space
	 * due to the refreservation (the head will no longer have any
	 * unique space, so the entire amount of the refreservation will need
	 * to be free).  We will immediately destroy the clone, freeing
	 * this space, but the freeing happens over many txg's.
	 */
	unused_refres_delta = (int64_t)MIN(ds->ds_reserved,
	    dsl_dataset_phys(ds)->ds_unique_bytes);

	if (unused_refres_delta > 0 &&
	    unused_refres_delta >
	    dsl_dir_space_available(ds->ds_dir, NULL, 0, TRUE)) {
		dsl_dataset_rele(ds, FTAG);
		return (SET_ERROR(ENOSPC));
	}

	dsl_dataset_rele(ds, FTAG);
	return (0);
}