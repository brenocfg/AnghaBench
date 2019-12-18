#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ spa_state; } ;
typedef  TYPE_1__ spa_t ;

/* Variables and functions */
 scalar_t__ POOL_STATE_ACTIVE ; 
 int /*<<< orphan*/  mmp_signal_thread (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_namespace_lock ; 
 TYPE_1__* spa_next (TYPE_1__*) ; 

void
mmp_signal_all_threads(void)
{
	spa_t *spa = NULL;

	mutex_enter(&spa_namespace_lock);
	while ((spa = spa_next(spa))) {
		if (spa->spa_state == POOL_STATE_ACTIVE)
			mmp_signal_thread(spa);
	}
	mutex_exit(&spa_namespace_lock);
}