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
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
struct TYPE_8__ {TYPE_1__ fd; } ;
struct TYPE_7__ {char const* oldname; char const* newname; } ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_2__ ChunkIndexRenameInfo ;
typedef  TYPE_3__ Chunk ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_chunk_index_chunk_id_index_name_idx_chunk_id ; 
 int /*<<< orphan*/  Anum_chunk_index_chunk_id_index_name_idx_index_name ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  CHUNK_INDEX_CHUNK_ID_INDEX_NAME_IDX ; 
 int /*<<< orphan*/  CStringGetDatum (char const*) ; 
 int /*<<< orphan*/  F_INT4EQ ; 
 int /*<<< orphan*/  F_NAMEEQ ; 
 int /*<<< orphan*/  Int32GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int chunk_index_scan_update (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  chunk_index_tuple_rename ; 
 char* get_rel_name (int /*<<< orphan*/ ) ; 

int
ts_chunk_index_rename(Chunk *chunk, Oid chunk_indexrelid, const char *newname)
{
	ScanKeyData scankey[2];
	const char *indexname = get_rel_name(chunk_indexrelid);
	ChunkIndexRenameInfo renameinfo = {
		.oldname = indexname,
		.newname = newname,
	};

	ScanKeyInit(&scankey[0],
				Anum_chunk_index_chunk_id_index_name_idx_chunk_id,
				BTEqualStrategyNumber,
				F_INT4EQ,
				Int32GetDatum(chunk->fd.id));
	ScanKeyInit(&scankey[1],
				Anum_chunk_index_chunk_id_index_name_idx_index_name,
				BTEqualStrategyNumber,
				F_NAMEEQ,
				CStringGetDatum(indexname));

	return chunk_index_scan_update(CHUNK_INDEX_CHUNK_ID_INDEX_NAME_IDX,
								   scankey,
								   2,
								   chunk_index_tuple_rename,
								   NULL,
								   &renameinfo);
}