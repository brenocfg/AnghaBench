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
typedef  int /*<<< orphan*/  ScheduledBgwJob ;

/* Variables and functions */
 int /*<<< orphan*/  CommitTransactionCommand () ; 
 int /*<<< orphan*/  JOB_FAILURE ; 
 int /*<<< orphan*/  JOB_STATE_SCHEDULED ; 
 int /*<<< orphan*/  StartTransactionCommand () ; 
 int /*<<< orphan*/  mark_job_as_ended (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scheduled_bgw_job_transition_state_to (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
on_failure_to_start_job(ScheduledBgwJob *sjob)
{
	StartTransactionCommand();
	mark_job_as_ended(sjob, JOB_FAILURE);
	scheduled_bgw_job_transition_state_to(sjob, JOB_STATE_SCHEDULED);
	CommitTransactionCommand();
}