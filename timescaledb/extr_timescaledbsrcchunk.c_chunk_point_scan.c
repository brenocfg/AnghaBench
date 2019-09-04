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
struct TYPE_13__ {TYPE_3__* space; } ;
struct TYPE_12__ {int /*<<< orphan*/ * coordinates; } ;
struct TYPE_11__ {int num_dimensions; TYPE_2__* dimensions; } ;
struct TYPE_9__ {int /*<<< orphan*/  id; } ;
struct TYPE_10__ {TYPE_1__ fd; } ;
typedef  TYPE_4__ Point ;
typedef  int /*<<< orphan*/  DimensionVec ;
typedef  TYPE_5__ ChunkScanCtx ;

/* Variables and functions */
 int /*<<< orphan*/  dimension_slice_and_chunk_constraint_join (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dimension_slice_scan (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
chunk_point_scan(ChunkScanCtx *scanctx, Point *p)
{
	int i;

	/* Scan all dimensions for slices enclosing the point */
	for (i = 0; i < scanctx->space->num_dimensions; i++)
	{
		DimensionVec *vec;

		vec = dimension_slice_scan(scanctx->space->dimensions[i].fd.id, p->coordinates[i]);

		dimension_slice_and_chunk_constraint_join(scanctx, vec);
	}
}