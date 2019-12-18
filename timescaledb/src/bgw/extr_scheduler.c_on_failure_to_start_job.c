#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  id; } ;
struct TYPE_8__ {TYPE_1__ fd; } ;
struct TYPE_9__ {TYPE_2__ job; } ;
typedef  TYPE_3__ ScheduledBgwJob ;

/* Variables and functions */
 int /*<<< orphan*/  CommitTransactionCommand () ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  JOB_FAILURE ; 
 int /*<<< orphan*/  JOB_STATE_SCHEDULED ; 
 int /*<<< orphan*/  StartTransactionCommand () ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_job_as_ended (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scheduled_bgw_job_transition_state_to (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_bgw_job_get_share_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
on_failure_to_start_job(ScheduledBgwJob *sjob)
{
	StartTransactionCommand();
	if (!ts_bgw_job_get_share_lock(sjob->job.fd.id, CurrentMemoryContext))
		elog(WARNING,
			 "scheduler detected that job %d was deleted while failing to start",
			 sjob->job.fd.id);
	else
		mark_job_as_ended(sjob, JOB_FAILURE);
	scheduled_bgw_job_transition_state_to(sjob, JOB_STATE_SCHEDULED);
	CommitTransactionCommand();
}