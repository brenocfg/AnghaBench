#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ storage; } ;
struct TYPE_5__ {size_t descendants; scalar_t__ last_internal_node; int /*<<< orphan*/  vector; } ;
typedef  TYPE_1__ SubspaceStoreInternalNode ;
typedef  TYPE_2__ DimensionSlice ;

/* Variables and functions */
 TYPE_2__* ts_dimension_vec_get (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static size_t
subspace_store_internal_node_descendants(SubspaceStoreInternalNode *node, int index)
{
	DimensionSlice *slice = ts_dimension_vec_get(node->vector, index);

	if (slice == NULL)
		return 0;

	if (node->last_internal_node)
		return 1;

	return ((SubspaceStoreInternalNode *) slice->storage)->descendants;
}