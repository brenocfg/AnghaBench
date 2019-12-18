#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ dimension_id; } ;
struct TYPE_11__ {TYPE_1__ fd; } ;
struct TYPE_10__ {scalar_t__ num_slices; scalar_t__ capacity; TYPE_3__** slices; } ;
typedef  TYPE_2__ DimensionVec ;
typedef  TYPE_3__ DimensionSlice ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 TYPE_2__* dimension_vec_expand (TYPE_2__*,scalar_t__) ; 

DimensionVec *
ts_dimension_vec_add_slice(DimensionVec **vecptr, DimensionSlice *slice)
{
	DimensionVec *vec = *vecptr;

	/* Ensure consistent dimension */
	Assert(vec->num_slices == 0 || vec->slices[0]->fd.dimension_id == slice->fd.dimension_id);

	if (vec->num_slices + 1 > vec->capacity)
		*vecptr = vec = dimension_vec_expand(vec, vec->capacity + 10);

	vec->slices[vec->num_slices++] = slice;

	return vec;
}