#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  id; } ;
struct TYPE_6__ {TYPE_1__ fd; } ;
struct TYPE_7__ {int may_need_mark_end; TYPE_2__ job; } ;
typedef  TYPE_3__ ScheduledBgwJob ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ts_bgw_job_stat_mark_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mark_job_as_started(ScheduledBgwJob *sjob)
{
	Assert(!sjob->may_need_mark_end);
	ts_bgw_job_stat_mark_start(sjob->job.fd.id);
	sjob->may_need_mark_end = true;
}