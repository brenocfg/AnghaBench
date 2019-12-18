#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zio_t ;
struct TYPE_21__ {TYPE_4__* vdev_spa; } ;
typedef  TYPE_2__ vdev_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_22__ {scalar_t__ ub_txg; } ;
typedef  TYPE_3__ uberblock_t ;
struct TYPE_20__ {int /*<<< orphan*/  mmp_delay; } ;
struct TYPE_23__ {scalar_t__ spa_final_txg; int /*<<< orphan*/  spa_vdev_txg_list; int /*<<< orphan*/  spa_config_dirty_list; TYPE_1__ spa_mmp; int /*<<< orphan*/  spa_root_vdev; TYPE_3__ spa_uberblock; } ;
typedef  TYPE_4__ spa_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  TXG_CLEAN (scalar_t__) ; 
 int ZIO_FLAG_CANFAIL ; 
 int ZIO_FLAG_CONFIG_WRITER ; 
 int ZIO_FLAG_TRYHARD ; 
 scalar_t__ list_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmp_update_uberblock (TYPE_4__*,TYPE_3__*) ; 
 scalar_t__ spa_freeze_txg (TYPE_4__*) ; 
 scalar_t__ spa_multihost (TYPE_4__*) ; 
 int /*<<< orphan*/  spa_name (TYPE_4__*) ; 
 TYPE_2__* txg_list_head (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* txg_list_next (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uberblock_update (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int vdev_label_sync_list (TYPE_4__*,int,scalar_t__,int) ; 
 int vdev_uberblock_sync_list (TYPE_2__**,int,TYPE_3__*,int) ; 
 int /*<<< orphan*/  zfs_dbgmsg (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zio_flush (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/ * zio_root (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zio_wait (int /*<<< orphan*/ *) ; 

int
vdev_config_sync(vdev_t **svd, int svdcount, uint64_t txg)
{
	spa_t *spa = svd[0]->vdev_spa;
	uberblock_t *ub = &spa->spa_uberblock;
	int error = 0;
	int flags = ZIO_FLAG_CONFIG_WRITER | ZIO_FLAG_CANFAIL;

	ASSERT(svdcount != 0);
retry:
	/*
	 * Normally, we don't want to try too hard to write every label and
	 * uberblock.  If there is a flaky disk, we don't want the rest of the
	 * sync process to block while we retry.  But if we can't write a
	 * single label out, we should retry with ZIO_FLAG_TRYHARD before
	 * bailing out and declaring the pool faulted.
	 */
	if (error != 0) {
		if ((flags & ZIO_FLAG_TRYHARD) != 0)
			return (error);
		flags |= ZIO_FLAG_TRYHARD;
	}

	ASSERT(ub->ub_txg <= txg);

	/*
	 * If this isn't a resync due to I/O errors,
	 * and nothing changed in this transaction group,
	 * and the vdev configuration hasn't changed,
	 * then there's nothing to do.
	 */
	if (ub->ub_txg < txg) {
		boolean_t changed = uberblock_update(ub, spa->spa_root_vdev,
		    txg, spa->spa_mmp.mmp_delay);

		if (!changed && list_is_empty(&spa->spa_config_dirty_list))
			return (0);
	}

	if (txg > spa_freeze_txg(spa))
		return (0);

	ASSERT(txg <= spa->spa_final_txg);

	/*
	 * Flush the write cache of every disk that's been written to
	 * in this transaction group.  This ensures that all blocks
	 * written in this txg will be committed to stable storage
	 * before any uberblock that references them.
	 */
	zio_t *zio = zio_root(spa, NULL, NULL, flags);

	for (vdev_t *vd =
	    txg_list_head(&spa->spa_vdev_txg_list, TXG_CLEAN(txg)); vd != NULL;
	    vd = txg_list_next(&spa->spa_vdev_txg_list, vd, TXG_CLEAN(txg)))
		zio_flush(zio, vd);

	(void) zio_wait(zio);

	/*
	 * Sync out the even labels (L0, L2) for every dirty vdev.  If the
	 * system dies in the middle of this process, that's OK: all of the
	 * even labels that made it to disk will be newer than any uberblock,
	 * and will therefore be considered invalid.  The odd labels (L1, L3),
	 * which have not yet been touched, will still be valid.  We flush
	 * the new labels to disk to ensure that all even-label updates
	 * are committed to stable storage before the uberblock update.
	 */
	if ((error = vdev_label_sync_list(spa, 0, txg, flags)) != 0) {
		if ((flags & ZIO_FLAG_TRYHARD) != 0) {
			zfs_dbgmsg("vdev_label_sync_list() returned error %d "
			    "for pool '%s' when syncing out the even labels "
			    "of dirty vdevs", error, spa_name(spa));
		}
		goto retry;
	}

	/*
	 * Sync the uberblocks to all vdevs in svd[].
	 * If the system dies in the middle of this step, there are two cases
	 * to consider, and the on-disk state is consistent either way:
	 *
	 * (1)	If none of the new uberblocks made it to disk, then the
	 *	previous uberblock will be the newest, and the odd labels
	 *	(which had not yet been touched) will be valid with respect
	 *	to that uberblock.
	 *
	 * (2)	If one or more new uberblocks made it to disk, then they
	 *	will be the newest, and the even labels (which had all
	 *	been successfully committed) will be valid with respect
	 *	to the new uberblocks.
	 */
	if ((error = vdev_uberblock_sync_list(svd, svdcount, ub, flags)) != 0) {
		if ((flags & ZIO_FLAG_TRYHARD) != 0) {
			zfs_dbgmsg("vdev_uberblock_sync_list() returned error "
			    "%d for pool '%s'", error, spa_name(spa));
		}
		goto retry;
	}

	if (spa_multihost(spa))
		mmp_update_uberblock(spa, ub);

	/*
	 * Sync out odd labels for every dirty vdev.  If the system dies
	 * in the middle of this process, the even labels and the new
	 * uberblocks will suffice to open the pool.  The next time
	 * the pool is opened, the first thing we'll do -- before any
	 * user data is modified -- is mark every vdev dirty so that
	 * all labels will be brought up to date.  We flush the new labels
	 * to disk to ensure that all odd-label updates are committed to
	 * stable storage before the next transaction group begins.
	 */
	if ((error = vdev_label_sync_list(spa, 1, txg, flags)) != 0) {
		if ((flags & ZIO_FLAG_TRYHARD) != 0) {
			zfs_dbgmsg("vdev_label_sync_list() returned error %d "
			    "for pool '%s' when syncing out the odd labels of "
			    "dirty vdevs", error, spa_name(spa));
		}
		goto retry;
	}

	return (0);
}