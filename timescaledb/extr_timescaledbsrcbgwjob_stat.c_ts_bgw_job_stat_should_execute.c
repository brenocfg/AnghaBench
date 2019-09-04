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
typedef  int /*<<< orphan*/  BgwJobStat ;
typedef  int /*<<< orphan*/  BgwJob ;

/* Variables and functions */

bool
ts_bgw_job_stat_should_execute(BgwJobStat *jobstat, BgwJob *job)
{
	/*
	 * Stub to allow the system to disable jobs based on the number of crashes
	 * or failures.
	 */
	return true;
}