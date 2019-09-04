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
struct TYPE_5__ {scalar_t__ range_start; scalar_t__ range_end; } ;
struct TYPE_6__ {TYPE_1__ fd; } ;
typedef  TYPE_2__ DimensionSlice ;

/* Variables and functions */

int
ts_dimension_slice_cmp(const DimensionSlice *left, const DimensionSlice *right)
{
	if (left->fd.range_start == right->fd.range_start)
	{
		if (left->fd.range_end == right->fd.range_end)
			return 0;

		if (left->fd.range_end > right->fd.range_end)
			return 1;

		return -1;
	}

	if (left->fd.range_start > right->fd.range_start)
		return 1;

	return -1;
}