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
struct TYPE_3__ {int tq_nthreads; int /*<<< orphan*/ ** tq_threadlist; } ;
typedef  TYPE_1__ taskq_t ;
typedef  int /*<<< orphan*/  kthread_t ;

/* Variables and functions */
 scalar_t__ taskq_now ; 

int
taskq_member(taskq_t *tq, kthread_t *t)
{
	int i;

	if (taskq_now)
		return (1);

	for (i = 0; i < tq->tq_nthreads; i++)
		if (tq->tq_threadlist[i] == t)
			return (1);

	return (0);
}