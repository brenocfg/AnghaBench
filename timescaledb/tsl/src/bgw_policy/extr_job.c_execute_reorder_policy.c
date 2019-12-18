#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_18__ ;
typedef  struct TYPE_20__   TYPE_11__ ;
typedef  struct TYPE_19__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  (* reorder_func ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_26__ {int /*<<< orphan*/  data; } ;
struct TYPE_25__ {int /*<<< orphan*/  data; } ;
struct TYPE_27__ {TYPE_5__ table_name; TYPE_4__ schema_name; } ;
struct TYPE_30__ {TYPE_6__ fd; int /*<<< orphan*/  table_id; } ;
struct TYPE_21__ {int /*<<< orphan*/  data; } ;
struct TYPE_23__ {int /*<<< orphan*/  data; } ;
struct TYPE_24__ {TYPE_18__ schema_name; TYPE_2__ table_name; } ;
struct TYPE_29__ {TYPE_3__ fd; } ;
struct TYPE_28__ {int /*<<< orphan*/  job_id; TYPE_18__ hypertable_index_name; int /*<<< orphan*/  hypertable_id; } ;
struct TYPE_22__ {int /*<<< orphan*/  id; } ;
struct TYPE_20__ {TYPE_1__ fd; } ;
struct TYPE_19__ {TYPE_7__ fd; } ;
typedef  TYPE_8__ Hypertable ;
typedef  TYPE_9__ Chunk ;
typedef  TYPE_10__ BgwPolicyReorder ;
typedef  TYPE_11__ BgwJob ;

/* Variables and functions */
 int /*<<< orphan*/  CommitTransactionCommand () ; 
 int /*<<< orphan*/  ERRCODE_TS_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  IsTransactionOrTransactionBlock () ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  NOTICE ; 
 int /*<<< orphan*/  NameStr (TYPE_18__) ; 
 int /*<<< orphan*/  StartTransactionCommand () ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_fast_restart (TYPE_11__*,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int get_chunk_id_to_reorder (int /*<<< orphan*/ ,TYPE_8__*) ; 
 int /*<<< orphan*/  get_namespace_oid (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  get_relname_relid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_bgw_policy_chunk_stats_record_job_run (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_10__* ts_bgw_policy_reorder_find_by_job (int /*<<< orphan*/ ) ; 
 TYPE_9__* ts_chunk_get_by_id (int,int /*<<< orphan*/ ,int) ; 
 TYPE_8__* ts_hypertable_get_by_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_timer_get_current_timestamp () ; 

bool
execute_reorder_policy(BgwJob *job, reorder_func reorder, bool fast_continue)
{
	int chunk_id;
	bool started = false;
	BgwPolicyReorder *args;
	Hypertable *ht;
	Chunk *chunk;
	int32 job_id = job->fd.id;

	if (!IsTransactionOrTransactionBlock())
	{
		started = true;
		StartTransactionCommand();
	}

	/* Get the arguments from the reorder_policy table */
	args = ts_bgw_policy_reorder_find_by_job(job_id);

	if (args == NULL)
		ereport(ERROR,
				(errcode(ERRCODE_TS_INTERNAL_ERROR),
				 errmsg("could not run reorder policy #%d because no args in policy table",
						job_id)));

	ht = ts_hypertable_get_by_id(args->fd.hypertable_id);

	/* Find a chunk to reorder in the selected hypertable */
	chunk_id = get_chunk_id_to_reorder(args->fd.job_id, ht);

	if (chunk_id == -1)
	{
		elog(NOTICE,
			 "no chunks need reordering for hypertable %s.%s",
			 ht->fd.schema_name.data,
			 ht->fd.table_name.data);
		goto commit;
	}

	/*
	 * NOTE: We pass the Oid of the hypertable's index, and the true reorder
	 * function should translate this to the Oid of the index on the specific
	 * chunk.
	 */
	chunk = ts_chunk_get_by_id(chunk_id, 0, false);
	elog(LOG, "reordering chunk %s.%s", chunk->fd.schema_name.data, chunk->fd.table_name.data);
	reorder(chunk->table_id,
			get_relname_relid(NameStr(args->fd.hypertable_index_name),
							  get_namespace_oid(NameStr(ht->fd.schema_name), false)),
			false,
			InvalidOid,
			InvalidOid,
			InvalidOid);
	elog(LOG,
		 "completed reordering chunk %s.%s",
		 chunk->fd.schema_name.data,
		 chunk->fd.table_name.data);

	/* Now update chunk_stats table */
	ts_bgw_policy_chunk_stats_record_job_run(args->fd.job_id,
											 chunk_id,
											 ts_timer_get_current_timestamp());

	if (fast_continue && get_chunk_id_to_reorder(args->fd.job_id, ht) != -1)
		enable_fast_restart(job, "reorder");

commit:
	if (started)
		CommitTransactionCommand();

	return true;
}