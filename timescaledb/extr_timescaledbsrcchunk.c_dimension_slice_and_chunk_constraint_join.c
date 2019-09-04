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
struct TYPE_3__ {int num_slices; int /*<<< orphan*/ * slices; } ;
typedef  TYPE_1__ DimensionVec ;
typedef  int /*<<< orphan*/  ChunkScanCtx ;

/* Variables and functions */
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  ts_chunk_constraint_scan_by_dimension_slice (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
dimension_slice_and_chunk_constraint_join(ChunkScanCtx *scanctx, DimensionVec *vec)
{
	int i;

	for (i = 0; i < vec->num_slices; i++)
	{
		/*
		 * For each dimension slice, find matching constraints. These will be
		 * saved in the scan context
		 */
		ts_chunk_constraint_scan_by_dimension_slice(vec->slices[i], scanctx, CurrentMemoryContext);
	}
}