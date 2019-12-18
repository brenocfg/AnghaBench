#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int vdev_children; struct TYPE_8__** vdev_child; } ;
typedef  TYPE_1__ vdev_t ;
struct TYPE_9__ {TYPE_1__* spa_root_vdev; } ;
typedef  TYPE_2__ spa_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_condense_indirect_start_sync (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_writeable (TYPE_2__*) ; 
 scalar_t__ vdev_indirect_should_condense (TYPE_1__*) ; 
 int /*<<< orphan*/  vdev_indirect_state_sync_verify (TYPE_1__*) ; 

__attribute__((used)) static void
spa_sync_condense_indirect(spa_t *spa, dmu_tx_t *tx)
{
	ASSERT(spa_writeable(spa));

	vdev_t *rvd = spa->spa_root_vdev;
	for (int c = 0; c < rvd->vdev_children; c++) {
		vdev_t *vd = rvd->vdev_child[c];
		vdev_indirect_state_sync_verify(vd);

		if (vdev_indirect_should_condense(vd)) {
			spa_condense_indirect_start_sync(vd, tx);
			break;
		}
	}
}