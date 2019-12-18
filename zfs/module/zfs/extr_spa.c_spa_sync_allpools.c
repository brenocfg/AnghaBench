#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  spa_t ;

/* Variables and functions */
 int /*<<< orphan*/  FTAG ; 
 scalar_t__ POOL_STATE_ACTIVE ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_get_dsl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_namespace_lock ; 
 int /*<<< orphan*/ * spa_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_open_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ spa_state (int /*<<< orphan*/ *) ; 
 scalar_t__ spa_suspended (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_writeable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txg_wait_synced (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
spa_sync_allpools(void)
{
	spa_t *spa = NULL;
	mutex_enter(&spa_namespace_lock);
	while ((spa = spa_next(spa)) != NULL) {
		if (spa_state(spa) != POOL_STATE_ACTIVE ||
		    !spa_writeable(spa) || spa_suspended(spa))
			continue;
		spa_open_ref(spa, FTAG);
		mutex_exit(&spa_namespace_lock);
		txg_wait_synced(spa_get_dsl(spa), 0);
		mutex_enter(&spa_namespace_lock);
		spa_close(spa, FTAG);
	}
	mutex_exit(&spa_namespace_lock);
}