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
struct TYPE_5__ {scalar_t__ vdev_initialize_state; int vdev_children; struct TYPE_5__** vdev_child; int /*<<< orphan*/  vdev_initialize_lock; TYPE_2__* vdev_spa; } ;
typedef  TYPE_1__ vdev_t ;
struct TYPE_6__ {int /*<<< orphan*/  spa_activities_lock; } ;
typedef  TYPE_2__ spa_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int B_FALSE ; 
 int B_TRUE ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RW_READER ; 
 int SCL_CONFIG ; 
 int SCL_STATE ; 
 scalar_t__ VDEV_INITIALIZE_ACTIVE ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_config_held (TYPE_2__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static boolean_t
spa_vdev_initializing_impl(vdev_t *vd)
{
	spa_t *spa = vd->vdev_spa;
	boolean_t initializing;

	ASSERT(spa_config_held(spa, SCL_CONFIG | SCL_STATE, RW_READER));
	ASSERT(MUTEX_HELD(&spa->spa_activities_lock));

	mutex_exit(&spa->spa_activities_lock);
	mutex_enter(&vd->vdev_initialize_lock);
	mutex_enter(&spa->spa_activities_lock);

	initializing = (vd->vdev_initialize_state == VDEV_INITIALIZE_ACTIVE);
	mutex_exit(&vd->vdev_initialize_lock);

	if (initializing)
		return (B_TRUE);

	for (int i = 0; i < vd->vdev_children; i++) {
		if (spa_vdev_initializing_impl(vd->vdev_child[i]))
			return (B_TRUE);
	}

	return (B_FALSE);
}