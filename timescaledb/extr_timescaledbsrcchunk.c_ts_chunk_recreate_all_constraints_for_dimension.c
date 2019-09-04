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
struct TYPE_3__ {int num_slices; int /*<<< orphan*/ * slices; } ;
typedef  int /*<<< orphan*/  Hyperspace ;
typedef  TYPE_1__ DimensionVec ;
typedef  int /*<<< orphan*/  ChunkScanCtx ;

/* Variables and functions */
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  chunk_recreate_constraint ; 
 int /*<<< orphan*/  chunk_scan_ctx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  chunk_scan_ctx_foreach_chunk (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chunk_scan_ctx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_chunk_constraint_scan_by_dimension_slice (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* ts_dimension_slice_scan_by_dimension (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ts_chunk_recreate_all_constraints_for_dimension(Hyperspace *hs, int32 dimension_id)
{
	DimensionVec *slices;
	ChunkScanCtx chunkctx;
	int i;

	slices = ts_dimension_slice_scan_by_dimension(dimension_id, 0);

	if (NULL == slices)
		return;

	chunk_scan_ctx_init(&chunkctx, hs, NULL);

	for (i = 0; i < slices->num_slices; i++)
		ts_chunk_constraint_scan_by_dimension_slice(slices->slices[i],
													&chunkctx,
													CurrentMemoryContext);

	chunk_scan_ctx_foreach_chunk(&chunkctx, chunk_recreate_constraint, 0);
	chunk_scan_ctx_destroy(&chunkctx);
}