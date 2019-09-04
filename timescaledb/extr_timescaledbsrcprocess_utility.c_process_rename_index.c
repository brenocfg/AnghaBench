#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  newname; } ;
typedef  TYPE_1__ RenameStmt ;
typedef  int /*<<< orphan*/  ProcessUtilityArgs ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Hypertable ;
typedef  int /*<<< orphan*/  Chunk ;
typedef  int /*<<< orphan*/  Cache ;

/* Variables and functions */
 int /*<<< orphan*/  IndexGetRelation (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_add_hypertable (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ts_chunk_get_by_relid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ts_chunk_index_rename (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_chunk_index_rename_parent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ts_hypertable_cache_get_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
process_rename_index(ProcessUtilityArgs *args, Cache *hcache, Oid relid, RenameStmt *stmt)
{
	Oid tablerelid = IndexGetRelation(relid, true);
	Hypertable *ht;

	if (!OidIsValid(tablerelid))
		return;

	ht = ts_hypertable_cache_get_entry(hcache, tablerelid);

	if (NULL != ht)
	{
		ts_chunk_index_rename_parent(ht, relid, stmt->newname);

		process_add_hypertable(args, ht);
	}
	else
	{
		Chunk *chunk = ts_chunk_get_by_relid(tablerelid, 0, false);

		if (NULL != chunk)
			ts_chunk_index_rename(chunk, relid, stmt->newname);
	}
}