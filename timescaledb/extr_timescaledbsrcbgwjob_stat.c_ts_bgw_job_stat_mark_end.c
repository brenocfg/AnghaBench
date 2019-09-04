#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
struct TYPE_8__ {TYPE_1__ fd; } ;
struct TYPE_7__ {int /*<<< orphan*/  result; TYPE_3__* job; } ;
typedef  TYPE_2__ JobResultCtx ;
typedef  int /*<<< orphan*/  JobResult ;
typedef  TYPE_3__ BgwJob ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  bgw_job_stat_scan_job_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bgw_job_stat_tuple_mark_end ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void
ts_bgw_job_stat_mark_end(BgwJob *job, JobResult result)
{
	JobResultCtx res = {
		.job = job,
		.result = result,
	};

	if (!bgw_job_stat_scan_job_id(job->fd.id,
								  bgw_job_stat_tuple_mark_end,
								  NULL,
								  &res,
								  RowExclusiveLock))
		elog(ERROR, "unable to find job statistics for job %d", job->fd.id);
}