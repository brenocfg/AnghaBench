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
struct TYPE_4__ {int /*<<< orphan*/  spa_suspend_lock; int /*<<< orphan*/  spa_suspend_cv; } ;
typedef  TYPE_1__ spa_t ;

/* Variables and functions */
 int /*<<< orphan*/  cv_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 scalar_t__ spa_suspended (TYPE_1__*) ; 

void
zio_resume_wait(spa_t *spa)
{
	mutex_enter(&spa->spa_suspend_lock);
	while (spa_suspended(spa))
		cv_wait(&spa->spa_suspend_cv, &spa->spa_suspend_lock);
	mutex_exit(&spa->spa_suspend_lock);
}