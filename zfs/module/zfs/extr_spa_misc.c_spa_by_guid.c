#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_7__ {scalar_t__ spa_state; int /*<<< orphan*/ * spa_pending_vdev; int /*<<< orphan*/ * spa_root_vdev; } ;
typedef  TYPE_1__ spa_t ;
typedef  int /*<<< orphan*/  avl_tree_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 TYPE_1__* AVL_NEXT (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 scalar_t__ POOL_STATE_UNINITIALIZED ; 
 TYPE_1__* avl_first (int /*<<< orphan*/ *) ; 
 scalar_t__ spa_guid (TYPE_1__*) ; 
 int /*<<< orphan*/  spa_namespace_avl ; 
 int /*<<< orphan*/  spa_namespace_lock ; 
 int /*<<< orphan*/ * vdev_lookup_by_guid (int /*<<< orphan*/ *,scalar_t__) ; 

spa_t *
spa_by_guid(uint64_t pool_guid, uint64_t device_guid)
{
	spa_t *spa;
	avl_tree_t *t = &spa_namespace_avl;

	ASSERT(MUTEX_HELD(&spa_namespace_lock));

	for (spa = avl_first(t); spa != NULL; spa = AVL_NEXT(t, spa)) {
		if (spa->spa_state == POOL_STATE_UNINITIALIZED)
			continue;
		if (spa->spa_root_vdev == NULL)
			continue;
		if (spa_guid(spa) == pool_guid) {
			if (device_guid == 0)
				break;

			if (vdev_lookup_by_guid(spa->spa_root_vdev,
			    device_guid) != NULL)
				break;

			/*
			 * Check any devices we may be in the process of adding.
			 */
			if (spa->spa_pending_vdev) {
				if (vdev_lookup_by_guid(spa->spa_pending_vdev,
				    device_guid) != NULL)
					break;
			}
		}
	}

	return (spa);
}