#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_7__ {int num_slices; TYPE_2__** slices; } ;
struct TYPE_5__ {int /*<<< orphan*/  id; } ;
struct TYPE_6__ {TYPE_1__ fd; } ;
typedef  TYPE_3__ Hypercube ;
typedef  int /*<<< orphan*/  ChunkConstraints ;

/* Variables and functions */
 int /*<<< orphan*/  chunk_constraints_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
ts_chunk_constraints_add_dimension_constraints(ChunkConstraints *ccs, int32 chunk_id,
											   Hypercube *cube)
{
	int i;

	for (i = 0; i < cube->num_slices; i++)
		chunk_constraints_add(ccs, chunk_id, cube->slices[i]->fd.id, NULL, NULL);

	return cube->num_slices;
}