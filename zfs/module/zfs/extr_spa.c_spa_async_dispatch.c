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
struct TYPE_5__ {int /*<<< orphan*/  spa_async_lock; int /*<<< orphan*/ * spa_async_thread; int /*<<< orphan*/  spa_async_suspended; } ;
typedef  TYPE_1__ spa_t ;

/* Variables and functions */
 int /*<<< orphan*/  TS_RUN ; 
 int /*<<< orphan*/  maxclsyspri ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p0 ; 
 int /*<<< orphan*/ * rootdir ; 
 scalar_t__ spa_async_tasks_pending (TYPE_1__*) ; 
 int /*<<< orphan*/  spa_async_thread ; 
 int /*<<< orphan*/ * thread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
spa_async_dispatch(spa_t *spa)
{
	mutex_enter(&spa->spa_async_lock);
	if (spa_async_tasks_pending(spa) &&
	    !spa->spa_async_suspended &&
	    spa->spa_async_thread == NULL &&
	    rootdir != NULL)
		spa->spa_async_thread = thread_create(NULL, 0,
		    spa_async_thread, spa, 0, &p0, TS_RUN, maxclsyspri);
	mutex_exit(&spa->spa_async_lock);
}