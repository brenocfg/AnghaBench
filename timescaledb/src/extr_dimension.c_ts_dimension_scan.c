#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32 ;
typedef  int /*<<< orphan*/  int16 ;
struct TYPE_5__ {int /*<<< orphan*/  num_dimensions; int /*<<< orphan*/  dimensions; } ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_1__ Hyperspace ;
typedef  int /*<<< orphan*/  Dimension ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Anum_dimension_hypertable_id_column_name_idx_hypertable_id ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  DIMENSION_HYPERTABLE_ID_COLUMN_NAME_IDX ; 
 int /*<<< orphan*/  F_INT4EQ ; 
 int /*<<< orphan*/  Int32GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmp_dimension_id ; 
 int /*<<< orphan*/  dimension_scan_internal (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dimension_tuple_found ; 
 TYPE_1__* hyperspace_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

Hyperspace *
ts_dimension_scan(int32 hypertable_id, Oid main_table_relid, int16 num_dimensions,
				  MemoryContext mctx)
{
	Hyperspace *space = hyperspace_create(hypertable_id, main_table_relid, num_dimensions, mctx);
	ScanKeyData scankey[1];

	/* Perform an index scan on hypertable_id. */
	ScanKeyInit(&scankey[0],
				Anum_dimension_hypertable_id_column_name_idx_hypertable_id,
				BTEqualStrategyNumber,
				F_INT4EQ,
				Int32GetDatum(hypertable_id));

	dimension_scan_internal(scankey,
							1,
							dimension_tuple_found,
							space,
							num_dimensions,
							DIMENSION_HYPERTABLE_ID_COLUMN_NAME_IDX,
							AccessShareLock,
							mctx);

	/* Sort dimensions in ascending order to allow binary search lookups */
	qsort(space->dimensions, space->num_dimensions, sizeof(Dimension), cmp_dimension_id);

	return space;
}