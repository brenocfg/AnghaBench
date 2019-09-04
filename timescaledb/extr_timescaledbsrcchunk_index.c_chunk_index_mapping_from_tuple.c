#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  tuple; } ;
typedef  TYPE_1__ TupleInfo ;
struct TYPE_13__ {int /*<<< orphan*/  hypertable_relid; int /*<<< orphan*/  table_id; } ;
struct TYPE_12__ {int /*<<< orphan*/  hypertableoid; void* parent_indexoid; void* indexoid; int /*<<< orphan*/  chunkoid; } ;
struct TYPE_11__ {int /*<<< orphan*/  hypertable_index_name; int /*<<< orphan*/  index_name; int /*<<< orphan*/  chunk_id; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_2__ FormData_chunk_index ;
typedef  TYPE_3__ ChunkIndexMapping ;
typedef  TYPE_4__ Chunk ;

/* Variables and functions */
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_rel_namespace (int /*<<< orphan*/ ) ; 
 void* get_relname_relid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* palloc (int) ; 
 TYPE_4__* ts_chunk_get_by_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ChunkIndexMapping *
chunk_index_mapping_from_tuple(TupleInfo *ti, ChunkIndexMapping *cim)
{
	FormData_chunk_index *chunk_index = (FormData_chunk_index *) GETSTRUCT(ti->tuple);
	Chunk *chunk = ts_chunk_get_by_id(chunk_index->chunk_id, 0, true);
	Oid nspoid_chunk = get_rel_namespace(chunk->table_id);
	Oid nspoid_hyper = get_rel_namespace(chunk->hypertable_relid);

	if (cim == NULL)
	{
		cim = palloc(sizeof(ChunkIndexMapping));
	}
	cim->chunkoid = chunk->table_id;
	cim->indexoid = get_relname_relid(NameStr(chunk_index->index_name), nspoid_chunk);
	cim->parent_indexoid =
		get_relname_relid(NameStr(chunk_index->hypertable_index_name), nspoid_hyper);
	cim->hypertableoid = chunk->hypertable_relid;

	return cim;
}