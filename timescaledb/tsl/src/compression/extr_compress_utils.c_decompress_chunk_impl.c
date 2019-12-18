#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ hypertable_id; scalar_t__ compressed_chunk_id; int /*<<< orphan*/  id; } ;
struct TYPE_14__ {TYPE_2__ fd; int /*<<< orphan*/  table_id; } ;
struct TYPE_11__ {scalar_t__ id; int /*<<< orphan*/  compressed_hypertable_id; } ;
struct TYPE_13__ {int /*<<< orphan*/  main_table_relid; TYPE_1__ fd; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_3__ Hypertable ;
typedef  TYPE_4__ Chunk ;
typedef  int /*<<< orphan*/  Cache ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  CHUNK ; 
 int /*<<< orphan*/  DROP_RESTRICT ; 
 int /*<<< orphan*/  ERRCODE_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE ; 
 int /*<<< orphan*/  ERRCODE_TS_HYPERTABLE_NOT_EXIST ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GetUserId () ; 
 int /*<<< orphan*/  HYPERTABLE_COMPRESSION ; 
 scalar_t__ INVALID_CHUNK_ID ; 
 int /*<<< orphan*/  LockRelationOid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NOTICE ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  catalog_get_table_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chunk_dml_trigger_drop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decompress_chunk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int /*<<< orphan*/  get_rel_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_cache_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_catalog_get () ; 
 int /*<<< orphan*/  ts_chunk_drop (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 TYPE_4__* ts_chunk_get_by_id (scalar_t__,int /*<<< orphan*/ ,int) ; 
 TYPE_4__* ts_chunk_get_by_relid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ts_chunk_set_compressed_chunk (TYPE_4__*,scalar_t__,int) ; 
 int /*<<< orphan*/  ts_compression_chunk_size_delete (int /*<<< orphan*/ ) ; 
 TYPE_3__* ts_hypertable_cache_get_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ts_hypertable_cache_pin () ; 
 TYPE_3__* ts_hypertable_get_by_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_hypertable_permissions_check (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
decompress_chunk_impl(Oid uncompressed_hypertable_relid, Oid uncompressed_chunk_relid,
					  bool if_compressed)
{
	Cache *hcache = ts_hypertable_cache_pin();
	Hypertable *uncompressed_hypertable =
		ts_hypertable_cache_get_entry(hcache, uncompressed_hypertable_relid);
	Hypertable *compressed_hypertable;
	Chunk *uncompressed_chunk;
	Chunk *compressed_chunk;

	if (uncompressed_hypertable == NULL)
		ereport(ERROR,
				(errcode(ERRCODE_TS_HYPERTABLE_NOT_EXIST),
				 errmsg("table \"%s\" is not a hypertable",
						get_rel_name(uncompressed_hypertable_relid))));

	ts_hypertable_permissions_check(uncompressed_hypertable->main_table_relid, GetUserId());

	compressed_hypertable =
		ts_hypertable_get_by_id(uncompressed_hypertable->fd.compressed_hypertable_id);
	if (compressed_hypertable == NULL)
		ereport(ERROR, (errcode(ERRCODE_INTERNAL_ERROR), errmsg("missing compressed hypertable")));

	uncompressed_chunk = ts_chunk_get_by_relid(uncompressed_chunk_relid, 0, true);
	if (uncompressed_chunk == NULL)
		ereport(ERROR,
				(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
				 errmsg("table \"%s\" is not a chunk", get_rel_name(uncompressed_chunk_relid))));

	if (uncompressed_chunk->fd.hypertable_id != uncompressed_hypertable->fd.id)
		elog(ERROR, "hypertable and chunk do not match");

	if (uncompressed_chunk->fd.compressed_chunk_id == INVALID_CHUNK_ID)
	{
		ts_cache_release(hcache);
		ereport((if_compressed ? NOTICE : ERROR),
				(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
				 errmsg("chunk \"%s\" is not compressed", get_rel_name(uncompressed_chunk_relid))));
		return false;
	}

	compressed_chunk = ts_chunk_get_by_id(uncompressed_chunk->fd.compressed_chunk_id, 0, true);

	/* acquire locks on src and compress hypertable and src chunk */
	LockRelationOid(uncompressed_hypertable->main_table_relid, AccessShareLock);
	LockRelationOid(compressed_hypertable->main_table_relid, AccessShareLock);
	LockRelationOid(uncompressed_chunk->table_id, AccessShareLock); /*upgrade when needed */

	/* aquire locks on catalog tables to keep till end of txn */
	LockRelationOid(catalog_get_table_id(ts_catalog_get(), HYPERTABLE_COMPRESSION),
					AccessShareLock);
	LockRelationOid(catalog_get_table_id(ts_catalog_get(), CHUNK), RowExclusiveLock);

	chunk_dml_trigger_drop(uncompressed_chunk->table_id);
	decompress_chunk(compressed_chunk->table_id, uncompressed_chunk->table_id);
	ts_compression_chunk_size_delete(uncompressed_chunk->fd.id);
	ts_chunk_set_compressed_chunk(uncompressed_chunk, INVALID_CHUNK_ID, true);
	ts_chunk_drop(compressed_chunk, DROP_RESTRICT, -1);

	ts_cache_release(hcache);
	return true;
}