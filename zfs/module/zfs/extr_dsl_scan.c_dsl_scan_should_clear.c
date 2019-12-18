#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int vdev_children; int /*<<< orphan*/  vdev_scan_io_queue_lock; TYPE_4__* vdev_scan_io_queue; struct TYPE_8__** vdev_child; } ;
typedef  TYPE_2__ vdev_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  range_seg_gap_t ;
typedef  int /*<<< orphan*/  longlong_t ;
struct TYPE_9__ {int /*<<< orphan*/  scn_clearing; int /*<<< orphan*/  scn_bytes_pending; TYPE_1__* scn_dp; } ;
typedef  TYPE_3__ dsl_scan_t ;
struct TYPE_10__ {scalar_t__ q_sio_memused; int /*<<< orphan*/  q_exts_by_size; } ;
typedef  TYPE_4__ dsl_scan_io_queue_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_11__ {TYPE_2__* spa_root_vdev; } ;
struct TYPE_7__ {TYPE_5__* dp_spa; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int MAX (int,int /*<<< orphan*/ ) ; 
 int MIN (int,int) ; 
 int PAGESIZE ; 
 int /*<<< orphan*/  dprintf (char*,int /*<<< orphan*/ ) ; 
 int metaslab_class_get_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int physmem ; 
 int /*<<< orphan*/  spa_normal_class (TYPE_5__*) ; 
 int zfs_btree_numnodes (int /*<<< orphan*/ *) ; 
 int zfs_scan_mem_lim_fact ; 
 int /*<<< orphan*/  zfs_scan_mem_lim_min ; 
 int zfs_scan_mem_lim_soft_fact ; 
 int zfs_scan_mem_lim_soft_max ; 

__attribute__((used)) static boolean_t
dsl_scan_should_clear(dsl_scan_t *scn)
{
	vdev_t *rvd = scn->scn_dp->dp_spa->spa_root_vdev;
	uint64_t mlim_hard, mlim_soft, mused;
	uint64_t alloc = metaslab_class_get_alloc(spa_normal_class(
	    scn->scn_dp->dp_spa));

	mlim_hard = MAX((physmem / zfs_scan_mem_lim_fact) * PAGESIZE,
	    zfs_scan_mem_lim_min);
	mlim_hard = MIN(mlim_hard, alloc / 20);
	mlim_soft = mlim_hard - MIN(mlim_hard / zfs_scan_mem_lim_soft_fact,
	    zfs_scan_mem_lim_soft_max);
	mused = 0;
	for (uint64_t i = 0; i < rvd->vdev_children; i++) {
		vdev_t *tvd = rvd->vdev_child[i];
		dsl_scan_io_queue_t *queue;

		mutex_enter(&tvd->vdev_scan_io_queue_lock);
		queue = tvd->vdev_scan_io_queue;
		if (queue != NULL) {
			/* # extents in exts_by_size = # in exts_by_addr */
			mused += zfs_btree_numnodes(&queue->q_exts_by_size) *
			    sizeof (range_seg_gap_t) + queue->q_sio_memused;
		}
		mutex_exit(&tvd->vdev_scan_io_queue_lock);
	}

	dprintf("current scan memory usage: %llu bytes\n", (longlong_t)mused);

	if (mused == 0)
		ASSERT0(scn->scn_bytes_pending);

	/*
	 * If we are above our hard limit, we need to clear out memory.
	 * If we are below our soft limit, we need to accumulate sequential IOs.
	 * Otherwise, we should keep doing whatever we are currently doing.
	 */
	if (mused >= mlim_hard)
		return (B_TRUE);
	else if (mused < mlim_soft)
		return (B_FALSE);
	else
		return (scn->scn_clearing);
}