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
typedef  int /*<<< orphan*/  pid_t ;
typedef  scalar_t__ BgwHandleStatus ;
typedef  int /*<<< orphan*/  BackgroundWorkerHandle ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ BGWH_POSTMASTER_DIED ; 
 scalar_t__ BGWH_STARTED ; 
 scalar_t__ BGWH_STOPPED ; 
 scalar_t__ WaitForBackgroundWorkerStartup (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bgw_on_postmaster_death () ; 

__attribute__((used)) static void
wait_for_background_worker_startup(BackgroundWorkerHandle *handle, pid_t *pidp)
{
	BgwHandleStatus status;

	if (handle == NULL)
		status = BGWH_STOPPED;
	else
		status = WaitForBackgroundWorkerStartup(handle, pidp);

	/*
	 * We don't care whether we get BGWH_STOPPED or BGWH_STARTED here, because
	 * the worker could have started and stopped very quickly before we read
	 * it. We can't get BGWH_NOT_YET_STARTED as that's what we're waiting for.
	 * We do care if the Postmaster died however.
	 */

	if (status == BGWH_POSTMASTER_DIED)
		bgw_on_postmaster_death();

	Assert(status == BGWH_STOPPED || status == BGWH_STARTED);
	return;
}