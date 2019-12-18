#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {size_t vdev_children; struct TYPE_7__** vdev_child; int /*<<< orphan*/  vdev_initialize_lock; TYPE_1__* vdev_ops; } ;
typedef  TYPE_2__ vdev_t ;
typedef  int /*<<< orphan*/  vdev_initializing_state_t ;
typedef  size_t uint64_t ;
typedef  int /*<<< orphan*/  list_t ;
struct TYPE_6__ {scalar_t__ vdev_op_leaf; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vdev_initialize_stop (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ vdev_is_concrete (TYPE_2__*) ; 

__attribute__((used)) static void
vdev_initialize_stop_all_impl(vdev_t *vd, vdev_initializing_state_t tgt_state,
    list_t *vd_list)
{
	if (vd->vdev_ops->vdev_op_leaf && vdev_is_concrete(vd)) {
		mutex_enter(&vd->vdev_initialize_lock);
		vdev_initialize_stop(vd, tgt_state, vd_list);
		mutex_exit(&vd->vdev_initialize_lock);
		return;
	}

	for (uint64_t i = 0; i < vd->vdev_children; i++) {
		vdev_initialize_stop_all_impl(vd->vdev_child[i], tgt_state,
		    vd_list);
	}
}