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
struct TYPE_13__ {void* storage; } ;
struct TYPE_12__ {int cardinality; int /*<<< orphan*/ * coordinates; } ;
struct TYPE_11__ {int num_dimensions; TYPE_1__* origin; } ;
struct TYPE_10__ {int /*<<< orphan*/ * vector; } ;
struct TYPE_9__ {int /*<<< orphan*/ * vector; } ;
typedef  TYPE_2__ SubspaceStoreInternalNode ;
typedef  TYPE_3__ SubspaceStore ;
typedef  TYPE_4__ Point ;
typedef  int /*<<< orphan*/  DimensionVec ;
typedef  TYPE_5__ DimensionSlice ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 TYPE_5__* ts_dimension_vec_find_slice (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void *
ts_subspace_store_get(SubspaceStore *store, Point *target)
{
	int i;
	DimensionVec *vec = store->origin->vector;
	DimensionSlice *match = NULL;

	Assert(target->cardinality == store->num_dimensions);

	for (i = 0; i < target->cardinality; i++)
	{
		match = ts_dimension_vec_find_slice(vec, target->coordinates[i]);

		if (NULL == match)
			return NULL;

		vec = ((SubspaceStoreInternalNode *) match->storage)->vector;
	}
	Assert(match != NULL);
	return match->storage;
}