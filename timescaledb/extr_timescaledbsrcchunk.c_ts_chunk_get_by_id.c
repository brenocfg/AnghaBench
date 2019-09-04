#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  int32 ;
typedef  int /*<<< orphan*/  int16 ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  Chunk ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_chunk_idx_id ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  CHUNK_ID_INDEX ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  F_INT4EQ ; 
 int /*<<< orphan*/  Int32GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * chunk_scan_find (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

Chunk *
ts_chunk_get_by_id(int32 id, int16 num_constraints, bool fail_if_not_found)
{
	ScanKeyData scankey[1];

	/*
	 * Perform an index scan on chunk id.
	 */
	ScanKeyInit(&scankey[0], Anum_chunk_idx_id, BTEqualStrategyNumber, F_INT4EQ, Int32GetDatum(id));

	return chunk_scan_find(CHUNK_ID_INDEX,
						   scankey,
						   1,
						   num_constraints,
						   CurrentMemoryContext,
						   fail_if_not_found);
}