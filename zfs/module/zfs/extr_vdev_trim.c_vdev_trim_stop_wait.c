#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  vdev_trim_lock; } ;
typedef  TYPE_1__ vdev_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  list_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 TYPE_1__* list_remove_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_namespace_lock ; 
 int /*<<< orphan*/  vdev_trim_stop_wait_impl (TYPE_1__*) ; 

void
vdev_trim_stop_wait(spa_t *spa, list_t *vd_list)
{
	vdev_t *vd;

	ASSERT(MUTEX_HELD(&spa_namespace_lock));

	while ((vd = list_remove_head(vd_list)) != NULL) {
		mutex_enter(&vd->vdev_trim_lock);
		vdev_trim_stop_wait_impl(vd);
		mutex_exit(&vd->vdev_trim_lock);
	}
}