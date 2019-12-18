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
typedef  int /*<<< orphan*/  tuple_found_func ;
typedef  scalar_t__ int64 ;
typedef  int /*<<< orphan*/  int32 ;
typedef  scalar_t__ StrategyNumber ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Anum_dimension_slice_dimension_id_range_start_range_end_idx_dimension_id ; 
 int /*<<< orphan*/  Anum_dimension_slice_dimension_id_range_start_range_end_idx_range_end ; 
 int /*<<< orphan*/  Anum_dimension_slice_dimension_id_range_start_range_end_idx_range_start ; 
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 scalar_t__ BTEqualStrategyNumber ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  DIMENSION_SLICE_DIMENSION_ID_RANGE_START_RANGE_END_IDX ; 
 int /*<<< orphan*/  F_INT4EQ ; 
 int /*<<< orphan*/  INT8OID ; 
 int /*<<< orphan*/  INTEGER_BTREE_FAM_OID ; 
 int /*<<< orphan*/  Int32GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Int64GetDatum (scalar_t__) ; 
 scalar_t__ InvalidStrategy ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ PG_INT64_MAX ; 
 scalar_t__ REMAP_LAST_COORDINATE (scalar_t__) ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dimension_slice_scan_limit_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_opcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_opfamily_member (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
dimension_slice_scan_with_strategies(int32 dimension_id, StrategyNumber start_strategy,
									 int64 start_value, StrategyNumber end_strategy,
									 int64 end_value, void *data, tuple_found_func tuple_found,
									 int limit)
{
	ScanKeyData scankey[3];
	int nkeys = 1;

	/*
	 * Perform an index scan for slices matching the dimension's ID and which
	 * enclose the coordinate.
	 */
	ScanKeyInit(&scankey[0],
				Anum_dimension_slice_dimension_id_range_start_range_end_idx_dimension_id,
				BTEqualStrategyNumber,
				F_INT4EQ,
				Int32GetDatum(dimension_id));
	if (start_strategy != InvalidStrategy)
	{
		Oid opno = get_opfamily_member(INTEGER_BTREE_FAM_OID, INT8OID, INT8OID, start_strategy);
		Oid proc = get_opcode(opno);

		Assert(OidIsValid(proc));

		ScanKeyInit(&scankey[nkeys++],
					Anum_dimension_slice_dimension_id_range_start_range_end_idx_range_start,
					start_strategy,
					proc,
					Int64GetDatum(start_value));
	}
	if (end_strategy != InvalidStrategy)
	{
		Oid opno = get_opfamily_member(INTEGER_BTREE_FAM_OID, INT8OID, INT8OID, end_strategy);
		Oid proc = get_opcode(opno);

		Assert(OidIsValid(proc));

		/*
		 * range_end is stored as exclusive, so add 1 to the value being
		 * searched. Also avoid overflow
		 */
		if (end_value != PG_INT64_MAX)
		{
			end_value++;

			/*
			 * If getting as input INT64_MAX-1, need to remap the incremented
			 * value back to INT64_MAX-1
			 */
			end_value = REMAP_LAST_COORDINATE(end_value);
		}
		else
		{
			/*
			 * The point with INT64_MAX gets mapped to INT64_MAX-1 so
			 * incrementing that gets you to INT_64MAX
			 */
			end_value = PG_INT64_MAX;
		}

		ScanKeyInit(&scankey[nkeys++],
					Anum_dimension_slice_dimension_id_range_start_range_end_idx_range_end,
					end_strategy,
					proc,
					Int64GetDatum(end_value));
	}

	dimension_slice_scan_limit_internal(DIMENSION_SLICE_DIMENSION_ID_RANGE_START_RANGE_END_IDX,
										scankey,
										nkeys,
										tuple_found,
										data,
										limit,
										AccessShareLock,
										CurrentMemoryContext);
}