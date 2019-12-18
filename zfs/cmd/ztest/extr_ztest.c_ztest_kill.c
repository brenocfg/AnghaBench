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
struct TYPE_3__ {int /*<<< orphan*/  zs_space; int /*<<< orphan*/  zs_alloc; } ;
typedef  TYPE_1__ ztest_shared_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  metaslab_class_get_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  metaslab_class_get_space (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_namespace_lock ; 
 int /*<<< orphan*/  spa_normal_class (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_write_cachefile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ztest_spa ; 

__attribute__((used)) static void
ztest_kill(ztest_shared_t *zs)
{
	zs->zs_alloc = metaslab_class_get_alloc(spa_normal_class(ztest_spa));
	zs->zs_space = metaslab_class_get_space(spa_normal_class(ztest_spa));

	/*
	 * Before we kill off ztest, make sure that the config is updated.
	 * See comment above spa_write_cachefile().
	 */
	mutex_enter(&spa_namespace_lock);
	spa_write_cachefile(ztest_spa, B_FALSE, B_FALSE);
	mutex_exit(&spa_namespace_lock);

	(void) kill(getpid(), SIGKILL);
}