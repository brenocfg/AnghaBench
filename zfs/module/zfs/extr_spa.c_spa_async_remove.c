#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ vs_checksum_errors; scalar_t__ vs_write_errors; scalar_t__ vs_read_errors; } ;
struct TYPE_6__ {int vdev_children; struct TYPE_6__** vdev_child; int /*<<< orphan*/  vdev_top; TYPE_1__ vdev_stat; void* vdev_delayed_close; void* vdev_remove_wanted; } ;
typedef  TYPE_2__ vdev_t ;
typedef  int /*<<< orphan*/  spa_t ;

/* Variables and functions */
 void* B_FALSE ; 
 int /*<<< orphan*/  VDEV_AUX_NONE ; 
 int /*<<< orphan*/  VDEV_STATE_REMOVED ; 
 int /*<<< orphan*/  vdev_set_state (TYPE_2__*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_state_dirty (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
spa_async_remove(spa_t *spa, vdev_t *vd)
{
	if (vd->vdev_remove_wanted) {
		vd->vdev_remove_wanted = B_FALSE;
		vd->vdev_delayed_close = B_FALSE;
		vdev_set_state(vd, B_FALSE, VDEV_STATE_REMOVED, VDEV_AUX_NONE);

		/*
		 * We want to clear the stats, but we don't want to do a full
		 * vdev_clear() as that will cause us to throw away
		 * degraded/faulted state as well as attempt to reopen the
		 * device, all of which is a waste.
		 */
		vd->vdev_stat.vs_read_errors = 0;
		vd->vdev_stat.vs_write_errors = 0;
		vd->vdev_stat.vs_checksum_errors = 0;

		vdev_state_dirty(vd->vdev_top);
	}

	for (int c = 0; c < vd->vdev_children; c++)
		spa_async_remove(spa, vd->vdev_child[c]);
}