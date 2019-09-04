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
typedef  int /*<<< orphan*/  int64 ;
typedef  int /*<<< orphan*/  DimensionSlice ;

/* Variables and functions */
 int ts_dimension_slice_cmp_coordinate (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cmp_coordinate_and_slice(const void *left, const void *right)
{
	int64 coord = *((int64 *) left);
	const DimensionSlice *slice = *((DimensionSlice **) right);

	return ts_dimension_slice_cmp_coordinate(slice, coord);
}