#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32 ;
struct TYPE_5__ {int /*<<< orphan*/  id; } ;
struct TYPE_6__ {TYPE_1__ fd; } ;
typedef  TYPE_2__ BgwJob ;

/* Variables and functions */
 int /*<<< orphan*/  CommitTransactionCommand () ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  IsTransactionOrTransactionBlock () ; 
 int /*<<< orphan*/  StartTransactionCommand () ; 
 int continuous_agg_materialize (scalar_t__,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_fast_restart (TYPE_2__*,char*) ; 
 scalar_t__ ts_continuous_agg_job_find_materializtion_by_job_id (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
execute_materialize_continuous_aggregate(BgwJob *job)
{
	bool started = false;
	int32 materialization_id;
	bool finshed_all_materialization;

	if (!IsTransactionOrTransactionBlock())
	{
		started = true;
		StartTransactionCommand();
	}

	materialization_id = ts_continuous_agg_job_find_materializtion_by_job_id(job->fd.id);
	if (materialization_id < 0)
		elog(ERROR, "cannot find continuous aggregate for job %d", job->fd.id);

	CommitTransactionCommand();

	/* always materialize verbosely for now */
	finshed_all_materialization = continuous_agg_materialize(materialization_id, true);

	StartTransactionCommand();

	if (!finshed_all_materialization)
		enable_fast_restart(job, "materialize continuous aggregate");

	if (started)
		CommitTransactionCommand();

	return true;
}