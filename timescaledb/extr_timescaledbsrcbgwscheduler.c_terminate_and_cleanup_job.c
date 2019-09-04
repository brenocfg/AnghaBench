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
struct TYPE_4__ {int may_need_mark_end; int /*<<< orphan*/ * handle; } ;
typedef  TYPE_1__ ScheduledBgwJob ;

/* Variables and functions */
 int /*<<< orphan*/  TerminateBackgroundWorker (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WaitForBackgroundWorkerShutdown (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  worker_state_cleanup (TYPE_1__*) ; 

__attribute__((used)) static void
terminate_and_cleanup_job(ScheduledBgwJob *sjob)
{
	if (sjob->handle != NULL)
	{
		TerminateBackgroundWorker(sjob->handle);
		WaitForBackgroundWorkerShutdown(sjob->handle);
	}
	sjob->may_need_mark_end = false;
	worker_state_cleanup(sjob);
}