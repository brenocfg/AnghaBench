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
typedef  int /*<<< orphan*/  (* register_background_worker_callback_type ) (int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  pid_t ;
struct TYPE_4__ {scalar_t__ state; int /*<<< orphan*/ * handle; } ;
typedef  TYPE_1__ ScheduledBgwJob ;
typedef  int BgwHandleStatus ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
#define  BGWH_NOT_YET_STARTED 131 
#define  BGWH_POSTMASTER_DIED 130 
#define  BGWH_STARTED 129 
#define  BGWH_STOPPED 128 
 int /*<<< orphan*/  CommitTransactionCommand () ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ JOB_STATE_SCHEDULED ; 
 scalar_t__ JOB_STATE_STARTED ; 
 int /*<<< orphan*/  StartTransactionCommand () ; 
 int WaitForBackgroundWorkerStartup (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bgw_scheduler_on_postmaster_death () ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  scheduled_bgw_job_transition_state_to (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static void
scheduled_ts_bgw_job_start(ScheduledBgwJob *sjob,
						   register_background_worker_callback_type bgw_register)
{
	pid_t pid;
	BgwHandleStatus status;

	scheduled_bgw_job_transition_state_to(sjob, JOB_STATE_STARTED);

	if (sjob->state != JOB_STATE_STARTED)
		return;

	Assert(sjob->handle != NULL);
	if (bgw_register != NULL)
		bgw_register(sjob->handle);

	status = WaitForBackgroundWorkerStartup(sjob->handle, &pid);
	switch (status)
	{
		case BGWH_POSTMASTER_DIED:
			bgw_scheduler_on_postmaster_death();
			break;
		case BGWH_STARTED:
			/* all good */
			break;
		case BGWH_STOPPED:
			StartTransactionCommand();
			scheduled_bgw_job_transition_state_to(sjob, JOB_STATE_SCHEDULED);
			CommitTransactionCommand();
			break;
		case BGWH_NOT_YET_STARTED:
			/* should not be possible */
			elog(ERROR, "unexpected bgworker state %d", status);
			break;
	}
}