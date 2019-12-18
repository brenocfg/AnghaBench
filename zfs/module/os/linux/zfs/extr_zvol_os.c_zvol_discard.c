#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ zv_open_count; scalar_t__ zv_volsize; TYPE_2__* zv_zso; int /*<<< orphan*/  zv_suspend_lock; int /*<<< orphan*/ * zv_zilog; TYPE_7__* zv_objset; int /*<<< orphan*/  zv_volblocksize; } ;
typedef  TYPE_3__ zvol_state_t ;
struct TYPE_12__ {int /*<<< orphan*/  lr; TYPE_3__* zv; struct bio* bio; } ;
typedef  TYPE_4__ zv_request_t ;
typedef  scalar_t__ uint64_t ;
struct bio {int dummy; } ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
typedef  int boolean_t ;
struct TYPE_13__ {scalar_t__ os_sync; } ;
struct TYPE_10__ {TYPE_1__* zvo_disk; int /*<<< orphan*/  zvo_queue; } ;
struct TYPE_9__ {int /*<<< orphan*/  part0; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int BIO_BI_SECTOR (struct bio*) ; 
 scalar_t__ BIO_BI_SIZE (struct bio*) ; 
 int /*<<< orphan*/  BIO_END_IO (struct bio*,int) ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  EIO ; 
 scalar_t__ P2ALIGN (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ P2ROUNDUP (scalar_t__,int /*<<< orphan*/ ) ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TXG_WAIT ; 
 int /*<<< orphan*/  WRITE ; 
 scalar_t__ ZFS_SYNC_ALWAYS ; 
 int /*<<< orphan*/  ZVOL_OBJ ; 
 scalar_t__ bio_is_fua (struct bio*) ; 
 int /*<<< orphan*/  bio_is_secure_erase (struct bio*) ; 
 int /*<<< orphan*/  bio_sectors (struct bio*) ; 
 int /*<<< orphan*/  blk_generic_end_io_acct (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  blk_generic_start_io_acct (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int dmu_free_long_range (TYPE_7__*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  dmu_tx_abort (int /*<<< orphan*/ *) ; 
 int dmu_tx_assign (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_tx_commit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dmu_tx_create (TYPE_7__*) ; 
 int /*<<< orphan*/  dmu_tx_mark_netfree (int /*<<< orphan*/ *) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  kmem_free (TYPE_4__*,int) ; 
 int /*<<< orphan*/  rw_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_rangelock_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zil_commit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zvol_log_truncate (TYPE_3__*,int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
zvol_discard(void *arg)
{
	zv_request_t *zvr = arg;
	struct bio *bio = zvr->bio;
	zvol_state_t *zv = zvr->zv;
	uint64_t start = BIO_BI_SECTOR(bio) << 9;
	uint64_t size = BIO_BI_SIZE(bio);
	uint64_t end = start + size;
	boolean_t sync;
	int error = 0;
	dmu_tx_t *tx;
	unsigned long start_jif;

	ASSERT(zv && zv->zv_open_count > 0);
	ASSERT(zv->zv_zilog != NULL);

	start_jif = jiffies;
	blk_generic_start_io_acct(zv->zv_zso->zvo_queue, WRITE,
	    bio_sectors(bio), &zv->zv_zso->zvo_disk->part0);

	sync = bio_is_fua(bio) || zv->zv_objset->os_sync == ZFS_SYNC_ALWAYS;

	if (end > zv->zv_volsize) {
		error = SET_ERROR(EIO);
		goto unlock;
	}

	/*
	 * Align the request to volume block boundaries when a secure erase is
	 * not required.  This will prevent dnode_free_range() from zeroing out
	 * the unaligned parts which is slow (read-modify-write) and useless
	 * since we are not freeing any space by doing so.
	 */
	if (!bio_is_secure_erase(bio)) {
		start = P2ROUNDUP(start, zv->zv_volblocksize);
		end = P2ALIGN(end, zv->zv_volblocksize);
		size = end - start;
	}

	if (start >= end)
		goto unlock;

	tx = dmu_tx_create(zv->zv_objset);
	dmu_tx_mark_netfree(tx);
	error = dmu_tx_assign(tx, TXG_WAIT);
	if (error != 0) {
		dmu_tx_abort(tx);
	} else {
		zvol_log_truncate(zv, tx, start, size, B_TRUE);
		dmu_tx_commit(tx);
		error = dmu_free_long_range(zv->zv_objset,
		    ZVOL_OBJ, start, size);
	}
unlock:
	zfs_rangelock_exit(zvr->lr);

	if (error == 0 && sync)
		zil_commit(zv->zv_zilog, ZVOL_OBJ);

	rw_exit(&zv->zv_suspend_lock);
	blk_generic_end_io_acct(zv->zv_zso->zvo_queue, WRITE,
	    &zv->zv_zso->zvo_disk->part0, start_jif);
	BIO_END_IO(bio, -error);
	kmem_free(zvr, sizeof (zv_request_t));
}