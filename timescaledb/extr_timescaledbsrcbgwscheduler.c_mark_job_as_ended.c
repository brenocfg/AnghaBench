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
struct TYPE_3__ {int may_need_mark_end; int /*<<< orphan*/  job; } ;
typedef  TYPE_1__ ScheduledBgwJob ;
typedef  int /*<<< orphan*/  JobResult ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ts_bgw_job_stat_mark_end (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mark_job_as_ended(ScheduledBgwJob *sjob, JobResult res)
{
	Assert(sjob->may_need_mark_end);
	ts_bgw_job_stat_mark_end(&sjob->job, res);
	sjob->may_need_mark_end = false;
}