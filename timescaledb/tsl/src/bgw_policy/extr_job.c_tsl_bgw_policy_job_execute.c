#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  job_type; int /*<<< orphan*/  id; } ;
struct TYPE_9__ {int bgw_type; TYPE_1__ fd; } ;
typedef  TYPE_2__ BgwJob ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
#define  JOB_TYPE_COMPRESS_CHUNKS 131 
#define  JOB_TYPE_CONTINUOUS_AGGREGATE 130 
#define  JOB_TYPE_DROP_CHUNKS 129 
#define  JOB_TYPE_REORDER 128 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 scalar_t__ bgw_policy_job_requires_enterprise_license (TYPE_2__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int execute_compress_chunks_policy (TYPE_2__*) ; 
 int execute_drop_chunks_policy (int /*<<< orphan*/ ) ; 
 int execute_materialize_continuous_aggregate (TYPE_2__*) ; 
 int execute_reorder_policy (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  license_enforce_enterprise_enabled () ; 
 int /*<<< orphan*/  license_print_expiration_warning_if_needed () ; 
 int /*<<< orphan*/  pg_unreachable () ; 
 int /*<<< orphan*/  reorder_chunk ; 

bool
tsl_bgw_policy_job_execute(BgwJob *job)
{
	if (bgw_policy_job_requires_enterprise_license(job))
		license_enforce_enterprise_enabled();
	license_print_expiration_warning_if_needed();

	switch (job->bgw_type)
	{
		case JOB_TYPE_REORDER:
			return execute_reorder_policy(job, reorder_chunk, true);
		case JOB_TYPE_DROP_CHUNKS:
			return execute_drop_chunks_policy(job->fd.id);
		case JOB_TYPE_CONTINUOUS_AGGREGATE:
			return execute_materialize_continuous_aggregate(job);
		case JOB_TYPE_COMPRESS_CHUNKS:
			return execute_compress_chunks_policy(job);
		default:
			elog(ERROR,
				 "scheduler tried to run an invalid job type: \"%s\"",
				 NameStr(job->fd.job_type));
	}
	pg_unreachable();
}