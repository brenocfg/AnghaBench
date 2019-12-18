#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ spa_state; } ;
typedef  TYPE_1__ spa_t ;

/* Variables and functions */
 int /*<<< orphan*/  FTAG ; 
 scalar_t__ POOL_STATE_UNINITIALIZED ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_async_suspend (TYPE_1__*) ; 
 int /*<<< orphan*/  spa_close (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_deactivate (TYPE_1__*) ; 
 int /*<<< orphan*/  spa_namespace_lock ; 
 TYPE_1__* spa_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_open_ref (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_remove (TYPE_1__*) ; 
 int /*<<< orphan*/  spa_unload (TYPE_1__*) ; 

void
spa_evict_all(void)
{
	spa_t *spa;

	/*
	 * Remove all cached state.  All pools should be closed now,
	 * so every spa in the AVL tree should be unreferenced.
	 */
	mutex_enter(&spa_namespace_lock);
	while ((spa = spa_next(NULL)) != NULL) {
		/*
		 * Stop async tasks.  The async thread may need to detach
		 * a device that's been replaced, which requires grabbing
		 * spa_namespace_lock, so we must drop it here.
		 */
		spa_open_ref(spa, FTAG);
		mutex_exit(&spa_namespace_lock);
		spa_async_suspend(spa);
		mutex_enter(&spa_namespace_lock);
		spa_close(spa, FTAG);

		if (spa->spa_state != POOL_STATE_UNINITIALIZED) {
			spa_unload(spa);
			spa_deactivate(spa);
		}
		spa_remove(spa);
	}
	mutex_exit(&spa_namespace_lock);
}