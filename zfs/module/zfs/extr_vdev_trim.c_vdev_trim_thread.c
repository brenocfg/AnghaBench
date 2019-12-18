#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__* vdev_trim_inflight; int /*<<< orphan*/  vdev_trim_lock; int /*<<< orphan*/  vdev_trim_cv; int /*<<< orphan*/ * vdev_trim_thread; scalar_t__ vdev_trim_secure; scalar_t__ vdev_trim_partial; scalar_t__ vdev_trim_rate; int /*<<< orphan*/  vdev_trim_exit_wanted; int /*<<< orphan*/  vdev_trim_io_lock; int /*<<< orphan*/  vdev_trim_io_cv; TYPE_1__* vdev_top; int /*<<< orphan*/  vdev_detached; scalar_t__ vdev_trim_last_offset; int /*<<< orphan*/ * vdev_spa; } ;
typedef  TYPE_2__ vdev_t ;
typedef  size_t uint64_t ;
struct TYPE_17__ {int /*<<< orphan*/  trim_tree; TYPE_4__* trim_msp; int /*<<< orphan*/  trim_extent_bytes_min; int /*<<< orphan*/  trim_flags; int /*<<< orphan*/  trim_type; int /*<<< orphan*/  trim_extent_bytes_max; TYPE_2__* trim_vdev; } ;
typedef  TYPE_3__ trim_args_t ;
typedef  int /*<<< orphan*/  spa_t ;
struct TYPE_18__ {int /*<<< orphan*/  ms_lock; int /*<<< orphan*/  ms_trim; int /*<<< orphan*/  ms_allocatable; int /*<<< orphan*/ * ms_sm; } ;
typedef  TYPE_4__ metaslab_t ;
struct TYPE_15__ {size_t vdev_ms_count; TYPE_4__** vdev_ms; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  RANGE_SEG64 ; 
 int /*<<< orphan*/  RW_READER ; 
 int /*<<< orphan*/  SCL_CONFIG ; 
 int /*<<< orphan*/  SPA_MINBLOCKSIZE ; 
 int /*<<< orphan*/  TRIM_TYPE_MANUAL ; 
 int /*<<< orphan*/  VDEV_TRIM_COMPLETE ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZIO_TRIM_SECURE ; 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  metaslab_disable (TYPE_4__*) ; 
 int /*<<< orphan*/  metaslab_enable (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  metaslab_load (TYPE_4__*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  range_tree_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  range_tree_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  range_tree_vacate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  range_tree_walk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  spa_config_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_exit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_get_dsl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txg_wait_synced (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vdev_is_concrete (TYPE_2__*) ; 
 int /*<<< orphan*/  vdev_trim_calculate_progress (TYPE_2__*) ; 
 int /*<<< orphan*/  vdev_trim_change_state (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  vdev_trim_load (TYPE_2__*) ; 
 int /*<<< orphan*/  vdev_trim_range_add ; 
 int vdev_trim_ranges (TYPE_3__*) ; 
 scalar_t__ vdev_writeable (TYPE_2__*) ; 
 int /*<<< orphan*/  zfs_trim_extent_bytes_max ; 
 int /*<<< orphan*/  zfs_trim_extent_bytes_min ; 

__attribute__((used)) static void
vdev_trim_thread(void *arg)
{
	vdev_t *vd = arg;
	spa_t *spa = vd->vdev_spa;
	trim_args_t ta;
	int error = 0;

	/*
	 * The VDEV_LEAF_ZAP_TRIM_* entries may have been updated by
	 * vdev_trim().  Wait for the updated values to be reflected
	 * in the zap in order to start with the requested settings.
	 */
	txg_wait_synced(spa_get_dsl(vd->vdev_spa), 0);

	ASSERT(vdev_is_concrete(vd));
	spa_config_enter(spa, SCL_CONFIG, FTAG, RW_READER);

	vd->vdev_trim_last_offset = 0;
	vd->vdev_trim_rate = 0;
	vd->vdev_trim_partial = 0;
	vd->vdev_trim_secure = 0;

	VERIFY0(vdev_trim_load(vd));

	ta.trim_vdev = vd;
	ta.trim_extent_bytes_max = zfs_trim_extent_bytes_max;
	ta.trim_extent_bytes_min = zfs_trim_extent_bytes_min;
	ta.trim_tree = range_tree_create(NULL, RANGE_SEG64, NULL, 0, 0);
	ta.trim_type = TRIM_TYPE_MANUAL;
	ta.trim_flags = 0;

	/*
	 * When a secure TRIM has been requested infer that the intent
	 * is that everything must be trimmed.  Override the default
	 * minimum TRIM size to prevent ranges from being skipped.
	 */
	if (vd->vdev_trim_secure) {
		ta.trim_flags |= ZIO_TRIM_SECURE;
		ta.trim_extent_bytes_min = SPA_MINBLOCKSIZE;
	}

	uint64_t ms_count = 0;
	for (uint64_t i = 0; !vd->vdev_detached &&
	    i < vd->vdev_top->vdev_ms_count; i++) {
		metaslab_t *msp = vd->vdev_top->vdev_ms[i];

		/*
		 * If we've expanded the top-level vdev or it's our
		 * first pass, calculate our progress.
		 */
		if (vd->vdev_top->vdev_ms_count != ms_count) {
			vdev_trim_calculate_progress(vd);
			ms_count = vd->vdev_top->vdev_ms_count;
		}

		spa_config_exit(spa, SCL_CONFIG, FTAG);
		metaslab_disable(msp);
		mutex_enter(&msp->ms_lock);
		VERIFY0(metaslab_load(msp));

		/*
		 * If a partial TRIM was requested skip metaslabs which have
		 * never been initialized and thus have never been written.
		 */
		if (msp->ms_sm == NULL && vd->vdev_trim_partial) {
			mutex_exit(&msp->ms_lock);
			metaslab_enable(msp, B_FALSE, B_FALSE);
			spa_config_enter(spa, SCL_CONFIG, FTAG, RW_READER);
			vdev_trim_calculate_progress(vd);
			continue;
		}

		ta.trim_msp = msp;
		range_tree_walk(msp->ms_allocatable, vdev_trim_range_add, &ta);
		range_tree_vacate(msp->ms_trim, NULL, NULL);
		mutex_exit(&msp->ms_lock);

		error = vdev_trim_ranges(&ta);
		metaslab_enable(msp, B_TRUE, B_FALSE);
		spa_config_enter(spa, SCL_CONFIG, FTAG, RW_READER);

		range_tree_vacate(ta.trim_tree, NULL, NULL);
		if (error != 0)
			break;
	}

	spa_config_exit(spa, SCL_CONFIG, FTAG);
	mutex_enter(&vd->vdev_trim_io_lock);
	while (vd->vdev_trim_inflight[0] > 0) {
		cv_wait(&vd->vdev_trim_io_cv, &vd->vdev_trim_io_lock);
	}
	mutex_exit(&vd->vdev_trim_io_lock);

	range_tree_destroy(ta.trim_tree);

	mutex_enter(&vd->vdev_trim_lock);
	if (!vd->vdev_trim_exit_wanted && vdev_writeable(vd)) {
		vdev_trim_change_state(vd, VDEV_TRIM_COMPLETE,
		    vd->vdev_trim_rate, vd->vdev_trim_partial,
		    vd->vdev_trim_secure);
	}
	ASSERT(vd->vdev_trim_thread != NULL || vd->vdev_trim_inflight[0] == 0);

	/*
	 * Drop the vdev_trim_lock while we sync out the txg since it's
	 * possible that a device might be trying to come online and must
	 * check to see if it needs to restart a trim. That thread will be
	 * holding the spa_config_lock which would prevent the txg_wait_synced
	 * from completing.
	 */
	mutex_exit(&vd->vdev_trim_lock);
	txg_wait_synced(spa_get_dsl(spa), 0);
	mutex_enter(&vd->vdev_trim_lock);

	vd->vdev_trim_thread = NULL;
	cv_broadcast(&vd->vdev_trim_cv);
	mutex_exit(&vd->vdev_trim_lock);
}