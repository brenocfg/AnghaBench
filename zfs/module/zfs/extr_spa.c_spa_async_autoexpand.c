#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int vdev_children; int /*<<< orphan*/  vdev_spa; int /*<<< orphan*/ * vdev_physpath; TYPE_1__* vdev_ops; struct TYPE_8__** vdev_child; } ;
typedef  TYPE_2__ vdev_t ;
struct TYPE_9__ {int /*<<< orphan*/  spa_autoexpand; } ;
typedef  TYPE_3__ spa_t ;
struct TYPE_7__ {int /*<<< orphan*/  vdev_op_leaf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESC_ZFS_VDEV_AUTOEXPAND ; 
 int /*<<< orphan*/  spa_event_notify (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
spa_async_autoexpand(spa_t *spa, vdev_t *vd)
{
	if (!spa->spa_autoexpand)
		return;

	for (int c = 0; c < vd->vdev_children; c++) {
		vdev_t *cvd = vd->vdev_child[c];
		spa_async_autoexpand(spa, cvd);
	}

	if (!vd->vdev_ops->vdev_op_leaf || vd->vdev_physpath == NULL)
		return;

	spa_event_notify(vd->vdev_spa, vd, NULL, ESC_ZFS_VDEV_AUTOEXPAND);
}