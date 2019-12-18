#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64 ;
struct TYPE_16__ {int /*<<< orphan*/  cube; } ;
struct TYPE_15__ {TYPE_1__* point; TYPE_3__* space; TYPE_4__* data; } ;
struct TYPE_11__ {int /*<<< orphan*/  id; int /*<<< orphan*/  aligned; } ;
struct TYPE_14__ {TYPE_2__ fd; } ;
struct TYPE_13__ {int /*<<< orphan*/ ** slices; } ;
struct TYPE_12__ {int num_dimensions; TYPE_5__* dimensions; } ;
struct TYPE_10__ {int /*<<< orphan*/ * coordinates; } ;
typedef  TYPE_3__ Hyperspace ;
typedef  TYPE_4__ Hypercube ;
typedef  int /*<<< orphan*/  DimensionSlice ;
typedef  TYPE_5__ Dimension ;
typedef  TYPE_6__ ChunkScanCtx ;
typedef  int /*<<< orphan*/  ChunkResult ;
typedef  TYPE_7__ Chunk ;

/* Variables and functions */
 int /*<<< orphan*/  CHUNK_IGNORED ; 
 int /*<<< orphan*/  CHUNK_PROCESSED ; 
 int /*<<< orphan*/  ts_dimension_slice_cut (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ts_dimension_slices_collide (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_dimension_slices_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ts_hypercube_get_slice_by_dimension_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ChunkResult
do_dimension_alignment(ChunkScanCtx *scanctx, Chunk *chunk)
{
	Hypercube *cube = scanctx->data;
	Hyperspace *space = scanctx->space;
	ChunkResult res = CHUNK_IGNORED;
	int i;

	for (i = 0; i < space->num_dimensions; i++)
	{
		Dimension *dim = &space->dimensions[i];
		DimensionSlice *chunk_slice, *cube_slice;
		int64 coord = scanctx->point->coordinates[i];

		if (!dim->fd.aligned)
			continue;

		/*
		 * The chunk might not have a slice for each dimension, so we cannot
		 * use array indexing. Fetch slice by dimension ID instead.
		 */
		chunk_slice = ts_hypercube_get_slice_by_dimension_id(chunk->cube, dim->fd.id);

		if (NULL == chunk_slice)
			continue;

		cube_slice = cube->slices[i];

		/*
		 * Only cut-to-align if the slices collide and are not identical
		 * (i.e., if we are reusing an existing slice we should not cut it)
		 */
		if (!ts_dimension_slices_equal(cube_slice, chunk_slice) &&
			ts_dimension_slices_collide(cube_slice, chunk_slice))
		{
			ts_dimension_slice_cut(cube_slice, chunk_slice, coord);
			res = CHUNK_PROCESSED;
		}
	}

	return res;
}