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
typedef  int /*<<< orphan*/  taskq_t ;
typedef  int /*<<< orphan*/  kthread_t ;

/* Variables and functions */
 int /*<<< orphan*/  taskq_tsd ; 
 scalar_t__ tsd_get_by_thread (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
taskq_member(taskq_t *tq, kthread_t *t)
{
	return (tq == (taskq_t *)tsd_get_by_thread(taskq_tsd, t));
}