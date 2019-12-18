#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64 ;
typedef  int /*<<< orphan*/  int64 ;
struct TYPE_11__ {int early_abort; int /*<<< orphan*/  htab; } ;
struct TYPE_9__ {int /*<<< orphan*/  id; } ;
struct TYPE_10__ {TYPE_1__ fd; } ;
typedef  int /*<<< orphan*/  StrategyNumber ;
typedef  int /*<<< orphan*/  Hyperspace ;
typedef  int /*<<< orphan*/  DimensionVec ;
typedef  TYPE_2__ Dimension ;
typedef  TYPE_3__ ChunkScanCtx ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chunk_scan_ctx_init (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dimension_slice_and_chunk_constraint_join (TYPE_3__*,int /*<<< orphan*/ *) ; 
 scalar_t__ hash_get_num_entries (int /*<<< orphan*/ ) ; 
 TYPE_3__* palloc (int) ; 
 int /*<<< orphan*/ * ts_dimension_slice_scan_range_limit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ChunkScanCtx *
chunks_find_all_in_range_limit(Hyperspace *hs, Dimension *time_dim, StrategyNumber start_strategy,
							   int64 start_value, StrategyNumber end_strategy, int64 end_value,
							   int limit, uint64 *num_found)
{
	ChunkScanCtx *ctx = palloc(sizeof(ChunkScanCtx));
	DimensionVec *slices;

	Assert(hs != NULL);

	/* must have been checked earlier that this is the case */
	Assert(time_dim != NULL);

	slices = ts_dimension_slice_scan_range_limit(time_dim->fd.id,
												 start_strategy,
												 start_value,
												 end_strategy,
												 end_value,
												 limit);

	/* The scan context will keep the state accumulated during the scan */
	chunk_scan_ctx_init(ctx, hs, NULL);

	/* No abort when the first chunk is found */
	ctx->early_abort = false;

	/* Scan for chunks that are in range */
	dimension_slice_and_chunk_constraint_join(ctx, slices);

	*num_found += hash_get_num_entries(ctx->htab);
	return ctx;
}