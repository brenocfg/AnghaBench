#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* vdev_ops; TYPE_1__* vdev_spa; } ;
typedef  TYPE_3__ vdev_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_7__ {int /*<<< orphan*/  (* vdev_op_need_resilver ) (TYPE_3__*,int /*<<< orphan*/ ,size_t) ;scalar_t__ vdev_op_leaf; } ;
struct TYPE_6__ {TYPE_3__* spa_root_vdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ,size_t) ; 

boolean_t
vdev_dtl_need_resilver(vdev_t *vd, uint64_t offset, size_t psize)
{
	ASSERT(vd != vd->vdev_spa->spa_root_vdev);

	if (vd->vdev_ops->vdev_op_need_resilver == NULL ||
	    vd->vdev_ops->vdev_op_leaf)
		return (B_TRUE);

	return (vd->vdev_ops->vdev_op_need_resilver(vd, offset, psize));
}