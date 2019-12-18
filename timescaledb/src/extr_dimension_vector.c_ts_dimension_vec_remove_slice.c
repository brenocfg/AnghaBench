#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32 ;
struct TYPE_3__ {size_t num_slices; int /*<<< orphan*/ * slices; } ;
typedef  TYPE_1__ DimensionVec ;
typedef  int /*<<< orphan*/  DimensionSlice ;

/* Variables and functions */
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ts_dimension_slice_free (int /*<<< orphan*/ ) ; 

void
ts_dimension_vec_remove_slice(DimensionVec **vecptr, int32 index)
{
	DimensionVec *vec = *vecptr;

	ts_dimension_slice_free(vec->slices[index]);
	memmove(vec->slices + index,
			vec->slices + (index + 1),
			sizeof(DimensionSlice *) * (vec->num_slices - index - 1));
	vec->num_slices--;
}