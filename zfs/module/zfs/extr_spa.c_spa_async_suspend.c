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
typedef  int /*<<< orphan*/  zthr_t ;
struct TYPE_4__ {int /*<<< orphan*/ * spa_livelist_condense_zthr; int /*<<< orphan*/ * spa_livelist_delete_zthr; int /*<<< orphan*/ * spa_checkpoint_discard_zthr; int /*<<< orphan*/ * spa_condense_zthr; int /*<<< orphan*/  spa_async_lock; int /*<<< orphan*/  spa_async_cv; int /*<<< orphan*/ * spa_async_thread; int /*<<< orphan*/  spa_async_suspended; } ;
typedef  TYPE_1__ spa_t ;

/* Variables and functions */
 int /*<<< orphan*/  cv_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_vdev_remove_suspend (TYPE_1__*) ; 
 int /*<<< orphan*/  zthr_cancel (int /*<<< orphan*/ *) ; 

void
spa_async_suspend(spa_t *spa)
{
	mutex_enter(&spa->spa_async_lock);
	spa->spa_async_suspended++;
	while (spa->spa_async_thread != NULL)
		cv_wait(&spa->spa_async_cv, &spa->spa_async_lock);
	mutex_exit(&spa->spa_async_lock);

	spa_vdev_remove_suspend(spa);

	zthr_t *condense_thread = spa->spa_condense_zthr;
	if (condense_thread != NULL)
		zthr_cancel(condense_thread);

	zthr_t *discard_thread = spa->spa_checkpoint_discard_zthr;
	if (discard_thread != NULL)
		zthr_cancel(discard_thread);

	zthr_t *ll_delete_thread = spa->spa_livelist_delete_zthr;
	if (ll_delete_thread != NULL)
		zthr_cancel(ll_delete_thread);

	zthr_t *ll_condense_thread = spa->spa_livelist_condense_zthr;
	if (ll_condense_thread != NULL)
		zthr_cancel(ll_condense_thread);
}