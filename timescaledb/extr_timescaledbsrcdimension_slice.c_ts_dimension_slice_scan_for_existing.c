#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  range_end; int /*<<< orphan*/  range_start; int /*<<< orphan*/  dimension_id; } ;
struct TYPE_7__ {TYPE_1__ fd; } ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  TYPE_2__ DimensionSlice ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Anum_dimension_slice_dimension_id_range_start_range_end_idx_dimension_id ; 
 int /*<<< orphan*/  Anum_dimension_slice_dimension_id_range_start_range_end_idx_range_end ; 
 int /*<<< orphan*/  Anum_dimension_slice_dimension_id_range_start_range_end_idx_range_start ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  DIMENSION_SLICE_DIMENSION_ID_RANGE_START_RANGE_END_IDX ; 
 int /*<<< orphan*/  F_INT4EQ ; 
 int /*<<< orphan*/  F_INT8EQ ; 
 int /*<<< orphan*/  Int32GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Int64GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dimension_slice_fill ; 
 int /*<<< orphan*/  dimension_slice_scan_limit_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,TYPE_2__**,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

DimensionSlice *
ts_dimension_slice_scan_for_existing(DimensionSlice *slice)
{
	ScanKeyData scankey[3];

	ScanKeyInit(&scankey[0],
				Anum_dimension_slice_dimension_id_range_start_range_end_idx_dimension_id,
				BTEqualStrategyNumber,
				F_INT4EQ,
				Int32GetDatum(slice->fd.dimension_id));
	ScanKeyInit(&scankey[1],
				Anum_dimension_slice_dimension_id_range_start_range_end_idx_range_start,
				BTEqualStrategyNumber,
				F_INT8EQ,
				Int64GetDatum(slice->fd.range_start));
	ScanKeyInit(&scankey[2],
				Anum_dimension_slice_dimension_id_range_start_range_end_idx_range_end,
				BTEqualStrategyNumber,
				F_INT8EQ,
				Int64GetDatum(slice->fd.range_end));

	dimension_slice_scan_limit_internal(DIMENSION_SLICE_DIMENSION_ID_RANGE_START_RANGE_END_IDX,
										scankey,
										3,
										dimension_slice_fill,
										&slice,
										1,
										AccessShareLock,
										CurrentMemoryContext);

	return slice;
}