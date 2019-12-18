#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {size_t vdev_children; int /*<<< orphan*/  vdev_scan_io_queue_lock; int /*<<< orphan*/ * vdev_scan_io_queue; struct TYPE_8__** vdev_child; } ;
typedef  TYPE_3__ vdev_t ;
typedef  size_t uint64_t ;
struct TYPE_9__ {TYPE_2__* scn_dp; } ;
typedef  TYPE_4__ dsl_scan_t ;
struct TYPE_7__ {TYPE_1__* dp_spa; } ;
struct TYPE_6__ {TYPE_3__* spa_root_vdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dsl_scan_io_queue_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
scan_io_queues_destroy(dsl_scan_t *scn)
{
	vdev_t *rvd = scn->scn_dp->dp_spa->spa_root_vdev;

	for (uint64_t i = 0; i < rvd->vdev_children; i++) {
		vdev_t *tvd = rvd->vdev_child[i];

		mutex_enter(&tvd->vdev_scan_io_queue_lock);
		if (tvd->vdev_scan_io_queue != NULL)
			dsl_scan_io_queue_destroy(tvd->vdev_scan_io_queue);
		tvd->vdev_scan_io_queue = NULL;
		mutex_exit(&tvd->vdev_scan_io_queue_lock);
	}
}