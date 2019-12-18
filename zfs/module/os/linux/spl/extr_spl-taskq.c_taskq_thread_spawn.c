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
struct TYPE_4__ {int tq_flags; scalar_t__ tq_nthreads; int tq_nspawn; scalar_t__ tq_maxthreads; } ;
typedef  TYPE_1__ taskq_t ;

/* Variables and functions */
 int TASKQ_ACTIVE ; 
 int TASKQ_DYNAMIC ; 
 int /*<<< orphan*/  TQ_NOSLEEP ; 
 int /*<<< orphan*/  dynamic_taskq ; 
 int /*<<< orphan*/  taskq_dispatch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskq_thread_spawn_task ; 

__attribute__((used)) static int
taskq_thread_spawn(taskq_t *tq)
{
	int spawning = 0;

	if (!(tq->tq_flags & TASKQ_DYNAMIC))
		return (0);

	if ((tq->tq_nthreads + tq->tq_nspawn < tq->tq_maxthreads) &&
	    (tq->tq_flags & TASKQ_ACTIVE)) {
		spawning = (++tq->tq_nspawn);
		taskq_dispatch(dynamic_taskq, taskq_thread_spawn_task,
		    tq, TQ_NOSLEEP);
	}

	return (spawning);
}