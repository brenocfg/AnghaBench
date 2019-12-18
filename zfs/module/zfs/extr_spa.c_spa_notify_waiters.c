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
struct TYPE_3__ {int /*<<< orphan*/  spa_activities_lock; int /*<<< orphan*/  spa_activities_cv; } ;
typedef  TYPE_1__ spa_t ;

/* Variables and functions */
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

void
spa_notify_waiters(spa_t *spa)
{
	/*
	 * Acquiring spa_activities_lock here prevents the cv_broadcast from
	 * happening between the waiting thread's check and cv_wait.
	 */
	mutex_enter(&spa->spa_activities_lock);
	cv_broadcast(&spa->spa_activities_cv);
	mutex_exit(&spa->spa_activities_lock);
}