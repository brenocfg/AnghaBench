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
typedef  int uint_t ;
struct TYPE_3__ {int spa_async_tasks; scalar_t__ spa_ccw_fail_time; } ;
typedef  TYPE_1__ spa_t ;
typedef  int hrtime_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int B_FALSE ; 
 int NANOSEC ; 
 int SPA_ASYNC_CONFIG_UPDATE ; 
 int gethrtime () ; 
 scalar_t__ zfs_ccw_retry_interval ; 

__attribute__((used)) static boolean_t
spa_async_tasks_pending(spa_t *spa)
{
	uint_t non_config_tasks;
	uint_t config_task;
	boolean_t config_task_suspended;

	non_config_tasks = spa->spa_async_tasks & ~SPA_ASYNC_CONFIG_UPDATE;
	config_task = spa->spa_async_tasks & SPA_ASYNC_CONFIG_UPDATE;
	if (spa->spa_ccw_fail_time == 0) {
		config_task_suspended = B_FALSE;
	} else {
		config_task_suspended =
		    (gethrtime() - spa->spa_ccw_fail_time) <
		    ((hrtime_t)zfs_ccw_retry_interval * NANOSEC);
	}

	return (non_config_tasks || (config_task && !config_task_suspended));
}