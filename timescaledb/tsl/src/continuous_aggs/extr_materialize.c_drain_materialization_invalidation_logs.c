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
struct TYPE_3__ {int /*<<< orphan*/  mctx; int /*<<< orphan*/  materialization_invalidation_threshold; int /*<<< orphan*/ ** invalidations; } ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_1__ InvalidationScanState ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_continuous_aggs_materialization_invalidation_log_idx_materialization_id ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  CONTINUOUS_AGGS_MATERIALIZATION_INVALIDATION_LOG ; 
 int /*<<< orphan*/  CONTINUOUS_AGGS_MATERIALIZATION_INVALIDATION_LOG_IDX ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  F_INT4EQ ; 
 int /*<<< orphan*/  Int32GetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scan_del_materialization_invalidation_tuple ; 
 int /*<<< orphan*/  ts_catalog_scan_all (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void
drain_materialization_invalidation_logs(int32 cagg_id, int64 materialization_invalidation_threshold,
										List **invalidations_out)
{
	InvalidationScanState scan_state = {
		.invalidations = invalidations_out,
		.materialization_invalidation_threshold = materialization_invalidation_threshold,
		.mctx = CurrentMemoryContext,
	};
	ScanKeyData scankey[1];

	ScanKeyInit(&scankey[0],
				Anum_continuous_aggs_materialization_invalidation_log_idx_materialization_id,
				BTEqualStrategyNumber,
				F_INT4EQ,
				Int32GetDatum(cagg_id));

	ts_catalog_scan_all(CONTINUOUS_AGGS_MATERIALIZATION_INVALIDATION_LOG /*=table*/,
						CONTINUOUS_AGGS_MATERIALIZATION_INVALIDATION_LOG_IDX /*=indexid*/
						,
						scankey /*=scankey*/,
						1 /*=num_keys*/,
						scan_del_materialization_invalidation_tuple /*=tuple_found*/,
						RowExclusiveLock /*=lockmode*/,
						&scan_state /*=data*/);
}