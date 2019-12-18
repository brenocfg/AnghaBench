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
struct TYPE_4__ {int /*<<< orphan*/  job_type; } ;
struct TYPE_5__ {int bgw_type; TYPE_1__ fd; } ;
typedef  TYPE_2__ BgwJob ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
#define  JOB_TYPE_COMPRESS_CHUNKS 131 
#define  JOB_TYPE_CONTINUOUS_AGGREGATE 130 
#define  JOB_TYPE_DROP_CHUNKS 129 
#define  JOB_TYPE_REORDER 128 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  license_print_expiration_warning_if_needed () ; 
 int /*<<< orphan*/  pg_unreachable () ; 

__attribute__((used)) static bool
bgw_policy_job_requires_enterprise_license(BgwJob *job)
{
	license_print_expiration_warning_if_needed();

	switch (job->bgw_type)
	{
		case JOB_TYPE_REORDER:
			return true;
		case JOB_TYPE_DROP_CHUNKS:
			return true;
		case JOB_TYPE_CONTINUOUS_AGGREGATE:
			return false;
		case JOB_TYPE_COMPRESS_CHUNKS:
			return false;
		default:
			elog(ERROR,
				 "scheduler could not determine the license type for job type: \"%s\"",
				 NameStr(job->fd.job_type));
	}
	pg_unreachable();
}