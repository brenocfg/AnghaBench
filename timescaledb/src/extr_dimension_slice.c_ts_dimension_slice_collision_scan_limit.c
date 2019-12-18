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
typedef  int /*<<< orphan*/  int64 ;
typedef  int /*<<< orphan*/  int32 ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  DimensionVec ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Anum_dimension_slice_dimension_id_range_start_range_end_idx_dimension_id ; 
 int /*<<< orphan*/  Anum_dimension_slice_dimension_id_range_start_range_end_idx_range_end ; 
 int /*<<< orphan*/  Anum_dimension_slice_dimension_id_range_start_range_end_idx_range_start ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  BTGreaterStrategyNumber ; 
 int /*<<< orphan*/  BTLessStrategyNumber ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  DIMENSION_SLICE_DIMENSION_ID_RANGE_START_RANGE_END_IDX ; 
 int DIMENSION_VEC_DEFAULT_SIZE ; 
 int /*<<< orphan*/  F_INT4EQ ; 
 int /*<<< orphan*/  F_INT8GT ; 
 int /*<<< orphan*/  F_INT8LT ; 
 int /*<<< orphan*/  Int32GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Int64GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dimension_slice_scan_limit_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dimension_vec_tuple_found ; 
 int /*<<< orphan*/ * ts_dimension_vec_create (int) ; 
 int /*<<< orphan*/ * ts_dimension_vec_sort (int /*<<< orphan*/ **) ; 

DimensionVec *
ts_dimension_slice_collision_scan_limit(int32 dimension_id, int64 range_start, int64 range_end,
										int limit)
{
	ScanKeyData scankey[3];
	DimensionVec *slices = ts_dimension_vec_create(limit > 0 ? limit : DIMENSION_VEC_DEFAULT_SIZE);

	ScanKeyInit(&scankey[0],
				Anum_dimension_slice_dimension_id_range_start_range_end_idx_dimension_id,
				BTEqualStrategyNumber,
				F_INT4EQ,
				Int32GetDatum(dimension_id));
	ScanKeyInit(&scankey[1],
				Anum_dimension_slice_dimension_id_range_start_range_end_idx_range_start,
				BTLessStrategyNumber,
				F_INT8LT,
				Int64GetDatum(range_end));
	ScanKeyInit(&scankey[2],
				Anum_dimension_slice_dimension_id_range_start_range_end_idx_range_end,
				BTGreaterStrategyNumber,
				F_INT8GT,
				Int64GetDatum(range_start));

	dimension_slice_scan_limit_internal(DIMENSION_SLICE_DIMENSION_ID_RANGE_START_RANGE_END_IDX,
										scankey,
										3,
										dimension_vec_tuple_found,
										&slices,
										limit,
										AccessShareLock,
										CurrentMemoryContext);

	return ts_dimension_vec_sort(&slices);
}