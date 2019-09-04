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
struct TYPE_3__ {int /*<<< orphan*/  tuple; int /*<<< orphan*/  mctx; } ;
typedef  TYPE_1__ TupleInfo ;
typedef  int /*<<< orphan*/  ScanTupleResult ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  DimensionSlice ;

/* Variables and functions */
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCAN_CONTINUE ; 
 int /*<<< orphan*/ * dimension_slice_from_tuple (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ScanTupleResult
dimension_slice_nth_tuple_found(TupleInfo *ti, void *data)
{
	DimensionSlice **slice = data;
	MemoryContext old = MemoryContextSwitchTo(ti->mctx);

	*slice = dimension_slice_from_tuple(ti->tuple);
	MemoryContextSwitchTo(old);
	return SCAN_CONTINUE;
}