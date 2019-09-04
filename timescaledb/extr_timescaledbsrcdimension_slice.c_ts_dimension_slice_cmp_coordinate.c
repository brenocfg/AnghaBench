#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64 ;
struct TYPE_4__ {scalar_t__ range_start; scalar_t__ range_end; } ;
struct TYPE_5__ {TYPE_1__ fd; } ;
typedef  TYPE_2__ DimensionSlice ;

/* Variables and functions */
 scalar_t__ REMAP_LAST_COORDINATE (scalar_t__) ; 

int
ts_dimension_slice_cmp_coordinate(const DimensionSlice *slice, int64 coord)
{
	coord = REMAP_LAST_COORDINATE(coord);
	if (coord < slice->fd.range_start)
		return -1;

	if (coord >= slice->fd.range_end)
		return 1;

	return 0;
}