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
 int /*<<< orphan*/  poll (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ spa_suspended (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_exit () ; 
 scalar_t__ zfs_abd_scatter_enabled ; 
 scalar_t__ zfs_compressed_arc_enabled ; 
 int /*<<< orphan*/  ztest_exiting ; 
 scalar_t__ ztest_random (int) ; 
 int /*<<< orphan*/  ztest_resume (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ztest_resume_thread(void *arg)
{
	spa_t *spa = arg;

	while (!ztest_exiting) {
		if (spa_suspended(spa))
			ztest_resume(spa);
		(void) poll(NULL, 0, 100);

		/*
		 * Periodically change the zfs_compressed_arc_enabled setting.
		 */
		if (ztest_random(10) == 0)
			zfs_compressed_arc_enabled = ztest_random(2);

		/*
		 * Periodically change the zfs_abd_scatter_enabled setting.
		 */
		if (ztest_random(10) == 0)
			zfs_abd_scatter_enabled = ztest_random(2);
	}

	thread_exit();
}