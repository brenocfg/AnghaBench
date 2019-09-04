#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  DimensionVec ;
typedef  int /*<<< orphan*/  DimensionSlice ;

/* Variables and functions */
 int /*<<< orphan*/ * ts_dimension_vec_add_slice (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ts_dimension_vec_sort (int /*<<< orphan*/ **) ; 

DimensionVec *
ts_dimension_vec_add_slice_sort(DimensionVec **vecptr, DimensionSlice *slice)
{
	DimensionVec *vec;

	*vecptr = vec = ts_dimension_vec_add_slice(vecptr, slice);
	return ts_dimension_vec_sort(vecptr);
}