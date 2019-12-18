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
 int /*<<< orphan*/  Anum_dimension_hypertable_id_column_name_idx_hypertable_id ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  DIMENSION_HYPERTABLE_ID_COLUMN_NAME_IDX ; 
 int /*<<< orphan*/  F_INT4EQ ; 
 int /*<<< orphan*/  Int32GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dimension_scan_internal (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dimension_tuple_delete ; 

int
ts_dimension_delete_by_hypertable_id(int32 hypertable_id, bool delete_slices)
{
	ScanKeyData scankey[1];

	/* Perform an index scan to delete based on hypertable_id */
	ScanKeyInit(&scankey[0],
				Anum_dimension_hypertable_id_column_name_idx_hypertable_id,
				BTEqualStrategyNumber,
				F_INT4EQ,
				Int32GetDatum(hypertable_id));

	return dimension_scan_internal(scankey,
								   1,
								   dimension_tuple_delete,
								   &delete_slices,
								   0,
								   DIMENSION_HYPERTABLE_ID_COLUMN_NAME_IDX,
								   RowExclusiveLock,
								   CurrentMemoryContext);
}