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
typedef  int /*<<< orphan*/  ScanKeyData ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_dimension_slice_id_idx_id ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  DIMENSION_SLICE_ID_IDX ; 
 int /*<<< orphan*/  F_INT4EQ ; 
 int /*<<< orphan*/  Int32GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dimension_slice_scan_limit_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dimension_slice_tuple_delete ; 

int
ts_dimension_slice_delete_by_id(int32 dimension_slice_id, bool delete_constraints)
{
	ScanKeyData scankey[1];

	ScanKeyInit(&scankey[0],
				Anum_dimension_slice_id_idx_id,
				BTEqualStrategyNumber,
				F_INT4EQ,
				Int32GetDatum(dimension_slice_id));

	return dimension_slice_scan_limit_internal(DIMENSION_SLICE_ID_IDX,
											   scankey,
											   1,
											   dimension_slice_tuple_delete,
											   &delete_constraints,
											   1,
											   RowExclusiveLock,
											   CurrentMemoryContext);
}