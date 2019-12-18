#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  tuple; } ;
typedef  TYPE_1__ TupleInfo ;
typedef  int /*<<< orphan*/  ScanTupleResult ;
typedef  int /*<<< orphan*/  DimensionVec ;
typedef  int /*<<< orphan*/  DimensionSlice ;

/* Variables and functions */
 int /*<<< orphan*/  SCAN_CONTINUE ; 
 int /*<<< orphan*/ * dimension_slice_from_tuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ts_dimension_vec_add_slice (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ScanTupleResult
dimension_vec_tuple_found(TupleInfo *ti, void *data)
{
	DimensionVec **slices = data;
	DimensionSlice *slice = dimension_slice_from_tuple(ti->tuple);

	*slices = ts_dimension_vec_add_slice(slices, slice);

	return SCAN_CONTINUE;
}