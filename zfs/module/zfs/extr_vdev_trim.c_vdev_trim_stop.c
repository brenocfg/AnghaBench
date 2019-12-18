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
typedef  scalar_t__ vdev_trim_state_t ;
struct TYPE_9__ {int /*<<< orphan*/  vdev_trim_exit_wanted; int /*<<< orphan*/ * vdev_trim_thread; TYPE_1__* vdev_ops; int /*<<< orphan*/  vdev_trim_lock; int /*<<< orphan*/  vdev_spa; } ;
typedef  TYPE_2__ vdev_t ;
typedef  int /*<<< orphan*/  list_t ;
struct TYPE_8__ {int vdev_op_leaf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  B_TRUE ; 
 int MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RW_WRITER ; 
 int SCL_CONFIG ; 
 int SCL_STATE ; 
 scalar_t__ VDEV_TRIM_CANCELED ; 
 int /*<<< orphan*/  list_insert_tail (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  spa_config_held (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_namespace_lock ; 
 int vdev_is_concrete (TYPE_2__*) ; 
 int /*<<< orphan*/  vdev_trim_change_state (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_trim_stop_wait_impl (TYPE_2__*) ; 

void
vdev_trim_stop(vdev_t *vd, vdev_trim_state_t tgt_state, list_t *vd_list)
{
	ASSERT(!spa_config_held(vd->vdev_spa, SCL_CONFIG|SCL_STATE, RW_WRITER));
	ASSERT(MUTEX_HELD(&vd->vdev_trim_lock));
	ASSERT(vd->vdev_ops->vdev_op_leaf);
	ASSERT(vdev_is_concrete(vd));

	/*
	 * Allow cancel requests to proceed even if the trim thread has
	 * stopped.
	 */
	if (vd->vdev_trim_thread == NULL && tgt_state != VDEV_TRIM_CANCELED)
		return;

	vdev_trim_change_state(vd, tgt_state, 0, 0, 0);
	vd->vdev_trim_exit_wanted = B_TRUE;

	if (vd_list == NULL) {
		vdev_trim_stop_wait_impl(vd);
	} else {
		ASSERT(MUTEX_HELD(&spa_namespace_lock));
		list_insert_tail(vd_list, vd);
	}
}