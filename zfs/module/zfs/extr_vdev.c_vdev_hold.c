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
struct TYPE_8__ {int vdev_children; TYPE_1__* vdev_ops; struct TYPE_8__** vdev_child; TYPE_3__* vdev_spa; } ;
typedef  TYPE_2__ vdev_t ;
struct TYPE_9__ {scalar_t__ spa_state; } ;
typedef  TYPE_3__ spa_t ;
struct TYPE_7__ {int /*<<< orphan*/  (* vdev_op_hold ) (TYPE_2__*) ;scalar_t__ vdev_op_leaf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ POOL_STATE_UNINITIALIZED ; 
 int /*<<< orphan*/  spa_is_root (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

void
vdev_hold(vdev_t *vd)
{
	spa_t *spa = vd->vdev_spa;

	ASSERT(spa_is_root(spa));
	if (spa->spa_state == POOL_STATE_UNINITIALIZED)
		return;

	for (int c = 0; c < vd->vdev_children; c++)
		vdev_hold(vd->vdev_child[c]);

	if (vd->vdev_ops->vdev_op_leaf)
		vd->vdev_ops->vdev_op_hold(vd);
}