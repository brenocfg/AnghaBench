#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64 ;
typedef  scalar_t__ int64 ;
struct TYPE_5__ {int /*<<< orphan*/  column_type; } ;
struct TYPE_6__ {TYPE_1__ fd; } ;
typedef  int /*<<< orphan*/  StrategyNumber ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  Hyperspace ;
typedef  TYPE_2__ Dimension ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  ChunkScanCtx ;

/* Variables and functions */
 int /*<<< orphan*/  BTGreaterEqualStrategyNumber ; 
 int /*<<< orphan*/  BTLessStrategyNumber ; 
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ INTERVALOID ; 
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/  InvalidStrategy ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * chunks_find_all_in_range_limit (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  ts_dimension_open_typecheck (scalar_t__,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ts_interval_from_now_to_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ts_time_value_to_internal (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static ChunkScanCtx *
chunks_typecheck_and_find_all_in_range_limit(Hyperspace *hs, Dimension *time_dim,
											 Datum older_than_datum, Oid older_than_type,
											 Datum newer_than_datum, Oid newer_than_type, int limit,
											 MemoryContext multi_call_memory_ctx, char *caller_name,
											 uint64 *num_found)
{
	ChunkScanCtx *chunk_ctx = NULL;
	int64 older_than = -1;
	int64 newer_than = -1;

	StrategyNumber start_strategy = InvalidStrategy;
	StrategyNumber end_strategy = InvalidStrategy;

	MemoryContext oldcontext;

	if (time_dim == NULL)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE), errmsg("no time dimension found")));

	if (older_than_type != InvalidOid)
	{
		ts_dimension_open_typecheck(older_than_type, time_dim->fd.column_type, caller_name);
		if (older_than_type == INTERVALOID)
			older_than =
				ts_interval_from_now_to_internal(older_than_datum, time_dim->fd.column_type);
		else
			older_than = ts_time_value_to_internal(older_than_datum, older_than_type);
		end_strategy = BTLessStrategyNumber;
	}

	if (newer_than_type != InvalidOid)
	{
		ts_dimension_open_typecheck(newer_than_type, time_dim->fd.column_type, caller_name);
		if (newer_than_type == INTERVALOID)
			newer_than =
				ts_interval_from_now_to_internal(newer_than_datum, time_dim->fd.column_type);
		else
			newer_than = ts_time_value_to_internal(newer_than_datum, newer_than_type);
		start_strategy = BTGreaterEqualStrategyNumber;
	}

	if (older_than_type != InvalidOid && newer_than_type != InvalidOid && older_than < newer_than)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("When both older_than and newer_than are specified, "
						"older_than must refer to a time that is more recent than newer_than so "
						"that a valid overlapping range is specified")));

	oldcontext = MemoryContextSwitchTo(multi_call_memory_ctx);
	chunk_ctx = chunks_find_all_in_range_limit(hs,
											   time_dim,
											   start_strategy,
											   newer_than,
											   end_strategy,
											   older_than,
											   limit,
											   num_found);
	MemoryContextSwitchTo(oldcontext);

	return chunk_ctx;
}