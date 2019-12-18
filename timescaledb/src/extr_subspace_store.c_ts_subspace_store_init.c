#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int16 ;
struct TYPE_9__ {int num_dimensions; TYPE_1__* dimensions; } ;
struct TYPE_8__ {int num_dimensions; int /*<<< orphan*/  mcxt; int /*<<< orphan*/  max_items; int /*<<< orphan*/  origin; } ;
struct TYPE_7__ {scalar_t__ type; } ;
typedef  TYPE_2__ SubspaceStore ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_3__ Hyperspace ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ DIMENSION_TYPE_OPEN ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 TYPE_2__* palloc (int) ; 
 int /*<<< orphan*/  subspace_store_internal_node_create (int) ; 

SubspaceStore *
ts_subspace_store_init(Hyperspace *space, MemoryContext mcxt, int16 max_items)
{
	MemoryContext old = MemoryContextSwitchTo(mcxt);
	SubspaceStore *sst = palloc(sizeof(SubspaceStore));

	/*
	 * make sure that the first dimension is a time dimension, otherwise the
	 * tree will grow in a way that makes pruning less effective.
	 */
	Assert(space->num_dimensions < 1 || space->dimensions[0].type == DIMENSION_TYPE_OPEN);

	sst->origin = subspace_store_internal_node_create(space->num_dimensions == 1);
	sst->num_dimensions = space->num_dimensions;
	/* max_items = 0 is treated as unlimited */
	sst->max_items = max_items;
	sst->mcxt = mcxt;
	MemoryContextSwitchTo(old);
	return sst;
}