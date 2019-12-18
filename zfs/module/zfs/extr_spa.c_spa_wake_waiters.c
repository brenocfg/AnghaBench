#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ spa_waiters; int /*<<< orphan*/  spa_activities_lock; int /*<<< orphan*/  spa_waiters_cancel; int /*<<< orphan*/  spa_waiters_cv; int /*<<< orphan*/  spa_activities_cv; } ;
typedef  TYPE_1__ spa_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

void
spa_wake_waiters(spa_t *spa)
{
	mutex_enter(&spa->spa_activities_lock);
	spa->spa_waiters_cancel = B_TRUE;
	cv_broadcast(&spa->spa_activities_cv);
	while (spa->spa_waiters != 0)
		cv_wait(&spa->spa_waiters_cv, &spa->spa_activities_lock);
	spa->spa_waiters_cancel = B_FALSE;
	mutex_exit(&spa->spa_activities_lock);
}