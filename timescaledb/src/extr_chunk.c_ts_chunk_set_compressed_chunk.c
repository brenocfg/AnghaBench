#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
struct TYPE_5__ {TYPE_1__ fd; } ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  TYPE_2__ Chunk ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_chunk_idx_id ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  CHUNK_ID_INDEX ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  F_INT4EQ ; 
 int /*<<< orphan*/  ForwardScanDirection ; 
 int /*<<< orphan*/  INVALID_CHUNK_ID ; 
 int /*<<< orphan*/  Int32GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ chunk_scan_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chunk_set_compressed_id_in_tuple ; 

bool
ts_chunk_set_compressed_chunk(Chunk *chunk, int32 compressed_chunk_id, bool isnull)
{
	int32 compress_id;
	ScanKeyData scankey[1];
	ScanKeyInit(&scankey[0],
				Anum_chunk_idx_id,
				BTEqualStrategyNumber,
				F_INT4EQ,
				Int32GetDatum(chunk->fd.id));
	if (isnull)
		compress_id = INVALID_CHUNK_ID;
	else
		compress_id = compressed_chunk_id;
	return chunk_scan_internal(CHUNK_ID_INDEX,
							   scankey,
							   1,
							   chunk_set_compressed_id_in_tuple,
							   &compress_id,
							   0,
							   ForwardScanDirection,
							   RowExclusiveLock,
							   CurrentMemoryContext) > 0;
}