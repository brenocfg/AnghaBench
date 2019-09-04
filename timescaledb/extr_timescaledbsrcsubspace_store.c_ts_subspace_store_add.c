#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_10__ ;

/* Type definitions */
struct TYPE_22__ {scalar_t__ dimension_id; int /*<<< orphan*/  range_start; } ;
struct TYPE_26__ {void (* storage_free ) (void*) ;TYPE_4__* storage; TYPE_3__ fd; } ;
struct TYPE_25__ {int num_slices; TYPE_7__** slices; } ;
struct TYPE_24__ {int num_dimensions; int max_items; int /*<<< orphan*/  mcxt; TYPE_4__* origin; } ;
struct TYPE_23__ {size_t descendants; TYPE_10__* vector; } ;
struct TYPE_20__ {scalar_t__ dimension_id; } ;
struct TYPE_21__ {TYPE_1__ fd; } ;
struct TYPE_19__ {scalar_t__ num_slices; TYPE_2__** slices; } ;
typedef  TYPE_4__ SubspaceStoreInternalNode ;
typedef  TYPE_5__ SubspaceStore ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_6__ Hypercube ;
typedef  TYPE_7__ DimensionSlice ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 TYPE_4__* subspace_store_internal_node_create (int) ; 
 size_t subspace_store_internal_node_descendants (TYPE_4__*,int) ; 
 void subspace_store_internal_node_free (void*) ; 
 TYPE_7__* ts_dimension_slice_copy (TYPE_7__ const*) ; 
 int /*<<< orphan*/  ts_dimension_vec_add_slice_sort (TYPE_10__**,TYPE_7__*) ; 
 TYPE_7__* ts_dimension_vec_find_slice (TYPE_10__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_dimension_vec_remove_slice (TYPE_10__**,int) ; 

void
ts_subspace_store_add(SubspaceStore *store, const Hypercube *hc, void *object,
					  void (*object_free)(void *))
{
	SubspaceStoreInternalNode *node = store->origin;
	DimensionSlice *last = NULL;
	MemoryContext old = MemoryContextSwitchTo(store->mcxt);
	int i;

	Assert(hc->num_slices == store->num_dimensions);

	for (i = 0; i < hc->num_slices; i++)
	{
		const DimensionSlice *target = hc->slices[i];
		DimensionSlice *match;

		Assert(target->storage == NULL);

		if (node == NULL)
		{
			/*
			 * We should have one internal node per dimension in the
			 * hypertable. If we don't have one for the current dimension,
			 * create one now. (There will always be one for time)
			 */
			Assert(last != NULL);
			last->storage = subspace_store_internal_node_create(i == (hc->num_slices - 1));
			last->storage_free = subspace_store_internal_node_free;
			node = last->storage;
		}

		Assert(store->max_items == 0 || node->descendants <= (size_t) store->max_items);

		/*
		 * We only call this function on a cache miss, so number of leaves
		 * will definitely increase see `Assert(last != NULL && last->storage
		 * == NULL);` at bottom.
		 */
		node->descendants += 1;

		Assert(0 == node->vector->num_slices ||
			   node->vector->slices[0]->fd.dimension_id == target->fd.dimension_id);

		/* Do we have enough space to store the object? */
		if (store->max_items > 0 && node->descendants > store->max_items)
		{
			/*
			 * Always delete the slice corresponding to the earliest time
			 * range. In the normal case that inserts are performed in
			 * time-order this is the one least likely to be reused. (Note
			 * that we made sure that the first dimension is a time dimension
			 * when creating the subspace_store). If out-of-order inserts are
			 * become significant we may wish to change this to something more
			 * sophisticated like LRU.
			 */
			size_t items_removed = subspace_store_internal_node_descendants(node, i);

			/*
			 * descendants at the root is inclusive of the descendants at the
			 * children, so if we have an overflow it must be in the time dim
			 */
			Assert(i == 0);

			Assert(store->max_items + 1 == node->descendants);

			ts_dimension_vec_remove_slice(&node->vector, i);

			/*
			 * Note we would have to do this to ancestors if this was not the
			 * root.
			 */
			node->descendants -= items_removed;
		}

		match = ts_dimension_vec_find_slice(node->vector, target->fd.range_start);

		/* Do we have a slot in this vector for the new object? */
		if (match == NULL)
		{
			DimensionSlice *copy;

			/*
			 * create a new copy of the range this slice covers, to store the
			 * object in
			 */
			copy = ts_dimension_slice_copy(target);

			ts_dimension_vec_add_slice_sort(&node->vector, copy);
			match = copy;
		}

		Assert(store->max_items == 0 || node->descendants <= (size_t) store->max_items);

		last = match;
		/* internal slices point to the next SubspaceStoreInternalNode */
		node = last->storage;
	}

	Assert(last != NULL && last->storage == NULL);
	last->storage = object; /* at the end we store the object */
	last->storage_free = object_free;
	MemoryContextSwitchTo(old);
}