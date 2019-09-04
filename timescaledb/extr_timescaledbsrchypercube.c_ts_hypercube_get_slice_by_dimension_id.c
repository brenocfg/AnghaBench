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
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_7__ {int /*<<< orphan*/  dimension_id; } ;
struct TYPE_9__ {TYPE_1__ fd; } ;
struct TYPE_8__ {int /*<<< orphan*/  num_slices; int /*<<< orphan*/  slices; } ;
typedef  TYPE_2__ Hypercube ;
typedef  TYPE_3__ DimensionSlice ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 void* bsearch (void**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmp_slices_by_dimension_id ; 
 int /*<<< orphan*/  hypercube_is_sorted (TYPE_2__*) ; 

DimensionSlice *
ts_hypercube_get_slice_by_dimension_id(Hypercube *hc, int32 dimension_id)
{
	DimensionSlice slice = {
		.fd.dimension_id = dimension_id,
	};
	void *ptr = &slice;

	if (hc->num_slices == 0)
		return NULL;

	Assert(hypercube_is_sorted(hc));

	ptr = bsearch(&ptr,
				  hc->slices,
				  hc->num_slices,
				  sizeof(DimensionSlice *),
				  cmp_slices_by_dimension_id);

	if (NULL == ptr)
		return NULL;

	return *((DimensionSlice **) ptr);
}