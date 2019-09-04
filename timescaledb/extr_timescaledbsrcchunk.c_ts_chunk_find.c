#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  id; } ;
struct TYPE_17__ {TYPE_1__ fd; int /*<<< orphan*/  constraints; } ;
struct TYPE_16__ {int early_abort; } ;
struct TYPE_15__ {int /*<<< orphan*/  num_dimensions; } ;
typedef  int /*<<< orphan*/  Point ;
typedef  TYPE_2__ Hyperspace ;
typedef  TYPE_3__ ChunkScanCtx ;
typedef  TYPE_4__ Chunk ;

/* Variables and functions */
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  chunk_fill_stub (TYPE_4__*,int) ; 
 int /*<<< orphan*/  chunk_point_scan (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  chunk_scan_ctx_destroy (TYPE_3__*) ; 
 TYPE_4__* chunk_scan_ctx_get_chunk (TYPE_3__*) ; 
 int /*<<< orphan*/  chunk_scan_ctx_init (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_chunk_constraint_scan_by_chunk_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

Chunk *
ts_chunk_find(Hyperspace *hs, Point *p)
{
	Chunk *chunk;
	ChunkScanCtx ctx;

	/* The scan context will keep the state accumulated during the scan */
	chunk_scan_ctx_init(&ctx, hs, p);

	/* Abort the scan when the chunk is found */
	ctx.early_abort = true;

	/* Scan for the chunk matching the point */
	chunk_point_scan(&ctx, p);

	/* Find the chunk that has N matching dimension constraints */
	chunk = chunk_scan_ctx_get_chunk(&ctx);

	chunk_scan_ctx_destroy(&ctx);

	if (NULL != chunk)
	{
		/* Fill in the rest of the chunk's data from the chunk table */
		chunk_fill_stub(chunk, false);

		/*
		 * When searching for the chunk that matches the point, we only
		 * scanned for dimensional constraints. We now need to rescan the
		 * constraints to also get the inherited constraints.
		 */
		chunk->constraints = ts_chunk_constraint_scan_by_chunk_id(chunk->fd.id,
																  hs->num_dimensions,
																  CurrentMemoryContext);
	}

	return chunk;
}