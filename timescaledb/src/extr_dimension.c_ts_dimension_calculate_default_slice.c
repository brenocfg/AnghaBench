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
typedef  int /*<<< orphan*/  Dimension ;

/* Variables and functions */
 scalar_t__ IS_OPEN_DIMENSION (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * calculate_closed_range_default (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * calculate_open_range_default (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

DimensionSlice *
ts_dimension_calculate_default_slice(Dimension *dim, int64 value)
{
	if (IS_OPEN_DIMENSION(dim))
		return calculate_open_range_default(dim, value);

	return calculate_closed_range_default(dim, value);
}