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
struct TYPE_6__ {int vdev_children; int /*<<< orphan*/  vdev_resilver_deferred; TYPE_1__* vdev_ops; scalar_t__ vdev_aux; struct TYPE_6__** vdev_child; } ;
typedef  TYPE_2__ vdev_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_5__ {int /*<<< orphan*/  vdev_op_leaf; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  vdev_is_concrete (TYPE_2__*) ; 

__attribute__((used)) static boolean_t
dsl_scan_check_deferred(vdev_t *vd)
{
	boolean_t need_resilver = B_FALSE;

	for (int c = 0; c < vd->vdev_children; c++) {
		need_resilver |=
		    dsl_scan_check_deferred(vd->vdev_child[c]);
	}

	if (!vdev_is_concrete(vd) || vd->vdev_aux ||
	    !vd->vdev_ops->vdev_op_leaf)
		return (need_resilver);

	if (!vd->vdev_resilver_deferred)
		need_resilver = B_TRUE;

	return (need_resilver);
}