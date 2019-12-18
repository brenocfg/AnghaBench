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
struct TYPE_8__ {size_t vdev_children; void* vdev_resilver_deferred; int /*<<< orphan*/ * vdev_dtl; TYPE_1__* vdev_ops; struct TYPE_8__** vdev_child; } ;
typedef  TYPE_2__ vdev_t ;
typedef  size_t uint64_t ;
struct TYPE_9__ {void* spa_resilver_deferred; } ;
typedef  TYPE_3__ spa_t ;
struct TYPE_7__ {int /*<<< orphan*/  vdev_op_leaf; } ;

/* Variables and functions */
 void* B_TRUE ; 
 size_t DTL_MISSING ; 
 scalar_t__ range_tree_is_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_writeable (TYPE_2__*) ; 

void
vdev_set_deferred_resilver(spa_t *spa, vdev_t *vd)
{
	for (uint64_t i = 0; i < vd->vdev_children; i++)
		vdev_set_deferred_resilver(spa, vd->vdev_child[i]);

	if (!vd->vdev_ops->vdev_op_leaf || !vdev_writeable(vd) ||
	    range_tree_is_empty(vd->vdev_dtl[DTL_MISSING])) {
		return;
	}

	vd->vdev_resilver_deferred = B_TRUE;
	spa->spa_resilver_deferred = B_TRUE;
}