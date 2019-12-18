#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zio_t ;
struct TYPE_22__ {int vdev_guid; int vdev_mmp_pending; scalar_t__ vdev_mmp_kstat_id; } ;
typedef  TYPE_1__ vdev_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_23__ {scalar_t__ ub_timestamp; int ub_mmp_config; int /*<<< orphan*/  ub_mmp_delay; int /*<<< orphan*/  ub_txg; int /*<<< orphan*/  ub_mmp_magic; } ;
typedef  TYPE_2__ uberblock_t ;
struct TYPE_25__ {int mmp_skip_error; int mmp_seq; int /*<<< orphan*/  mmp_io_lock; scalar_t__ mmp_kstat_id; int /*<<< orphan*/ * mmp_zio_root; int /*<<< orphan*/  mmp_delay; TYPE_2__ mmp_ub; TYPE_1__* mmp_last_leaf; } ;
struct TYPE_24__ {TYPE_4__ spa_mmp; } ;
typedef  TYPE_3__ spa_t ;
typedef  TYPE_4__ mmp_thread_t ;
typedef  int hrtime_t ;
typedef  int /*<<< orphan*/  abd_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 scalar_t__ MMP_BLOCKS_PER_LABEL ; 
 int /*<<< orphan*/  MMP_FAIL_INTVS_OK (int /*<<< orphan*/ ) ; 
 int MMP_FAIL_INT_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MMP_INTERVAL_OK (int /*<<< orphan*/ ) ; 
 int MMP_INTERVAL_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MMP_MAGIC ; 
 int /*<<< orphan*/  MMP_MIN_INTERVAL ; 
 int MMP_SEQ_SET (int) ; 
 int MSEC2NSEC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RW_READER ; 
 int /*<<< orphan*/  SCL_STATE ; 
 scalar_t__ VDEV_LABELS ; 
 scalar_t__ VDEV_UBERBLOCK_COUNT (TYPE_1__*) ; 
 int /*<<< orphan*/  VDEV_UBERBLOCK_OFFSET (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  VDEV_UBERBLOCK_SIZE (TYPE_1__*) ; 
 int ZIO_FLAG_CANFAIL ; 
 int ZIO_FLAG_CONFIG_WRITER ; 
 int ZIO_FLAG_DONT_PROPAGATE ; 
 int ZIO_FLAG_GODFATHER ; 
 int /*<<< orphan*/ * abd_alloc_for_io (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abd_copy_from_buf (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  abd_zero (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ gethrestime_sec () ; 
 int gethrtime () ; 
 int /*<<< orphan*/  mmp_delay_update (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int mmp_next_leaf (TYPE_3__*) ; 
 int /*<<< orphan*/  mmp_tag ; 
 int /*<<< orphan*/  mmp_write_done ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_config_enter (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_exit (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int spa_get_random (scalar_t__) ; 
 int /*<<< orphan*/  spa_mmp_history_add (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,TYPE_1__*,int,scalar_t__,int) ; 
 int /*<<< orphan*/  spa_mmp_history_set_skip (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  spa_name (TYPE_3__*) ; 
 int /*<<< orphan*/  vdev_label_write (int /*<<< orphan*/ *,TYPE_1__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,int) ; 
 int /*<<< orphan*/  zfs_dbgmsg (char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  zfs_multihost_fail_intervals ; 
 int /*<<< orphan*/  zfs_multihost_interval ; 
 int /*<<< orphan*/  zio_nowait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zio_null (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * zio_root (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
mmp_write_uberblock(spa_t *spa)
{
	int flags = ZIO_FLAG_CONFIG_WRITER | ZIO_FLAG_CANFAIL;
	mmp_thread_t *mmp = &spa->spa_mmp;
	uberblock_t *ub;
	vdev_t *vd = NULL;
	int label, error;
	uint64_t offset;

	hrtime_t lock_acquire_time = gethrtime();
	spa_config_enter(spa, SCL_STATE, mmp_tag, RW_READER);
	lock_acquire_time = gethrtime() - lock_acquire_time;
	if (lock_acquire_time > (MSEC2NSEC(MMP_MIN_INTERVAL) / 10))
		zfs_dbgmsg("MMP SCL_STATE acquisition pool '%s' took %llu ns "
		    "gethrtime %llu", spa_name(spa), lock_acquire_time,
		    gethrtime());

	mutex_enter(&mmp->mmp_io_lock);

	error = mmp_next_leaf(spa);

	/*
	 * spa_mmp_history has two types of entries:
	 * Issued MMP write: records time issued, error status, etc.
	 * Skipped MMP write: an MMP write could not be issued because no
	 * suitable leaf vdev was available.  See comment above struct
	 * spa_mmp_history for details.
	 */

	if (error) {
		mmp_delay_update(spa, B_FALSE);
		if (mmp->mmp_skip_error == error) {
			spa_mmp_history_set_skip(spa, mmp->mmp_kstat_id - 1);
		} else {
			mmp->mmp_skip_error = error;
			spa_mmp_history_add(spa, mmp->mmp_ub.ub_txg,
			    gethrestime_sec(), mmp->mmp_delay, NULL, 0,
			    mmp->mmp_kstat_id++, error);
			zfs_dbgmsg("MMP error choosing leaf pool '%s' "
			    "gethrtime %llu fail_mask %#x", spa_name(spa),
			    gethrtime(), error);
		}
		mutex_exit(&mmp->mmp_io_lock);
		spa_config_exit(spa, SCL_STATE, mmp_tag);
		return;
	}

	vd = spa->spa_mmp.mmp_last_leaf;
	if (mmp->mmp_skip_error != 0) {
		mmp->mmp_skip_error = 0;
		zfs_dbgmsg("MMP write after skipping due to unavailable "
		    "leaves, pool '%s' gethrtime %llu leaf %#llu",
		    spa_name(spa), gethrtime(), vd->vdev_guid);
	}

	if (mmp->mmp_zio_root == NULL)
		mmp->mmp_zio_root = zio_root(spa, NULL, NULL,
		    flags | ZIO_FLAG_GODFATHER);

	if (mmp->mmp_ub.ub_timestamp != gethrestime_sec()) {
		/*
		 * Want to reset mmp_seq when timestamp advances because after
		 * an mmp_seq wrap new values will not be chosen by
		 * uberblock_compare() as the "best".
		 */
		mmp->mmp_ub.ub_timestamp = gethrestime_sec();
		mmp->mmp_seq = 1;
	}

	ub = &mmp->mmp_ub;
	ub->ub_mmp_magic = MMP_MAGIC;
	ub->ub_mmp_delay = mmp->mmp_delay;
	ub->ub_mmp_config = MMP_SEQ_SET(mmp->mmp_seq) |
	    MMP_INTERVAL_SET(MMP_INTERVAL_OK(zfs_multihost_interval)) |
	    MMP_FAIL_INT_SET(MMP_FAIL_INTVS_OK(
	    zfs_multihost_fail_intervals));
	vd->vdev_mmp_pending = gethrtime();
	vd->vdev_mmp_kstat_id = mmp->mmp_kstat_id;

	zio_t *zio  = zio_null(mmp->mmp_zio_root, spa, NULL, NULL, NULL, flags);
	abd_t *ub_abd = abd_alloc_for_io(VDEV_UBERBLOCK_SIZE(vd), B_TRUE);
	abd_zero(ub_abd, VDEV_UBERBLOCK_SIZE(vd));
	abd_copy_from_buf(ub_abd, ub, sizeof (uberblock_t));

	mmp->mmp_seq++;
	mmp->mmp_kstat_id++;
	mutex_exit(&mmp->mmp_io_lock);

	offset = VDEV_UBERBLOCK_OFFSET(vd, VDEV_UBERBLOCK_COUNT(vd) -
	    MMP_BLOCKS_PER_LABEL + spa_get_random(MMP_BLOCKS_PER_LABEL));

	label = spa_get_random(VDEV_LABELS);
	vdev_label_write(zio, vd, label, ub_abd, offset,
	    VDEV_UBERBLOCK_SIZE(vd), mmp_write_done, mmp,
	    flags | ZIO_FLAG_DONT_PROPAGATE);

	(void) spa_mmp_history_add(spa, ub->ub_txg, ub->ub_timestamp,
	    ub->ub_mmp_delay, vd, label, vd->vdev_mmp_kstat_id, 0);

	zio_nowait(zio);
}