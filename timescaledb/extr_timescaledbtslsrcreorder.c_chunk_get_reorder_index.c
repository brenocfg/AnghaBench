#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  table_id; } ;
struct TYPE_7__ {int /*<<< orphan*/  main_table_relid; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ Hypertable ;
typedef  int /*<<< orphan*/  ChunkIndexMapping ;
typedef  TYPE_2__ Chunk ;

/* Variables and functions */
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int ts_chunk_index_get_by_hypertable_indexrelid (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ts_chunk_index_get_by_indexrelid (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_indexing_find_clustered_index (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
chunk_get_reorder_index(Hypertable *ht, Chunk *chunk, Oid index_relid, ChunkIndexMapping *cim_out)
{
	/*
	 * Index search order: 1. Explicitly named index 2. Chunk cluster index 3.
	 * Hypertable cluster index
	 */
	if (OidIsValid(index_relid))
	{
		if (ts_chunk_index_get_by_indexrelid(chunk, index_relid, cim_out))
			return true;

		return ts_chunk_index_get_by_hypertable_indexrelid(chunk, index_relid, cim_out);
	}

	index_relid = ts_indexing_find_clustered_index(chunk->table_id);
	if (OidIsValid(index_relid))
		return ts_chunk_index_get_by_indexrelid(chunk, index_relid, cim_out);

	index_relid = ts_indexing_find_clustered_index(ht->main_table_relid);
	if (OidIsValid(index_relid))
		return ts_chunk_index_get_by_hypertable_indexrelid(chunk, index_relid, cim_out);

	return false;
}