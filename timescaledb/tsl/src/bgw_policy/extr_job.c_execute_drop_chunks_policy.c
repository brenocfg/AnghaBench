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
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_6__ {int /*<<< orphan*/  cascade_to_materializations; int /*<<< orphan*/  cascade; int /*<<< orphan*/  older_than; int /*<<< orphan*/  hypertable_id; } ;
struct TYPE_8__ {TYPE_1__ fd; } ;
struct TYPE_7__ {int /*<<< orphan*/  space; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_2__ Hypertable ;
typedef  int /*<<< orphan*/  Dimension ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  Cache ;
typedef  TYPE_3__ BgwPolicyDropChunks ;

/* Variables and functions */
 int /*<<< orphan*/  CommitTransactionCommand () ; 
 int /*<<< orphan*/  ERRCODE_TS_HYPERTABLE_NOT_EXIST ; 
 int /*<<< orphan*/  ERRCODE_TS_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GetTransactionSnapshot () ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  IsTransactionOrTransactionBlock () ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  PopActiveSnapshot () ; 
 int /*<<< orphan*/  PushActiveSnapshot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StartTransactionCommand () ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  get_rel_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hyperspace_get_open_dimension (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* ts_bgw_policy_drop_chunks_find_by_job (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_cache_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_chunk_do_drop_chunks (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_dimension_get_partition_type (int /*<<< orphan*/ *) ; 
 TYPE_2__* ts_hypertable_cache_get_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ts_hypertable_cache_pin () ; 
 int /*<<< orphan*/  ts_hypertable_id_to_relid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_interval_subtract_from_now (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool
execute_drop_chunks_policy(int32 job_id)
{
	bool started = false;
	BgwPolicyDropChunks *args;
	Oid table_relid;
	Hypertable *hypertable;
	Cache *hcache;
	Dimension *open_dim;

	if (!IsTransactionOrTransactionBlock())
	{
		started = true;
		StartTransactionCommand();
		PushActiveSnapshot(GetTransactionSnapshot());
	}

	/* Get the arguments from the drop_chunks_policy table */
	args = ts_bgw_policy_drop_chunks_find_by_job(job_id);

	if (args == NULL)
		ereport(ERROR,
				(errcode(ERRCODE_TS_INTERNAL_ERROR),
				 errmsg("could not run drop_chunks policy #%d because no args in policy table",
						job_id)));

	table_relid = ts_hypertable_id_to_relid(args->fd.hypertable_id);
	hcache = ts_hypertable_cache_pin();
	hypertable = ts_hypertable_cache_get_entry(hcache, table_relid);
	/* First verify that the hypertable corresponds to a valid table */
	if (hypertable == NULL)
		ereport(ERROR,
				(errcode(ERRCODE_TS_HYPERTABLE_NOT_EXIST),
				 errmsg("could not run drop_chunks policy #%d because \"%s\" is not a hypertable",
						job_id,
						get_rel_name(table_relid))));

	open_dim = hyperspace_get_open_dimension(hypertable->space, 0);
	ts_chunk_do_drop_chunks(table_relid,
							ts_interval_subtract_from_now(&args->fd.older_than, open_dim),
							(Datum) 0,
							ts_dimension_get_partition_type(open_dim),
							InvalidOid,
							args->fd.cascade,
							args->fd.cascade_to_materializations,
							LOG);

	ts_cache_release(hcache);
	elog(LOG, "completed dropping chunks");

	if (started)
	{
		PopActiveSnapshot();
		CommitTransactionCommand();
	}
	return true;
}