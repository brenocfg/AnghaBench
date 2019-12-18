#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {void* schemaname; void* relname; } ;
struct TYPE_9__ {int /*<<< orphan*/  schema_name; int /*<<< orphan*/  table_name; } ;
struct TYPE_13__ {TYPE_1__ fd; } ;
struct TYPE_12__ {TYPE_2__* space; } ;
struct TYPE_11__ {int kind; int /*<<< orphan*/  options; TYPE_8__* relation; } ;
struct TYPE_10__ {int /*<<< orphan*/  num_dimensions; } ;
typedef  TYPE_3__ ReindexStmt ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_4__ Hypertable ;
typedef  TYPE_5__ Chunk ;

/* Variables and functions */
 void* NameStr (int /*<<< orphan*/ ) ; 
#define  REINDEX_OBJECT_INDEX 129 
#define  REINDEX_OBJECT_TABLE 128 
 int /*<<< orphan*/  ReindexTable (TYPE_8__*,int /*<<< orphan*/ ) ; 
 TYPE_5__* ts_chunk_get_by_relid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
reindex_chunk(Hypertable *ht, Oid chunk_relid, void *arg)
{
	ReindexStmt *stmt = (ReindexStmt *) arg;
	Chunk *chunk = ts_chunk_get_by_relid(chunk_relid, ht->space->num_dimensions, true);

	switch (stmt->kind)
	{
		case REINDEX_OBJECT_TABLE:
			stmt->relation->relname = NameStr(chunk->fd.table_name);
			stmt->relation->schemaname = NameStr(chunk->fd.schema_name);
			ReindexTable(stmt->relation, stmt->options);
			break;
		case REINDEX_OBJECT_INDEX:
			/* Not supported, a.t.m. See note in process_reindex(). */
			break;
		default:
			break;
	}
}