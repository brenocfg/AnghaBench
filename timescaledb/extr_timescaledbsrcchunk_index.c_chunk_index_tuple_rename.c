#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  scanrel; int /*<<< orphan*/  tuple; } ;
typedef  TYPE_2__ TupleInfo ;
struct TYPE_8__ {int /*<<< orphan*/  table_name; int /*<<< orphan*/  schema_name; } ;
struct TYPE_12__ {TYPE_1__ fd; } ;
struct TYPE_11__ {char const* newname; scalar_t__ isparent; } ;
struct TYPE_10__ {int /*<<< orphan*/  index_name; int /*<<< orphan*/  hypertable_index_name; int /*<<< orphan*/  chunk_id; } ;
typedef  int /*<<< orphan*/  ScanTupleResult ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_3__ FormData_chunk_index ;
typedef  TYPE_4__ ChunkIndexRenameInfo ;
typedef  TYPE_5__ Chunk ;

/* Variables and functions */
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RenameRelationInternal (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  SCAN_CONTINUE ; 
 int /*<<< orphan*/  SCAN_DONE ; 
 char* chunk_index_choose_name (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_namespace_oid (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  get_relname_relid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_copytuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_freetuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  namestrcpy (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  ts_catalog_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* ts_chunk_get_by_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ScanTupleResult
chunk_index_tuple_rename(TupleInfo *ti, void *data)
{
	ChunkIndexRenameInfo *info = data;
	HeapTuple tuple = heap_copytuple(ti->tuple);
	FormData_chunk_index *chunk_index = (FormData_chunk_index *) GETSTRUCT(tuple);

	if (info->isparent)
	{
		/*
		 * If the renaming is for a hypertable index, we also rename all
		 * corresponding chunk indexes
		 */
		Chunk *chunk = ts_chunk_get_by_id(chunk_index->chunk_id, 0, true);
		Oid chunk_schemaoid = get_namespace_oid(NameStr(chunk->fd.schema_name), false);
		const char *chunk_index_name =
			chunk_index_choose_name(NameStr(chunk->fd.table_name), info->newname, chunk_schemaoid);
		Oid chunk_indexrelid = get_relname_relid(NameStr(chunk_index->index_name), chunk_schemaoid);

		/* Update the metadata */
		namestrcpy(&chunk_index->index_name, chunk_index_name);
		namestrcpy(&chunk_index->hypertable_index_name, info->newname);

		/* Rename the chunk index */
		RenameRelationInternal(chunk_indexrelid, chunk_index_name, false);
	}
	else
		namestrcpy(&chunk_index->index_name, info->newname);

	ts_catalog_update(ti->scanrel, tuple);
	heap_freetuple(tuple);

	if (info->isparent)
		return SCAN_CONTINUE;

	return SCAN_DONE;
}