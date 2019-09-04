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
struct TYPE_5__ {scalar_t__ dimension_id; scalar_t__ range_start; scalar_t__ range_end; } ;
struct TYPE_6__ {TYPE_1__ fd; } ;
typedef  TYPE_2__ DimensionSlice ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 

bool
ts_dimension_slices_collide(DimensionSlice *slice1, DimensionSlice *slice2)
{
	Assert(slice1->fd.dimension_id == slice2->fd.dimension_id);

	return (slice1->fd.range_start < slice2->fd.range_end &&
			slice1->fd.range_end > slice2->fd.range_start);
}