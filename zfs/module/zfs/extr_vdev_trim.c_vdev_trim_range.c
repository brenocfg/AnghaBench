#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ vdev_trim_rate; scalar_t__* vdev_trim_inflight; scalar_t__* vdev_trim_offset; size_t vdev_guid; int /*<<< orphan*/  vdev_trim_lock; TYPE_3__* vdev_spa; int /*<<< orphan*/  vdev_trim_io_lock; int /*<<< orphan*/  vdev_top; int /*<<< orphan*/  vdev_trim_io_cv; } ;
typedef  TYPE_1__ vdev_t ;
typedef  size_t uint64_t ;
struct TYPE_16__ {size_t trim_type; size_t trim_bytes_done; int /*<<< orphan*/  trim_flags; TYPE_1__* trim_vdev; } ;
typedef  TYPE_2__ trim_args_t ;
struct TYPE_17__ {int /*<<< orphan*/ * spa_txg_zio; } ;
typedef  TYPE_3__ spa_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_18__ {int /*<<< orphan*/  dp_mos_dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINTR ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 scalar_t__ MSEC_TO_TICK (int) ; 
 int /*<<< orphan*/  RW_READER ; 
 int /*<<< orphan*/  SCL_STATE_ALL ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 size_t TRIM_TYPE_AUTO ; 
 size_t TRIM_TYPE_MANUAL ; 
 size_t TXG_MASK ; 
 int /*<<< orphan*/  TXG_WAIT ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZFS_SPACE_CHECK_RESERVED ; 
 int /*<<< orphan*/  ZIO_FLAG_CANFAIL ; 
 int /*<<< orphan*/  ZIO_PRIORITY_TRIM ; 
 int /*<<< orphan*/  cv_timedwait_sig (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  cv_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ddi_get_lbolt () ; 
 int /*<<< orphan*/  dmu_tx_assign (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_tx_commit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dmu_tx_create_dd (int /*<<< orphan*/ ) ; 
 size_t dmu_tx_get_txg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_sync_task_nowait (TYPE_8__*,int /*<<< orphan*/ ,size_t*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 size_t* kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_config_enter (TYPE_3__*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_exit (TYPE_3__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_8__* spa_get_dsl (TYPE_3__*) ; 
 int /*<<< orphan*/  vdev_autotrim_cb ; 
 scalar_t__ vdev_autotrim_should_stop (int /*<<< orphan*/ ) ; 
 scalar_t__ vdev_trim_calculate_rate (TYPE_2__*) ; 
 int /*<<< orphan*/  vdev_trim_cb ; 
 scalar_t__ vdev_trim_should_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  vdev_trim_zap_update_sync ; 
 scalar_t__ zfs_trim_queue_limit ; 
 int /*<<< orphan*/  zio_nowait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zio_trim (int /*<<< orphan*/ ,TYPE_1__*,size_t,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vdev_trim_range(trim_args_t *ta, uint64_t start, uint64_t size)
{
	vdev_t *vd = ta->trim_vdev;
	spa_t *spa = vd->vdev_spa;

	mutex_enter(&vd->vdev_trim_io_lock);

	/*
	 * Limit manual TRIM I/Os to the requested rate.  This does not
	 * apply to automatic TRIM since no per vdev rate can be specified.
	 */
	if (ta->trim_type == TRIM_TYPE_MANUAL) {
		while (vd->vdev_trim_rate != 0 && !vdev_trim_should_stop(vd) &&
		    vdev_trim_calculate_rate(ta) > vd->vdev_trim_rate) {
			cv_timedwait_sig(&vd->vdev_trim_io_cv,
			    &vd->vdev_trim_io_lock, ddi_get_lbolt() +
			    MSEC_TO_TICK(10));
		}
	}
	ta->trim_bytes_done += size;

	/* Limit in flight trimming I/Os */
	while (vd->vdev_trim_inflight[0] + vd->vdev_trim_inflight[1] >=
	    zfs_trim_queue_limit) {
		cv_wait(&vd->vdev_trim_io_cv, &vd->vdev_trim_io_lock);
	}
	vd->vdev_trim_inflight[ta->trim_type]++;
	mutex_exit(&vd->vdev_trim_io_lock);

	dmu_tx_t *tx = dmu_tx_create_dd(spa_get_dsl(spa)->dp_mos_dir);
	VERIFY0(dmu_tx_assign(tx, TXG_WAIT));
	uint64_t txg = dmu_tx_get_txg(tx);

	spa_config_enter(spa, SCL_STATE_ALL, vd, RW_READER);
	mutex_enter(&vd->vdev_trim_lock);

	if (ta->trim_type == TRIM_TYPE_MANUAL &&
	    vd->vdev_trim_offset[txg & TXG_MASK] == 0) {
		uint64_t *guid = kmem_zalloc(sizeof (uint64_t), KM_SLEEP);
		*guid = vd->vdev_guid;

		/* This is the first write of this txg. */
		dsl_sync_task_nowait(spa_get_dsl(spa),
		    vdev_trim_zap_update_sync, guid, 2,
		    ZFS_SPACE_CHECK_RESERVED, tx);
	}

	/*
	 * We know the vdev_t will still be around since all consumers of
	 * vdev_free must stop the trimming first.
	 */
	if ((ta->trim_type == TRIM_TYPE_MANUAL &&
	    vdev_trim_should_stop(vd)) ||
	    (ta->trim_type == TRIM_TYPE_AUTO &&
	    vdev_autotrim_should_stop(vd->vdev_top))) {
		mutex_enter(&vd->vdev_trim_io_lock);
		vd->vdev_trim_inflight[ta->trim_type]--;
		mutex_exit(&vd->vdev_trim_io_lock);
		spa_config_exit(vd->vdev_spa, SCL_STATE_ALL, vd);
		mutex_exit(&vd->vdev_trim_lock);
		dmu_tx_commit(tx);
		return (SET_ERROR(EINTR));
	}
	mutex_exit(&vd->vdev_trim_lock);

	if (ta->trim_type == TRIM_TYPE_MANUAL)
		vd->vdev_trim_offset[txg & TXG_MASK] = start + size;

	zio_nowait(zio_trim(spa->spa_txg_zio[txg & TXG_MASK], vd,
	    start, size, ta->trim_type == TRIM_TYPE_MANUAL ?
	    vdev_trim_cb : vdev_autotrim_cb, NULL,
	    ZIO_PRIORITY_TRIM, ZIO_FLAG_CANFAIL, ta->trim_flags));
	/* vdev_trim_cb and vdev_autotrim_cb release SCL_STATE_ALL */

	dmu_tx_commit(tx);

	return (0);
}