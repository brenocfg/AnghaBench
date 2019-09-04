#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  Point ;
typedef  int /*<<< orphan*/  Hyperspace ;
typedef  int /*<<< orphan*/  Hypercube ;
typedef  TYPE_1__ ChunkScanCtx ;

/* Variables and functions */
 int /*<<< orphan*/  chunk_collision_scan (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  chunk_scan_ctx_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/  chunk_scan_ctx_foreach_chunk (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chunk_scan_ctx_init (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_collision_resolution ; 
 int /*<<< orphan*/  do_dimension_alignment ; 

__attribute__((used)) static void
chunk_collision_resolve(Hyperspace *hs, Hypercube *cube, Point *p)
{
	ChunkScanCtx scanctx;

	chunk_scan_ctx_init(&scanctx, hs, p);

	/* Scan for all chunks that collide with the hypercube of the new chunk */
	chunk_collision_scan(&scanctx, cube);
	scanctx.data = cube;

	/* Cut the hypercube in any aligned dimensions */
	chunk_scan_ctx_foreach_chunk(&scanctx, do_dimension_alignment, 0);

	/*
	 * If there are any remaining collisions with chunks, then cut-to-fit to
	 * resolve those collisions
	 */
	chunk_scan_ctx_foreach_chunk(&scanctx, do_collision_resolution, 0);

	chunk_scan_ctx_destroy(&scanctx);
}