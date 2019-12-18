#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64 ;
struct TYPE_14__ {scalar_t__ id; scalar_t__ aligned; } ;
struct TYPE_19__ {TYPE_1__ fd; } ;
struct TYPE_18__ {scalar_t__ num_slices; int /*<<< orphan*/ * slices; } ;
struct TYPE_17__ {int num_slices; int /*<<< orphan*/ * slices; } ;
struct TYPE_16__ {int num_dimensions; TYPE_6__* dimensions; } ;
struct TYPE_15__ {int /*<<< orphan*/ * coordinates; } ;
typedef  TYPE_2__ Point ;
typedef  TYPE_3__ Hyperspace ;
typedef  TYPE_4__ Hypercube ;
typedef  TYPE_5__ DimensionVec ;
typedef  TYPE_6__ Dimension ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int hypercube_is_sorted (TYPE_4__*) ; 
 int /*<<< orphan*/  ts_dimension_calculate_default_slice (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_dimension_slice_scan_for_existing (int /*<<< orphan*/ ) ; 
 TYPE_5__* ts_dimension_slice_scan_limit (scalar_t__,int /*<<< orphan*/ ,int) ; 
 TYPE_4__* ts_hypercube_alloc (int) ; 

Hypercube *
ts_hypercube_calculate_from_point(Hyperspace *hs, Point *p)
{
	Hypercube *cube;
	int i;

	cube = ts_hypercube_alloc(hs->num_dimensions);

	/* For each dimension, calculate the hypercube's slice in that dimension */
	for (i = 0; i < hs->num_dimensions; i++)
	{
		Dimension *dim = &hs->dimensions[i];
		int64 value = p->coordinates[i];
		bool found = false;

		/* Assert that dimensions are in ascending order */
		Assert(i == 0 || dim->fd.id > hs->dimensions[i - 1].fd.id);

		/*
		 * If this is an aligned dimension, we'd like to reuse any existing
		 * slice that covers the coordinate in the dimension
		 */
		if (dim->fd.aligned)
		{
			DimensionVec *vec;

			vec = ts_dimension_slice_scan_limit(dim->fd.id, value, 1);

			if (vec->num_slices > 0)
			{
				cube->slices[i] = vec->slices[0];
				found = true;
			}
		}

		if (!found)
		{
			/*
			 * No existing slice found, or we are not aligning, so calculate
			 * the range of a new slice
			 */
			cube->slices[i] = ts_dimension_calculate_default_slice(dim, value);

			/*
			 * Check if there's already an existing slice with the calculated
			 * range. If a slice already exists, use that slice's ID instead
			 * of a new one.
			 */
			ts_dimension_slice_scan_for_existing(cube->slices[i]);
		}
	}

	cube->num_slices = hs->num_dimensions;

	Assert(hypercube_is_sorted(cube));

	return cube;
}