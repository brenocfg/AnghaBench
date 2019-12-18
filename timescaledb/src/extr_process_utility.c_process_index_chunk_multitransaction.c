#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_8__ {int /*<<< orphan*/  id; } ;
struct TYPE_11__ {TYPE_2__ fd; } ;
struct TYPE_9__ {scalar_t__ max_chunks; int /*<<< orphan*/  indexinfo; int /*<<< orphan*/  ht_hasoid; int /*<<< orphan*/  n_ht_atts; int /*<<< orphan*/  barrier_table; int /*<<< orphan*/  multitransaction; } ;
struct TYPE_7__ {int /*<<< orphan*/  objectId; } ;
struct TYPE_10__ {TYPE_3__ extended_options; int /*<<< orphan*/  main_table_relid; TYPE_1__ obj; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_4__ CreateIndexInfo ;
typedef  TYPE_5__ Chunk ;
typedef  int /*<<< orphan*/  CatalogSecurityContext ;

/* Variables and functions */
 int /*<<< orphan*/  AccessExclusiveLock ; 
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CommitTransactionCommand () ; 
 int /*<<< orphan*/  GetTransactionSnapshot () ; 
 int /*<<< orphan*/  NoLock ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PopActiveSnapshot () ; 
 int /*<<< orphan*/  PushActiveSnapshot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ShareLock ; 
 int /*<<< orphan*/  StartTransactionCommand () ; 
 scalar_t__ chunk_index_columns_changed (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relation_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relation_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_adjust_indexinfo_attnos (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_catalog_database_info_become_owner (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_catalog_database_info_get () ; 
 int /*<<< orphan*/  ts_catalog_restore_user (int /*<<< orphan*/ *) ; 
 TYPE_5__* ts_chunk_get_by_relid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ts_chunk_index_create_from_adjusted_index_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
process_index_chunk_multitransaction(int32 hypertable_id, Oid chunk_relid, void *arg)
{
	CreateIndexInfo *info = (CreateIndexInfo *) arg;
	CatalogSecurityContext sec_ctx;
	Chunk *chunk;
	Relation hypertable_index_rel;
	Relation chunk_rel;

	Assert(info->extended_options.multitransaction);

	/* Start a new transaction for each relation. */
	StartTransactionCommand();
	PushActiveSnapshot(GetTransactionSnapshot());

#ifdef DEBUG
	if (info->extended_options.max_chunks == 0)
	{
		PopActiveSnapshot();
		CommitTransactionCommand();
		return;
	}

	/*
	 * if max_chunks is < 0 then we're indexing all the chunks, if it's >= 0
	 * then we're only indexing some of the chunks, and leaving the root index
	 * marked as invalid
	 */
	if (info->extended_options.max_chunks > 0)
		info->extended_options.max_chunks -= 1;

	if (OidIsValid(info->extended_options.barrier_table))
	{
		/*
		 * For isolation tests, and debugging, it's useful to be able to
		 * pause CREATE INDEX immediately before it starts working on chunks.
		 * We acquire and immediately release a lock on a barrier table to do
		 * this.
		 */
		Relation barrier = relation_open(info->extended_options.barrier_table, AccessExclusiveLock);

		relation_close(barrier, AccessExclusiveLock);
	}
#endif

	/*
	 * Change user since chunks are typically located in an internal schema
	 * and chunk indexes require metadata changes. In the single-transaction
	 * case, we do this once for the entire table.
	 */
	ts_catalog_database_info_become_owner(ts_catalog_database_info_get(), &sec_ctx);

	/*
	 * Hold a lock on the hypertable index, and the chunk to prevent
	 * from being altered. Since we use the same relids across transactions,
	 * there is a potential issue if the id gets reassigned between one
	 * sub-transaction and the next. CLUSTER has a similar issue.
	 *
	 * We grab a ShareLock on the chunk, because that's what CREATE INDEX
	 * does. For the hypertable's index, we are ok using the weaker
	 * AccessShareLock, since we only need to prevent the index itself from
	 * being ALTERed or DROPed during this part of index creation.
	 */
	chunk_rel = relation_open(chunk_relid, ShareLock);
	hypertable_index_rel = relation_open(info->obj.objectId, AccessShareLock);

	chunk = ts_chunk_get_by_relid(chunk_relid, 0, true);

	/*
	 * use ts_chunk_index_create instead of ts_chunk_index_create_from_stmt to
	 * handle cases where the index is altered. Validation happens when
	 * creating the hypertable's index, which goes through the usual
	 * DefineIndex mechanism.
	 */
	if (chunk_index_columns_changed(info->extended_options.n_ht_atts,
									info->extended_options.ht_hasoid,
									RelationGetDescr(chunk_rel)))
		ts_adjust_indexinfo_attnos(info->extended_options.indexinfo,
								   info->main_table_relid,
								   hypertable_index_rel,
								   chunk_rel);

	ts_chunk_index_create_from_adjusted_index_info(hypertable_id,
												   hypertable_index_rel,
												   chunk->fd.id,
												   chunk_rel,
												   info->extended_options.indexinfo);

	relation_close(hypertable_index_rel, NoLock);
	relation_close(chunk_rel, NoLock);

	ts_catalog_restore_user(&sec_ctx);

	PopActiveSnapshot();
	CommitTransactionCommand();
}