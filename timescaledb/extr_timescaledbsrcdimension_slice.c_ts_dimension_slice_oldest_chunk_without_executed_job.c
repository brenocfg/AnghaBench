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
typedef  int /*<<< orphan*/  int64 ;
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_3__ {int chunk_id; int /*<<< orphan*/  job_id; } ;
typedef  int /*<<< orphan*/  StrategyNumber ;
typedef  TYPE_1__ ChunkStatInfo ;

/* Variables and functions */
 int /*<<< orphan*/  dimension_slice_check_chunk_stats_tuple_found ; 
 int /*<<< orphan*/  dimension_slice_scan_with_strategies (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int) ; 

int
ts_dimension_slice_oldest_chunk_without_executed_job(int32 job_id, int32 dimension_id,
													 StrategyNumber start_strategy,
													 int64 start_value, StrategyNumber end_strategy,
													 int64 end_value)
{
	ChunkStatInfo info = {
		.job_id = job_id,
		.chunk_id = -1,
	};

	dimension_slice_scan_with_strategies(dimension_id,
										 start_strategy,
										 start_value,
										 end_strategy,
										 end_value,
										 &info,
										 dimension_slice_check_chunk_stats_tuple_found,
										 -1);

	return info.chunk_id;
}