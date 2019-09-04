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
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_4__ {int /*<<< orphan*/  cascade_to_materializations; int /*<<< orphan*/  cascade; int /*<<< orphan*/  older_than; int /*<<< orphan*/  hypertable_id; } ;
struct TYPE_5__ {TYPE_1__ fd; } ;
typedef  TYPE_2__ BgwPolicyDropChunks ;

/* Variables and functions */
 int /*<<< orphan*/  CommitTransactionCommand () ; 
 int /*<<< orphan*/  ERRCODE_TS_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  INTERVALOID ; 
 int /*<<< orphan*/  IntervalPGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  IsTransactionOrTransactionBlock () ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  StartTransactionCommand () ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* ts_bgw_policy_drop_chunks_find_by_job (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_chunk_do_drop_chunks (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_hypertable_id_to_relid (int /*<<< orphan*/ ) ; 

bool
execute_drop_chunks_policy(int32 job_id)
{
	bool started = false;
	BgwPolicyDropChunks *args;

	if (!IsTransactionOrTransactionBlock())
	{
		started = true;
		StartTransactionCommand();
	}

	/* Get the arguments from the drop_chunks_policy table */
	args = ts_bgw_policy_drop_chunks_find_by_job(job_id);

	if (args == NULL)
		ereport(ERROR,
				(errcode(ERRCODE_TS_INTERNAL_ERROR),
				 errmsg("could not run drop_chunks policy #%d because no args in policy table",
						job_id)));

	ts_chunk_do_drop_chunks(ts_hypertable_id_to_relid(args->fd.hypertable_id),
							IntervalPGetDatum(&args->fd.older_than),
							0,
							INTERVALOID,
							InvalidOid,
							args->fd.cascade,
							args->fd.cascade_to_materializations,
							LOG);
	elog(LOG, "completed dropping chunks");

	if (started)
		CommitTransactionCommand();
	return true;
}