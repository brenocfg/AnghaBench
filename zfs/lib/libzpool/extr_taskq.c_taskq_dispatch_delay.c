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
typedef  int /*<<< orphan*/  uint_t ;
typedef  int /*<<< orphan*/  taskqid_t ;
typedef  int /*<<< orphan*/  taskq_t ;
typedef  int /*<<< orphan*/  task_func_t ;
typedef  int /*<<< orphan*/  clock_t ;

/* Variables and functions */

taskqid_t
taskq_dispatch_delay(taskq_t *tq,  task_func_t func, void *arg, uint_t tqflags,
    clock_t expire_time)
{
	return (0);
}