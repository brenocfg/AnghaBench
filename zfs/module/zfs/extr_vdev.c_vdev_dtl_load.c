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
struct TYPE_7__ {int vdev_children; struct TYPE_7__** vdev_child; int /*<<< orphan*/  vdev_dtl_lock; int /*<<< orphan*/ * vdev_dtl; int /*<<< orphan*/ * vdev_dtl_sm; int /*<<< orphan*/  vdev_dtl_object; TYPE_1__* vdev_ops; TYPE_3__* vdev_spa; } ;
typedef  TYPE_2__ vdev_t ;
struct TYPE_8__ {int /*<<< orphan*/ * spa_meta_objset; } ;
typedef  TYPE_3__ spa_t ;
typedef  int /*<<< orphan*/  objset_t ;
struct TYPE_6__ {scalar_t__ vdev_op_leaf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 size_t DTL_MISSING ; 
 int /*<<< orphan*/  SM_ALLOC ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int space_map_load (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int space_map_open (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_is_concrete (TYPE_2__*) ; 

int
vdev_dtl_load(vdev_t *vd)
{
	spa_t *spa = vd->vdev_spa;
	objset_t *mos = spa->spa_meta_objset;
	int error = 0;

	if (vd->vdev_ops->vdev_op_leaf && vd->vdev_dtl_object != 0) {
		ASSERT(vdev_is_concrete(vd));

		error = space_map_open(&vd->vdev_dtl_sm, mos,
		    vd->vdev_dtl_object, 0, -1ULL, 0);
		if (error)
			return (error);
		ASSERT(vd->vdev_dtl_sm != NULL);

		mutex_enter(&vd->vdev_dtl_lock);
		error = space_map_load(vd->vdev_dtl_sm,
		    vd->vdev_dtl[DTL_MISSING], SM_ALLOC);
		mutex_exit(&vd->vdev_dtl_lock);

		return (error);
	}

	for (int c = 0; c < vd->vdev_children; c++) {
		error = vdev_dtl_load(vd->vdev_child[c]);
		if (error != 0)
			break;
	}

	return (error);
}