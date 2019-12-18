#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  tuple; int /*<<< orphan*/  scanrel; } ;
typedef  TYPE_1__ TupleInfo ;
struct TYPE_11__ {scalar_t__ lowest_modified_value; scalar_t__ greatest_modified_value; } ;
struct TYPE_10__ {scalar_t__ lowest_modified_value; scalar_t__ greatest_modified_value; } ;
struct TYPE_9__ {scalar_t__ materialization_invalidation_threshold; int /*<<< orphan*/ * invalidations; int /*<<< orphan*/  mctx; } ;
typedef  int /*<<< orphan*/  ScanTupleResult ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_2__ InvalidationScanState ;
typedef  TYPE_3__ Invalidation ;
typedef  TYPE_4__* Form_continuous_aggs_materialization_invalidation_log ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCAN_CONTINUE ; 
 int /*<<< orphan*/  lappend (int /*<<< orphan*/ ,TYPE_3__*) ; 
 TYPE_3__* palloc (int) ; 
 int /*<<< orphan*/  ts_catalog_delete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ScanTupleResult
scan_del_materialization_invalidation_tuple(TupleInfo *ti, void *data)
{
	InvalidationScanState *scan_state = (InvalidationScanState *) data;

	MemoryContext old_ctx = MemoryContextSwitchTo(scan_state->mctx);
	Form_continuous_aggs_materialization_invalidation_log invalidation_form =
		((Form_continuous_aggs_materialization_invalidation_log) GETSTRUCT(ti->tuple));
	Invalidation *invalidation = palloc(sizeof(*invalidation));

	invalidation->lowest_modified_value = invalidation_form->lowest_modified_value;
	invalidation->greatest_modified_value = invalidation_form->greatest_modified_value;

	Assert(invalidation->lowest_modified_value <= invalidation->greatest_modified_value);
	/* this will pick up invalidations where the mat threshold lies inside the
	 * range. so if we had [1Jan, 20Jan] as the invalidation range and our
	 * threshold is Jan8. This will pick it up
	 */
	if (invalidation->lowest_modified_value < scan_state->materialization_invalidation_threshold)
	{
		*scan_state->invalidations = lappend(*scan_state->invalidations, invalidation);
		ts_catalog_delete(ti->scanrel, ti->tuple);
	}

	MemoryContextSwitchTo(old_ctx);

	return SCAN_CONTINUE;
}