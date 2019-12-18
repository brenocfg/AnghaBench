#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ zv_open_count; scalar_t__ zv_volsize; TYPE_3__* zv_zso; int /*<<< orphan*/  zv_suspend_lock; int /*<<< orphan*/  zv_dn; } ;
typedef  TYPE_4__ zvol_state_t ;
struct TYPE_14__ {int /*<<< orphan*/  lr; TYPE_4__* zv; struct bio* bio; } ;
typedef  TYPE_5__ zv_request_t ;
struct TYPE_10__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_15__ {scalar_t__ uio_resid; scalar_t__ uio_loffset; int /*<<< orphan*/  member_1; TYPE_1__ member_0; } ;
typedef  TYPE_6__ uio_t ;
typedef  scalar_t__ uint64_t ;
struct bio {int dummy; } ;
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_12__ {TYPE_2__* zvo_disk; int /*<<< orphan*/  zvo_queue; int /*<<< orphan*/  zvo_kstat; } ;
struct TYPE_11__ {int /*<<< orphan*/  part0; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_END_IO (struct bio*,int) ; 
 int DMU_MAX_ACCESS ; 
 int ECKSUM ; 
 int /*<<< orphan*/  EIO ; 
 scalar_t__ MIN (scalar_t__,int) ; 
 int /*<<< orphan*/  READ ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_sectors (struct bio*) ; 
 int /*<<< orphan*/  blk_generic_end_io_acct (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  blk_generic_start_io_acct (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dataset_kstats_update_read_kstats (int /*<<< orphan*/ *,scalar_t__) ; 
 int dmu_read_uio_dnode (int /*<<< orphan*/ ,TYPE_6__*,scalar_t__) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  kmem_free (TYPE_5__*,int) ; 
 int /*<<< orphan*/  rw_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_io_account_read (scalar_t__) ; 
 int /*<<< orphan*/  uio_from_bio (TYPE_6__*,struct bio*) ; 
 int /*<<< orphan*/  zfs_rangelock_exit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
zvol_read(void *arg)
{
	int error = 0;

	zv_request_t *zvr = arg;
	struct bio *bio = zvr->bio;
	uio_t uio = { { 0 }, 0 };
	uio_from_bio(&uio, bio);

	zvol_state_t *zv = zvr->zv;
	ASSERT(zv && zv->zv_open_count > 0);

	ssize_t start_resid = uio.uio_resid;
	unsigned long start_jif = jiffies;
	blk_generic_start_io_acct(zv->zv_zso->zvo_queue, READ, bio_sectors(bio),
	    &zv->zv_zso->zvo_disk->part0);

	uint64_t volsize = zv->zv_volsize;
	while (uio.uio_resid > 0 && uio.uio_loffset < volsize) {
		uint64_t bytes = MIN(uio.uio_resid, DMU_MAX_ACCESS >> 1);

		/* don't read past the end */
		if (bytes > volsize - uio.uio_loffset)
			bytes = volsize - uio.uio_loffset;

		error = dmu_read_uio_dnode(zv->zv_dn, &uio, bytes);
		if (error) {
			/* convert checksum errors into IO errors */
			if (error == ECKSUM)
				error = SET_ERROR(EIO);
			break;
		}
	}
	zfs_rangelock_exit(zvr->lr);

	int64_t nread = start_resid - uio.uio_resid;
	dataset_kstats_update_read_kstats(&zv->zv_zso->zvo_kstat, nread);
	task_io_account_read(nread);

	rw_exit(&zv->zv_suspend_lock);
	blk_generic_end_io_acct(zv->zv_zso->zvo_queue, READ,
	    &zv->zv_zso->zvo_disk->part0, start_jif);
	BIO_END_IO(bio, -error);
	kmem_free(zvr, sizeof (zv_request_t));
}