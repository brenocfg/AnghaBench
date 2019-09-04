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
struct TYPE_13__ {TYPE_1__* space; } ;
struct TYPE_10__ {int /*<<< orphan*/  range_end; int /*<<< orphan*/  range_start; int /*<<< orphan*/  dimension_id; } ;
struct TYPE_12__ {TYPE_2__ fd; } ;
struct TYPE_11__ {TYPE_4__** slices; } ;
struct TYPE_9__ {int num_dimensions; } ;
typedef  TYPE_3__ Hypercube ;
typedef  int /*<<< orphan*/  DimensionVec ;
typedef  TYPE_4__ DimensionSlice ;
typedef  TYPE_5__ ChunkScanCtx ;

/* Variables and functions */
 int /*<<< orphan*/  dimension_slice_and_chunk_constraint_join (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dimension_slice_collision_scan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
chunk_collision_scan(ChunkScanCtx *scanctx, Hypercube *cube)
{
	int i;

	/* Scan all dimensions for colliding slices */
	for (i = 0; i < scanctx->space->num_dimensions; i++)
	{
		DimensionVec *vec;
		DimensionSlice *slice = cube->slices[i];

		vec = dimension_slice_collision_scan(slice->fd.dimension_id,
											 slice->fd.range_start,
											 slice->fd.range_end);

		/* Add the slices to all the chunks they are associated with */
		dimension_slice_and_chunk_constraint_join(scanctx, vec);
	}
}