#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_9__ {int /*<<< orphan*/  id; } ;
struct TYPE_13__ {TYPE_1__ fd; } ;
struct TYPE_10__ {int /*<<< orphan*/  range_start; } ;
struct TYPE_12__ {TYPE_2__ fd; } ;
struct TYPE_11__ {int /*<<< orphan*/  space; } ;
typedef  TYPE_3__ Hypertable ;
typedef  TYPE_4__ DimensionSlice ;
typedef  TYPE_5__ Dimension ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTLessEqualStrategyNumber ; 
 int /*<<< orphan*/  InvalidStrategy ; 
 int /*<<< orphan*/  REORDER_SKIP_RECENT_DIM_SLICES_N ; 
 TYPE_5__* hyperspace_get_open_dimension (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* ts_dimension_slice_nth_latest_slice (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ts_dimension_slice_oldest_chunk_without_executed_job (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
get_chunk_id_to_reorder(int32 job_id, Hypertable *ht)
{
	Dimension *time_dimension = hyperspace_get_open_dimension(ht->space, 0);
	DimensionSlice *nth_dimension =
		ts_dimension_slice_nth_latest_slice(time_dimension->fd.id,
											REORDER_SKIP_RECENT_DIM_SLICES_N);

	if (!nth_dimension)
		return -1;

	Assert(time_dimension != NULL);

	return ts_dimension_slice_oldest_chunk_without_executed_job(job_id,
																time_dimension->fd.id,
																BTLessEqualStrategyNumber,
																nth_dimension->fd.range_start,
																InvalidStrategy,
																-1);
}