#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64 ;
struct TYPE_15__ {int num_slices; int /*<<< orphan*/ ** slices; } ;
struct TYPE_14__ {TYPE_7__* cube; } ;
struct TYPE_13__ {TYPE_1__* point; TYPE_2__* space; TYPE_3__* data; } ;
struct TYPE_12__ {int /*<<< orphan*/ ** slices; } ;
struct TYPE_11__ {int num_dimensions; } ;
struct TYPE_10__ {int /*<<< orphan*/ * coordinates; } ;
typedef  TYPE_2__ Hyperspace ;
typedef  TYPE_3__ Hypercube ;
typedef  int /*<<< orphan*/  DimensionSlice ;
typedef  TYPE_4__ ChunkScanCtx ;
typedef  int /*<<< orphan*/  ChunkResult ;
typedef  TYPE_5__ Chunk ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CHUNK_IGNORED ; 
 int /*<<< orphan*/  CHUNK_PROCESSED ; 
 int /*<<< orphan*/  ts_dimension_slice_cut (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ts_dimension_slices_collide (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_dimension_slices_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_hypercubes_collide (TYPE_3__*,TYPE_7__*) ; 

__attribute__((used)) static ChunkResult
do_collision_resolution(ChunkScanCtx *scanctx, Chunk *chunk)
{
	Hypercube *cube = scanctx->data;
	Hyperspace *space = scanctx->space;
	ChunkResult res = CHUNK_IGNORED;
	int i;

	if (chunk->cube->num_slices != space->num_dimensions ||
		!ts_hypercubes_collide(cube, chunk->cube))
		return CHUNK_IGNORED;

	for (i = 0; i < space->num_dimensions; i++)
	{
		DimensionSlice *cube_slice = cube->slices[i];
		DimensionSlice *chunk_slice = chunk->cube->slices[i];
		int64 coord = scanctx->point->coordinates[i];

		/*
		 * Only cut if we aren't reusing an existing slice and there is a
		 * collision
		 */
		if (!ts_dimension_slices_equal(cube_slice, chunk_slice) &&
			ts_dimension_slices_collide(cube_slice, chunk_slice))
		{
			ts_dimension_slice_cut(cube_slice, chunk_slice, coord);
			res = CHUNK_PROCESSED;

			/*
			 * Redo the collision check after each cut since cutting in one
			 * dimension might have resolved the collision in another
			 */
			if (!ts_hypercubes_collide(cube, chunk->cube))
				return res;
		}
	}

	Assert(!ts_hypercubes_collide(cube, chunk->cube));

	return res;
}