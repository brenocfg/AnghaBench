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
typedef  int /*<<< orphan*/  StrategyNumber ;
typedef  int /*<<< orphan*/  DimensionVec ;

/* Variables and functions */
 int DIMENSION_VEC_DEFAULT_SIZE ; 
 int /*<<< orphan*/  dimension_slice_scan_with_strategies (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dimension_vec_tuple_found ; 
 int /*<<< orphan*/ * ts_dimension_vec_create (int) ; 
 int /*<<< orphan*/ * ts_dimension_vec_sort (int /*<<< orphan*/ **) ; 

DimensionVec *
ts_dimension_slice_scan_range_limit(int32 dimension_id, StrategyNumber start_strategy,
									int64 start_value, StrategyNumber end_strategy, int64 end_value,
									int limit)
{
	DimensionVec *slices = ts_dimension_vec_create(limit > 0 ? limit : DIMENSION_VEC_DEFAULT_SIZE);

	dimension_slice_scan_with_strategies(dimension_id,
										 start_strategy,
										 start_value,
										 end_strategy,
										 end_value,
										 &slices,
										 dimension_vec_tuple_found,
										 limit);

	return ts_dimension_vec_sort(&slices);
}