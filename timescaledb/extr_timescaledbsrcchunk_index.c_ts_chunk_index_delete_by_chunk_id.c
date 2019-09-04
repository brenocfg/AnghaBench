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
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_3__ {int drop_index; } ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  TYPE_1__ ChunkIndexDeleteData ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_chunk_index_chunk_id_index_name_idx_chunk_id ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  CHUNK_INDEX_CHUNK_ID_INDEX_NAME_IDX ; 
 int /*<<< orphan*/  F_INT4EQ ; 
 int /*<<< orphan*/  Int32GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int chunk_index_scan_update (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  chunk_index_tuple_delete ; 

int
ts_chunk_index_delete_by_chunk_id(int32 chunk_id, bool drop_index)
{
	ScanKeyData scankey[1];
	ChunkIndexDeleteData data = {
		.drop_index = drop_index,
	};

	ScanKeyInit(&scankey[0],
				Anum_chunk_index_chunk_id_index_name_idx_chunk_id,
				BTEqualStrategyNumber,
				F_INT4EQ,
				Int32GetDatum(chunk_id));

	return chunk_index_scan_update(CHUNK_INDEX_CHUNK_ID_INDEX_NAME_IDX,
								   scankey,
								   1,
								   chunk_index_tuple_delete,
								   NULL,
								   &data);
}