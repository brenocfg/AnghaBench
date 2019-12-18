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
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_3__ {int /*<<< orphan*/  materialization_invalidation_threshold; int /*<<< orphan*/  mctx; int /*<<< orphan*/ ** invalidations; } ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_1__ InvalidationScanState ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_continuous_aggs_hypertable_invalidation_log_idx_hypertable_id ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  CONTINUOUS_AGGS_HYPERTABLE_INVALIDATION_LOG ; 
 int /*<<< orphan*/  CONTINUOUS_AGGS_HYPERTABLE_INVALIDATION_LOG_IDX ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  F_INT4EQ ; 
 int /*<<< orphan*/  Int32GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PG_INT64_MAX ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scan_take_invalidation_tuple ; 
 int /*<<< orphan*/  ts_catalog_scan_all (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void
drain_invalidation_log(int32 raw_hypertable_id, List **invalidations_out)
{
	InvalidationScanState scan_state = {
		.invalidations = invalidations_out,
		.mctx = CurrentMemoryContext,
		.materialization_invalidation_threshold = PG_INT64_MAX,
	};
	ScanKeyData scankey[1];

	ScanKeyInit(&scankey[0],
				Anum_continuous_aggs_hypertable_invalidation_log_idx_hypertable_id,
				BTEqualStrategyNumber,
				F_INT4EQ,
				Int32GetDatum(raw_hypertable_id));

	ts_catalog_scan_all(CONTINUOUS_AGGS_HYPERTABLE_INVALIDATION_LOG /*=table*/,
						CONTINUOUS_AGGS_HYPERTABLE_INVALIDATION_LOG_IDX /*=indexid*/
						,
						scankey /*=scankey*/,
						1 /*=num_keys*/,
						scan_take_invalidation_tuple /*=tuple_found*/,
						RowExclusiveLock /*=lockmode*/,
						&scan_state /*=data*/);
}