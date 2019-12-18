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
typedef  int /*<<< orphan*/  zbookmark_phys_t ;
struct TYPE_16__ {int /*<<< orphan*/  vdev_scan_io_queue_lock; int /*<<< orphan*/ * vdev_scan_io_queue; } ;
typedef  TYPE_2__ vdev_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  dva_t ;
struct TYPE_17__ {TYPE_1__* dp_scan; int /*<<< orphan*/ * dp_spa; } ;
typedef  TYPE_3__ dsl_pool_t ;
struct TYPE_18__ {int /*<<< orphan*/ * blk_dva; } ;
typedef  TYPE_4__ blkptr_t ;
struct TYPE_15__ {int /*<<< orphan*/  scn_is_sorted; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int BP_GET_NDVAS (TYPE_4__ const*) ; 
 int /*<<< orphan*/  BP_IS_EMBEDDED (TYPE_4__ const*) ; 
 scalar_t__ BP_IS_GANG (TYPE_4__ const*) ; 
 int /*<<< orphan*/  DVA_GET_VDEV (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scan_exec_io (TYPE_3__*,TYPE_4__ const*,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * scan_io_queue_create (TYPE_2__*) ; 
 int /*<<< orphan*/  scan_io_queue_insert (int /*<<< orphan*/ *,TYPE_4__ const*,int,int,int /*<<< orphan*/  const*) ; 
 TYPE_2__* vdev_lookup_top (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dsl_scan_enqueue(dsl_pool_t *dp, const blkptr_t *bp, int zio_flags,
    const zbookmark_phys_t *zb)
{
	spa_t *spa = dp->dp_spa;

	ASSERT(!BP_IS_EMBEDDED(bp));

	/*
	 * Gang blocks are hard to issue sequentially, so we just issue them
	 * here immediately instead of queuing them.
	 */
	if (!dp->dp_scan->scn_is_sorted || BP_IS_GANG(bp)) {
		scan_exec_io(dp, bp, zio_flags, zb, NULL);
		return;
	}

	for (int i = 0; i < BP_GET_NDVAS(bp); i++) {
		dva_t dva;
		vdev_t *vdev;

		dva = bp->blk_dva[i];
		vdev = vdev_lookup_top(spa, DVA_GET_VDEV(&dva));
		ASSERT(vdev != NULL);

		mutex_enter(&vdev->vdev_scan_io_queue_lock);
		if (vdev->vdev_scan_io_queue == NULL)
			vdev->vdev_scan_io_queue = scan_io_queue_create(vdev);
		ASSERT(dp->dp_scan != NULL);
		scan_io_queue_insert(vdev->vdev_scan_io_queue, bp,
		    i, zio_flags, zb);
		mutex_exit(&vdev->vdev_scan_io_queue_lock);
	}
}