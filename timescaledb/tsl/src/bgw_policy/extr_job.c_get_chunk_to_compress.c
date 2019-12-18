#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64 ;
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_8__ {int /*<<< orphan*/  id; } ;
struct TYPE_10__ {TYPE_1__ fd; } ;
struct TYPE_9__ {int /*<<< orphan*/  space; } ;
typedef  int /*<<< orphan*/  StrategyNumber ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_2__ Hypertable ;
typedef  int /*<<< orphan*/  FormData_ts_interval ;
typedef  TYPE_3__ Dimension ;

/* Variables and functions */
 int /*<<< orphan*/  BTLessStrategyNumber ; 
 int /*<<< orphan*/  InvalidStrategy ; 
 TYPE_3__* hyperspace_get_open_dimension (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_dimension_get_partition_type (TYPE_3__*) ; 
 int /*<<< orphan*/  ts_dimension_slice_get_chunkid_to_compress (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_interval_subtract_from_now (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  ts_time_value_to_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32
get_chunk_to_compress(Hypertable *ht, FormData_ts_interval *older_than)
{
	Dimension *open_dim = hyperspace_get_open_dimension(ht->space, 0);
	StrategyNumber end_strategy = BTLessStrategyNumber;
	Oid partitioning_type = ts_dimension_get_partition_type(open_dim);
	int64 end_value = ts_time_value_to_internal(ts_interval_subtract_from_now(older_than, open_dim),
												partitioning_type);
	return ts_dimension_slice_get_chunkid_to_compress(open_dim->fd.id,
													  InvalidStrategy, /*start_strategy*/
													  -1,			   /*start_value*/
													  end_strategy,
													  end_value);
}