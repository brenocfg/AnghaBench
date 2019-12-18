#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ int32 ;
struct TYPE_23__ {int /*<<< orphan*/  older_than; int /*<<< orphan*/  hypertable_id; } ;
struct TYPE_26__ {TYPE_6__ fd; } ;
struct TYPE_22__ {int /*<<< orphan*/  table_name; int /*<<< orphan*/  schema_name; } ;
struct TYPE_25__ {TYPE_5__ fd; int /*<<< orphan*/  table_id; } ;
struct TYPE_20__ {int /*<<< orphan*/  data; } ;
struct TYPE_19__ {int /*<<< orphan*/  data; } ;
struct TYPE_21__ {TYPE_3__ table_name; TYPE_2__ schema_name; } ;
struct TYPE_24__ {TYPE_4__ fd; } ;
struct TYPE_18__ {int id; } ;
struct TYPE_17__ {TYPE_1__ fd; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_7__ Hypertable ;
typedef  TYPE_8__ Chunk ;
typedef  int /*<<< orphan*/  Cache ;
typedef  TYPE_9__ BgwPolicyCompressChunks ;
typedef  TYPE_10__ BgwJob ;

/* Variables and functions */
 int /*<<< orphan*/  CommitTransactionCommand () ; 
 int /*<<< orphan*/  ERRCODE_TS_HYPERTABLE_NOT_EXIST ; 
 int /*<<< orphan*/  ERRCODE_TS_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GetTransactionSnapshot () ; 
 scalar_t__ INVALID_CHUNK_ID ; 
 int /*<<< orphan*/  IsTransactionOrTransactionBlock () ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  NOTICE ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PopActiveSnapshot () ; 
 int /*<<< orphan*/  PushActiveSnapshot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StartTransactionCommand () ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_fast_restart (TYPE_10__*,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int,...) ; 
 scalar_t__ get_chunk_to_compress (TYPE_7__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_rel_name (int /*<<< orphan*/ ) ; 
 TYPE_9__* ts_bgw_policy_compress_chunks_find_by_job (int) ; 
 int /*<<< orphan*/  ts_cache_release (int /*<<< orphan*/ *) ; 
 TYPE_8__* ts_chunk_get_by_id (scalar_t__,int /*<<< orphan*/ ,int) ; 
 TYPE_7__* ts_hypertable_cache_get_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ts_hypertable_cache_pin () ; 
 int /*<<< orphan*/  ts_hypertable_id_to_relid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsl_compress_chunk_wrapper (int /*<<< orphan*/ ,int) ; 

bool
execute_compress_chunks_policy(BgwJob *job)
{
	bool started = false;
	BgwPolicyCompressChunks *args;
	Oid table_relid;
	Hypertable *ht;
	Cache *hcache;
	int32 chunkid;
	Chunk *chunk = NULL;
	int job_id = job->fd.id;

	if (!IsTransactionOrTransactionBlock())
	{
		started = true;
		StartTransactionCommand();
		PushActiveSnapshot(GetTransactionSnapshot());
	}

	/* Get the arguments from the compress_chunks_policy table */
	args = ts_bgw_policy_compress_chunks_find_by_job(job_id);

	if (args == NULL)
		ereport(ERROR,
				(errcode(ERRCODE_TS_INTERNAL_ERROR),
				 errmsg("could not run compress_chunks policy #%d because no args in policy table",
						job_id)));

	table_relid = ts_hypertable_id_to_relid(args->fd.hypertable_id);
	hcache = ts_hypertable_cache_pin();
	ht = ts_hypertable_cache_get_entry(hcache, table_relid);
	/* First verify that the hypertable corresponds to a valid table */
	if (ht == NULL)
		ereport(ERROR,
				(errcode(ERRCODE_TS_HYPERTABLE_NOT_EXIST),
				 errmsg("could not run compress_chunks policy #%d because \"%s\" is not a "
						"hypertable",
						job_id,
						get_rel_name(table_relid))));

	chunkid = get_chunk_to_compress(ht, &args->fd.older_than);
	if (chunkid == INVALID_CHUNK_ID)
	{
		elog(NOTICE,
			 "no chunks for hypertable %s.%s that satisfy compress chunk policy",
			 ht->fd.schema_name.data,
			 ht->fd.table_name.data);
	}
	else
	{
		chunk = ts_chunk_get_by_id(chunkid, 0, true);
		tsl_compress_chunk_wrapper(chunk->table_id, false);
		elog(LOG,
			 "completed compressing chunk %s.%s",
			 NameStr(chunk->fd.schema_name),
			 NameStr(chunk->fd.table_name));
	}

	chunkid = get_chunk_to_compress(ht, &args->fd.older_than);
	if (chunkid != INVALID_CHUNK_ID)
		enable_fast_restart(job, "compress_chunks");

	ts_cache_release(hcache);
	if (started)
	{
		PopActiveSnapshot();
		CommitTransactionCommand();
	}
	return true;
}