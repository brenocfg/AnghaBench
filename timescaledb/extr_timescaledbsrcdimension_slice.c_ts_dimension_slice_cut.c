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
typedef  scalar_t__ int64 ;
struct TYPE_5__ {scalar_t__ dimension_id; scalar_t__ range_end; scalar_t__ range_start; } ;
struct TYPE_6__ {TYPE_1__ fd; } ;
typedef  TYPE_2__ DimensionSlice ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ REMAP_LAST_COORDINATE (scalar_t__) ; 

bool
ts_dimension_slice_cut(DimensionSlice *to_cut, DimensionSlice *other, int64 coord)
{
	Assert(to_cut->fd.dimension_id == other->fd.dimension_id);

	coord = REMAP_LAST_COORDINATE(coord);

	if (other->fd.range_end <= coord && other->fd.range_end > to_cut->fd.range_start)
	{
		/* Cut "before" the coordinate */
		to_cut->fd.range_start = other->fd.range_end;

		return true;
	}
	else if (other->fd.range_start > coord && other->fd.range_start < to_cut->fd.range_end)
	{
		/* Cut "after" the coordinate */
		to_cut->fd.range_end = other->fd.range_start;

		return true;
	}

	return false;
}