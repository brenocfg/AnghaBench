#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TimestampTz ;
struct TYPE_4__ {scalar_t__ consecutive_crashes; int /*<<< orphan*/  next_start; } ;
struct TYPE_5__ {TYPE_1__ fd; } ;
typedef  TYPE_2__ BgwJobStat ;
typedef  int /*<<< orphan*/  BgwJob ;

/* Variables and functions */
 int /*<<< orphan*/  DT_NOBEGIN ; 
 int /*<<< orphan*/  calculate_next_start_on_crash (scalar_t__,int /*<<< orphan*/ *) ; 

TimestampTz
ts_bgw_job_stat_next_start(BgwJobStat *jobstat, BgwJob *job)
{
	if (jobstat == NULL)
		/* Never previously run - run right away */
		return DT_NOBEGIN;

	if (jobstat->fd.consecutive_crashes > 0)
		return calculate_next_start_on_crash(jobstat->fd.consecutive_crashes, job);

	return jobstat->fd.next_start;
}