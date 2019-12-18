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
typedef  int /*<<< orphan*/  DimensionSlice ;

/* Variables and functions */
 int DIMENSION_SLICE_RANGE_END_CMP (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int DIMENSION_SLICE_RANGE_START_CMP (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

int
ts_dimension_slice_cmp(const DimensionSlice *left, const DimensionSlice *right)
{
	int res = DIMENSION_SLICE_RANGE_START_CMP(left, right);

	if (res == 0)
		res = DIMENSION_SLICE_RANGE_END_CMP(left, right);

	return res;
}