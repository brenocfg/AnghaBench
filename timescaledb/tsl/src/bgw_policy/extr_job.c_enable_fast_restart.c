#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  id; } ;
struct TYPE_11__ {TYPE_1__ fd; } ;
struct TYPE_9__ {int /*<<< orphan*/  last_start; } ;
struct TYPE_10__ {TYPE_2__ fd; } ;
typedef  TYPE_3__ BgwJobStat ;
typedef  TYPE_4__ BgwJob ;

/* Variables and functions */
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,char const*) ; 
 TYPE_3__* ts_bgw_job_stat_find (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_bgw_job_stat_set_next_start (TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
enable_fast_restart(BgwJob *job, const char *job_name)
{
	BgwJobStat *job_stat = ts_bgw_job_stat_find(job->fd.id);

	ts_bgw_job_stat_set_next_start(job, job_stat->fd.last_start);
	elog(LOG, "the %s job is scheduled to run again immediately", job_name);
}